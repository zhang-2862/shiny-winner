#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

class MainBoard {
public:
    virtual void show() = 0;
    virtual ~MainBoard(){};
};

class HWMainBoard : public MainBoard {
public:
    void show() override {
        cout << "HW-MainBoard" << endl;
    }
};

class XMMainBoard : public MainBoard {
public:
    void show() override {
        cout << "XM-MainBoard" << endl;
    }
};

class CPU {
public:
    virtual void show() = 0;
    virtual ~CPU(){};
};

class HWCPU : public CPU {
public:
    void show() override {
        cout << "HW-CPU" << endl;
    }
};

class XMCPU : public CPU {
public:
    void show() override {
        cout << "XM-CPU" << endl;
    }
};

class ComputerFactory {
public:
    virtual MainBoard* createMainBoard() = 0;
    virtual CPU* createCPU() = 0;

    virtual ~ComputerFactory(){};
};

class HWFactory : public ComputerFactory {
public:
    MainBoard* createMainBoard() override {
        return new HWMainBoard();
    }

    CPU* createCPU() override {
        return new HWCPU();
    }
};

class XMFactory : public ComputerFactory {
public:
    MainBoard* createMainBoard() override {
        return new XMMainBoard();
    }

    CPU* createCPU() override {
        return new XMCPU();
    }
};

int main(int argc, char* argv[]) {
    ComputerFactory* HWfatory = new HWFactory();
    ComputerFactory* XMfatory = new XMFactory();

    CPU* CPU = XMfatory->createCPU();
    MainBoard* MainBoard = XMfatory->createMainBoard();
    CPU->show();
    MainBoard->show();
    cout << endl;

    CPU = HWfatory->createCPU();
    MainBoard = HWfatory->createMainBoard();
    MainBoard->show();
    CPU->show();

    return 0;
}

