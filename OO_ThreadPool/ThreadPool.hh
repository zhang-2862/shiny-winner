#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "TaskQueue.hh"

#include <thread>
#include <vector>

using std::thread;
using std::vector;

class Task; //任务类 前向声明

class ThreadPool {
public:
    ThreadPool(size_t threadNum, size_t queSize);
    ~ThreadPool();

    void start();
    void stop();
    void addTask(Task* ptask);

private:
    Task* getTask();
    void doTask();

private:
    size_t threadNum_;// 子线程数量
    vector<thread> threads_;// 装工作线程的容器
    size_t queSize_;// 任务队列大小
    TaskQueue taskQue_;// 任务队列
    bool isExit_; // 进程退出标志
};

#endif

