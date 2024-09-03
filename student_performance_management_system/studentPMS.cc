#include <iostream>
#include <list>

using namespace std;

class Student {
friend struct ScoreCompare;
public:
    Student(string name, int age, double chinese, double math, double english)
        : name_(name),
          age_(age),
          chinese_(chinese),
          math_(math),
          english_(english)
    {}

    void display() const {
        cout << name_ << ":\t"
             << " age: " << age_
             << "\tchinese: " << chinese_
             << "\tmath: " << math_
             << "\tenglish: " << english_ << endl;
    }

    /* Student(const Student& rhs) */
    /*     : name_(rhs.name_), */
    /*       age_(rhs.age_), */
    /*       chinese_(rhs.chinese_), */
    /*       math_(rhs.math_), */
    /*       english_(rhs.english_) */
    /* {} */


private:
    string name_;
    int age_;
    int chinese_;
    int math_;
    int english_;
};

struct ScoreCompare {
    bool operator()(const Student& stu1, const Student& stu2) {
        int stu1_sum = stu1.chinese_ + stu1.english_ + stu1.math_;
        int stu2_sum = stu2.chinese_ + stu2.english_ + stu2.math_;

        if ( stu1_sum != stu2_sum) {
            return stu1_sum > stu2_sum;
        } else if (stu1.chinese_ != stu2.chinese_) {
            return stu1.chinese_ > stu2.chinese_;
        } else if (stu1.math_ != stu2.math_) {
            return stu1.math_ > stu2.math_;
        } else if (stu1.english_ != stu2.english_) {
            return stu1.english_ > stu2.english_;
        } else {
            return true;
        }
    }
};

int main(int argc, char* argv[]) {
    Student stu("libai", 27, 99, 88, 66);
    Student stu2(stu);
    Student stu3("dufu", 33, 69, 85, 76);
    Student stu4("baijuyi", 47, 92, 90, 66);
    Student stu5("xinqiji", 41, 94, 78, 86);

    list<Student> stu_list;
    stu_list.push_back(stu);
    stu_list.push_back(stu2);
    stu_list.push_back(stu3);
    stu_list.push_back(stu4);
    stu_list.push_back(stu5);

    stu_list.sort(ScoreCompare());

    for (const auto& e : stu_list) {
        e.display();
    }

    return 0;
}

