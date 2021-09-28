

/*
 * Date:2021-09-28 08:30
 * filename:threadpool.h
 *
 */

#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <pthread.h>
#include <iostream>
#include <queue>
using namespace std;
using callback = void(*)(void*);

struct Task {
	Task() {
		function = nullptr;
		arg = nullptr;
	}

	Task(callback f, void* arg) {
		function = f;
		this->arg = arg;
	}
	callback function;
	void* arg;
};

//任务队列
class TaskQueue {
public:
	TaskQueue();
	~TaskQueue();

	//添加任务
	void addTask(Task& task);
	void addTask(callback func, void* arg);

	//取出一个任务
	Task takeTask();

	//获取当前队列中任务个数
	inline int taskNumber() {
		return m_queue.size();
	}

private:
	pthread_mutex_t m_mutex;		//互斥锁
	std::queue<Task> m_queue;	//任务队列
};

TaskQueue::TaskQueue() {
	pthread_mutex_init(&m_mutex, NULL);
}

TaskQueue::~TaskQueue() {
	pthread_mutex_destroy(&m_mutex);
}

void TaskQueue::addTask(Task& task) {
	pthread_mutex_lock(&m_mutex);
	m_queue.push(task);
	pthread_mutex_unlock(&m_mutex);
}

Task TaskQueue::takeTask() {
	Task t;
	pthread_mutex_lock(&m_mutex);
	if (m_queue.size() > 0) {
		t = m_queue.front();
		m_queue.pop();
	}
	pthread_mutex_unlock(&m_mutex);
	return t;
}

class ThreadPool {
public:
	ThreadPool(int min, int max);
	~ThreadPool();

	//添加任务
	void addTask(Task task);
	//获取忙线程的个数
	int getBushNumer();
	//获取活着的线程个数
	int getAliveNumber();

private:
	//工作的线程的任务函数
	static void* worker(void* arg);
	//管理者线程的任务函数
	static void* manager(void* arg);
	void threadExit();

private:
	pthread_mutex_t m_lock;
	pthread_cond_t m_notEmpty;
	pthread_t* m_threadIDs;
	pthread_t m_managerID;
	TaskQueue* m_taskQ;
	int m_minNum;
	int m_maxNum;
	int m_busyNum;
	int m_aliveNum;
	int m_exitNum;
	bool m_shutdom = false;
};

#endif
