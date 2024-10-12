#include "DirScanner.hh"
#include <iostream>

int main(int argc, char* argv[]) {
    DirScanner dirScanner;
    dirScanner("data/cn_copus");
    vector<string> files = dirScanner.files();
    for (auto& string: files) {
        std::cout << string << std::endl;
    }

    return 0;
}

