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

struct Derived : public Base  // here we are declaring Derived as subclass of Base
{
    // inheritance means that Derived IS A Base. This means that Derived has everything that Base has, and it can be
    // used wherever Base can be used
 
    // this is the class declaration and we qualified inheritance as 'public': this means that all the codebase where Derived is used
    // will "see" this inheritance relation.

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

/* But what happens if we declare a method in a derived class that already exist (with the same signature) in the base class? It depends! */

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
        sayHi() takes a const ref to Base, and you could think 'well, first_try::Base has its hi() method, so obviously sayHi() will always call it,
        even if I pass a Derived'...
        This is wrong. Consider the example below
    */
}

}  // namespace second_try

namespace third_try
{
struct Base
{
    virtual void hi() const { puts("Hi, I'm Base"); }  // same as in first_try, but now we mark hi() as virtual!
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
        Because now Base::hi is virtual! Virtual it's a powerfull qualifier, since allows the compiler to 'understand' that the 'derived' reference passed to
        the second sayHi is not a 'pure' Base, but it's a Derived; and since Derived has overridden the hi method, it calls the correct one!
    */    
    
    /*  Note for an experienced C programmer:
        This effect is called "dynamic dispatch" because the decision on which function has to be called (dispatch) is done at run time (dynamic).
        It can be achieved looking to a table of functions (vtable - similar to a C-style array of pointer to functions) to find the function whose signature
        has the "best match".
        This lookup as a slight overhead during execution, but with modern compilers and hardware architectures it's usually not an issue.
    */
}

}  // namespace third_try

// for the sake of completeness: from C++11, when you override a virtual function of base class, you should specific the qualifier 'override' on the subclass:
struct Derived : public third_try::Base
{
    void hi() const override { puts("Hi, I'm Derived"); }  // note the use of override here! This allows the compiler to check if we are effectively
                                                           // overriding a virtual function. If not, it throws a compile error!
};

/* 
    Pure virtual functions
        Now that we understand what a virtual function does, we can introduce another concept: pure virtual.
        In the example above, Derived COULD override hi, but don't have to do it: if Derived doesn't override hi, the Base version is available.
        Pure virtual, instead, forces the Derived to override the hi function, Derived MUST do that, or the code will not compile.    
*/

namespace pure_virtual
{
struct Base
{
    virtual void hi() const = 0;    // using '= 0' instead of the implementation '{ ... }' is the way to declare a method as "pure virtual"
 
    // a class which has at least one pure virtual method is called ABSTRACT class
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
    // we cannot define a variable of type Base, since it needs a hi method! - Base is an abstract class and so a concrete instance cannot be created
    // the same happens for WrongDerived, since it needs a hi method! - WrongDerived is an abstract class and so a concrete instance cannot be created

    Derived derived;  // we can define a Derived instance since it implements the pure virtual function!
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

/*
    DISCLAIMER:
        At a first sight, inheritance seems really cool; an old-school C programmer usually thinks "I'm going to use it everywhere, because it saves me
        a lot of job".
        Inheritance is really powerful, but it's NOT the golden hammer of a C++ programmer (i.e. the tool that can be used everywhere, for any purpose, ...).
        Public inheritance between two classes is a relation between them: it's the strongest relation between them and it creates a strong coupling
        between the classes. Once you decide to establish an inheritance relation between two classes, it will be very very difficult breaking it afterwards.
        
        Use inheritance when you want to effective model the "IS A" relation.
*/
