#include <string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

class CowString{
    class CharProxy {
    /* friend ostream& operator<<(ostream&, const CharProxy&); */
    public:
        CharProxy(CowString& pCows, size_t idx)
            : _idx(idx),
             _pCows(pCows)
        {}

        // 进行写操作 则重新申请一块内存空间存放该字符串并修改
        char& operator=(const char& c) {
            if (_idx <_pCows.size()) {
                if (_pCows.use_count() > 1) {
                    // 原字符串引用计数-1
                    --*(int*)(_pCows._pstr - kRefcountLength);

                    char* temp =
                        /* new char[strlen(_pCows._pstr)]() +4 ; */
                        new char[_pCows.size() + 1 + kRefcountLength]() + kRefcountLength;
                    strcpy(temp, _pCows._pstr);
                    // 更改_pCows指向
                    _pCows._pstr = temp;
                    // 初始化引用计数
                    *(int*)(_pCows._pstr - kRefcountLength) = 1;
                }
                // 修改字符
                _pCows._pstr[_idx] = c;
                return _pCows._pstr[_idx];
            } else {
                static char nullchar = '\0';
                return nullchar;
            }
        }

        operator char() {
            return _pCows._pstr[_idx];
        }

    private:
        size_t _idx;
        CowString& _pCows;
    };

    /* friend ostream& operator<<(ostream&, const CharProxy&); */

public:
    CowString();
    CowString(const char * pstr);
    ~CowString();
    CowString(const CowString & rhs);
    CowString & operator=(const CowString & rhs);

    // 利用代理类中的重载 区分取下标后的读写操作
    CharProxy operator[](size_t idx); 

    size_t size() const{
        return strlen(_pstr);
    }

    const char * c_str() const{
        return _pstr;
    }

    int use_count() const{
        return *(int*)(_pstr - kRefcountLength);
    }

    friend
    ostream & operator<<(ostream & os,const CowString & rhs);

private:
    static char * malloc(const char * pstr = nullptr){
        if(pstr){
            // 有参构造，返回（字符串长度+1+引用字段长度）进行偏移后的指向字符串的指针
            return new char[strlen(pstr) + 1 + kRefcountLength]() + kRefcountLength;
        }else{
            return new char[1 + kRefcountLength]() + kRefcountLength;
        }
    }

    void release(){
        decreaseRefcount();
        if(use_count() == 0){
            delete [] (_pstr - kRefcountLength);
            cout << ">> delete heap" << endl;
        }
        _pstr = nullptr;
    }

    void initRefcount(){
        *(int*)(_pstr - kRefcountLength) = 1;
    }

    void increaseRefcount(){
        ++*(int*)(_pstr - kRefcountLength);
    }
    void decreaseRefcount(){
        --*(int*)(_pstr - kRefcountLength);
    }

private:
    static const int kRefcountLength = 4;
    char * _pstr;
};

ostream & operator<<(ostream & os,const CowString & rhs) {
    if (rhs._pstr) {
        os << rhs._pstr; 
    }
    return os;
}

CowString::CowString() 
    : _pstr(malloc())
{
    initRefcount();
}

CowString::CowString(const char * pstr)
    : _pstr(malloc(pstr))
{
    strcpy(_pstr, pstr);
    initRefcount();
}

CowString::~CowString() {
    release();
}

CowString::CowString(const CowString & rhs)
    : _pstr(rhs._pstr)
{
    increaseRefcount();
}

CowString& CowString::operator=(const CowString & rhs)
{
    if (this != &rhs) {
        release();
        _pstr = rhs._pstr;
        increaseRefcount();
    }
    return *this;
}


CowString::CharProxy CowString::operator[](size_t idx) {
    CharProxy cp(*this, idx);
    return cp;
}

void test01() {
    CowString str("hello_abcdefghijklmn");    
    CowString str1(str);
    cout << "str: " << str << endl;
    cout << "ref_count: " << str.use_count() << endl;
    cout << "str1: " << str1 << endl;
    cout << "ref_count: " << str1.use_count() << endl;

    /* cout << "str: " << str[0] << endl; */
    str[0] = 'H';
    cout << "str[0] 修改后" << endl;
    cout << "str: " << str[0] << endl;
    cout << "str1: " << str1[0] << endl;

    cout << "str: " << str << endl;
    cout << "ref_count: " << str.use_count() << endl;
    cout << "str1: " << str1 << endl;
    cout << "ref_count: " << str1.use_count() << endl;
}

int main(void) {
    test01();
}
