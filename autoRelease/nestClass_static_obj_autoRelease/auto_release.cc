#include <iostream>
#include <ostream>
using std::cout;
using std::endl;

class Singleton {
    friend std::ostream& operator<<(std::ostream&, const Singleton&);
    class AutoReles {
        /* friend class Singleton; */
    public:
        AutoReles(){};
        ~AutoReles() {
            if (_pInstance) {
                delete _pInstance;
                _pInstance = nullptr;
            }
        }
    };

public:
    static Singleton* getInstance(int x, int y) {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton(x,y);
        }
        return _pInstance;
    }

    void print() const {
        cout << _x << endl;
        cout << _y << endl;
    }
    
private:
    ~Singleton(){};
    Singleton() = default;
    Singleton(int x, int y)
        : _x(x),
         _y(y)
    {};
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) =delete;
private:
    static AutoReles _ar;
    static Singleton* _pInstance;
    int _x;
    int _y;
};
Singleton* Singleton::_pInstance= nullptr;
Singleton::AutoReles Singleton::_ar;

std::ostream& operator<<(std::ostream& os, const Singleton& rhs) {
    os << rhs._x << " " << rhs._y;
    return os;
}

int main(int argc, char* argv[]) {
    Singleton::getInstance(2,3);
    Singleton::getInstance(2,3)->print();
    cout << *Singleton::getInstance(2,3) << endl;

    return 0;
}

