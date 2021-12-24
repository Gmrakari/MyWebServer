

/*
 * filename:threadpool.cpp
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> //pthread_mutex_t pthread_create pthread_cond_t 
#include <string.h> //memset
#include <unistd.h> //sleep
#include <signal.h>	//pthread_kill
#include <errno.h>  //ESRCH

#include "threadpool.h"

#define DEFAULT_TIME 10
#define MIN_WAIT_TASK_NUM 10
#define DEFAULT_THREAD_VARY 10
#define true 1
#define false 0

//子线程任务结构体
typedef struct Task {
	void *(function)(void* arg);			//函数指针，回调函数
	void *arg;												//上面函数的参数
}threadpool_task_t;

struct threadpool_t {
	pthread_mutex_t lock;						//锁住本结构体
	pthread_mutex_t thread_counter;   //记录忙状态线程个数的锁 --busy_thr_num
	pthread_cond_t queue_not_full;  //当任务队列满时，添加任务的线程阻塞，等待此条件变量
	pthread_cond_t queue_not_empty; //任务队列里不为空时，通知等待任务的线程

	pthread_t *threads;							//存放线程池中每个线程的tid 数组表示
	pthread_t adjust_tid;						//存放管理者线程tid

	threadpool_task_t* task_queue;	//任务队列

	int min_thr_num;								//最小线程数
	int max_thr_num;								//最大线程数
	int live_thr_num;								//存活线程数
	int busy_thr_num;								//忙状态的线程数
	int wait_exit_thr_num;					//要销毁的线程个数

	int queue_front;								//队头下标
	int queue_rear;									//队尾下标
	int queue_size;									//队中实际任务数
	int queue_max_size;							//可容纳任务数上限

	int shutdown;										//标志位 线程池使用状态 true or false
};

typedef struct threadpool_t threadpool_t;

/**
 * @function void* threadpool_thread(void* threadpool)
 * @desc the worker thread
 * @parm threadpool the pool which own the thread
 */
static void* threadpool_thread(void* threadpool) {
	threadpool_t *pool = (threadpool_t *)threadpool;
	threadpool_task_t task;

	while (true) {
		/* Lock must be taken to wait on conditional varable */
		/*刚创建出线程，等待任务队列里有任务，否则阻塞等待任务队列里有任务后再唤醒接收任务 */
		pthread_mutex_lock(&(pool->lock));

		/* queue_size == 0 说明没有任务 调wait阻塞在条件变量上，若有任务，跳过该while */
		/* pool->shutdown = false -> !false = true 说明不关闭线程池 */
		while ((pool->queue_size == 0) && (!pool->shutdown)) {
			printf("thread 0x:%x is waitting\n", (unsigned int)pthread_self());
			pthread_cond_wait(&(pool->queue_not_empty), &(pool->lock));

			/* 清除指定数目的空闲线程，如果要结束的线程个数大于0,结束线程 */
			if (pool->wait_exit_thr_num > 0) {
				pool->wait_exit_thr_num--;

				/* 如果线程池里线程个数大于最小值时可以结束当前线程 */
				if (pool->live_thr_num > pool->min_thr_num) {
					printf("thread 0x%x is exiting\n", (unsigned int)pthread_self());
					pool->live_thr_num--;
					pthread_mutex_unlock(&(pool->lock));
					pthread_exit(NULL);
				} 
			}
		}

		/* 如果指定了true，要关闭线程池里的每个进程，自行退出处理 */
		if (pool->shutdown) {
			pthread_mutex_unlock(&(pool->lock));
			printf("thread 0x:%x is exiting\n", (unsigned int)pthread_self());
			pthread_exit(NULL);	//自行结束
		}

		/* 从任务队列里面获取任务，是一个出队的操作 */
		task.function = pool->task_queue[pool->queue_front].function;
		task.arg = pool->task_queue[pool->queue_front].arg;

		pool->queue_front = (pool->queue_front + 1) % pool->queue_max_size;		//出队，模拟环形队列

		pool->queue_size--;

		/* 通知可以有新的任务添加进来 */
		pthread_cond_broadcast(&(pool->queue_not_full));

		/* 任务取出后，立即将 线程池锁 释放 */
		pthread_mutex_unlock(&(pool->lock));

		/* 执行任务 */
		printf("thread 0x%x start working\n", (unsigned int)pthread_self());
		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num++;
		pthread_mutex_unlock(&(pool->thread_counter));
		
		//task.function(task.arg);
		*(*(task.function))(task.arg);//执行回调函数任务

		/* 任务结束处理 */
		printf("thread 0x%x end working\n", (unsigned int)pthread_self());
		pthread_mutex_lock(&(pool->thread_counter));
		pool->busy_thr_num--;
		pthread_mutex_unlock(&(pool->thread_counter));
	}
	pthread_exit(NULL);
}

