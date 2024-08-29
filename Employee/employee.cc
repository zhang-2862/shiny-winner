#include <iostream>
#include <string.h>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Person {
public:
    Person(const char* name, int age)
        : _name(new char[strlen(name) + 1]()),
         _age(age)
    {
        strcpy(_name, name);
    }
    ~Person() {
        if (_name) {
            delete[] _name;
            _name = nullptr;
        }
    }
    Person(const Person& rhs)
        : _name(new char[strlen(rhs._name) + 1]()),
         _age(rhs._age)
    {
        strcpy(_name, rhs._name);    
    }

    Person& operator=(const Person& rhs) {
        if (this != &rhs) {
            _name = new char[strlen(rhs._name) + 1]();
            strcpy(_name, rhs._name);
            _age = rhs._age;
        }
        return *this;
    }

    void display() {
        cout << "name: " << _name
            << " age: " << _age << endl;
    }
    
private:
    char* _name;
    int _age;
};

class Employee : public Person {
public:
    Employee(const char* name, int age, const char* department, int salary)
        : Person(name, age),
         _department(new char[strlen(department) + 1]()),
          _salary(salary)
    {
        strcpy(_department, department);
        ++_numOfEmployee;
        _sumSalary += _salary;
    }

    ~Employee() {
        if (_department) {
            delete[] _department;
            _department = nullptr;
        }
        --_numOfEmployee;
        _sumSalary -= _salary;
    }

    Employee(const Employee& rhs)
        : Person(rhs),
         _department(new char[strlen(rhs._department) + 1]()),
          _salary(rhs._salary)
    {
        strcpy(_department, rhs._department);
        ++_numOfEmployee;
        _sumSalary += _salary;
    }

    Employee& operator=(const Employee& rhs) {
        if (this != &rhs) {
            _sumSalary -= _salary;
            Person::operator=(rhs);
            _department = new char[strlen(rhs._department) + 1]();
            strcpy(_department, rhs._department);
            _salary = rhs._salary;
            _sumSalary += _salary;
        }
        return *this;
    }

    void display() {
        Person::display();
        cout << "department: " << _department
            << " salary: " << _salary << endl; 
    }

    static double average() {
        return double(_sumSalary) / _numOfEmployee; 
    }

private:
    static int _numOfEmployee;
    static int _sumSalary;
    char* _department;
    int _salary;
};
int Employee::_numOfEmployee = 0;
int Employee::_sumSalary = 0;

int main(int argc, char* argv[]) {
    vector<Employee> empl;
    Employee p1("李白", 25, "吏部", 10000);
    Employee p2("杜甫", 37, "户部", 9900);
    Employee p3("李商隐", 26, "礼部", 7000);
    Employee p4("白居易", 39, "工部", 8800);
    Employee p5("杜牧", 27, "刑部", 8700);
    Employee p6("辛弃疾", 34, "兵部", 6600);
    Employee p7("李渊", 45, "礼部", 20000);
    Employee p8(p7);

        
    empl.emplace_back(p1);
    empl.emplace_back(p2);
    empl.emplace_back(p3);
    empl.emplace_back(p4);
    empl.emplace_back(p5);
    empl.emplace_back(p6);
    empl.emplace_back(p7);
    empl.emplace_back(p8);

    for (auto& e : empl) {
        e.display();
    }
    cout << endl;
    cout << "averageSalary: " << Employee::average() << endl; 
    cout << endl;

    cout << "test for 'operator='" << endl;
    p8 = p1;
    p8.display();

    return 0;
}

