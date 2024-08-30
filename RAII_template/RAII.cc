#include <iostream>
#include <string.h>
using std::cout;
using std::endl;

class Computer {
public:
    Computer(const char* brand, int price)
        : brand_(new char[strlen(brand) + 1]()),
          price_(price)
    {
        strcpy(brand_, brand);
    }

    void print() {
        cout << brand_ << " " << price_ << endl;
    }

    ~Computer() {
        cout << "~Computer" << endl;
        if (brand_) {
            delete[] brand_;
            brand_ = nullptr;
        }
    }

private:
    char* brand_;
    int price_;
};

template<class T>
class Raii {
public:
    Raii(T* data) : data_(data) {}
    ~Raii() {
        cout << "~Raii()" << endl;
        if (data_) {
            delete data_;
            data_ = nullptr;
        }
    }

    T* operator->() {
        return data_;
    }

    T& operator*() {
        return *data_;
    }

    T* get() {
        return data_;
    }

    void reset(T* data) {
        if (data_) {
            delete data_;
            data_ = nullptr;
        }
        data_ = data;
    }

    Raii(const Raii* rhs) = delete;
    Raii& operator=(const Raii* rhs) = delete;

private:
    T* data_;
};

int main(int argc, char* argv[]) {
    Raii<Computer> rc(new Computer("xiaomi", 10000));
    Computer* pc = new Computer("apple", 20000);
    rc->print();
    (*rc).print();
    (rc.get())->print();
    rc.reset(pc);
    rc->print();


    return 0;
}

