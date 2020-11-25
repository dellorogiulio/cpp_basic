/* 
 --- TEMPLATES ---	
*/
/*
    'Function templates are special functions that can operate with generic types.
	This allows us to create a function template whose functionality can be adapted to more than one type or class
	without repeating the entire code for each type.' [https://www.cplusplus.com/doc/oldtutorial/templates/]
*/

#include <vector>
#include <map>
#include <array>
#include <cassert>
#include <iostream>

/* 
	We can start from the add functions of the 4th concept (function_overloading) and adjust
	them to return the correct value
*/

namespace non_template
{
long add(long l1, long l2)
{
    std::cout << "add(long,long)\n";
    return l1 + l2;
}

float add(float f1, float f2)
{
    std::cout << "add(float,float)\n";
    return f1 + f2;
}

int add(int i1, int i2)
{
    std::cout << "add(int,int)\n";
    return i1 + i2;
}
}  // namespace non_template

// Now we have 3 functions, with different signatures, which add the first argument to the second

/*
	At the end of the day, we just want to take two variable of the same type and sum them. In other words we would like
	to have something like this:

	T add(T t1, T t2)
	{
		return t1+t2;
	}

	with T of every type.

	Cpp allows us to do that in a simple way:
*/

template <typename T>  // here we are saying: "it doesn't matter which type T is, if you can sum two T, sum them!"
T add(T t1, T t2)
{
    std::cout << "add(T,T)\n";
    return t1 + t2;
}

void useAddFunctions()
{
    float f1 = 1.2;
    float f2 = 3.4;
    float added_f = non_template::add(f1, f2);  // prints 'add(float,float)'
    float added_f2 = add<float>(f1, f2);        // prints 'add(T,T)'
    assert(added_f == added_f2);
    /*
		The add<float> syntax means 'call add with T=float' with is exactly the same as 
		non_template::add(float, float);
	*/

    double d1 = 1245.9;
    double d2 = 4321.6;
    // THIS IS A COMPILER ERROR
    //double added_d = non_template::add(d1, d2);  -> call of overloaded 'add(double&, double&)' is ambiguous
    double added_d2 = add<double>(d1, d2);
    /*
		In this case the compiler is not able to understand which function call in the non_template namespace
		since there is no non_template::add(double, double)!
		The template add<double> works instead as expected!
	*/
}

/*
	Templates are not limited on functions. They can work on classes too:
*/

template <typename T>
class Foo
{
    T value_;

   public:
    T value() const { return value_; }
};

/*
	Foo is a template class which has a T attribute value_ and a method value which returns a T too!
	But how templates work?
	Behind the scenes, templates are just 'suggestions' for the compiler: once the compiler finds a declaration of
	Foo<int> (and only at this point!) it 'reads' the template class/function substituting T with the given type! Once it
	has written the declaration of Foo<int>, it tryies to compile it. If all class and methods are fine with the given T, 
	the compilation ends correctly.
*/

// we can define more than one template

template <typename T, typename S>
struct Bar
{
    T value1;
    S value2;
};

// Bar is a template class in which value1 is of type T and value2 of type S!

void useClassTemplate()
{
    Foo<int> foo_int;
    int value_i = foo_int.value();  // value_ of foo_int is an int!

    Foo<double> foo_d;
    double value_d = foo_d.value();  // value_ of foo_d is a double instead!

    /*
		keep in mind that every Foo<something> is a DIFFERENT CLASS from Foo<SomethingElse>!
		Foo<int> and Foo<double> are two complete different class which has nothing in common!
    	We cannot do something like
			foo_d = foo_i; 
	*/

    Bar<int, double> bar;
    int bar_value1 = bar.value1;     // value1 is of type int
    double bar_value2 = bar.value2;  // value2 is a double
}

void stdContainers()
{
    std::vector<int> vector_of_int{1, 2, 3, 4, 5};                  // Now we can understand what vector<int> means! It's a templated class!
    std::map<std::string, int> my_map{{"hello", 1}, {"world", 2}};  // map is template class with two templates: the key type and the value type
}

/*
	Templates are useful when we need a repetitive pattern on function or templates which applyies to different types!
*/

void useAddFunctionsAgain()
{
    /*
		What happens when the compiler has to choose between 'writing' a template or using an existing function?
		In other words, what 'add' function is called in this case?
 	*/
    using namespace non_template;
    int result = add(2, 3);  // prints 'add(int, int)'

    // if exists a non-template function which fits the needed signature, the compiler always prefers them agains templated version
}

int main()
{
    useAddFunctions();
    useClassTemplate();
    stdContainers();
    useAddFunctionsAgain();
}