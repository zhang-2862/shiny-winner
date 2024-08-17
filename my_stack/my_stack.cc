#include <iostream>
using std::cout;
using std::endl;

class Stack {
public:
	bool empty();	//判断栈是否为空
	bool full();	//判断栈是否已满
	void push(int); //元素入栈
	void pop();     //元素出栈
	int  top();		//获取栈顶元素
    Stack(int size);
    ~Stack();
                    
private:
    int _size;
    int _eleNums;
    int* _pStack;
    int* _pTop; // 始终指向下一个元素填放的位置
};

Stack::Stack(int size)
    :_size(size),
    _eleNums(0),
    _pStack(nullptr),
    _pTop(nullptr)
{
    _pStack = new int[size + 1](); //空出一个位置用来给_pTop指针在栈满时往后指
    _pTop = _pStack;
}

Stack::~Stack() {
    if (_pStack != nullptr) {
        delete[] _pStack;
    }
}

bool Stack::empty() {
    return _eleNums == 0;
}

bool Stack::full() {
    return _eleNums == _size;
}

void Stack::push(int ele) {
    if (!full()) {
        *_pTop = ele;
        _eleNums++;
        _pTop++;
    }
}

void Stack::pop() {
    if (!empty()) {
        _pTop--;
        _eleNums--;
    }
}

int Stack::top() {
    if (!empty()) {
        int* cur = _pTop;
        return *(cur--);
    }
    return -1;
}


int main(int argc, char* argv[]) {
    Stack s(5);
    if (s.empty()) {
        cout << "s is empty" << endl;
    }

    // 往栈中填充元素
    cout << "往栈中填充元素" << endl;
    for (int i = 0; i < 5; ++i) {
        s.push(i);
    }

    if (s.full()) {
        cout << "s is full" << endl;
    }

    // 出栈
    cout << "出栈" << endl;
    s.pop();

    // 查看栈顶元素
    cout << "查看栈顶元素" << endl;
    cout << s.top() << endl;

    // 打印栈中所有元素
    cout << "打印栈中所有元素" << endl;
    while (!s.empty()) {
        cout << s.top() << endl;
        s.pop();
    }
    
    return 0;
}

