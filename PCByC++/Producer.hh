#ifndef __PRODUCER_H__
#define __PRODUCER_H__

class TaskQueue;

class Producer {
public:
    Producer();
    ~Producer();
    
    void produce(TaskQueue& TaskQue);

private:

};

#endif

