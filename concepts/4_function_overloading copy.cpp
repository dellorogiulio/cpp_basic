/* 
 --- FUNCTION OVERLOADING ---
		In C++ you can declare functions overloading. As a matter of fact, in C, the signature of the function is simply its name.
        In C++, instead, the function's signature contains also ALL its arguments type. This allows the user to define functions
        with the same name which take different arguments.
*/

/*
	More info:
	https://www.youtube.com/watch?v=V9zuox47zr0
*/

int function()
{
    return 0;
}

int function(int)
{
    return 1;
}
// there is no ambiguity in function() and function(int)

/*  Function overloading is useful to keep concept clean. Consider the case in which we want to sum two variables.
    We don't care which is the type of the variables, we simply want to sum them
*/
long add(long, long)
{
    return 45;
}

float add(float, float)
{
    return 12.4;
}

int add(int, int)
{
    return 7;
}

/*  In C, all these functions will be probably declaired as addl (for long), addf (for floats), etc.
    In C++ we can have the same function name.
*/

void functionOverloading()
{
    int no_parameters = function();   // no_parameters is equal to 0
    int int_parameter = function(1);  // int_parameter is equal to 1

    long l1 = 1;
    long l2 = 2;
    long l3 = add(l1, l2);  // l3 is equal to 45

    float f1 = 1.2;
    float f2 = 2.1;
    auto f3 = add(f1, f2);  // f3 is equal to 12.4

    int i1 = 2;
    int i2 = 1;
    auto i3 = add(i1, i2);  // i3 is equal to 7
}

/*
    In C++ is possible to use one or more 'default argument'. This means that one it's allowd to call a function without 
    providing one or more arguments.
    See the example below:
*/

int sum1(int n1, int n2)
{
    return n1 + n2;
}

void callSum1()
{
    // if we want to call sum1, we need to provide it two arguments
    int r1 = sum1(1, 2);  // r1 is equal to 3
    // nothing surprising here...
}

int sum2(int n1, int n2, int n3 = 0)
{
    return n1 + n2 + n3;
}

void callSum2()
{
    // we can call sum2 with three arguments
    int r1 = sum2(1, 2, 3);  // r1 is equal to 6
    // but we can call sum2 with two parameters too
    int r2 = sum2(1, 2);  // r2 is equal to 3 since n3 is defaulted to 0!
}

/*
    a default arguments can only be followed by other default arguments; in other words, isn't possible to declare 
    something like this:

    int sum3(int n1, int n2 = 0, int n3)
    {
        ...
    }

    because n2 has a default value but n3 doesn't
*/

void defaultArguments()
{
    callSum1();
    callSum2();
}

int main()
{
    functionOverloading();
    defaultArguments();
}
