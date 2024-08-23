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
    // 测试size() 和 c_str()
    String str("hello");
    cout << "str.size:" << str.size() << endl;
    char c_str[6];
    strcpy(c_str, str.c_str());
    cout << c_str << endl;
}

void test06() {
    // 测试 ==  !=  <   >   <=  >=
    String str1("hello");
    String str2("Hello");
    String str3("aello");
    String str4("hello");
    cout << "str1: " << str1 << endl;
    cout << "str2: " << str2 << endl;
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl;
    if (str1 == str4) {
        cout << "str1 == str4" << endl;
    }

    if (str1 != str3) {
        cout << "str1 != str3" << endl;
    }
    
    if (str1 >= str4 && str1 >= str3) {
        cout << "str1 >= str4 && str1 >= str3" << endl;
    }

    if (str4 <= str1 && str3 <= str1) {
        cout << "str4 <= str1 && str3 <= str1" << endl;
    }

    if (str3 < str1) {
        cout << "str3 < str1" << endl;
    }

    if (str1 > str2) {
        cout << "str1 > str2" << endl;
    }
}

void test07() {
    // 测试 operator>>
    String str;
    cin >> str;
    cout << str << endl;
}

void test08() {
    // 测试operator+
    String str1("hello");
    String str2("world");
    char c_str[] = " iiiiii!";
    String res;
    res = str1 + str2;
    cout << res << endl;
    res = c_str + str2;
    cout << res << endl;
}

int main(int argc, char* argv[]) {
    test08();
    
    return 0;
}

