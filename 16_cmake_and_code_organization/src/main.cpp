#include <iostream>

// here we include the header file
#include <my_class.h>

int main()
{
    MyClass my_class(3);
    std::cout << "Value is: " << my_class.value() << "\n";
    return 0;
}
