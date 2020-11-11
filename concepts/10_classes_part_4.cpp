/* 
 --- CLASSES PART 4 ---	
*/
#include <string>
#include <stdio.h>

/*
    INHERITANCE 
        "The capability of a class to derive properties and characteristics from another class is called Inheritance. 
        Inheritance is one of the most important feature of Object Oriented Programming.
        - Sub Class: The class that inherits properties from another class is called Sub class or Derived Class.
        - Super Class: The class whose properties are inherited by sub class is called Base Class or Super class."
        (https://www.geeksforgeeks.org/inheritance-in-c/)

    Inheritance is very important for modern programming languages, because it allows to create complex and flexible functionalities and the code re-usability.
    Therefore, inheritance allows to better explain what a programmer wants to obtain with a specific class.

*/

/* 
    More info:
    https://www.youtube.com/watch?v=X8nYM8wdNRE
    https://www.youtube.com/watch?v=tXFqS31ZOFM
 */

/* BASIC CONCEPT */

namespace first_try
{
struct Base
{
   protected:  // see concept 8: protected means that only classes that extends Base can access base_value
    int base_value = 1;

   public:
    int baseValue() const { return base_value; }
    void hi() const { puts("Hi, I'm Base"); }
};

struct Derived : public Base  // here we are declairing Derived as subclass of Base
{
    // now Derived IS a Base. This means that Derived has everything that Base has.

    // we can declare new Derived attributes and methods
   private:
    int my_value = 3;

   public:
    int myMethod() const { return my_value; };
};

void basicConcept()
{
    Derived derived;
    int v = derived.baseValue();  // as you can see here, Derived has the Base method baseValue!
    int v2 = derived.myMethod();  // and of course all its own methods
}
}  // namespace first_try

/* But what happens if we declare a method in a derived class that already exist in the base class? It depends! */

namespace second_try
{
struct Derived : public first_try::Base
{
    void hi() const { puts("Hi, I'm Derived"); }  // here we are declairing exactly the same method as first_try::Base!
};

void basicConcept()
{
    Derived derived;
    derived.hi();  // prints "Hi, I'm Derived"!
    // this should not be surprising, since we are overriding the first_try::Base::hi method!

    first_try::Base base;
    base.hi();  // prints "Hi, I'm Base" -> no surprise
}

/*
    POLYMORPHISM:
    Polymorphism is the characteristic of a subclass to been "seen" as its superclass.
    In other words, we can "see" Derived as a Base class since Derived is a Base class!
*/

void sayHi(const first_try::Base& base)  // this function takes a Base class as const ref
{
    base.hi();
}

void usePolymorphism()
{
    puts("--- second_try::usePolymorphism() ---");
    second_try::Derived derived;
    first_try::Base base;
    sayHi(base);     // prints "Hi, I'm Base"
    sayHi(derived);  // prints "Hi, I'm Base" too!
    /* 
        Why?
        sayHi takes a const ref to Base, and you could think 'well, first_try::Base has its hi method, so obviously sayHi will always call it'...
        This is wrong. Consider the example below
    */
}

}  // namespace second_try

namespace third_try
{
struct Base
{
    virtual void hi() const { puts("Hi, I'm Base"); }  // same as in first_try, but now we mark hi as virtual!
};

struct Derived : public Base
{
    void hi() const { puts("Hi, I'm Derived"); }  // here we are declairing exactly the same method as Base!
};

void sayHi(const Base& base)  // this function takes a Base class as const ref
{
    base.hi();
}

void usePolymorphism()
{
    puts("--- third_try::usePolymorphism() ---");
    Derived derived;
    Base base;
    sayHi(base);     // prints "Hi, I'm Base"
    sayHi(derived);  // prints ""Hi, I'm Derived"!
    /* 
        Why?
        Because now Base::hi is virtual! Virtual its a powerfull tool, since allows the compiler to 'understand' that Base reference passed to
        sayHi is not a 'pure' Base, but it's a Derived, and since Derived has override the hi method, it calls the correct one!
    */
}

}  // namespace third_try

// for the sake of completeness: when you override a virtual function of base class, you should specific the qualifier 'override' on the subclass:
struct Derived : public third_try::Base
{
    void hi() const override { puts("Hi, I'm Derived"); }  // note the use of override here! This allows the compiler to check if we are effectively
                                                           // overriding a virtual function. If not, it throws a compile error!
};

/* 
    Pure virtual functions
        Now that we understand what a virtual function does, we can introduce another concept: pure virtual.
        In the example above, Derived COULD override hi, but don't must do it: if Derived doesn't override hi, exists the Base version.
        Pure virtual instead forces the Derived to override the hi function, Derived MUST do that, or the code will not compile.    
*/

namespace pure_virtual
{
struct Base
{
    virtual void hi() const = 0;
};

struct WrongDerived : public Base
{
};

struct Derived : public Base
{
    void hi() const override { puts("Hi, I'm Derived"); }
};

void sayHi(const Base& base)  // this function takes a Base class as const ref
{
    base.hi();
}

void usePolymorphism()
{
    puts("--- pure_virtual::usePolymorphism() ---");
    // THIS IS A COMPILE ERROR
    //Base b;
    //WrongDerived derived;
    // we cannot declare a variable to be Base, since it needs a hi method!
    // same as WrongDerived, since it needs a hi method!

    Derived derived;  // we can declare a Derived instance since its respect the pure virtual function!
    sayHi(derived);   // prints "Hi, I'm Derived"!
}

}  // namespace pure_virtual

/*
    Why virtual functions are so important?
    Because this allows to create interfaces between developers and between functionalities. 
    We will see a more interest example in the next episode
*/

int main()
{
    first_try::basicConcept();
    second_try::basicConcept();
    second_try::usePolymorphism();
    third_try::usePolymorphism();
    pure_virtual::usePolymorphism();
}