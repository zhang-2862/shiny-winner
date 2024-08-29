#include <algorithm>
#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;

template<class T>
T add(T lhs, T rhs) {
    return lhs + rhs;
}

template<>
set<int> add(set<int> lhs, set<int> rhs) {
    set<int> temp;
    std::set_union(lhs.cbegin(), lhs.cend(),
                   rhs.cbegin(), rhs.cend(),
                   std::inserter(temp, temp.begin()));
    return temp;
}

template<class T>
void print(T t) {
    for (const auto& e : t) {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    set<int> s1{1,2,3,4,5};
    set<int> s2{3,4,5,6,7};
    set<int> s3;

    s3 = add(s1, s2);
    print(s3);
    
    return 0;
}

