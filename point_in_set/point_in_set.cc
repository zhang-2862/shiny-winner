#include <cmath>
#include <iostream>
#include <set>

using std::cout;
using std::endl;
using std::set;

class Point {
    friend std::ostream& operator<<(std::ostream& os, const Point& rhs);
    friend bool operator<(const Point& lhs, const Point& rhs);
    friend struct ComparePoint;
    friend struct std::less<Point>;

public:
    Point(int ix, int iy)
        : ix_(ix),
          iy_(iy)
    {}

private:
    int ix_;
    int iy_;
};

std::ostream& operator<<(std::ostream& os, const Point& rhs) {
    os << "(" << rhs.ix_
       << ", "<< rhs.iy_
       << ")" << endl;
    return os;
}

// 方式一 重载operator<
bool operator<(const Point& lhs, const Point& rhs) {
    cout << "operator <" << endl;

    double l_hypot = hypot(lhs.ix_, lhs.iy_);
    double r_hypot = hypot(rhs.ix_, rhs.iy_);
    if (l_hypot != r_hypot) {
        return l_hypot < r_hypot;
    } else if (lhs.ix_ != rhs.ix_){
        return lhs.ix_ < rhs.ix_;
    } else {
        return lhs.iy_ < rhs.iy_;
    }
}

// 方式二 函数对象
struct ComparePoint {
    bool operator()(const Point& lhs, const Point& rhs) const {
        cout << "sturct ComparePoint" << endl;
        double l_hypot = hypot(lhs.ix_, lhs.iy_);
        double r_hypot = hypot(rhs.ix_, rhs.iy_);
        if (l_hypot != r_hypot) {
            return l_hypot < r_hypot;
        } else if (lhs.ix_ != rhs.ix_){
            return lhs.ix_ < rhs.ix_;
        } else {
            return lhs.iy_ < rhs.iy_;
        }
    }
};

// 方式三 模板特化
namespace std
{
template<>
    struct less<Point>
{
    bool operator()(const Point& lhs, const Point& rhs) const {
        cout << "template<> struct less<Point> operator()" << endl;
        double l_hypot = hypot(lhs.ix_, lhs.iy_);
        double r_hypot = hypot(rhs.ix_, rhs.iy_);
        if (l_hypot != r_hypot) {
            return l_hypot < r_hypot;
        } else if (lhs.ix_ != rhs.ix_){
            return lhs.ix_ < rhs.ix_;
        } else {
            return lhs.iy_ < rhs.iy_;
        }
    }
};
}// end of namespace std

int main(int argc, char* argv[]) {
    Point p1(-5,3);
    Point p2(3,3);
    Point p3(-5,-3);
    Point p4(2,-4);
    Point p5(8,6);

    set<Point> s_point;
    s_point.insert(p1);
    s_point.insert(p2);
    s_point.insert(p3);
    s_point.insert(p4);
    s_point.insert(p5);


    for (const auto& e : s_point) {
        cout << e;
    }
    cout << endl;

    return 0;
}

