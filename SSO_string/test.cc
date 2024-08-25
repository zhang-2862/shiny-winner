#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;

void test0(){
    string str1("hello");
    cout << str1.size() << endl;
    cout << str1.capacity() << endl;

    cout << endl;
    string str2("hello,world!!!!");
    cout << str2.size() << endl;
    cout << str2.capacity() << endl;
    cout << &str2 << endl;
    printf("%p\n",&str2[0]);
    printf("%p\n",str2.c_str());

    cout << endl;
    string str3("hello,world!!!!!!!");
    cout << str3.size() << endl;
    cout << str3.capacity() << endl;
    cout << &str3 << endl;
    printf("%p\n",&str3[0]);
    printf("%p\n",str3.c_str());

    cout << endl;
    string str4 = str3;
    cout << &str4 << endl;
    printf("%p\n",&str4[0]);
    printf("%p\n",str4.c_str());

    
}

int main(void){
    test0();
    return 0;
}
