#ifndef __TASKQUEUE_H__
#define __TASkQUEUE_H__

#include "Task.hh"

#include <condition_variable>
#include <queue>
#include <mutex>

using std::queue;
using std::mutex;
using std::condition_variable;

class Task;


class TaskQueue {
    using ElemType = Task*;
public:
    TaskQueue(size_t capacity);
    ~TaskQueue();

    void push(ElemType value);
    ElemType pop();
    bool full();
    bool empty();
    void wakeup();

private:
    size_t capacity_;
    queue<ElemType> que_;
    mutex mutex_;
    condition_variable notFull_;
    condition_variable notEmpty_;
    bool flag_; //用来辅助线程池退出
};

#endif

