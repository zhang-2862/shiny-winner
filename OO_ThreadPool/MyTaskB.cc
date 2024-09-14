#include "MyTaskB.hh"

#include <iostream>
#include <thread>

using std::cout;
using std::endl;

MyTaskB::MyTaskB() {}
MyTaskB::~MyTaskB() {}

void MyTaskB::process() {
    srand(clock());
    int x = rand() % 100 + 900;
    std::string s = "(b)~~~~ ";
    s += std::to_string(x);

    // 模拟任务执行耗时
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    cout << "MyTask B: task-> " << s << endl;
}
