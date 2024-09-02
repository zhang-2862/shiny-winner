#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <string>
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;
using std::sort;

class Person {
public:
    Person(const string& name)
        : name_(name),
          avg_score_(0)
    {}

    deque<double>& get_scores() {
        return scores_;
    }

    double& get_avg_score() {
        return avg_score_;
    }

    const string& get_name() const{
        return name_;
    }

private:
    string name_;
    double avg_score_;
    deque<double> scores_;
};

void test() {
    srand(time(NULL));
    Person p1("A");
    Person p2("B");
    Person p3("C");
    Person p4("D");
    Person p5("E");

    vector<Person> vP;
    vP.push_back(p1);
    vP.push_back(p2);
    vP.push_back(p3);
    vP.push_back(p4);
    vP.push_back(p5);

    for (int i = 0; i< 5; ++i) {
        for (int j = 0; j< 10; ++j) {
            double temp = 40 + rand()%61;
            vP[i].get_scores().push_back(temp);
        }
        sort(vP[i].get_scores().begin(), vP[i].get_scores().end());
        vP[i].get_scores().pop_front();
        vP[i].get_scores().pop_back();
        for (const auto& e : vP[i].get_scores()) {
            vP[i].get_avg_score() += e;
        }
        vP[i].get_avg_score() /= 8;
    }

    auto it = vP.begin();
    for (; it != vP.end(); ++it) {
        cout << it->get_name() << " "
            << it->get_avg_score() << endl;
    }

    for (auto& e : vP) {
        cout << e.get_name() << " "
            << e.get_avg_score() << endl;
    }
}

int main(int argc, char* argv[]) {
    test();
    return 0;
}

