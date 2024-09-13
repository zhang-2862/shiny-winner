#include "Producer.hh"
#include "TaskQueue.hh"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

Producer::Producer() {};
Producer::~Producer() {};

void Producer::produce(TaskQueue& taskQue) {
    srand(clock());

    int cnt = 20;
    while (cnt--) {
        int task_id = rand() % 100;
        cout << "Producer: "<< std::this_thread::get_id() 
            << " ----- " <<  task_id << endl;
        taskQue.push(task_id);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
