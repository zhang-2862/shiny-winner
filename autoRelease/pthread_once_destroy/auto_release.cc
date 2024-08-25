#include <iostream>
#include <ostream>
#include <pthread.h>
using std::cout;
using std::endl;

class Singleton {
    friend std::ostream& operator<<(std::ostream&, const Singleton&);

public:
    static Singleton* getInstance(int x, int y) {
            pthread_once(&_once_control, init_r);
            return _pInstance;
        }

    void init(int x, int y) {
        _x = x;
        _y = y;
    }

private:
    static void init_r() {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton(0,0);
        }
        atexit(destroy);
    }

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
    static pthread_once_t _once_control; 
    int _x;
    int _y;
};
Singleton* Singleton::_pInstance= nullptr;
pthread_once_t Singleton::_once_control = PTHREAD_ONCE_INIT;

std::ostream& operator<<(std::ostream& os, const Singleton& rhs) {
    os << rhs._x << " " << rhs._y;
    return os;
}

int main(int argc, char* argv[]) {
    Singleton::getInstance(2,3);
    cout << *Singleton::getInstance(2,3) << endl;

    return 0;
}

