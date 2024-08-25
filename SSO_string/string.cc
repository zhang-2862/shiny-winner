#include <iostream>
#include <string.h>
using std::cout;
using std::endl;
using std::ostream;

class String {
public:
    String(const char * pstr);
    ~String();
    char & operator[](size_t idx);
    size_t size() {
        return _size;
    }

    size_t capacity() {
        return _capacity;
    }

    const char* c_str() {
        if (_size > 15) {
            return _buffer._pointer;
        } else {
            return _buffer._local;
        }
    }

    friend
    ostream & operator<<(ostream & os,const String & rhs);
private:
	union Buffer{
		char * _pointer;
		char _local[16];
	};
	
	size_t _size;
	size_t _capacity;
    Buffer _buffer;
};


ostream & operator<<(ostream & os,const String & rhs) {
    if (rhs._capacity > 15) {
        os << rhs._buffer._pointer << endl;
    } else {
        os << rhs._buffer._local << endl;
    }
    return os;
}

String::String(const char * pstr)
    : _size(strlen(pstr)),
     _capacity(_size)
{
    if (_size > 15) {
        _buffer._pointer = new char[_size + 1]();
        strncpy(_buffer._pointer, pstr, _size);
    } else {
        // _size <= 15 则将_capacity设置为15
        _capacity = 15;
        strncpy(_buffer._local, pstr, _size);
    }
}

String::~String() {
    if (_size > 15 && _buffer._pointer) {
        delete _buffer._pointer;
        _buffer._pointer = nullptr;
    }
}


char& String::operator[](size_t idx) {
    if (_size > 15) {
        return _buffer._pointer[idx];
    } else {
        return _buffer._local[idx];
    }
}

void test0(){
    String str1("hello");
    String str2("hello,world!!!!!");
    //...
    cout << str1.size() << endl;
    cout << str1.capacity() << endl;
    cout << &str1 << endl;
    printf("%p\n", &str1[0]);
    printf("%p\n", str1.c_str());
    cout << endl;

    cout << str2.size() << endl;
    cout << str2.capacity() << endl;
    cout << &str2 << endl;
    printf("%p\n", &str2[0]);
    printf("%p\n", str2.c_str());
    cout << endl;
}

int main(void) {
    test0();

}
