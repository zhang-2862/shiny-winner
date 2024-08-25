#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Base {
public:
    Base(const char* commodity) 
        : _commodity(new char[strlen(commodity) + 1]())
        {
            cout << "Base(const char*)" << endl;
            strcpy(_commodity, commodity);
        }

    Base(const Base& rhs)
        : _commodity(rhs._commodity)
    {
        cout << "Base(const Base*)" << endl;
        _commodity = new char[strlen(rhs._commodity) + 1]();
        strcpy(_commodity, rhs._commodity);
    }

    Base& operator=(const Base& rhs) {
        cout << "Base& operator=(const Base&)" << endl;
        if (this != &rhs) {
            if (_commodity) {
                delete[] _commodity;
                _commodity = new char[strlen(rhs._commodity) + 1]();
                strcpy(_commodity, rhs._commodity);
            }
        }
        return *this;
    }
        
    ~Base() {
        if (_commodity) {
            cout << "~Base()" << endl;
            delete[] _commodity;
            _commodity = nullptr;
        }
    }

protected:
    char* _commodity;
};

class Derived
: public Base
{
    friend
    std::ostream& operator<<(std::ostream& os, const Derived& rhs);
public:
    Derived(const char* commodity, const char* computer) 
        : Base(commodity),
         _computer(new char[strlen(computer) + 1]())
    {
        cout << "Derived(const char*, const char*)" << endl;
        strcpy(_computer, computer);
    }

    Derived(const Derived& rhs)
        : Base(rhs),
         _computer(new char[strlen(rhs._computer) + 1]())
    {
        cout << "Derived(const Derived&)" << endl;
        strcpy(_computer, rhs._computer);
    }
    
    Derived& operator=(const Derived& rhs) {
        cout << "Derived& operator=(const Derived&)" << endl;
        if (this != &rhs) {
            Base::operator=(rhs);
            if (_computer != nullptr) {
                delete[] _computer;
                _computer = new char[strlen(rhs._computer) + 1]();
                strcpy(_computer, rhs._computer);
            }
        }
        return *this;
    }
    ~Derived() {
        if (_computer) {
            cout << "~Derived" << endl;
            delete[] _computer;
            _computer = nullptr;
        }
    }


private:
    char* _computer;
};

std::ostream& operator<<(std::ostream& os, const Derived& rhs) {
    os << rhs._commodity << " " << rhs._computer;
    return os;
}

int main(int argc, char* argv[]) {
    Derived d("computer", "DELL");
    /* Derived d2(d); */
    /* cout << d2 << endl; */
    Derived d3("computer", "Apple");
    d = d3;
    /* cout << d2 << endl; */
    
    return 0;
}

