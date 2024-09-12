#include <cmath>
#include <iostream>
#include <memory>

using std::cout;
using std::endl;

class Figure {
public:
    virtual void display() const = 0;
    virtual double area() const = 0;

    virtual ~Figure()
    {}
};

class Rectangle : public Figure{
public:
    Rectangle(int width, int length)
        : width_(width),
          length_(length)
    {}

    void display() const override {
        cout << "Rectangle";
    }

    double area() const override {
        return width_ * length_;
    }

    ~Rectangle() {
        cout << "~Rectangle()" << endl;
    }

private:
    int width_;
    int length_;
};

class Circle : public Figure{
public:
    Circle(int radius)
        : radius_(radius)
    {}

    void display() const override {
        cout << "Circle";
    }

    double area() const override {
        return radius_ * radius_ * 3.14;
    }

    ~Circle() {
        cout << "~Circle()" << endl;
    }

private:
    int radius_;
};

class Triangle : public Figure{
public:
    Triangle(int a, int b, int c)
        : a_(a),
          b_(b),
          c_(c)
    {}

    void display() const override {
        cout << "Triangle";
    }

    double area() const override{
        double p = (a_ + b_ + c_) / 2.0;
        return sqrt(p * (p - a_) * (p - b_) * (p - c_));
    }

private:
    int a_;
    int b_;
    int c_;
};


class Factory {
public:
    virtual Figure* create() = 0;
    virtual ~Factory()
    {}
};

class RectangleFactory : public Factory {
public:
    Figure* create() override {
        Rectangle * prec = new Rectangle(5, 10);
        return prec;
    }
};

class CircleFactory : public Factory {
public:
    Figure* create() override {
        Circle * pcir = new Circle(5);
        return pcir;
    }
};

class TriangleFactory : public Factory {
public:
    Figure* create() override {
        Triangle * ptri = new Triangle(3, 4, 5);
        return ptri;
    }
};

void func(Figure* pfig) {
    pfig->display();
    cout << "的面积为：" << pfig->area() << endl;
}

int main(int argc, char* argv[]) {
    std::unique_ptr<Factory> recFac(new RectangleFactory());
    std::unique_ptr<Figure> prec(recFac->create());

    std::unique_ptr<Factory> cirFac(new CircleFactory());
    std::unique_ptr<Figure> pcir(cirFac->create());

    std::unique_ptr<Factory> triFac(new RectangleFactory());
    std::unique_ptr<Figure> ptri(triFac->create());

    func(prec.get());
    func(pcir.get());
    func(ptri.get());

    return 0;
}

