/* 
 --- NAMESPACES ---
		Namespaces are a sort of container in which everything is declaired in remains 
		in it.
		Namespaces are useful to keep the code clean and organize and they "allow" function
		redefinitions.
*/

/*
	More info:
	https://www.youtube.com/watch?v=ts1Eek5w7ZA&t=650s
*/

namespace namespace1  // here a namespace declaration
{                     // no need to indent in a namespace
int function1()
{
    return 1;
}

int function2()
{
    return 2;
}
}  // namespace namespace1
/* no need to semicolon at the end of namespace */

namespace namespace2
{
int function1()
{
    return 1;
}

int function2()
{
    return 2;
}
}  // namespace namespace2

namespace namespace3
{
/*
	Obviously not only function can be define in a namespace;
	Classes, variables, functions... everything can be define in a namespace
*/
int value = 2;

// And you can nest namespaces in a namespace
namespace namespace3_inner
{
int value = 3;
}
}  // namespace namespace3

int main()
{
    int n1 = namespace1::function1();
    int n2 = namespace2::function1();
    /*  Note that function1 has the same signature in namespace1 and namespace2 but,
		since they are "confined" in the namespace, there is no ambiguity
	*/

    {
        /*	It is possible to "keep up" everything which is a namespace to the current scope
			by using the keyword "using namespace"
		*/
        using namespace namespace1;
        /* 	now everything which is contained in namespace1 is available in the current scope
			without using "namespace1::"
		*/
        int n3 = function1();  // no ambiguity: function1() without anything in front of it can be only namespace1::function1
                               // no need to use "namespace1::" since everything in it is accesible here
    }
    /*	Note that now everything in namespace1 is "packed back" in the namespace and is NO more 
		accessible without the "namespace1::" indication */

    // THIS IS A COMPILE ERROR
    // int n4 = function1(); -> 'function1' was not declared in this scope

    /* you can obviously use more than one "using namespace" sintax, but pay attention */
    using namespace namespace1;
    using namespace namespace2;
    /* Now everything in namespace1 and namespace2 is accessible to the current scope */

    // THIS IS A COMPILE ERROR
    // int n5 = function1(); ->  call of overloaded 'function1()' is ambiguous
    /* the compiler is in fact no more able to decide which function1 use, since namespace1::function1 and
	   namespace2::function1 are both visible in the current scope
	*/

    /*  It is possible to access namespace members with no limit */
    int n6 = namespace3::value;
    int n7 = namespace3::namespace3_inner::value;

    return 0;
}