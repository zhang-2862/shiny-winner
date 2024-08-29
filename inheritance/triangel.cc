#include <cmath>
#include <iostream>
#include <string>
#include <ostream>
using std::cout;
using std::endl;
using std::string;

class Color {
public:
    Color(string color)
        : _color(color)
    {}

    string getColor() {
        return _color;
    }


private:
    string _color;
};


class Point {
    friend class Line;
    friend
    std::ostream& operator<<(std::ostream& os, const Point& rhs);
public:
    Point(float x, float y)
        : _x(x),
         _y(y)
    {}

private:
    float _x;
    float _y;
};

std::ostream& operator<<(std::ostream& os, const Point& rhs) {
    cout << rhs._x << "," << rhs._y;
    return os;
}


class Line {
public:
    Line(Point& p1, Point& p2)
        : _p1(p1),
         _p2(p2)
    {}

    float getDistance() {
        float dx = powf(_p1._x - _p2._x, 2);
        float dy = powf(_p1._y - _p2._y, 2);
        return sqrtf(dx + dy);
    }
    
private:
    Point _p1;
    Point _p2;
};

class Triangle : public Line, public Color {
public:
    Triangle (Point p1, Point p2, string color, float height) 
        : Line(p1, p2),
         Color(color),
         _height(height)
    {}

    float getArea() {
        return getDistance() * _height / 2;
    }

    void getTriangle() {
        cout << "颜色：" << getColor() << endl
             << "面积：" << getArea() << endl; 
    }
        
private:
    float _height;
};

int main(int argc, char* argv[]) {
    Triangle triangle({0,3}, {4,0} , "black", 10.0);
    triangle.getTriangle();

    return 0;
}

