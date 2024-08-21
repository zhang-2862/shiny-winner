#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    Base(int x)
        :_data(x)
    {}

    friend Base operator+(const Base&, const Base&);
    
    bool operator==(int x) {
        return _data == x;
    }
    // 为能进行== 比较可以定义类型转换函数,作为第二种解决方案
    operator int() {
        return _data;
    }        

private:
    int _data;
};

Base operator+(const Base& lhs, const Base& rhs) {
    return(Base(rhs._data - lhs._data));
}

int main(int argc, char* argv[]) {
    int i = 2;
    int j = 7;

    Base x(i);
    Base y(j);
    cout << ( x + y == j - i) << endl;
    cout << ( j - i == x + y) << endl;
    
    return 0;
}

