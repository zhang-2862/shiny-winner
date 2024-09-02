#include <iostream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::vector;

void test() {
    vector<char> vc = {'H', 'E', 'L', 'L', 'O'};
    string str(vc.begin(), vc.end());
    cout << str << endl;
}

int main(int argc, char* argv[]) {
    test();

    return 0;
}

