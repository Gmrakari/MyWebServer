

/*
 * Date:2021-09-26 16:54
 * filename:main.cpp
 *
 */

#include "threadpool.cpp"

void taskFunc(void* arg) {
	int num = *(int*)arg;
	printf("thread %ld is working, num = %d\n", pthread_self(), num);
	sleep(1);
}

int main() {
	//创建线程池
	ThreadPool* pool = threadPoolCreate(3, 10, 100);
	for (int i = 0; i < 100; i++) {
		int* num = (int*)malloc(sizeof(int));
		*num = i + 100;
		threadPoolAdd(pool, taskFunc, num);
	}
	sleep(30);

	threadPoolDestroy(pool);
	return 0;
}
