#include <cmath>
#include <iostream>
#include <functional>
using std::cout;
using std::endl;
using std::bind;
using std::function;

class Figure {
public:
    using DisplayCallback = function<void()>;
    using AreaCallback = function<double()>;

    void setDisplayCallback(DisplayCallback &&cb) {
        dispalyCallback_ = std::move(cb);
    }

    void setArearCallback(AreaCallback &&cb) {
        areaCallback_ = std::move(cb);
    }

    void handleDisaplayCallback() const {
        if (dispalyCallback_) {
            dispalyCallback_();
        }
    }

    double handleAreaCallback() const {
        if (areaCallback_) {
            return areaCallback_();
        } else {
            return 0.0;
        }
    }

private:
    DisplayCallback dispalyCallback_;
    AreaCallback areaCallback_;
};

class Rectangle {
public:
    Rectangle(int width, int length)
        : width_(width),
          length_(length)
    {}

    void dispaly(int i) {
        cout << "Rectangle" << endl;
    }

    double dispalyArea() {
        return width_ * length_;
    }

private:
    int width_;
    int length_;
};

class Circle {
public:
    Circle(int radius)
        : radius_(radius)
    {}

    void show() {
        cout << "Circle" << endl;
    }

    double showArea() {
        return radius_ * radius_ * 3.14;
    }

private:
    int radius_;
};

class Triangle {
public:
    Triangle(int a, int b, int c)
        : a_(a),
          b_(b),
          c_(c)
    {}

    void print() {
        cout << "Triangle" << endl;
    }

    double printArea() {
        double p = (a_ + b_ + c_) / 2.0;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    int a_;
    int b_;
    int c_;
};

void func(const Figure& fig) {
    fig.handleDisaplayCallback();
    cout << fig.handleAreaCallback() << endl;
}

int main(int argc, char* argv[]) {
    Rectangle rectangle(5, 10);
    Circle circle(5);
    Triangle triangle(3, 4, 5);

    Figure fig;

    fig.setDisplayCallback(bind(&Rectangle::dispaly, &rectangle, 1));
    fig.setArearCallback(bind(&Rectangle::dispalyArea, &rectangle));
    func(fig);

    fig.setDisplayCallback(bind(&Circle::show, &circle));
    fig.setArearCallback(bind(&Circle::showArea, &circle));
    func(fig);

    fig.setDisplayCallback(bind(&Triangle::print, &triangle));
    fig.setArearCallback(bind(&Triangle::printArea, &triangle));
    func(fig);


    return 0;
}

