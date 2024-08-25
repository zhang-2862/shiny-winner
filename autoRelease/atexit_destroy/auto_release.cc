#include <iostream>
#include <ostream>
using std::cout;
using std::endl;

class Singleton {
    friend std::ostream& operator<<(std::ostream&, const Singleton&);

public:
    static Singleton* getInstance(int x, int y) {
        if (_pInstance == nullptr) {
            atexit(destroy);
            _pInstance = new Singleton(x,y);
        }
        return _pInstance;
    }

private:
    static void destroy() {
        if (_pInstance) {
            delete _pInstance;
            _pInstance = nullptr;
        }
    }
    ~Singleton(){};
    Singleton() = default;
    Singleton(int x, int y)
        : _x(x),
         _y(y)
    {};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) =delete;
private:
    static Singleton* _pInstance;
    int _x;
    int _y;
};
Singleton* Singleton::_pInstance= nullptr;

std::ostream& operator<<(std::ostream& os, const Singleton& rhs) {
    os << rhs._x << " " << rhs._y;
    return os;
}

int main(int argc, char* argv[]) {
    Singleton::getInstance(2,3);
    cout << *Singleton::getInstance(2,3) << endl;

    return 0;
}

