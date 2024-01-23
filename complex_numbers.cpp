#include <iostream>
#include <cmath>
#include <stdexcept>

class Complex {
    private:
        float real, imag;

    public:
        Complex(float r = 0, float i = 0) {
            real = r;
            imag = i;
        }

        float get_real() const {
            return real;
        }

        float get_imag() const {
            return imag;
        }
        
        void set_real(float re) {
            real = re;
        }

        void set_imag(float im) {
            imag = im;
        }

        bool operator== (Complex const &other) const {
            return real == other.real && imag == other.imag;
        }

        bool operator== (float x) const {
            return real == x && imag == 0;
        }

        float absolute_value() const {
            return std::sqrt(real * real + imag * imag);
        }

        float norm() const {
            return real * real + imag * imag;
        }

        Complex operator+ (Complex const &other) const {
            Complex res;
            res.real = real + other.real;
            res.imag = imag + other.imag;
            return res;
        }

        Complex operator- (Complex const &other) const {
            Complex res;
            res.real = real - other.real;
            res.imag = imag - other.imag;
            return res;
        }

        Complex operator* (Complex const &other) const {
            Complex res;
            res.real = real * other.real - imag * other.imag;
            res.imag = real * other.imag + imag * other.real;
            return res;
        }

        Complex operator* (float x) const {
            return Complex(real * x, imag * x);
        }

        Complex operator/ (float x) const {
            if (x == 0)
                throw std::runtime_error("Trying to divide by zero");
            return Complex(real / x, imag / x);
        }

        Complex conjugate() const {
            return Complex(real, -imag);
        }

        Complex operator/ (Complex const &other) const {
            Complex res;
            if (other == Complex(0, 0))
                throw std::runtime_error("Trying to divide by zero");
            res = Complex(real, imag) * other.conjugate() / other.norm();
            return res;
        }

        Complex operator^ (int n) const {
            float r = absolute_value();
            float im = imag / r;
            float phi = std::asin(im);
            float new_phi = n * phi;
            return Complex(std::cos(new_phi), std::sin(new_phi)) * pow(r, n);
        }
};

std::ostream& operator<< (std::ostream &os, Complex const &obj) {
    return os << obj.get_real() << (obj.get_imag() >= 0 ? "+" : "") << obj.get_imag() << 'i';
}

int main() {
    Complex num1(1, 2), num2(3, 4);
    std::cout << (num1 + num2) << '\n';
    Complex num_to_power(3, 4);
    std::cout << (num_to_power ^ 3) << '\n';
    Complex num_to_get_abs(5, 12);
    std::cout << num_to_get_abs.absolute_value() << '\n';
    Complex mul1(1, 2), mul2(5, 6);
    std::cout << (mul1 * mul2) << '\n';
    Complex divided(2, 3), divider(3, 4);
    std::cout << (divided / divider) << '\n';
    return 0;
}

