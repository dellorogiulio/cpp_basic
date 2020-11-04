/* 
 --- AUTO ---
		If a type can be determinate by the compiler, you can use the 'auto' keyword to say the compiler: "Hey, deduce the type here for me".      
*/

/*
	More info:
	https://www.youtube.com/watch?v=2vOPEuiGXVo&t=861s
*/
#include <vector>
#include <map>
#include <string>

int add(int, int)
{
    return 1;
}

float add(float, float)
{
    return 12.3;
}

int myFunction()
{
    int value = 1;
    auto another_value = value;  // another_value is an int.

    // you can use auto directly with a variable definition:
    auto int_value = 10;      // 10 is deduced to be an int here.
    auto float_value = 3.4f;  // indicating 'f' float_value is set to be a float

    // auto is useful when dealing with function return function
    auto int_result = add(value, 1);
    auto float_result = add(float_value, 2.3);
    return int_result;
}

// auto is useful when dealing with very long types, we will see this in class concepts,
// for now, take it as it is.

struct MyStruct
{
    std::vector<std::vector<std::map<unsigned int, std::string>>> something;  // no matter to understand this now, just look at the very long type name
};

void useMyStruct()
{
    // here we create a MyStruct instance
    MyStruct my_struct;

    // an now we want to access vector_of_vector_of_strings, maybe by const ref
    // we can declare the type explicitly:
    const std::vector<std::vector<std::map<unsigned int, std::string>>>& something = my_struct.something;
    // or use auto:
    const auto& something_other = my_struct.something;
}

int main()
{
    myFunction();
    useMyStruct();
}