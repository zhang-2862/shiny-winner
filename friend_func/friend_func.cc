#include <cmath>
#include <iostream>
using std::cout;
using std::endl;

class Line;
class Point;

class Point {
    friend class Line;
    /* friend double Line::distance(); */
public:
    Point(int x = 0, int y = 0)
        :_x(x),
        _y(y)
    {}
private:
    int _x;
    int _y;
};

class Line {
public:
    Line(const Point& p1, const Point& p2)
        :_p1(p1),
        _p2(p2)
    {}

    double distance() {
        return sqrt(pow(_p1._x - _p2._x, 2) + pow(_p1._y - _p2._y, 2));
    }
private:
    Point _p1;
    Point _p2;
};

int main(int argc, char* argv[]) {
    Line line({0,0},{3,4});
    cout << line.distance() << endl;

    return 0;
}

