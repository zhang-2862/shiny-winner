#include <iostream>
#include <string>

using namespace std;

template<class T = int, int kCapacity = 10>
class Stack {
public:
    Stack()
        : top_(-1)
    {
        stack_ = new T[kCapacity]();
    }

    ~Stack() {
        if (stack_) {
            delete[] stack_;
            stack_ = nullptr;
        }
    }

    bool IsEmpty() {
       return top_ == -1;        
    }

    bool IsFull() {
        return top_ == kCapacity - 1;
    }

    void Push(const T& ele) {
        if (!IsFull()) {
            stack_[++top_] = ele;
        } else {
            cout << "stack is full now!" << endl;
        }
    }

    void Pop() {
        if (!IsEmpty()) {
            --top_;
        } else {
            cout << "stack is empty now!" << endl;
        }
    }

    T Peek() {
        if (!IsEmpty()) {
            return stack_[top_];
        } else {
            throw "stack is empty!"; 
        }
    }

    size_t Size() {
        return top_ + 1;
    }

private:
    T* stack_;
    int top_;
};

int main(int argc, char* argv[]) {
    Stack<string> s;
    if (s.IsEmpty()) {
        cout << "stack is empty" << endl;
    }

    s.Push("hello, world");
    s.Push("hello, new world");
    s.Push("bye, old world");

    string str = s.Peek();
    cout << str << endl;

    for (int i = 0; i < 3; ++i) {
        string temp = s.Peek();
        s.Pop();
        cout << temp << endl;
        cout << "stack's size: " << s.Size() << endl;
    }


    if (s.IsEmpty()) {
        cout << "stack is empty" << endl;
    }
    
    return 0;
}

