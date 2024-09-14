#include "ThreadPool.hh"
#include "MyTaskA.hh"
#include "MyTaskB.hh"

#include <iostream>

using std::cout;
using std::endl;

void test() {
    ThreadPool threadpool(8, 10);
    std::unique_ptr<Task> task_A(new MyTaskA);
    std::unique_ptr<Task> task_B(new MyTaskB);

    threadpool.start(); // 启动线程池
    cout << "start..." << endl;
    
    for (int i = 0; i < 50; ++i) {
        threadpool.addTask(task_A.get());
        threadpool.addTask(task_B.get());
    }

    threadpool.stop();

    cout << "end..." << endl;
}

int main(int argc, char* argv[]) {
    test();

    return 0;
}

