#include <iostream>
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {
    string str("hello");
    string str2("0123456789abcde");
    string str3("0123456789abcdef");
    char* p = (char*)&str;
    p = p + 16;
    cout << p << endl;
    
    char* p1 = (char*)&str2;
    p1 = p1 + 16;
    cout << p1 << endl;

    char* p2 = (char*)&str3;
    p2 = p2 + 24;
    cout << *p2 << endl;
    /* p2 = p2 + 24; */

    size_t* p3 = (size_t*)&str3 ;
    cout << *p3 << endl;
    p3 = (size_t*)&str3 -2;
    cout << *p3 << endl;

    cout << "--------------" << endl;

    char* p4 = (char*)&str3[0];
    p4 = p4 - 16;
    cout << *(size_t*)p4 << endl;
    /* size_t* p5 = (size_t*)&str; */
    /* cout << ++*p5 << endl; */

    return 0;
}

