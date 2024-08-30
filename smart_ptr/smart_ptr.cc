#include <iostream>
#include <memory>
#include <deque>
#include <vector>
using std::cout;
using std::endl;
using std::deque;
using std::vector;
using std::shared_ptr;

class Child;

class Parent {
public:
    Parent() { cout << "Parent" << endl; }
    ~Parent() { cout << "~Parent" << endl; }

    /* shared_ptr<Child> p_child_; */
    std::weak_ptr<Child> p_child_;
};

class Child {
public:
    Child() { cout << "Child" << endl; }
    ~Child() { cout << "~Child" << endl; }

    shared_ptr<Parent> p_parent_;
    /* std::weak_ptr<Parent> p_parent_; */
};

void test01() {
    std::unique_ptr<int> up(new int(10));
    vector<std::unique_ptr<int>> v_up;
    v_up.push_back(std::move(up));
    cout << "End" << endl;
}

void test02() {
    shared_ptr<Parent> spp(new Parent);
    shared_ptr<Child> spc(new Child);
    cout << spp.use_count() << endl;
    cout << spc.use_count() << endl;

    spp->p_child_ = spc;
    spc->p_parent_= spp;

    cout << spp.use_count() << endl;
    cout << spc.use_count() << endl;
}

void test03() {
    std::auto_ptr<int> ap(new int(10));
    cout << &(*ap) << endl;
    std::auto_ptr<int> ap2(ap);
    cout << &(*ap)<< endl;
    cout << &(*ap2)<< endl;
    cout << *ap2 << endl;
}

void test04() {
    std::shared_ptr<int> up(new int(10));
    vector<std::shared_ptr<int>> v_up;
    cout << up.use_count() << endl;

    v_up.push_back(up);
    cout << up.use_count() << endl;

    v_up.push_back(std::move(up));
    cout << up.use_count() << endl;

    cout << v_up[0].use_count() << endl;
    cout << v_up[1].use_count() << endl;

    cout << "End" << endl;

}


int main(void) {
    /* test01(); */
    /* test02(); */
    /* test03(); */
    test04();

    return 0;
}
