#include "my_string.hh"
#include <sstream>

String::String()
    :_pstr(new char[1]()),
    _capacity(0)
{}

String::String(const String & rhs) 
    :_pstr(new char[rhs._capacity + 1]()),
    _capacity(rhs._capacity)
{
    strcpy(_pstr, rhs._pstr);
}

String::String(const char* rhs) 
    :_pstr(new char[strlen(rhs) + 1]()),
    _capacity(strlen(rhs))
{
    strcpy(_pstr, rhs);
}

String::~String() {
    if (_pstr != nullptr) {
        delete[] _pstr;
        _pstr = nullptr;
    }
}

String& String::operator=(const String& rhs) {
    if (this != &rhs) {
        if (_pstr != nullptr) {
            delete[] _pstr;
            _pstr = new char[rhs._capacity + 1]();
            strcpy(_pstr, rhs._pstr);
            _capacity = rhs._capacity;
        }
    }
    return *this;
}

String& String::operator=(const char* rhs) {
    if (_pstr != nullptr) {
        delete[] _pstr;
    }
    _pstr = new char[strlen(rhs) + 1]();
    strcpy(_pstr, rhs);
    _capacity = strlen(rhs);
    return *this;
}

String& String::operator+=(const String& rhs) {
    if (_pstr != nullptr) {
        strcat(_pstr, rhs._pstr);
    } else {
        throw "operator+= lhs is a nullptr.";
    }
    return *this;
}

String& String::operator+=(const char* rhs) {
    if (_pstr != nullptr) {
        strcat(_pstr, rhs);
    } else {
        throw "operator+= lhs is a nullptr.";
    }
    return *this;
}

char& String::operator[](std::size_t index) {
    if (_pstr != nullptr) {
        if (index >= 0 && index < _capacity) {
            return _pstr[index];
        } else {
            cerr << "index out of range!" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    throw "operator[] lhs is a nullptr.";
}

const char& String::operator[](std::size_t index) const {
    if (_pstr != nullptr) {
        if (index >= 0 && index < _capacity) {
            return _pstr[index];
        } else {
            cerr << "index out of range!" << endl;
            static char nullchar = '\0';
            return nullchar;
        }
    }
    throw "operator[] lhs is a nullptr.";
}

std::size_t String::size() const {
    return _capacity;
}

const char* String::c_str() const {
    return _pstr;
}

bool operator==(const String& lhs, const String& rhs) {
    return strcmp(lhs._pstr, rhs._pstr) == 0;
}
	
bool operator!=(const String &lhs, const String& rhs) {
    return !(lhs == rhs);
} 
	
bool operator<(const String& lhs, const String& rhs) {
    return strcmp(lhs._pstr, rhs._pstr) < 0;
}

bool operator>(const String& lhs, const String& rhs) {
    return !(lhs < rhs);
}
	
bool operator<=(const String& lhs, const String& rhs) {
    return (lhs < rhs) || (lhs == rhs);
}
	
bool operator>=(const String& lhs, const String& rhs) {
    return (lhs > rhs) || (lhs == rhs);
}
	
std::ostream& operator<<(std::ostream &os, const String &s) {
    if (s._pstr != nullptr) {
        os << s._pstr;
        return os;
    }
    throw "operator<< rhs is a nullptr";
}

std::istream& operator>>(std::istream &is, String &s) {
    char buff[1024];
    is >> buff;
    s._pstr = new char[strlen(buff) + 1]();
    strcpy(s._pstr, buff);
    s._capacity = strlen(buff);
    return is;
}

String operator+(const String& lhs, const String& rhs) {
    String temp = lhs;
    temp += rhs;
    return temp;
}

String operator+(const String& lhs, const char* rhs) {
    String temp = lhs;
    temp += rhs;
    return temp;
}

String operator+(const char* lhs, const String& rhs) {
    String temp = lhs;
    temp += rhs;
    return temp;
}
