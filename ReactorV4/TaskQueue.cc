#include "TaskQueue.hh"

using std::unique_lock;

TaskQueue::TaskQueue(size_t capacity)
    : capacity_(capacity),
      que_(),
      mutex_(),
      notFull_(),
      notEmpty_(),
      flag_(true)
{}

TaskQueue::~TaskQueue() {}

void TaskQueue::push(ElemType value) {
    unique_lock<mutex> mtx(mutex_);
    // 若队列满，则阻塞
    while (full()) {
        notFull_.wait(mtx);
    }
    que_.push(value);
    mtx.unlock();
    // 此时队列不空, 通知任务线程
    notEmpty_.notify_one();
}

ElemType TaskQueue::pop() {
    unique_lock<mutex> mtx(mutex_);

    while (empty() && flag_) {
        notEmpty_.wait(mtx);
    }
    if (flag_) {
        ElemType tmp = que_.front();
        que_.pop();
        // 操作完后解锁
        mtx.unlock();
        // 队列不满，通知主线程
        notFull_.notify_one();
        return tmp;
    } else {
        return nullptr;
    }
}

bool TaskQueue::full() {
    return que_.size() == capacity_;
}

bool TaskQueue::empty() {
    return que_.empty();
}

void TaskQueue::wakeup() {
    notEmpty_.notify_all();
}


