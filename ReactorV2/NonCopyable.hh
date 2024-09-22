#ifndef __NonCopyable_H__
#define __NonCopyable_H__

class NonCopyable {
protected:
    NonCopyable() {}
    ~NonCopyable() {}

private:
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
};

#endif

