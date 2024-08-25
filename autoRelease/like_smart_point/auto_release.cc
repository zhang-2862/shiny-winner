#include <iostream>
using std::cout;
using std::endl;

class Singleton {
    friend class AutoReles;
public:
    static Singleton* getInstance() {
        if (_pInstance == nullptr) {
            _pInstance = new Singleton();
        }
        return _pInstance;
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
    static Singleton* _pInstance;
    int _x;
    int _y;
};
Singleton* Singleton::_pInstance= nullptr;

class AutoReles {
public:
    AutoReles(Singleton* pSingleton)
        : _pSingleton(pSingleton)
    {}
    ~AutoReles() {
        if (_pSingleton) {
            delete _pSingleton;
            _pSingleton = nullptr;
        }
    }
private:
    Singleton* _pSingleton;
};

int main(int argc, char* argv[]) {
    AutoReles ar(Singleton::getInstance());

    return 0;
}