/* 管理者线程 */
void* adjust_thread(void* threadpool) {
	int is_thread_alive(pthread_t tid);
	int i;
  threadpool_t *pool = (threadpool_t *)threadpool;
	while (!pool->shutdown) {

		sleep(DEFAULT_TIME);										//定时 对线程池管理

		pthread_mutex_lock(&(pool->lock));
		int queue_size = pool->queue_size;			// 关注 任务数量
		int live_thr_num = pool->live_thr_num;	//存活 线程数量
		pthread_mutex_unlock(&(pool->lock));

		pthread_mutex_lock(&(pool->thread_counter));
		int busy_thr_num = pool->busy_thr_num;			//忙着的线程数
		pthread_mutex_unlock(&(pool->thread_counter));

		/* 创建新线程 算法 : 任务数量大于最小线程池个数，且存货的线程数小于最大线程个数时
		 * 比如 30 >= 10 && 40 < 100 */
		if (queue_size >= MIN_WAIT_TASK_NUM && live_thr_num < pool->max_thr_num) {
			pthread_mutex_lock(&(pool->lock));
			int add = 0;

			/* 一次增加 DEFAULT_THREAD 个线程 */
			for (i = 0; i < pool->max_thr_num && add < DEFAULT_THREAD_VARY
					&& pool->live_thr_num < pool->max_thr_num; i++) {
				if (pool->threads[i] == 0 || !is_thread_alive(pool->threads[i])) {
					pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void *)pool);
					add++;
					pool->live_thr_num++;
				}
			}
			pthread_mutex_unlock(&(pool->lock));
		}
		/* 销毁多余的空闲线程 算法:忙线程*2 小于 存活的线程数 且 存活的线程数 大于 最小线程数时 */
		if ((busy_thr_num * 2) < live_thr_num && live_thr_num > pool->min_thr_num) {
			pthread_mutex_lock(&(pool->lock));
			pool->wait_exit_thr_num = DEFAULT_THREAD_VARY; /* 要销毁的线程数 设置为10 */
			pthread_mutex_unlock(&(pool->lock));

			/* 一次减少 DEFAULT_THREAD 个线程 */
			for (i = 0;i < DEFAULT_THREAD_VARY; i++) {
				/* 通知处在空闲状态的线程， 他们会自行终止 */
				pthread_cond_signal(&(pool->queue_not_empty));
			}
		}
	}
	return NULL;
}

/**
 * check a thread is alive
 */
int is_thread_alive(pthread_t tid);
int threadpool_free(threadpool_t* pool) {
	if (pool == NULL)
		return -1;

	if (pool->task_queue)
		free(pool->task_queue);
	if (pool->threads) {
		free(pool->threads);
		pthread_mutex_lock(&(pool->lock));
		pthread_mutex_destroy(&(pool->lock));
		pthread_mutex_lock(&(pool->thread_counter));
		pthread_mutex_destroy(&(pool->thread_counter));
		pthread_cond_destroy(&(pool->queue_not_empty));
		pthread_cond_destroy(&(pool->queue_not_full));
	}
	free(pool);
	pool = NULL;

	return 0;
}

