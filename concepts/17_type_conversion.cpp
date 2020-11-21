/* 
 --- TYPE CONVERSION ---

    In C++ some types are related to each other.
    When two types are related, we can use an object or value of one type where an operand of the related type
    is expected.
    Two types are related if there is a CONVERSION between them.

    Some of this conversions are used automatically by the compiler (without programmer intervention,
    and - sometimes - knowledge). They are called IMPLICIT CONVERSIONS (integer promotion to larger types,
    non-bool expressions to bool, C-style array to pointer, ...).

    Sometimes we want to explicitly force an object to be converted to a different type and so we use
    a CAST to request the explicit conversion.
    Although necessary at times, casts are inherently dangerous constructs and should be avoided
    as much as possible.

*/
#include <stdio.h>
#include <stdint.h>
#include <array>

namespace c_style_cast
{
/* C-Style type casting
    in C the only explicit conversion is through the CAST OPERATOR
    ( type-name ) expression
    where
    type-name 	- 	either the type void or any scalar type
    expression 	- 	any expression of scalar type (unless type-name is void, in which case it can be anything) 

    More info:
    https://en.cppreference.com/w/c/language/cast

    The cast operator allows you to do a lot of (potentially dangerous) conversions.
    The C philosophy is to avoid putting barriers in your way and to give you
    the responsibility of not abusing that freedom.
*/
void example()
{
    /* example of C-style cast operator */
    float f1 = 1.6;
    int a = (int)f1;   //floating point is converted to int, and precision is lost
    printf("C-style casting float %f to int returns %d\r\n", f1, a);

    float f2 = 100000.5;
    short b = (short)f2; // the real part of the floating point doesn't fit into short 
    printf("C-style casting float %f to short returns %hd\r\n", f2, b);  
    short b2 = (short)100000.500000; // the real part of the floating point doesn't fit into short 
    printf("C-style casting float 100000.500000 to short returns %hd\r\n", b2); 
                            // When a finite value of real floating type is converted to an integer type
                            // other than _Bool, the fractional part is discarded (i.e., the value is truncated toward zero).
                            // If the value of the integral part cannot be represented by the integer type,
                            // the behavior is UNDEFINED.
    
    int c = 100000;
    short d = (short)c;     // the int value doesn't fit into a short object
    printf("C-style casting int %d to short returns %hd\r\n", c, d);
}
}   // c_style_cast end

/* C++ type casting
    C++ offers some different named casting operators, with the following syntax:
    cast-name<type-name>(expression)
    Cast-name may be one of the following:
    - static_cast
    - reinterpret_cast
    - dynamic_cast
*/

namespace cpp_static_cast
{
/* Any well-defined type conversion can be requested using a static_cast.
    This conversion can be checked and done at compile time, using a combination
    of implicit and user-defined conversions.
    If a type conversion doen't exists, the compiler gives a compile error,
    and so it's a little bit safer than C-style cast.

    More info:
    https://en.cppreference.com/w/cpp/language/static_cast
*/

class Base { 
}; 

class Derived : private Base { // Inherited private/protected not public 
}; 

void example()
{


    float f1 = 1.6;
    int a = static_cast<int>(f1);   //floating point is converted to int, and precision is lost
    printf("C++ static_cast<int>(%f) returns %d\r\n", f1, a);

    double d;
    void* p = &d;
    double* dp = static_cast<double*>(p);   //ok: converts void* back to the original pointer type
 
    char c = 'a'; 
    int* q1 = (int*)&c;  // C-style cast passes at compile time, may fail at run time 
    //int* q2 = static_cast<int*>(&c);  // compile error: invalid 'static_cast' from type 'char*' to type 'int*'

    Derived d1; 
    Base* b1 = (Base*)(&d1); // C-style cast is allowed 
    //Base* b2 = static_cast<Base*>(&d1); // compile error: 'Base' is an inaccessible base of 'Derived'
}
}   // cpp_static_cast end

