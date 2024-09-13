#ifndef __TASKQUEUE_H__
#define __TASkQUEUE_H__

#include <condition_variable>
#include <queue>
#include <mutex>

using std::queue;
using std::mutex;
using std::condition_variable;

class TaskQueue {
public:
    TaskQueue(size_t capacity);
    ~TaskQueue();

    void push(int& value);
    int pop();
    bool full();
    bool empty();

private:
    size_t capacity_;
    queue<int> que_;
    mutex mutex_;
    condition_variable notFull_;
    condition_variable notEmpty_;
};

#endif

