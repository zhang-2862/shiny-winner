#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    virtual void print() {
        cout << "Base::print()" << endl;
    }
    virtual void display() {
        cout << "Base::display()" << endl;
    }
    virtual void show() {
        cout << "Base::show()" << endl;
    }
private:
    long _base = 10;
};

class Derived : public Base {
    virtual void print() {
        cout << "Derived;:print()" << endl;
    }
    virtual void display() {
        cout << "Derived;:display()" << endl;
    }
    virtual void show() {
        cout << "Derived;:show()" << endl;
    }
private:
    long _derived = 100;
};

static long pos = 0;
const char* str = "i am in literal constant area";

int main(int argc, char* argv[]) {
    Derived d;
    long* pDerived = reinterpret_cast<long*>(&d);
    long* pVtable = reinterpret_cast<long*>(pDerived[0]);

    /* printf("virtual pDerived:table address:  %p\n", pDerived); */
    printf("virtual table address:  %p\n", pVtable);
    cout << "global static area:  " << &pos << endl;
    printf("literal constant area:  %p\n", str);
    
    return 0;
}

