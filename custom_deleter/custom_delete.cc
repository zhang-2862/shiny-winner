#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;

struct FileDeleter {
    void operator()(FILE* fp) {
        if (fp) {
            fclose(fp);
            cout << "FileDeleter" << endl;
        }
    }
};


int main(int argc, char* argv[]) {
    FILE* fp = fopen("a.txt", "r");
    /* unique_ptr<FILE, FileDeleter> up_f(fp); */
    FileDeleter fDeleter;
    std::shared_ptr<FILE> sp_f(fp, fDeleter);
    cout << endl;

    return 0;
}