namespace cpp_reinterpret_cast
{
/* reinterpret_cast converts between types by reinterpreting the underlying bit pattern.
    reinterpret_cast<newType>(expression)
    It does not compile to any CPU instructions. It is purely a compile-time directive
    which instructs the compiler to treat expression as if it had the type newType. 
    A reinterpret_cast is inherently machine dependent. Safely using reinterpret_cast
    requires completely understanding the types involved as well as the details of how
    the compiler implements the cast.

    More info:
    https://en.cppreference.com/w/cpp/language/reinterpret_cast
*/

struct MyData {
    MyData() : m(42) {}
    uint32_t m;
};

using VendorOpaqueData = std::array<uint8_t, 4>;

void vendorSendData(const VendorOpaqueData* p) { /* magic stuff */ }
VendorOpaqueData vendorGetData() { return VendorOpaqueData(); }

void example()
{
    /* The only scenario when reinterpret_cast should be used is when interfacing with opaque data types.
        This occurs frequently in vendor APIs over which the programmer has no control.
        The same scenario occurs when you want to handle in C++ some buffers with raw data, sent (or received) as a raw
        array of bytes (old-style communication API between devices).
        Another use case of "opaque" data types is when you want to expose an API to C but write the implementation in C++.
    */

    // send data
    MyData data_to_send;
    VendorOpaqueData* d1;
    //d1 = &data_to_send;                                     // compile error
    //d1 = static_cast<VendorOpaqueData*>(&data_to_send);     // compile error
    d1 = reinterpret_cast<VendorOpaqueData*>(&data_to_send);  // ok
    vendorSendData(d1);

    // do other stuff...

    // retrieve data
    VendorOpaqueData d2 = vendorGetData();
    MyData received_data;
    //received_data = d2;                                   // compile error
    //received_data = *static_cast<MyData*>(&d2);           // compile error
    received_data = *reinterpret_cast<MyData*>(&d2);        // ok

}
}   // cpp_reinterpret_cast end

namespace cpp_dynamic_cast
{
/* dynamic_cast is one of the way to get Run-Time Type Identification (RTTI), that is
    the possibility to explicitly query for the type of an object during program execution
    (at run-time).
    RTTI can be completely disabled with a compilation flag, since it has some huge performance
    drawbacks on embedded platforms.

    dynamic_cast safely converts a POINTER or a REFERENCE to a base type into a pointer or
    a reference to a derived type (when possible).
    dynamic_cast<type*>(e)  - if the conversion is not possible, it returns nullptr
    dynamic_cast<type&>(e)  - if the conversion is not possible, it throws std::bad_cast exception
    dynamic_cast<type&&>(e) - if the conversion is not possible, it throws std::bad_cast exception
    It's useful when we have a method in the derived class only and we want to call it through
    a pointer (or reference) to a base class.
    It should be used carefully. When possible, it's better to define a virtual function
    in the base class, rather than managing the types directly with dynamic_cast
*/

struct Base
{
    virtual void doSomething() { printf("Base::doSomething()\r\n"); }
};

struct Derived : public Base
{
    void doSomething() { printf("Derived::doSomething()\r\n"); }
    void doSomethingSpecial() { printf("Derived::doSomethingSpecial()\r\n"); }
};

void doEverythingYouCan(Base* b)
{
    b->doSomething();   // the proper doSomething() is called automatically, since it's virtual
    //b->doSomethingSpecial();    // compile error, since 'Base' doesn't have doSomethingSpecial()
    // I need a way to call doSomethingSpecial() only if I pass a 'Derived*' 
    if (Derived* d = dynamic_cast<Derived*>(b))
    {   // use the 'Derived' object to which d points
        d->doSomethingSpecial();
    }
}

void example()
{
    Base b;
    doEverythingYouCan(&b);

    Derived d;
    doEverythingYouCan(&d);
}
}   // cpp_dynamic_cast

int main()
{
    c_style_cast::example();

    cpp_static_cast::example();
    cpp_reinterpret_cast::example();
    cpp_dynamic_cast::example();
}

/*  DISCLAIMER
    Casts interfere with normal C++ type checking.
    As a result, we strongly recommend to avoid casts.
    This advice is particularly applicable to reinterpret_cast (they are always hazardous).
    Every time you write a cast, you should think hard about whether you can get the same result
    in a different way.
*/
