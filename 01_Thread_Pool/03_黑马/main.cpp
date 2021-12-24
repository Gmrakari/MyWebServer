

/*
 * Date:2021-12-24 07:08
 * filename:main.c
 *
 */


#include "threadpool.h"
#include <stdio.h>
#include <pthread.h> //pthread_self
#include <unistd.h>	//sleep
#if 1
/* 线程池中的线程，模拟处理函数 */
void* process(void* arg) {
	printf("thread 0x:%x working on task %d\n", (unsigned int)pthread_self(), *(int *)arg);
	sleep(1);
	printf("task %d is end\n", *(int *)arg);

	return NULL;
}

int main(void) {
	//threadpool_t* threadpool_create(int min_thr_num, int max_thr_num, int queue_max_size);
	
	threadpool_t *thp = threadpool_create(3, 100, 100);
	printf("pool inited");

	//int *num = (int *)malloc(sizeof(int)*20);
	int num[20], i;
	for (i = 0;i < 20; i++) {
		num[i] = i;
		printf("add task %d\n", i);
		threadpool_add(thp, process, (void*)&num[i]);
	}
	sleep(10);
	threadpool_destroy(thp);

	return 0;
}

#endif
