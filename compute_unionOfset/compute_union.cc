#include <iostream>
#include <set>
using std::cout;
using std::cin;
using std::endl;
using std::set;

void ReadData(set<int>& A, set<int>& B) {
    int n(0);
    int m(0);
    cin >>n>>m;

    for (int i = 0; i < n; ++i) {
        int temp = 0;
        cin >> temp;
        A.insert(temp);
    }

    for (int i = 0; i < m; ++i) {
        int temp = 0;
        cin >> temp;
        B.insert(temp);
    }
}

void ComputeUnion(set<int>& A, set<int>& B) {
    for (const auto& e : B) {
        A.insert(e);
    }
}

void Display(set<int>& set) {
    for (const auto& e : set) {
        cout << e << " ";
    }
    cout << endl;
}

int main(int argc, char* argv[]) {
    set<int> A;
    set<int> B;
    ReadData(A, B);
    ComputeUnion(A, B);
    Display(A);

    return 0;
}

