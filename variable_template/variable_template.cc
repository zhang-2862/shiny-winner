#include <iostream>
using std::cout;
using std::endl;

double add() {
    return 0.0;
}

template<class T, class... Args>
double add(T x1, Args... args) {
    return x1 + add(args...);
}


int main(int argc, char* argv[]) {
    double res = 0;
    res = add(1, 2, 3, 4, 5);
    cout << res << endl;
    
    return 0;
}

