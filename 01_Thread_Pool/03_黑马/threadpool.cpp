

/*
 * Date:2021-12-13 21:17
 * filename:threadpool.cpp
 *
 */

#include <stdio.h> 
#include <stdlib.h>
#include <pthread.h> //pthread_mutex_t pthread_create pthread_cond_t 
#include <string.h> //memset

#include "threadpool.h"

#define DEFAULT_TIME 10
#define MIN_WAIT_TASK_NUM 10
#define DEFAULT_THREAD_VARY 10
#define true 1
#define false 0

struct Task {
	void *(function)(void* arg);			//函数指针，回调函数
	void *arg;												//上面函数的参数
};

typedef struct Task threadpool_task_t;		//子线程任务结构体

struct threadpool_t {
	pthread_mutex_t lock;						//锁住本结构体
	pthread_mutex_t thread_count;   //记录忙状态线程个数的锁 --busy_thr_num
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
void* threadpool_thread(void* threadpool);

void* adjust_thread(void* threadpool);

/**
 * check a thread is alive
 */
int is_thread_alive(pthread_t tid);
int threadpool_free(threadpool_t* pool);

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
				|| pthread_mutex_init(&(pool->thread_count), NULL) != 0
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

	//==为真 任务队列满了 调用wait阻塞
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
	return 0;
}

int threadpool_all_threadnum(threadpool_t* pool) {
	return 0;
}

int threadpool_busy_threadnum(threadpool_t* pool) {
	return 0;
}

#if 1
/* 线程池中的线程，模拟处理函数 */
void* process(void* arg) {

}


