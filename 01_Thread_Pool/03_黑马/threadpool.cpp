

/*
 * Date:2021-12-13 21:17
 * filename:threadpool.cpp
 *
 */

#include <stdlib.h>
#include <pthread.h>

struct Task {
	void *(function)(void* arg);
	void *arg;
};

typedef struct Task threadpool_task_t;

struct threadpool_t {
	pthread_mutex_t lock;						//锁住本结构体
	pthread_mutex_t thread_count;   //记录忙状态线程个数的锁 --busy_thr_num
	pthread_cond_t queue_not_full;  //当任务队列满时，添加任务的线程阻塞，等待此条件变量
	pthread_cond_t queue_not_empty; //任务队列里不为空时，通知等待任务的线程

	pthread_t *threads;							//存放线程池中每个线程的tid 数组表示
	pthread_t adjust_tid;						//存放管理者线程tid

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

threadpool_t* threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size) {
	return NULL;
}

int	threadpool_add(threadpool_t* pool, void* (*function)(void* arg), void* arg) {
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
