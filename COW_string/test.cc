#include <string.h>
#include <iostream>

using std::cout;
using std::endl;
class String
{
public:
    String()
    :_pstr(new char[5]() + 4)
    {
        cout << "String()" << endl;
        //_pstr创建的是一个char型指针,需要转换成int型指针控制4个字节
        *(int *)(_pstr - 4) = 1;
    }
    //String s1 = "hello";
    String(const char *pstr)
    :_pstr(new char[strlen(pstr) + 5]() + 4)//new char[strlen(pstr) + 5]()，加了()后，数据都初始化为0了，就相当于memset，已经初始化了并设置为0了。
    {
        cout << "String(const char *)" << endl;
        strcpy(_pstr, pstr);
        *(int *)(_pstr - 4) = 1;
    }
    //String s2 = s1;
    String(const String &rhs)
    :_pstr(rhs._pstr)
    {
        cout << "String(const String &)" << endl;
        ++*(int *)(rhs._pstr - 4);
    }
    int getRef()
    {
        return *(int *)(_pstr - 4);
    }
    size_t size() const
    {
        return strlen(_pstr);
    }
    //String s3 = "world"
    //s3 = s1;
    String &operator=(const String &rhs)
    {
        cout << "String &operator=(const String &)" << endl;
        if(this != &rhs)//1、自复制
        {
            /* auto ref = --*(_pstr - 4); */
            --*(int *)(_pstr - 4);
            if(0 == *(int *)(_pstr - 4))//2、释放左操作数
            {
                /* delete []_pstr; //error*/
                //这里需要先把指针偏移，然后delete
                delete [](_pstr - 4);
                _pstr = nullptr;
            }
            _pstr = rhs._pstr;//3、浅拷贝
            ++*(_pstr - 4);
        }
        return *this;//4、返回this指针
    }
    //将String风格字符转换成C风格
    const char* c_str() const
    {
        return _pstr;
    }
    ~String()
    {
        cout << "~String()" << endl;
        //析构函数这里，对于指向同一字符串的对象，释放掉一个对象，引用计数减一
        //并不需要对每个对象都delete,只需要对引用计数为0的
        //最后一个对象delete释放掉即可，
        --*(int *)(_pstr - 4);
        if(0 == *(int *)(_pstr - 4))
        {
            //这里需要先把指针偏移，然后delete
            delete [](_pstr - 4);
            /* delete []_pstr;//error */
        }
        /* if(nullptr == _pstr) */
        /* { */
        /*     delete [] _pstr; */
        /*     _pstr = nullptr; */
        /* } */
    }
    friend std::ostream &operator<<(std::ostream &os, const String &rhs);
private:
    //设计模式之代理模式
    class CharProxy
    {
    public:
        CharProxy(String &str, size_t idx)
        :_str(str)
        ,_idx(idx)
        {
            cout << "CharProxy(String &, size_t)" << endl;
        }

        char &operator=(const char &ch)
        {
            if(_idx < _str.size())
            {
                if(_str.getRef() > 1)
                {
                    --*(int *)(_str._pstr - 4);
                    char *tmp = new char[strlen(_str._pstr)]() + 4;
                    strcpy(tmp, _str._pstr);
                    _str._pstr = tmp;
                    cout << "tmp.sizeof = " << strlen(tmp) << endl;
                    *(int *)(_str._pstr - 4) = 1;
                }
                _str._pstr[_idx] = ch;//真正的的赋值操作
                return _str._pstr[_idx];
            }
            else
            {
                static char nullchar = '\0';
                return nullchar;
            }
        }
        //类型转换函数，将自定义的CharProxy转换为char
        //代替输出流运算符的重载
        operator char()
        {
            return _str._pstr[_idx];
        }
        /* friend std::ostream &operator<<(std::ostream &os, const CharProxy &rhs); */
    private:
        String &_str;
        size_t _idx;
    };
public:
    //CharProxy要在String下标运算符重载之前定义
    //不可以返回CharProxy类型的引用，因为return的是临时变量是个右值
    CharProxy operator[](size_t idx)
    {
        return CharProxy(*this, idx);
    }
    /* friend std::ostream &operator<<(std::ostream &os, const CharProxy &rhs); */
private:
    char *_pstr;
};
std::ostream &operator<<(std::ostream &os, const String &rhs)
{
    //判断一下rhs的数据成员是否为空
    if(rhs._pstr)
    {
        os << rhs._pstr;
    }
    return os;
}
#if 0
//因为rhs要同时访问String和CharProxy的私有成员
//所以要将该输出流运算符同时设置为String和CharProxy的友元函数
std::ostream &operator<<(std::ostream &os, const String::CharProxy &rhs)
{
    os << rhs._str._pstr[rhs._idx];
    return os;
}
#endif
int main()
{
    String s1("hello");
    String s2 = s1;
    String s3("world");
    s3 = s1;
    cout << "s1.getRef = " << s1.getRef() << endl;
    cout << "s2.getRef = " << s2.getRef() << endl;
    cout << "s3.getRef = " << s3.getRef() << endl;
    cout <<"s1 = " << s1 << endl << "s2 = " << s2 << endl << "s3 = " << s3 << endl;
    printf("s1's address = %p\n", s1.c_str());
    printf("s2's address = %p\n", s2.c_str());
    printf("s3's address = %p\n", s3.c_str());
    
    cout << endl;
    s3[0] = 'H';
    cout << "s1.getRef = " << s1.getRef() << endl;
    cout << "s2.getRef = " << s2.getRef() << endl;
    cout << "s3.getRef = " << s3.getRef() << endl;
    cout <<"s1 = " << s1 << endl << "s2 = " << s2 << endl << "s3 = " << s3 << endl;
    printf("s1's address = %p\n", s1.c_str());
    printf("s2's address = %p\n", s2.c_str());
    printf("s3's address = %p\n", s3.c_str());

    cout << endl;
    //s[0]将自动匹配可以转换的类型，CharProxy类中定义了char的类型转换函数
    //所以此时s[0]将自动从CharProxy类型转换成char，所以可以直接输出，而不需要重载CharProxy的输出流运算符
    cout << "s3[0]" << s1[0] << endl;
    cout << "s1.getRef = " << s1.getRef() << endl;
    cout << "s2.getRef = " << s2.getRef() << endl;
    cout << "s3.getRef = " << s3.getRef() << endl;
    cout <<"s1 = " << s1 << endl << "s2 = " << s2 << endl << "s3 = " << s3 << endl;
    printf("s1's address = %p\n", s1.c_str());
    printf("s2's address = %p\n", s2.c_str());
    printf("s3's address = %p\n", s3.c_str());
    return 0;
}

