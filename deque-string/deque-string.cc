#include <iostream>
#include <deque>
#include <string>

using namespace std;

void test() {
    cout << "please input 5 words" << endl;
    string str;
    deque<string> dS;
    for (int i = 0; i < 5; ++i) {
        cin >> str;
        dS.push_back(str);
    }

    for (const auto& e : dS) {
        cout << e << endl;
    }
}

int main(int argc, char* argv[]) {
    test();

    return 0;
}

