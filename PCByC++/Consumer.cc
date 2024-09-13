#include "Consumer.hh"
#include "TaskQueue.hh"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

Consumer::Consumer() {};

Consumer::~Consumer() {};

void Consumer::consum(TaskQueue& taskQue) {
    int cnt = 20;
    while (cnt--) {
        int task_id = taskQue.pop();
        cout << "Consumer: "<< std::this_thread::get_id() 
            << " ----- " << task_id << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

