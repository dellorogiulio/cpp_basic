/* 
 --- CLASSES PART 5 ---	
*/
#include <string>
#include <stdio.h>
#include <cmath>
#include <cassert>

/*
    OPERATORS 
    in this last episode on classes we will see operators.
    Operators allows us to define all the well-known operators such as =, ==, !=, +, - and so on.
    See https://en.cppreference.com/w/cpp/language/operators
*/
/* 
    More info:
    https://www.youtube.com/watch?v=mS9755gF66w
 */

/*  we want to model a complex number: 1 + 3i */
/*
    the Complex class has to provide:
    - real part by a 'double real()' method
    - imaginary part by a 'double imag()' method
    - module by 'double abs()'
    - phase by 'double phase()'
    - conjugate by a 'Complex conj()' 
    - all typical mathematic operation must be available:
        - multiplication/division by scalar
        - addition/subtraction between Complex
        - multiplication/division between Complex
    - we must be able to check if two Complex are equals

*/
class Complex
{
    double real_;
    double imag_;

   public:
    Complex(double real, double imag) :
        real_(real),
        imag_(imag)
    {
    }

    Complex(const Complex& other) :
        real_(other.real_),
        imag_(other.imag_)
    {
        // copy constructor
    }

    Complex& operator=(const Complex& other)
    {
        // copy assignment operator
        if (this != &other)
        {
            real_ = other.real_;
            imag_ = other.imag_;
        }
        return *this;
    }

    /*  methods that we expect from a complex number */
    double real() const { return real_; }
    double imag() const { return imag_; }
    double abs() const { return std::sqrt(real() * real() + imag() * imag()); }
    double phase() const { return std::atan2(imag(), real()); }
    Complex conj() const { return Complex(real(), -imag()); }

    /* now we want to be able to say complex_1 + complex_2, how to do that? */

    Complex operator+(const Complex& other) const  // we can simply define an operator+ which takes another complex!
    {
        return Complex(real_ + other.real(), imag_ + other.imag());
    }

    Complex operator-(const Complex& other) const  // we can simply define an operator- which takes another complex!
    {
        return Complex(real_ - other.real(), imag_ - other.imag());
    }

    Complex operator*(double value) const  // multiplication by scalar
    {
        return Complex(real_ * value, imag_ * value);
    }

    Complex operator/(double value) const  // division by scalar
    {
        return Complex(real_ / value, imag_ / value);
    }

    Complex operator*(const Complex& other) const
    {
        return Complex(real() * other.real() - imag() * other.imag(),
                       real() * other.imag() + imag() * other.real());
    }

    Complex operator/(const Complex& other) const
    {
        return ((*this) * other.conj()) / (other.abs() * other.abs());
    }

    bool operator==(const Complex& other) const
    {
        return real_ == other.real() &&
               imag_ == other.imag();
        // maybe == on double type is not a good idea, but it's an example...
    }

    bool operator!=(const Complex other) const
    {
        return !(*this == other);
    }
};

void printComplex(const std::string& title, const Complex& c)
{
    c.imag() >= 0 ? printf("%s: %3.2f+%3.2fi\n", title.c_str(), c.real(), c.imag())
                  : printf("%s: %3.2f%3.2fi\n", title.c_str(), c.real(), c.imag());
}

int main()
{
    Complex c1(1, 2);
    Complex c2(2, 3);
    Complex sum = c1 + c2;
    Complex difference = c1 - c2;
    Complex multiply = c1 * c2;
    Complex divison = c1 / c2;

    Complex difference_test(-1, -1);
    Complex multiply_test(-4, 7);
    Complex divison_test(8.0 / 13.0, 1.0 / 13.0);
    assert(difference_test == difference);
    assert(multiply_test == multiply);
    assert(divison_test == divison);

    c1 = c2;
    if (c1 != c2)
    {
        puts("c1 and c2 should be the same");
        return -1;
    }

    printComplex("sum", sum);
    printComplex("difference", difference);
    printComplex("multiply", multiply);
    printComplex("divison", divison);
}
