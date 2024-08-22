#include "my_string.hh"
using std::cout;
using std::endl;

void test01() {
    // 测试空字符串
    String str;
    cout << str << endl;
    // 测试 String(const char*);
    // 测试 String(const String&);
    String str2 = String("hello, world2");
    cout << String("hello, world") << endl;
    cout << String(str2) <<endl;
}

void test02() {
    // 测试赋值运算符
    String str("hello");
    cout << str << endl;

    String str2("world");
    str = str2;
    cout << str << endl;

    str = "hello,world";
    cout << str << endl;
}

void test03() {
    // 测试+=运算符；
    String str("hello");
    String str2("world");
    str += str2;
    cout << str << endl;

    str += "!";
    cout << str << endl;
}

void test04() {
    // 测试取下表运算符
    String str("hello");
    cout << str[1] << endl;

    str[1] = 'E';
    cout << str[1] << endl;

    const String str2("world");
    cout << str2[1];
    /* str2[1] = 'O';//erorr; */
}

void test05() {
    //TODO 测试size() 和 c_str()
    String str("hello");
    cout << str.size() << endl;
}


int main(int argc, char* argv[]) {
    test04();
    
    return 0;
}

