#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::allocator;

template<typename T>
class Vector {
public:
    Vector()
        : start_(nullptr),
          finish_(nullptr),
          end_of_storage_(nullptr)
    {}

    // TODO 内存泄露问题
    ~Vector()
    {
        if (start_) {
            // 销毁对象
            for (; start_ != finish_;) {
                alloc_.destroy(--finish_);
            }
            // 释放空间
            alloc_.deallocate(start_, end_of_storage_ - start_);
        }
        cout << "~Vector" << endl;
    }

    void push_back(const T& x) {
        // 当容量为零，大小为0时
        if (end_of_storage_ - start_ == 0) {
            // 申请空间，并更新指针指向
            start_ = alloc_.allocate(1);
            finish_ = start_ + 1;
            end_of_storage_ = start_ + 1;

            // 构建对象
            alloc_.construct(start_, x);
        } else if (end_of_storage_ - finish_ > 0) {
            // 还有剩余空间
            alloc_.construct(finish_, x);
            ++finish_;
        } else {
            // 没有剩余空间
            reallocate();// 重新分配空间

            alloc_.construct(finish_, x);
            ++finish_;
        }
    }

    void pop_back() {
        if (size() > 0) {
            --finish_;
            alloc_.destroy(finish_);
        }
    }

    int size() {
        return finish_ - start_;
    }

    int capacity() {
        return end_of_storage_ - start_;
    }

    T* begin() {
        return start_;
    }

    T* end() {
        return finish_;
    }

private:
    void reallocate() {
        int old_size = size();
        T* temp = alloc_.allocate(old_size * 2); //空间大小翻倍
        /* T* travl = temp;// 用来遍历空间 */

        // 将原来的元素复制到新的空间上
        /* for (;start_ != finish_; ++start_) { */
        /*     T val = *start_; */
        /*     alloc_.construct(travl++, val); */
        /* } */
        std::uninitialized_copy(start_, finish_, temp);
        // 将旧空间上的对象销毁以及回收空间
        while (start_ != finish_) {
            alloc_.destroy(--finish_);
        }
        alloc_.deallocate(start_, old_size);
        // 更新指针指向
        start_ = temp;
        finish_ = temp + old_size;
        end_of_storage_ = start_ + old_size * 2;
    }

private:
    static allocator<T> alloc_;
    T* start_;
    T* finish_;
    T* end_of_storage_;
};

template<typename T>
allocator<T> Vector<T>::alloc_;


int main(int argc, char* argv[]) {
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);

    cout << vec.capacity() << endl;
    cout << vec.size() << endl;

    auto it = vec.begin();
    for (; it != vec.end(); ++it) {
        cout << *it << endl;
    }

    vec.pop_back();
    vec.pop_back();

    for (auto& e : vec) {
        cout << e << endl;
    }

    cout << vec.capacity() << endl;
    cout << vec.size() << endl;

    return 0;
}

