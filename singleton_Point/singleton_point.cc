#include <iostream>
using std::cout;
using std::endl;

class Point {
public:
    static Point* getInstance() {
        if(_pInstance == nullptr) {
            _pInstance = new Point(0,0);
        }
        cout << "getInstance() is called." << endl;
        return _pInstance;
    }

    void init(int x, int y) {
        _x = x;
        _y = y;
    }

    static void destruct() {
        if(_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
        }
        cout << "destruct() is called." << endl;
    }
    
    void print() {
        cout << "(" << _x << "," << _y << ")" << endl;
    }

private:
    Point() = default;
    ~Point(){}

    Point(int x, int y)
    :_x(x),
    _y(y)
    {
        cout << "Point(int x, int y) is called." << endl;
    }

    Point(const Point&) = delete;
    Point& operator=(const Point&) = delete;

private:
    int _x;
    int _y;
    static Point* _pInstance;
};
Point* Point::_pInstance = nullptr;

int main(int argc, char* argv[]) {

    Point::getInstance()->print();
    Point::getInstance()->init(3, 4);
    Point::getInstance()->print();
    Point::destruct();
    Point::destruct();
    Point::destruct();
    
    return 0;
}

