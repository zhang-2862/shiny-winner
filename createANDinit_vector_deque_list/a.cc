#include <iostream>
#include <vector>
#include <deque>
#include <list>
using std::cout;
using std::endl;
using std::list;
using std::deque;
using std::vector;

void display(vector<int> v) {
    for (const auto& e : v) {
        cout << e << " ";
    }
    cout << endl;
}

void test01() {
    vector<int> v;
    vector<int> v1(10);
    vector<int> v2(10,6);
    vector<int> v3(v1);
    vector<int> v4(v2.begin(), v2.end());
    vector<int> v5{1, 2, 3, 4, 5, 6,};
    // deque list 同上
    display(v);
    display(v1);
    display(v2);
    display(v3);
    display(v4);
    display(v5);
}

int main(int argc, char* argv[]) {
    test01();
    return 0;
}

