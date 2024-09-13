#include "Producer.hh"
#include "Consumer.hh"
#include "TaskQueue.hh"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;
using std::thread;

void test() {
    TaskQueue taskQue(10);
    Producer pr;
    Consumer co;
    thread t_pr(&Producer::produce, pr, std::ref(taskQue));
    thread t_co(&Consumer::consum, co, std::ref(taskQue));

    t_pr.join();
    t_co.join();
}

int main(int argc, char* argv[]) {
    test();

    return 0;
}

