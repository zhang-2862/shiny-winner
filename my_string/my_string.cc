#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class String {
public:
	String();
	String(const char *pstr);
	String(const String &rhs);
	String &operator=(const String &rhs);
	~String();
	void print() const;
    size_t length() const;
    const char * c_str() const;

private:
	char * _pstr;
};

String::String()
:_pstr(new char[1]())
{}

String::~String() {
    if (_pstr != nullptr) {
        delete [] _pstr;
    }
}

String::String(const char *pstr)
:_pstr(new char[strlen(pstr) + 1]())
{
    strcpy(_pstr, pstr);
}

String::String(const String &rhs)
:_pstr(new char[rhs.length() + 1]())
{
    strcpy(_pstr, rhs.c_str());
}

String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        if(_pstr != nullptr) {
            delete[] _pstr;
        }
        _pstr = new char[rhs.length() + 1]();
        strcpy(_pstr, rhs.c_str());
    }
    return *this;
}

void String::print() const {
    cout << _pstr << endl;
}

size_t String:: length() const {
    size_t len= 0;
    char* cur = _pstr;
    while (*cur++) {
        len++;
    }
    return len;
}

const char* String::c_str() const {
    char* str;
    if (_pstr != nullptr) {
        str = new char[length() + 1]();
        strcpy(str, _pstr);
    }
    return (const char*)str;
}
    
    
void test() {
    String str("hello,world");
    String str1 = str;
    str1.print();
}


int main(int argc, char* argv[]) {
    test();
	/* String str1; */
	/* str1.print(); */
	

	/* String str2 = "Hello,world"; */
	/* String str3("wangdao"); */
	
	/* str2.print(); */		
	/* str3.print(); */	
	
	/* String str4 = str3; */
	/* str4.print(); */
	
	/* str4 = str2; */
	/* str4.print(); */
	
	return 0;
}
