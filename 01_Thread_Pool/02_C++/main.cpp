

/*
 * Date:2021-09-28 10:23
 * filename:main.cpp
 *
 */

#include "threadpool.cpp"

void taskFunc(void* arg) {
	int num = *(int*)arg;
	cout << "thread:" << pthread_self() <<
	" is working, num = " << num << endl;

	sleep(1);
}  

int main() {
	//创建线程池
	ThreadPool* pool = new ThreadPool(3, 10); 

	for (int i = 0; i < 100;i++) {
		int* num = new int;
		*num = i + 100;
		pool->addTask(Task(taskFunc, num));
	}

	sleep(30);
}
