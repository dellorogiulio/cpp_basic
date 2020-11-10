/* 
 --- CLASSES PART 2 ---	
*/
#include <string>

/*
    How can we regulate the access to the class attributes and methods?

    VISIBILITY
    There are three types of visibility:
    - private -> only the class instance can access the attribute/method
    - public -> everyone can access the attribute/method
    - protected -> only the class subclasses can access the attribute/method (we will see in inheritance concept) 
*/

namespace no_good
{
struct Person
{
    std::string name;
    std::string surname;

    std::string fullName()
    {
        return name + " " + surname;
    }
};
}  // namespace no_good

void useNoGoodPerson()
{
    using namespace no_good;
    Person person = {.name = "Mario", .surname = "Rossi"};
    auto full_name = person.fullName();
    // is bad to can access directly the class attributes
    person.name = "Paolo";
    // now name is "Paolo" but the real name was "Mario" (of course, here const is mandatory but it is not the point)!
}

namespace better
{
struct Person
{
   private:  // we can deny the access of the class attributes by declairing 'private'
    std::string name;
    std::string surname;

   public:  // under public all that can be accessed from the outside
    void setNameAndSurname(const std::string& name, const std::string& surname)
    {
        // not the use of this here!
        if (this->name == "")
        {
            // since name is ambiguous, 'name' is the LOCAL variable and the class attribute can be accessed by this->name
            this->name = name;
        }
        if (this->surname == "")
        {
            this->surname = surname;
        }
    }

    std::string fullName()
    {
        return name + " " + surname;
    }
};
}  // namespace better

/*  It's now possible to appreciate the difference between structs and classes: default visibility.
    Struct has PUBLIC as default visibility.
    Class has PRIVATE as default visibility.
    That's it. Nothing else.
    Of course, it is possible to override a modifier by explicitly declairing 'public' or 'private' (as in the example above) 
*/

void useBetterPerson()
{
    using namespace better;
    Person person;
    person.setNameAndSurname("Mario", "Rossi");
    auto full_name = person.fullName();

    // THIS IS A COMPILE ERROR
    //person.name = "Paolo"; -> Person::name is private within this context
    // we cannot access person.name since we are outside the class itself!

    // But now that we made name and surname private, how can we initialize them?
    // We need always a "set" function? Of course, no! We can use constructors
}

/*
    CONSTRUCTOR
    A constructor is a special method which is used to build a class instance.
*/

namespace the_best
{
class Person
{
   private:
    const std::string name_;  // note the ending '_' which indicates that is a class attribute (https://google.github.io/styleguide/cppguide.html)
    const std::string surname_;

   public:
    // a constructor has the same name as the class
    Person(const std::string name, const std::string surname)  // How initialize the class attributes? by using an initializer lists (https://en.cppreference.com/w/cpp/language/constructor)
        : // an initializer list starts with a :
        name_(name),  // then a comma-separated list of all attributes which must be initialized
        surname_(surname)
    {
        /*
        NOTE: one can think to initialize the class attributes in the constructor body, such as:
        name_ = name;
        surname_ = surname;
        
        this is not technically correct: once the first { is open in the constructor body, all the class should be initialized.
        assign the attributes in the constructor body involves a first initialization of all class attributes to them default value, and then
        override it by the assignment.
        */
    }

    std::string fullName() { return name_ + " " + surname_; }

};
};  // namespace the_best

void useTheBestPerson()
{
    the_best::Person person("Mario", "Rossi"); // here we are calling the above declaired constructor
    auto full_name = person.fullName();
}

int main()
{
    useNoGoodPerson();
    useBetterPerson();
    useTheBestPerson();
}
