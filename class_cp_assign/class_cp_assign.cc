#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Student {
public:
    Student()
    :_stu_id(0)
    ,_stu_name(new char[strlen("default") + 1]())
    ,_stu_age(0)
    {
        strcpy(_stu_name, "default");
        cout << "default init" << endl;
    }

    Student(int id, const char* str, int age) 
    :_stu_id(id)
    ,_stu_name(new char[strlen(str) + 1]())
    ,_stu_age(age)
    {
        strcpy(_stu_name, str);
    }

    Student(const Student& rhs)
    :_stu_id(rhs._stu_id)
    ,_stu_name(new char[strlen(rhs._stu_name) + 1])
    ,_stu_age(rhs._stu_age)
    {
        strcpy(_stu_name, rhs._stu_name);
        cout << "copy" << endl;
    }

    Student& operator=(const Student& rhs) {
        if (this != &rhs) {
            delete [] this->_stu_name;
            this->_stu_name = new char[strlen(rhs._stu_name) + 1]();
            strcpy(this->_stu_name, rhs._stu_name);
            this->_stu_id = rhs._stu_id;
            this->_stu_age = rhs._stu_age;
        }
        cout << "assign" << endl;
        return *this;
    }

    void print() {
        cout << "学号：" << this->_stu_id << endl;
        cout << "姓名：" << this->_stu_name << endl;
        cout << "年龄：" << this->_stu_age << endl;
    }
        

    ~Student() {
        if (this->_stu_name != NULL) {
            delete [] this->_stu_name;
            this->_stu_name = nullptr;
        }
        cout << "destruct" << endl;
    }
private:
    int _stu_id;
    char* _stu_name;
    int _stu_age;
};

int main(int argc, char* argv[]) {

    Student A;
    Student B(1, "blanca", 1000);
    Student C(B);
    
    A.print();
    B.print();
    C.print();

    cout << "A after assign " << endl;
    A = B;
    A.print();
    
    return 0;
}

