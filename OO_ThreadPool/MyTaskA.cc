#include "MyTaskA.hh"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

MyTaskA::MyTaskA() {}
MyTaskA::~MyTaskA() {}

void MyTaskA::process() {
    srand(clock());
    int x = rand() % 100;

    // 模拟任务执行耗时
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    cout << "MyTask A: task-> " << x << endl;
}
