/* 
 --- STREAMS ---	
*/
#include <iostream>  // here we go!
#include <fstream>
/*
    STREAMS:
    'A stream is an abstraction that represents a device on which input and ouput operations are performed.
    A stream can basically be represented as a source or destination of characters of indefinite length.'
    (http://www.cplusplus.com/reference/iolibrary/)

    To me, this seems quite explicative: streams are a way to interact with some sort of device to set or get information.
    Writing on a file or on the console is not different: we can see the console as a 'special' file to write into!

*/

int veryComplexFunction(int value)
{
    return value + 1;
}

void streamBasic()
{
    // Until now, we used C logging functions, as 'puts' or 'printf' but now it's time to introduce the Cpp counterpart!

    std::cout << "hello world" << std::endl;
    /*
        this is by the most common example that you can find on the web. 
        This line of code has a specific meaning: "take the string 'hello world' and the 'std::endl' variable and put them 
        in the 'std::cout' stream."
        Reading from left to right:
        - std::cout is the stream in which we are pushing things
        - << is the stream operator which allows us to put things into streams
        - 'hello world'... we now know what this is
        - << again, stream operator to 'concatenate' different things 
        - std::endl is a cpp 'line terminator'. Be careful: std::endl is NOT equivalent to '\n', since the endl provides a 
          new line and a fflush. Since generally fflush isn't needed, try to avoid std::endl as much as possible! 
          (good time about this argument: https://www.youtube.com/watch?v=GMqQOEZYVJQ&t=7s)         
    */

    /*
        The stream operator '<<' is an operator which allows to put different things into a stream.
        We should have understood operator right now, so you should not be surprise to discover that the operator<< is 
        overloaded for different types:
    */
    std::cout << "We can put strings into streams, but also integers (" << 12 << "), floating numbers (" << 13.21 << ")"
              << " and (obviously), function call return values: " << veryComplexFunction(3) << "\n";

    // cout isn't the only stream, std::cerr and std::clog exist to provide a sort of 'logging level'
}

// How stream can interact with a custom class?

struct MyStruct
{
    float magic_number_;
    float magic_number_too;

    MyStruct(float m, float n) :
        // really poor variable names...
        magic_number_(m),
        magic_number_too(n)
    {
    }

    // what if we want to make our class to interact with strems?
    // We need to declare a class-extern function in the form:
    // 'std::ostream& operator<<(std::ostream& stream, const MyStruct& my_struct);'
    // which puts my_struct to the stream
};

// this function is out the class declaration
std::ostream& operator<<(std::ostream& stream, const MyStruct& my_class)
{
    stream << my_class.magic_number_ << " " << my_class.magic_number_too;
    return stream;
}

void useMyStruct()
{
    // we are now able to stream MyStruct to a stream!
    MyStruct my_struct(2.3, 3.14);
    std::cout << "my_struct is: " << my_struct << "\n";
}

// What to do if we are dealing with private data?

class MyClass
{
    float magic_number_;
    float magic_number_too;

   public:
    MyClass(float m, float n) :
        // really poor variable names...
        magic_number_(m),
        magic_number_too(n)
    {
    }

    friend std::ostream& operator<<(std::ostream& stream, const MyClass& my_class);
    /*
        Wait, what is that? Here we are declaring a friend function.
        Declaring a function (class) 'friend' of a class 'Class', we are allowing that function (class) to access all private
        data of the class 'Class'. In this case we have to DECLARE, inside the class body, that a function with the given signature 
        is allowed to access the class private data.
    */
};

// An now we can declare the function out of the class declaration
std::ostream& operator<<(std::ostream& stream, const MyClass& my_class)
{
    stream << my_class.magic_number_ << " " << my_class.magic_number_too;
    return stream;
}

void useMyClass()
{
    // Now we can stream MyClass too!
    MyClass my_class(2.3, 3.14);
    std::cout << "my_class is: " << my_class << "\n";
}

/*
    As you may have guessed, interaction with files happens in the same way!
    We can open a file, stream in-to or out-from a file!
*/

void interactWithFile()
{
    std::fstream file_stream;
    // we open a file to read and write
    file_stream.open("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    file_stream << " more lorem ipsum";  // here we stream text into the file
    file_stream.close();                 // that's it

    std::fstream file_stream_2;
    file_stream_2.open("test2.txt", std::fstream::in);  // open for reading
    std::cout << file_stream_2.rdbuf();                 // we are getting the internal buffer and streaming it to the console
}

int main()
{
    streamBasic();
    useMyStruct();
    useMyClass();
}
