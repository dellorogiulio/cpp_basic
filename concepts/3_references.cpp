/* 
 --- REFERENCES ---
		A reference is basically an alias to something something else.
		This involves two things:
		- a reference refers to something already existing
		- a reference cannot be declared without an initialization

		They are generally used when you want to pass an object without copying it; in this case
		in 99% of the case, the reference is indicated as const.
		
*/

/*
	More info:
	https://www.youtube.com/watch?v=IzoFn3dfsPA
*/

int function1()
{
    int value = 2;
    int& ref_to_value = value;  // ref_to_value is now an alias to value.
                                // this means that ref_to_value and value are the SAME thing.

    // THIS IS A COMPILE ERROR since a reference cannot be declared without an initialization
    // int& another_ref_to_value; -> 'another_ref_to_value' declared as reference but not initialized
    // another_ref_to_value = value;
    // this error should not be surprising: since a reference is just an alias, it cannot be declared without referencing to something

    ref_to_value = 4;  // now value is equal to 4. Since ref_to_value is an alias to value.

    // a const reference is useful when we want to "read" the variable value without modifying it.

    const int& const_ref_to_value = value;
    // THIS IS A COMPILE ERROR
    // const_ref_to_value = 5; -> assignment of read-only reference 'const_ref_to_value'

    return 0;
}

int function2(const int& const_ref_value)
{
    // Note: const_ref_value is an alias to everything is passed to function2.
    // In this case: when main calls function2(my_value), into function2, const_ref_value IS my_value but without the permission to modify it.
    if (const_ref_value > 8)
        return 2;
    return 1;
}

void function3(int& non_const_ref_value)
{
    // here non_const_ref_value can be edited and so the value of the passed argument can be modified
    non_const_ref_value = 33;
}

int& function4()
{
    // pay attention to not return reference to temporay variables! (i.e. dangling references)
    // Referring to a dangling reference is an UNDEFINED BEHAVIOR (Anything at all can happen; the Standard imposes no requirements,
    // The program may fail to compile, or it may execute incorrectly (either crashing or silently generating incorrect results),
    // or it may fortuitously do exactly what the programmer intended.).
    int i = 2;
    return i;  // in gcc this returns a warning and not a compile error:  warning: reference to local variable 'i' returned [-Wreturn-local-addr]
               // this is obviously wrong since the value of 'i' will be available no more once the stack of function4 is cleared.
}

int& function5()
{
    // You can istead return reference to variable that exists along all the program execution, such as static variable (static storage duration).
    // Pay attention: when you get a reference for a function, you are not in charge to control che life-time of the referenced object.
    static int always_present_value = 3;
    return always_present_value;
}

int main()
{
    function1();
    int my_value = 10;
    function2(my_value);
    function3(my_value);  // after this function call, my_value is 33
    int& unavailable_value = function4();  // reference to local here!
    int& available_value = function5();    // reference to variable with static storage duration (i.e. existing)

    // It is not (generally) possible to break the const rule:
    const int my_const_value = 12;
    // THIS IS A COMPILE ERROR
    // function3(my_const_value); ->  binding reference of type 'int&' to 'const int' discards qualifiers
    // we cannot pass a const int as a int&, because function3 CAN possible modify it.

    // References are useful when we don't want (or we can't) make a copy of an object or when we need to keep a reference to something that changes
}
