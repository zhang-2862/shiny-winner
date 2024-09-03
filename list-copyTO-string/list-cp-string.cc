#include <iostream>
#include <list>
#include <deque>

using namespace std;

void test() {
    deque<int> even_id;
    deque<int> odd_id;
    list<int> i_list{1, 2, 3, 4, 5, 6, 77, 88, 99 ,100};
    for (const auto& e : i_list) {
        if (e & 0x1) {
            odd_id.push_back(e);
        } else {
            even_id.push_back(e);
        }
    }

    cout << "even_id: ";
    for (const auto& e :even_id) {
        cout << e << " ";
    }
    cout << endl;

    cout << "odd_id: ";
    for (const auto& e :odd_id) {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    test();

    return 0;
}

