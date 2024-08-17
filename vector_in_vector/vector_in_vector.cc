#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

int main(int argc, char* argv[]) {
    int rows = 5;
    int cols = 5;
    vector<vector<int>> v_v(5, vector<int>(5, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            v_v[i][j] = i * rows + j ;
        }
    }

    for (auto& rows : v_v) {
        for (auto& e : rows) {
            cout << e << " ";
        }
        cout << endl;
    }
    
    return 0;
}

