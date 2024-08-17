#include <iostream>
#include <string.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

// 商品类
class Commodity {
public:
    Commodity(const char* name, int num)
    :_name(new char[strlen(name) + 1]()),
    _num(num)
    {
        strcpy(_name, name);
    }

    void print() const {
        cout << _name << " " << _num <<endl;
    }

    ~Commodity() {
        if (_name != nullptr) {
            delete [] _name;
            _name = nullptr;
        }
    }

private:
    char* _name;
    int _num;
};

// 购物车类
class ShoppingCart {
public:
    static ShoppingCart* getInstance() {
        if (_pInstance == nullptr) {
            _pInstance = new ShoppingCart();
        }
        return _pInstance;
    }

    static void destroy() {
        if (_pInstance != nullptr) {
            delete _pInstance;
            _pInstance = nullptr;
        } 
    }

    void addCommodity(Commodity* pCommodity) {
        _pVComputer.push_back(pCommodity);
    }

    void print() const {
        for (const auto& e: _pVComputer) {
            /* cout << "ShoppingCart: print" << endl; */
            e->print();
        }
    }
    
private:
    ShoppingCart() = default;
    ShoppingCart(const ShoppingCart&) = delete;
    ShoppingCart& operator=(const ShoppingCart&) = delete;

    ~ShoppingCart() {
        if (!_pVComputer.empty()) {
            for (auto& e: _pVComputer) {
                delete e;
                e = nullptr;
            }
        }
        /* cout << "ShoppingCart is destroyed" << endl; */
    }

    
private:
    vector<Commodity*> _pVComputer; // 用于保存商品对象指针的数组
    static ShoppingCart* _pInstance;
};
ShoppingCart* ShoppingCart::_pInstance = nullptr;

int main(int argc, char* argv[]) {
    char name[128];
    int num;
    while (scanf("%s%d", name, &num) == 2) {
        Commodity* pCommodity = new Commodity(name, num);
        ShoppingCart::getInstance()->addCommodity(pCommodity);
    }
    ShoppingCart::getInstance()->print();
    ShoppingCart::destroy();

    return 0;
}

