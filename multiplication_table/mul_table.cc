#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

void table() {
    vector<vector<int>> vv(9, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9});
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j <= i; ++j) {
            cout << vv[i][j] << " * " << vv[j][i]
                << " = " << vv[i][j]*vv[j][i] << "\t";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]) {
    table();

    return 0;
}

