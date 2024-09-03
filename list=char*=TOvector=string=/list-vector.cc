#include <iostream>
#include <string>
#include <vector>
#include <list>

using namespace std;

void test01() {
    list<const char*> lst = {"hello", "world", "!"};
    vector<string> vS{lst.begin(), lst.end()};
    for (const auto& e : vS) {
        cout << e << endl;
    }
}

int main(int argc, char* argv[]) {
    test01();

    return 0;
}

