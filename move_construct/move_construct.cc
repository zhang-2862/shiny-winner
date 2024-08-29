#include <iostream>
#include <string.h>
#include <ostream>
using std::cout;
using std::endl;

class String {
    friend std::ostream& operator<<(std::ostream&, const String&);
public:
    String(const char* pstr)
        : pstr_(new char[strlen(pstr) + 1]())
    {
        cout << "String(const char* pstr)" << endl;
        strcpy(pstr_, pstr);
    }

    ~String() {
        if (pstr_) {
            cout << "~String()" << endl;
            delete[] pstr_;
            pstr_ = nullptr;
        }
    }

    String(String&& rhs)
        : pstr_(rhs.pstr_)
    {
        cout << "String(String&&)" << endl;
        rhs.pstr_ = nullptr;
    }

    String& operator=(String&& rhs) {
        cout << "String& operator=(String&& rhs)" << endl;
        if (this != &rhs) {
            delete[] pstr_;
            pstr_ = rhs.pstr_;
            rhs.pstr_ = nullptr;
        }
        return *this;
    }


private:
    char* pstr_;
};

std::ostream& operator<<(std::ostream& os, const String& rhs) {
    os << rhs.pstr_;    
    return os;
}

int main(int argc, char* argv[]) {
    String s(String("hello"));
    cout << s << endl;

    String s1 = String("hello");
    cout << "over" << endl;
    cout << s1 << endl;

    s1 = String(String("old world"));
    cout << s1 << endl;
    
    return 0;
}

