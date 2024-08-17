#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Point {
public:
    Point();
    Point(int x, int y);
    void print() const;

private:
    int _x;
    int _y;
};

Point::Point()
:_x(0),
    _y(0)
{}

Point::Point(int x, int y)
:_x(x),
    _y(y)
{}

void Point::print() const {
    cout<< "(" << _x <<  "," << _y <<")" << endl;
}

int main(int argc, char* argv[]) {
    Point p1(1,1);
    Point p2(1,2);
    Point p3(1,3);
    Point p4(1,4);
    Point p5(1,5);
    
    vector<Point> vec_Point{p1, p2, p3, p4, p5};

    for(auto& e: vec_Point) {
        e.print();
    }
    
    return 0;
}

