#include <iostream>
#include <limits>
using std::cout;
using std::cin;
using std::endl;

void inputInterger(int& num) {
    cout << "请输入一个int型数据" << endl;
    cin >> num;
    while (!cin.eof()) {
        if (cin.bad()) {
            cout << "cin has broken!" << endl;
            return;
        } else if (cin.fail()) {
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入一个int型数据" << endl;
            cin >>num;
        } else {
            cout << "num: " << num <<endl;
            break;
        }
    }
}

int main(int argc, char* argv[]) {
    int num = 0;
    inputInterger(num);
    
    return 0;
}

