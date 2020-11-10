/* 
 --- CLASSES PART 1 ---
		Classes are fundamental part of the language, since C++ is typically called a "Object-oriented language".
        Classes allow to keep data and logic "pack" in a single point.
*/

/*
	More info:
	https://www.youtube.com/watch?v=2BP8NhxjrO0
    https://www.youtube.com/watch?v=3dHBFBw13E0
*/

// Consider the case in which we need to model a Person and see C vs Cpp

#include <string>

// C-Style
// in C you can declare a struct, create a struct instance and than pass by pointer the instance to functions

namespace c_style
{
struct Person
{
    std::string name;
    std::string surname;
};

std::string getfullName(Person* person)
{
    return person->name + " " + person->surname;
}
}  // namespace c_style

void cStylePerson()
{
    c_style::Person person = {.name = "Mario", .surname = "Rossi"};  // declaration and initialization
    auto full_name = c_style::getfullName(&person);                  // call function on the instance
}

// Cpp-Style
// in C++, struct are classes: the only difference is the default visibility (see later)
namespace cpp_style
{
struct Person
{
    std::string name;  // this is called "class attribute"
    std::string surname;

    // it is possible to declare a function which 'lives' only inside the class, this is called "class method"
    std::string fullName()  // <- no arguments
    {
        return name + " " + surname;  // see how it is possible to access directly the 'name' and the 'surname' attributes
    }

    std::string getName()
    {
        return this->name;  // what's 'this'? See later!
        // of course, return name; will be ok: name and this->name are exactly the same!
    }
};
}  // namespace cpp_style

void cppStylePerson()
{
    cpp_style::Person person = {.name = "Mario", .surname = "Rossi"};
    auto full_name = person.fullName();
    // see how fullName() can be accessed directly by the person instance.

    /*  But how this works?
        the compiler see the fullName() method as fullName(Person* this)
        Every class method has in fact an "hidden" parameter (the first one) which is a pointer to the class instance.
        the call of person.fullName() "becomes" fullName(&person) as seen by the compiler.     
    */
    auto name = person.getName();
    // In the name() method, a variable 'this' is in fact accessible. Remember that 'this' is of type Person*
}

int main()
{
    cStylePerson();
    cppStylePerson();
}
