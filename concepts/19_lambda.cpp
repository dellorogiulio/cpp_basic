/* 
 --- LAMBDA ---	
*/
/*
    'A lambda is an unnamed function that is useful for short snippets of code that are impossible to reuse and
	are not worth naming.'
*/

#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
/*
	To better understand a lambda, could be useful to keep in mind what a function pointer is.
	A function pointer is a C type and it just the memory address of the first instruction of a function.
	We can make a simple example:
*/

int aSimpleFunction(int a, int b)
{
    return a + b;
}

void everyoneLovesPointer()
{
    int integer = 2;
    int* int_ptr = &integer;  // this is not surprising: we are assigning a int pointer to the memory address of an int

    // we know that it is possible to access the value of a pointer by deferencing it:
    int value = *int_ptr;

    // function pointer is equivalent, but with a little bit messy syntax:
    int (*function_ptr)(int, int) = &aSimpleFunction;

    // this is the syntax to declare 'function_ptr' as a pointer to a function which takes two int and return an int.
    // [return_type](*[variable_name])([argument_types])

    // How can we access the function pointed by a function pointer? Deferencing it!
    int function_call_result = (*function_ptr)(3, 4);
    assert(function_call_result == aSimpleFunction(3, 4));

    // The Cpp counterpart of C-function pointer is std::function. They have a more 'standard' syntax:
    // std::function<[return_type]([argument_types])> [variable_name];

    std::function<int(int, int)> cpp_function(&aSimpleFunction);      // we can assing a function pointer to a std::function
    std::function<int(int, int)> same_cpp_function(aSimpleFunction);  // or directly to the function itself

    // When function pointers are useful? Everytime we need to pass a function to call in a second time!
    // Let's make an example
}

namespace not_so_good
{
// basic timer example -> can only accept functions which take no arguments and returns void
class Timer
{
    std::chrono::milliseconds time_to_wait_;
    std::function<void()> function_to_call_;
    std::thread timer_thread_;

    void timerThreadFunction()
    {
        // this function will be called in a separate thread:
        // it simply sleeps the requested time and then calls the passed function pointer
        std::this_thread::sleep_for(time_to_wait_);
        function_to_call_();
    }

   public:
    Timer(const std::chrono::milliseconds& time, std::function<void()> function_to_call) :
        time_to_wait_(time),
        function_to_call_(function_to_call)
    {
    }

    void start()
    {
        // here we are creating a parallel thread in which run the timerThreadFunction
        timer_thread_ = std::thread(&Timer::timerThreadFunction, this);
    }

    void waitTimerToEnds() { timer_thread_.join(); }
};
}  // namespace not_so_good

void logFunction()
{
    std::cout << "Hello from Timer!\n";
}

void useTimerWithFunctionPointer()
{
    not_so_good::Timer t(std::chrono::seconds(1), &logFunction);
    t.start();
    t.waitTimerToEnds();
}

// Ok..But lambdas??

void lambdas()
{
    // we see that lambda is an anonymous function which is directly assigned to a variable
    // the backbone of a lambda is:
    auto lambda = []() {};  // There are a lot of brackets! Let's explain this.

    /*
		[] -> capture list: a set of variable to capture from the local scope
        () -> argument list: classic arguments to the function
        {} -> body: the function body 
	
	Pay attention: a lambda can only the assigned by auto. In Cpp a lambda has un unknowable type, so no way to 
	instantiate it without 'auto'
	*/
    // We can try to traduce the 'aSimpleFunction' in a lambda; it will look something like this:

    auto a_simple_lambda = [](int a, int b) {
        return a + b;
    };
    // it has no capture, takes two int and returns the sum of them.
    /*
		Wait...where is the return type? In lambda it is (generally) not necessary.
		Lambda can deduce the return type for us.
		If we want (or need) to specify the return type, we can do by using an arrow '->'
	*/
    auto same_as_above = [](int a, int b) -> int {  // '-> int' express the return type
        return a + b;
    };

    // call a lambda is straight forward:
    int return_value = a_simple_lambda(1, 3);
    int same_return_value = same_as_above(1, 3);
    assert(return_value == same_return_value);

    // Back to our (not_so_good) Timer:
    not_so_good::Timer timer(std::chrono::milliseconds(2), []() {
        std::cout << "Lambda here!\n";
    });

    /*
		Have you see how simple is to declare a function to be passed to the timer?
		Generally, without lambda, we would declare a function just to pass it to the timer.
		With lambda there is no need to do that! We can declare the lambda directly where we need it!
	*/
    timer.start();
    timer.waitTimerToEnds();
}

// There are other cases in which lambdas are useful? YES!
// You could be surprise to discover that lambda can be faster then regular function. This because the compiler
// is free to better optimize the code.
// Take a look of the following link: (it will take a bit to open since it will run the benchmark)
// https://quick-bench.com/q/QQxwS4DZHOGW2COTLhHy4yCS6Lg

// Sometimes, you could find yourself to write a function just to be used inside one another function; something like this:

namespace do_not_use_lambda
{
int computeVeryComplexValue(int input)
{
    // very complicated and time-consuming stuff here
    return input + 1;
}

int calledFunction(int input1, int input2)
{
    if (input1 > input2)
        return computeVeryComplexValue(input1);
    return computeVeryComplexValue(input2);
}
}  // namespace do_not_use_lambda

// the code below is quite good: it keeps logic separated using two functions. However, if 'computeVeryComplexValue' is
// used in 'calledFunction' only, it's better include 'computeVeryComplexValue' directly in the calling function:

namespace use_lambda
{
int calledFunction(int input1, int input2)
{
    auto compute_very_complex_value = [](int input) {
        // very complicated and time-consuming stuff here
        return input + 1;
    };
    if (input1 > input2)
        return compute_very_complex_value(input1);
    return compute_very_complex_value(input2);
}

}  // namespace use_lambda

void otherUsesOfLambda()
{
    do_not_use_lambda::calledFunction(2, 3);
    use_lambda::calledFunction(2, 3);
}

// Lambdas are very handy when used with std::algo!
// If we want to find the first even number in a vector, how can we do it? Well, at least in three ways!

bool isEven(int i)
{
    return !(i % 2);
}

void lambdasAndAlgorithms()
{
    std::vector<int> test_data({1, 3, 5, 7, 9, 11, 2, 5, 4});

    // we can use std::find_if

    // we can pass the 'isEven' predicate
    auto with_function = std::find_if(test_data.begin(), test_data.end(), isEven);

    auto is_even = [](int i) {
        return !(i % 2);
    };
    // we can pass the 'is_even' lambda as predicate
    auto with_passed_lambda = std::find_if(test_data.begin(), test_data.end(), is_even);

    // or we can instantiate the lambda directly in the find_if:
    auto with_lambda = std::find_if(test_data.begin(), test_data.end(), [](int i) {
        return !(i % 2);
    });

    // the last case is probably it compact and the most elegant solution!
}
int main()
{
    everyoneLovesPointer();
    useTimerWithFunctionPointer();
    lambdas();
    otherUsesOfLambda();
    lambdasAndAlgorithms();
}