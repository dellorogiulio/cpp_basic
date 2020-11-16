/* 
 --- CLASSES PART 2 ---	
*/
#include <string>

/*
    We saw how C++ allows us to pack together data and logic in a struct (attributes and methods).
    This is a starting point, but as developers, we could not be completely satisfied.
    In perfect C-style, everyone who (and every portion of code which) has access to the struct instance,
    has full access to all its attributes (read and write) and methods too.
    Everyone can change any attribute, every method can be called everywhere, ...
    Not a big advantage up to now, at all.
    
    How can C++ help regulating the access rights to the struct (or class) attributes and methods?

    VISIBILITY
    Every item inside a class (attribute or method), can have one of the following three types of visibility:
    - private -> only the class instance can access the attribute/method
    - public -> everyone can access the attribute/method
    - protected -> only the subclasses of the class can access the attribute/method (we will see what it means in inheritance concept) 
*/

/*
	More info:
	https://www.youtube.com/watch?v=Z_hPJ_EhceI
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
    // it's bad because we can access directly to the class attributes
    person.name = "Paolo";
    // now 'person' name is "Paolo" but the real name was "Mario" (of course, here const is mandatory but it is not the point)!
}

namespace better
{
struct Person
{
   private:  // we can deny the access of the class attributes by declaring them 'private'
    std::string name;
    std::string surname;

   public:  // here starts the 'public' section, that contains everything that can be accessed from the outside of the instance
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

/*  It's now possible to appreciate the difference between structs and classes: default visibility (i.e. the visibility of the items of it's not explicitly set).
    Struct has PUBLIC as default visibility.
    Class has PRIVATE as default visibility.
    That's it. Nothing else.
    Of course, it is possible to override a modifier by explicitly declaring 'public' or 'private' (as in the example above) 
*/

void useBetterPerson()
{
    using namespace better;
    Person person;
    person.setNameAndSurname("Mario", "Rossi");	// this is the only way to set 'name' and 'surname' at the moment;
						// designated initializers won't work anymore since .name and .surname are private
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
    It describes what happens just after the memory to store the class has been reserved: the memory is filled somehow,
    the attributes are initialized in some way, ...
    Writing a constructor we can be sure that when an instance is constructed, it's in a known state.
    
    Thinking to C language, what happens when we define and instance in this way:
    Person person;
    without initializing it?
    Is the memory filled with zeroes? Is it filled with random data? Is it leaved as it is (dirty)?
    Who knows? Who cares?
    This can bring to bugs.
    
    A constructor helps a lot.
*/

namespace the_best
{
class Person
{
   private:
    const std::string name_;  // note the trailing '_' which indicates that this is a class attribute (https://google.github.io/styleguide/cppguide.html)
    const std::string surname_;

   public:
    // a constructor has ALWAYS the same name as the class, and it CAN take a list of input parameters
    Person(const std::string name, const std::string surname)  // How to initialize the class attributes? by using an initializer lists (https://en.cppreference.com/w/cpp/language/constructor)
        : // an initializer list starts with a :
        name_(name),  // then a comma-separated list of all attributes which must be initialized
        surname_(surname)	// look to this syntax: it means that the constructor of every attribute is called, passing it the proper parameter
    {
        /*
        NOTE: one can think to initialize the class attributes inside the constructor body, such as:
        name_ = name;
        surname_ = surname;
        
        this is not technically correct: once the first { is open in the constructor body, all the class should be already initialized.
	    This is because before the constructor body is opened, the instance has already been constructed (memory allocated and, maybe, filled in some way).
        Setting the attributes in the constructor body involves a first (useless) initialization of all the class attributes to their default value, and then
        overwriting them by the assignment.
        */
    }

    std::string fullName() const { return name_ + " " + surname_; }
    /* 
    What does 'const' here means? 
        a class method marked by 'const' is used to indicate that the method CANNOT change the class instance.
        This means that, in the function body, it's not allowed to modify any class attributes or to call any class method which is non-const.
	
        See the example below.
    
        void notAllowedMethod() const { name_ = "Marco"; }

        The above method cannot compile, since the method is marked as const: implicitly name_ is marked as const too, and then is not possible to edit it.

    But How does it works?
        We saw that a class method has always a hidden argument 'this'. A non-const method will look like:

        void nonConstMethod(); -> 'seen by the compiler as' void nonConstMethod(Person* this)

        a const method is the same, but 'this' is const-qualified!

        void constMethod() const; -> void constMethod(const Person* this);

        Since 'this' is const, we are not allowed to modify it.

    Why const method are so important?
        A const method can be called even over a class instance which is const. This means that we can call a const method when we have a const reference. 

        std::string callFullName(const Person& person)
        {
            return person.fullName(); 

            If fullName would not be marked as const, we could not call it here!
        }

        TIP:
            one more time... const-qualify everything is possibile
            This will help a lot the compiler creating optimized code.
            Once you start const-qualifying data you quickly find that const-ness is pervasive (i.e. more and more items will be required to be const).
            This is true even for legacy C code.
            On embedded systems, when data is const-qualified, the compiler is FREE to put it in read-only memory (no guarantee that it will do; it's up to the compiler).
    */
};
}  // namespace the_best

void useTheBestPerson()
{
    const the_best::Person person("Mario", "Rossi");  // here we are calling the above declared constructor
    // not the use of const
    auto full_name = person.fullName();  // the call of fullName() on person (which is const) is allowed since fullName is a const method
}

int main()
{
    useNoGoodPerson();
    useBetterPerson();
    useTheBestPerson();
}
