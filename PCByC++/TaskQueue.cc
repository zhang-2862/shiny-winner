#include "TaskQueue.hh"

using std::unique_lock;

TaskQueue::TaskQueue(size_t capacity)
    : capacity_(capacity)
{}

TaskQueue::~TaskQueue() {}

void TaskQueue::push(int& value) {
    unique_lock<mutex> mtx(mutex_);
    // 若队列满，则阻塞
    while (full()) {
        notFull_.wait(mtx);
    }
    que_.push(value);
    mtx.unlock();
    // 此时队列不空, 通知消费者进程
    notEmpty_.notify_one();
}

int TaskQueue::pop() {
    unique_lock<mutex> mtx(mutex_);
    while (empty()) {
        notEmpty_.wait(mtx);
    }
    int tmp = que_.front();
    que_.pop();
    // 操作完后解锁
    mtx.unlock();
    // 队列不满，通知生产者进程
    notFull_.notify_one();
    
    return tmp;
}

bool TaskQueue::full() {
    return que_.size() == capacity_;
}

bool TaskQueue::empty() {
    return que_.empty();
}


