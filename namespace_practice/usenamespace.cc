#include <iostream>
using std::cout;
using std::endl;

namespace MySpace
{
extern int add(int x, int y);
extern double add(double x, int y);
extern double add(int x, double y);
extern int add(int x, int y, int z);
extern double add(double x, double y = 100.0);
}

int main(int argc, char* argv[]) {
    int x = 10;
    int y = 20;
    int z = 30;
    int dx = 1.0;
    int dy = 2.0;
    int ret = MySpace::add(x, y);
    cout << ret << endl;

    double dret = MySpace::add(dx, y);
    cout << dret << endl;

    dret = MySpace::add(x, dy);
    cout << dret << endl;

    ret = MySpace::add(x, y, z);
    cout << ret << endl;

    dret = MySpace::add(dx);
    cout << dret << endl;
    
    return 0;
}

