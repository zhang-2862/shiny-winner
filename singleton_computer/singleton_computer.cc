#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer {
public:
    static Computer* getInstance() {
        if (_pInstance == nullptr) {
            _pInstance = new Computer("unkown", 0);
            cout << "getInstance() is called." << endl;
        }
        return _pInstance;
    }

    static void destory() {
        if (_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
            cout << "destroy() is called." << endl;
        }
    }

    void init(const char* brand, int price) {
        if (_brand != nullptr) {
            _brand = new char[strlen(brand) + 1]();
            strcpy(_brand, brand);
            _price = price;
            cout << "init() is called." << endl;
        }
    }

    void print() const {
        cout << "brand: " << _brand <<endl 
             << "price: " << _price <<endl;
    }

private:
    Computer() = default;
    Computer(const Computer&) = delete;
    Computer& operator=(const Computer&) = delete;

    Computer(const char* brand, int price)
    :_brand(new char[strlen(brand) + 1]()),
    _price(price)
    {
        strcpy(_brand, brand);
        cout << "Computer(char*,int)" << endl;
    }

    ~Computer() {
        if (_brand != nullptr) {
            delete [] _brand;
            _brand = nullptr;
        }
    }

private:
    char* _brand;
    int _price;
    static Computer* _pInstance;
};
Computer* Computer::_pInstance = nullptr;

int main(int argc, char* argv[]) {
    Computer::getInstance();
    Computer::getInstance()->print();
    Computer::getInstance()->init("DELL", 8000);
    Computer::getInstance()->print();
    Computer::destory();
    Computer::getInstance()->init("HUAWEI", 10000);
    Computer::getInstance()->print();
    Computer::destory();
    Computer::destory();

    return 0;
}

