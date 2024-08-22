#include <iostream>
using std::cout;
using std::endl;

class Complex {
public:
    Complex(int x = 0, int y = 0)
        : _real(x),
          _imag(y)
    {}

    friend Complex operator+(const Complex&, const Complex&);
    friend Complex operator-(const Complex&, const Complex&);
    friend std::ostream& operator<<(std::ostream&, const Complex&);

    Complex& operator+=(const Complex& rhs) {
        _real += rhs._real;
        _imag += rhs._imag;
        return *this;
    }

    Complex& operator-=(const Complex& rhs) {
        _real -= rhs._real;
        _imag -= rhs._imag;
        return *this;
    }

    Complex& operator++() {
        ++_real;
        ++_imag;
        return *this;
    }

    Complex& operator--() {
        --_real;
        --_imag;
        return *this;
    }

    Complex operator++(int) {
        Complex complex(*this);
        ++_real;
        ++_imag;
        return complex;
    }

    Complex operator--(int) {
        Complex complex(*this);
        --_real;
        --_imag;
        return complex;
    }

private:
    int _real;
    int _imag;
};

Complex operator+(const Complex& lhs, const Complex& rhs) {
    /* Complex complex; */
    /* complex._real = lhs._real + rhs._real; */
    /* complex._imag = lhs._imag + rhs._imag; */
    /* return complex; */
    return Complex(lhs._real + rhs._real, lhs._imag + lhs._imag);
}

Complex operator-(const Complex& lhs, const Complex& rhs) {
    /* Complex complex; */
    /* complex._real = lhs._real - rhs._real; */
    /* complex._imag = lhs._imag - rhs._imag; */
    /* return complex; */
    return Complex(lhs._real - rhs._real, lhs._imag - lhs._imag);
}

std::ostream& operator<<(std::ostream& os, const Complex& rhs) {
    os << rhs._real << " + " << rhs._imag << "i";    
    return os;
}

int main(int argc, char* argv[]) {
    Complex cpl(0,0);
    Complex cpl2(1,1);

    cout << "cpl = " << cpl << endl;
    cout << "cpl2 = " << cpl2 << endl;

    // operator +
    cout << "cpl + cpl2" << endl;
    cout << cpl + cpl2 << endl << endl;
    
    // operator -
    cout << "cpl - cpl2" << endl;
    cout << cpl - cpl2 << endl << endl;

    // operator +=
    cout << "cpl += cpl2" << endl;
    cpl += cpl2;
    cout <<  cpl << endl << endl;

    // operator -=
    cout << "cpl -= cpl2" << endl;
    cpl -= cpl2;
    cout <<  cpl << endl << endl;
    
    // operator ++
    cout << "cpl++" << endl;
    cout << ++cpl << endl;
    cout <<  cpl << endl << endl;
    
    // operator --
    cout << "cpl--" << endl;
    cout << --cpl << endl;
    cout <<  cpl << endl << endl;
    
    // operator 后++
    cout << "cpl++" << endl;
    cout << ++cpl << endl;
    cout <<  cpl << endl << endl;
    
    // operator 后--
    cout << "cpl--" << endl;
    cout << --cpl << endl;
    cout <<  cpl << endl << endl;
    
    return 0;
}

