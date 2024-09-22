#include "ThreadPool.hh"

#include <iostream>

using std::cout;
using std::endl;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
    : threadNum_(threadNum),
      threads_(),
      queSize_(queSize),
      taskQue_(queSize_),
      isExit_(false)
{}

ThreadPool::~ThreadPool() {}

void ThreadPool::start() {
    for (size_t i = 0; i < threadNum_; ++i) {
        threads_.emplace_back([this](){
                         this->doTask();
                         });
    }
}

void ThreadPool::stop() {
    // 队列不为空，先等任务执行完
    while (!taskQue_.empty()) {
        ;
    }
    // 将退出标志位设置成true
    isExit_ = true;

    taskQue_.wakeup();// 唤醒所有被阻塞的线程,以进行回收

    for (auto& thread : threads_) {
        // 主线程等待子线程结束
        thread.join();
    }
}

void ThreadPool::addTask(Task&& taskcb) {
    if (taskcb) {
        taskQue_.push(std::move(taskcb));
    }
}

void ThreadPool::addTask(const Task& taskcb) {
    if (taskcb) {
        taskQue_.push(taskcb);
    }
}

Task ThreadPool:: getTask() {
    return taskQue_.pop();
}

void ThreadPool::doTask() {
    while (!isExit_) {
        Task taskcb = getTask();
        if (taskcb) {
            // OO面向对象时：ptask->process();
            // OB基于对象写法：
            taskcb();
        } else {
            cout << "ptask == nullptr" << endl;
        }
    }
}

