/* 
 --- EXCEPTIONS ---
		Exceptions are a method to handle errors in modern languages.
        The fundamental idea is to throw an error (aka, an exception), when something goes wrong.
	An Exception Handling System (EHS) is the set of resources responsible to have exceptions working.
*/

/*
	More info:
	https://www.youtube.com/watch?v=EyXXLpFriMc
*/

// consider the example below: we compare the C function atoi to the C++ stoi

/* C-Style error handling
    in C the error is generally handled by the return value. 
    The reference page of std::atoi is quite explicative: https://en.cppreference.com/w/cpp/string/byte/atoi
    "Return value: Integer value corresponding to the contents of str on success.
    If the converted value falls out of range of corresponding return type,
    the return value is undefined.
    If no conversion can be performed, ​0​ is returned."

    We can see that two errors can occur: 
    1) no conversion can be performed -> return 0
    2) if the converted value is out of range of the return type -> undefined behaviour

    The first error can be handled by checking if the return type is 0, while the second one can only be 
    garanteed by the input data.
*/

/* C++Style error handling
    C++ offers an Exception Handling System (EHS) and so errors are handled by throwing and exception (we will see later what this mean).
    The atoi reference page (https://en.cppreference.com/w/cpp/string/basic_string/stol) reports:
    "Return value: Integer value corresponding to the content of str.
    Exceptions: std::invalid_argument if no conversion could be performed
                std::out_of_range if the converted value would fall out of the range of the result type or if the underlying function
                (std::strtol or std::strtoll) sets errno to ERANGE."


    The possible errors are the same as before: no conversion and out of range.
    Now we can see that the return value is the "correct" value only; there is no 0 return value and no undefined behaviour.
    These cases are instead reported by the exceptions.
*/

#include <string>
#include <stdio.h>
#include <stdexcept>

// now we can see how an exception works
void canThrowFunction()
{
    // when a function can throw and exception and we want to handle it, we need to use the try/catch blocks:
    try  // this "say" to the compiler: everthing inside the try block can potentially throw an exception
    {
    }
    // the 'catch' scope catches the exception thrown in the 'try', if any.
    // the 'catch' function needs to know which type (or "family") of exception it has to catch
    catch (const std::invalid_argument& e)  // this means: catch all exceptions which are "invalid_argument exception"
    {
    }
}
/* 
    https://en.cppreference.com/w/cpp/error/exception reports all the standard exceptions. 
    
    As you can see, a variety of exception 'families' exist: logic_error, runtime_error, bad_cast, etc..
    Each family has its own specific error; the 'logic_error' for example can be: invalid_argument, domain_error, length_error, etc.

    In a catch block, you can specify a general family (ex: std::logic_error), a specific type (ex: std::invalid_argument) or
    a generic exception (std::exception). In case way, it is possible to decide which errors handle and in which way. 
    Consider the example below:
*/

void handledStoi(const std::string& string_value)
{
    try
    {
        auto value = std::stoi(string_value);
        printf("Everything ok: %d\n", value);
    }
    catch (const std::invalid_argument& e)
    {
        // we fall here if string_value cannot be converted to a number
        puts("Invalid argument");
    }
    // you can declare more than one catch block, specifying an exception type/family for each one.
    catch (const std::out_of_range& e)
    {
        // we fall here if string_value can be converted to a number but overflows an int
        puts("Out of range");
    }
}

void callHandledStoi()
{
    handledStoi("123");
    handledStoi("ciao");                      // -> invalid_argument
    handledStoi("987665455255325235523532");  // -> out_of_range

    /* Outputs:
        Everything ok: 123
        Invalid argument
        Out of range
    */
}

// keep in mind that the order of the catch blocks is important!
// consider the example below:

void wrongOrderCatch()
{
    try
    {
        // of course we can directly throw and exception by using the keyword 'throw'
        throw std::invalid_argument("this will be caught by the std::exception block!");
    }
    //  since the "more generic" std::exception block is declared before the std::invalid_argument,
    //  that block will caught the exception!
    catch (std::exception e)
    {
        puts("generic");
    }
    // this catch will be the "correct" block, but since it is declared after the std::exception block, will catch nothing!
    catch (std::invalid_argument e)
    {
        puts("invalid");
    }

    /*
    NOTE:   this generally implies a compile warning:
            exception of type 'std::invalid_argument' will be caught
            by earlier handler for 'std::exception' 
    */
}

void callWrongOrderCatch()
{
    wrongOrderCatch();
    // Outputs:
    //    generic
}

int main()
{
    callHandledStoi();
    callWrongOrderCatch();
}
