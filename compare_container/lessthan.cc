#include <iostream>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::list;
using std::vector;

void test01() {
    list<int> l1{10, 3, 5, 7, 9};
    list<int> l2{2, 4, 6, 8, 10,20};
    if (l1 < l2) {
        cout << "l1 < l2" << endl;
    }
}

void test02() {
    list<int> l1{1, 3, 5, 7, 9, 11};
    list<int> l2{2, 4, 6, 8, 10};
    if (l1 < l2) {
        cout << "l1 < l2" << endl;
    }
}

int main(int argc, char* argv[]) {
    test01();
    test02();
    return 0;
}

