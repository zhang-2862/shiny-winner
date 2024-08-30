#include <iostream>
using std::cout;
using std::endl;

void test01() {
    int&& rref = 10;

    &rref; // 可以取地址
}

int gnum = 10;
int&& func() {
    return std::move(gnum);
}

void test02() {
    /* &func(); // 无法取地址 */
}

int main(int argc, char* argv[]) {


    return 0;
}

