/* 
 --- CLASSES PART 1 ---
		Classes are fundamental part of the language, since C++ is typically called a "Object-oriented language".
        Classes allow to keep data and logic "packed together" in a single point.
*/

/*
	More info:
	https://www.youtube.com/watch?v=2BP8NhxjrO0
    https://www.youtube.com/watch?v=3dHBFBw13E0
*/

// Consider the case in which we need to model a Person and see C vs Cpp

#include <string>

// C-Style
// in C you can:
// - declare a struct (i.e. list which type of data it contains and their names)
// - create (define) a struct instance (so that memory is allocated to store the instance itself)
// - pass by pointer the instance to functions

namespace c_style
{
struct Person
{
    std::string name;
    std::string surname;
};	// this is the declaration of the struct (no memory is reserved at this point)

std::string getfullName(const Person* person)		// note the const pointer since getfullName() doesn't change the input parameter person (TIP: const-qualify everything is possible)
{
    return person->name + " " + person->surname;
}
}  // namespace c_style

void cStylePerson()
{
    c_style::Person person = {.name = "Mario", .surname = "Rossi"};  // definition and initialization together (i.e. memory is allocated for 'person' and it's filled
								     // note the C99 "designated initializers" used to initialize 'person' (.name = xxx .surname = yyy)
    auto full_name = c_style::getfullName(&person);                  // pass a pointer to the instance to a function
}

// Cpp-Style
// in C++, struct are classes: the only difference is the default visibility (see later)
namespace cpp_style
{
struct Person
{
    std::string name;  // this is called "class attribute" (or "class member")
    std::string surname;

    // it is possible to declare a function which 'lives' only inside the class, this is called "class method"
    std::string fullName()  // <- no arguments
    {
        return name + " " + surname;  // see how inside this struct it is possible to access directly the 'name' and the 'surname' attributes (members) through their names
    }

    std::string getName()
    {
        return this->name;  // what's 'this'? See later!
        // of course, writing "return name;" is ok too: 'name' and 'this->name' are exactly the same!
    }
};
	
// The answer to a classic question from an experienced (embedded) C programmer:
// The "sizeof(...)" of a C++ struct is well-defined, but it's a consequence of a lot of concepts (not fully clear, at this point).
// In some simple scenarios, it's equal to the C "sizeof(...)", but it's not a general rule.
// And so:
// - DO NOT RELY on the "sizeof(..)" of a C++ struct
// - and so, DO NOT IMPLEMENT ANYMORE some low-level C-style "magic" on the instances (i.e. memcpy(), memcmp(), ...)
// (see https://www.cprogramming.com/tutorial/size_of_class_object.html)
	
}  // namespace cpp_style

void cppStylePerson()
{
    cpp_style::Person person = {.name = "Mario", .surname = "Rossi"};
    auto full_name = person.fullName();
    // see how fullName() can be called directly over the 'person' instance.

    /*  But how this works?
        the compiler sees the signature of class method fullName() as fullName(Person* this)
        The signature of every class method has in fact a "hidden" parameter (the first one) which is a pointer to the class instance.
	This hidden parameter is called 'this'
        The call of person.fullName() "becomes" fullName(&person) from the compiler "point of view".
    */
    auto name = person.getName();
    // Now you understand why in the body of getName() method, a variable 'this' is accessible. Remember that 'this' is of type Person*
}

int main()
{
    cStylePerson();
    cppStylePerson();
}
