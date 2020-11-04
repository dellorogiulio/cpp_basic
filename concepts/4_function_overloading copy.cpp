/* 
 --- FUNCTION OVERLOADING ---
		In C++ you can declare functions overloading. In C infact, the signature of the function is simply its name.
        In C++, instead, the function's signature contains also the arguments type. This allows the user to define functions
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

int main()
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