threadpool_t* threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size) {
	threadpool_t* pool = NULL;
	int i;
	do {
		if ((pool = (threadpool_t *)malloc(sizeof(threadpool_t))) == NULL) {
			printf("malloc threadpool fail\n");
			break;
		}

		pool->min_thr_num = min_thr_num;
		pool->max_thr_num = max_thr_num;
		pool->live_thr_num = min_thr_num;  //活着的线程数 初值
		pool->busy_thr_num = 0;						//0个产品
		pool->wait_exit_thr_num = 0;

		pool->queue_front = 0;
		pool->queue_rear = 0;
		pool->queue_size = 0;
		pool->queue_max_size = queue_max_size;

		pool->shutdown = false; //不关闭线程池

		//根据最大线程上限数，给工作线程数数组开辟空间并清零
		pool->threads = (pthread_t*)malloc(sizeof(pthread_t) * max_thr_num);
		if (pool->threads == NULL) {
			printf("malloc threads fail\n");
			break;
		}
		memset(pool->threads, 0, sizeof(pthread_t) * max_thr_num);

		//队列开辟空间
		pool->task_queue = (threadpool_task_t*)malloc(sizeof(threadpool_task_t) * queue_max_size);
		if (pool->task_queue == NULL) {
			printf("malloc task_queue fail\n");
			break;
		}

		//初始化互斥锁和条件变量
		if (pthread_mutex_init(&(pool->lock), NULL) != 0
				|| pthread_mutex_init(&(pool->thread_counter), NULL) != 0
				|| pthread_cond_init(&(pool->queue_not_full), NULL) != 0
				|| pthread_cond_init(&(pool->queue_not_empty), NULL) != 0) {
			printf("init the lock or cond fail\n");
			break;
		}

		/* 启动min_thr_num个work thread */
		for (i = 0;i < min_thr_num; i++) {
			pthread_create(&(pool->threads[i]), NULL, threadpool_thread, (void*)pool); //pool指向当前线程池
			printf("start thread 0x%x...\n",(unsigned int)pool->threads[i]);
		}

		pthread_create(&(pool->adjust_tid), NULL, adjust_thread, (void*)pool);

		return pool;

	}while(false);

	threadpool_free(pool);
	return NULL;
}

/**
	* int threadpool_add(threadpool_t *pool, void *(*function)(void *), void *arg)
	* add a new task in the queue of a thread pool
	* Type: int (threadpool_t *, void *(*)(void *), void *)
  * Name: threadpool_add
		---
	* @function threadpool_add
  * @desc add a new task in the queue of a thread pool
  * @param pool     Thread pool to which add the task.
  * @param function Pointer to the function that will perform the task.
  * @param argument Argument to be passed to the function.
  * @return 0 if all goes well,else -1
 **
 */
int	threadpool_add(threadpool_t* pool, void* (*function)(void* arg), void* arg) {
	pthread_mutex_lock(&(pool->lock));

	//==为真 任务队列满了 调用wait阻塞 并且pool->shutdown不关闭
	while ((pool->queue_size == pool->queue_max_size) && (!pool->shutdown)) {
		pthread_cond_wait(&(pool->queue_not_full), &(pool->lock));
	}
	if (pool->shutdown) {
		pthread_mutex_unlock(&(pool->lock));
	}

	/* 清空工作线程 调用的回调函数的参数arg */
	if (pool->task_queue[pool->queue_rear].arg != NULL) {
		free(pool->task_queue[pool->queue_rear].arg);
		pool->task_queue[pool->queue_rear].arg = NULL;
	}

	/* 添加任务到任务队列 */
	pool->task_queue[pool->queue_rear].function = function;
	pool->task_queue[pool->queue_rear].arg = arg;
	pool->queue_rear = (pool->queue_rear + 1) % pool->queue_max_size; //队尾指针移动，模拟循环队列
	pool->queue_size++;

	/* 添加完任务，队列不为空，唤醒线程池中 等待处理任务线程 */
	pthread_cond_signal(&(pool->queue_not_empty));
	pthread_mutex_unlock(&(pool->lock));

	return 0;
}

int threadpool_destroy(threadpool_t* pool) {
	int i;
	if (pool == NULL) 
		return -1;

	pool->shutdown = true;

	/* 销毁管理线程 */
	pthread_join(pool->adjust_tid, NULL);

	for (i = 0; i < pool->live_thr_num; i++) {
		/* 通知所有的空闲线程 */
		pthread_cond_broadcast(&(pool->queue_not_empty));
	}
	for (i = 0;i < pool->live_thr_num; i++) {
		pthread_join(pool->threads[i], NULL);
	}
	threadpool_free(pool);

	return 0;
}

int threadpool_all_threadnum(threadpool_t* pool) {
	int all_threadnum = -1;
	pthread_mutex_lock(&(pool->lock));
	all_threadnum = pool->live_thr_num;
	pthread_mutex_unlock(&(pool->lock));
	return all_threadnum;
}

int threadpool_busy_threadnum(threadpool_t* pool) {
	int busy_threadnum = -1;
	pthread_mutex_lock(&(pool->lock));
	busy_threadnum = pool->busy_thr_num;
	pthread_mutex_unlock(&(pool->lock));
	return busy_threadnum;
}

int is_thread_alive(pthread_t tid) {
	int kill_rc = pthread_kill(tid, 0); //信号
	if (kill_rc == ESRCH) {
		return false;
	}
	return true;
}



