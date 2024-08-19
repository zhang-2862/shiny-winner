#include <iostream>
#include <fstream>
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "usage: programa_name file_name" << endl;
        return EXIT_FAILURE;
    }

    std::ifstream ifs(argv[1]);
    
    std::string word;
    while (ifs >> word) {
        cout << word << endl;
    }

    ifs.close();
    
    return 0;
}

