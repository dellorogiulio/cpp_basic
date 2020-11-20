/* 
 --- STD CONTAINERS AND ALGORITHMS ---	
*/
/*
    STD CONTAINERS
    'The Containers library is a generic collection of class templates and algorithms that allow programmers to easily
    implement common data structures like queues, lists and stacks.
    [...] The container manages the storage space that is allocated for its elements and provides member functions to access them,
    either directly or through iterators (objects with properties similar to pointers).'
    (https://en.cppreference.com/w/cpp/container)

    The most famous (and used) containers are:
    - std::vector:  in this containers 'the elements are stored contiguously, which means that elements can be accessed
                    not only through iterators, but also using offsets to regular pointers to elements.
                    This means that a pointer to an element of a vector may be passed to any function that expects a
                    pointer to an element of an array (since C++03). The storage of the vector is handled automatically,
                    being expanded and contracted as needed.'
    - std::array    'This container is an aggregate type with the same semantics as a struct holding a C-style array T[N]
                    as its only non-static data member. Unlike a C-style array, it doesn't decay to T* automatically. 
    - std::map      'std::map is a sorted associative container that contains key-value pairs with unique keys.
                    Keys are sorted by using the comparison function' 

*/

#include <vector>
#include <map>
#include <array>

#include <algorithm>

#include <iostream>

int main()
{
    // vector is dynamic
    std::vector<int> vector_of_int;
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 0

    // to dynamically add an element to a vector, use the push_back method which handles the memory increasing, if needed.
    vector_of_int.push_back(2);                                              // we are pushing back the value 2 to the vector, which expands to accept this new value
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 1
    vector_of_int.push_back(4);
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 2

    // to clear a vector, you should call 'clear' which reset the size to 0.
    vector_of_int.clear();
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 0 again

    vector_of_int.reserve(10);                                               // here we are reserving space for 10 ELEMENTS, which means 10 ints (aka 10 * sizeof(int))
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 0 since we are not resizing the vector, we are only reserving space!
    vector_of_int.resize(10);                                                // now we are increasing the size to 10!
    // pay attantion: pushing_back an element now will involve the size to be 11!
    vector_of_int.push_back(4);
    std::cout << "vector_of_int.size() = " << vector_of_int.size() << "\n";  // size is 11!

    vector_of_int = {5, 3, 1, 8, 2, 7, 6};  // we can re assign a vector to a new list of int values! (note, this overrides the old values!)

    // How can we iterate of containers?

    // C-style for loop: this is supported only by the index-accessible aggregate containers
    std::cout << "C LOOP\n";
    for (int i = 0; i < vector_of_int.size(); ++i)
    {
        std::cout << vector_of_int[i] << " ";
    }
    std::cout << "\n";

    /*  ITERATORS
        Iterators are the CPP new way to iterate over containers! This are always allowed between containers.
        What a iterator is? Is a way to move through a container, moving from the 'begin' to the 'end' (everything this means)
    */
    std::vector<int>::iterator vector_begin = vector_of_int.begin();  // this is the begin of the vector
    auto vector_end = vector_of_int.end();                            // and this is the end
    // 'auto' here is very friendly

    std::cout << "INTERATORS LOOP\n";
    for (auto it = vector_of_int.begin(); it != vector_of_int.end(); ++it)
    {
        std::cout << *it << " ";  // an iterator is a sort of 'pointer to element'. This means that, deferencing it, we can
                                  // get directly the element
    }
    std::cout << "\n";

    // Cpp11 -> range-based loop
    // Cpp11 introduced the friendliest way to iterate over containers!
    // everything which expose a begin and end iterator, can be iterate with a shorter syntax
    std::cout << "RANGE-BASED LOOP\n";
    for (const auto& elem : vector_of_int)  // obviously elem here is of type const int&
    {
        std::cout << elem << " ";  // try to use const and reference everwhere it's possible to improve for-loop performance
    }
    std::cout << "\n";

    /*
        ALGORITHMS 
        'The algorithms library defines functions for a variety of purposes (e.g. searching, sorting, counting, manipulating)
        that operate on ranges of elements' (https://en.cppreference.com/w/cpp/algorithm)
        
        The idea under algorithms is to be 'orthogonal' to containers: each algorithm can be used on every containers and viceversa.
    */

    // if we want to sort a vector, we can use the std::sort algo!
    std::sort(vector_of_int.begin(), vector_of_int.end());
    // this is the common interface between algorithms and containers: iterators!
    // we indicate from which iterator, to which iterator apply the algoritm and that's it!

    std::cout << "AFTER SORT THE VECTOR OF INT IS\n";
    for (const auto& elem : vector_of_int)
    {
        std::cout << elem << " ";
    }
    std::cout << "\n";

    // We can find an element into a container using the find function
    auto five_it = std::find(vector_of_int.begin(), vector_of_int.end(), 5);  // looking for 5
    // 'five_it' is an iterator to the found element, if present, end() otherwise.
    if (five_it != vector_of_int.end())
    {
        // to compute the index of the element (if the containers allows indices), we can use the std::distance function
        auto index = std::distance(vector_of_int.begin(), five_it);
        std::cout << "Found " << *five_it << " at index " << index << "\n";
    }
    else
    {
        std::cout << "Element not found (l'ghè mia)\n";
    }

    // MAP allows to keep a key-value pair
    std::map<const std::string, long> zip_map = {
        {"lecco", 23900},
        {"ballabio", 23811},
        {"mandello del lario", 23826},
    };

    // we create a map where keys are strings, and values are long.
    // This means that, given a string, it returns a long if it is present

    std::cout << zip_map["lecco"] << "\n";  // it prints 23900

    // Since maps are not iterable with indicies, C-style loop is not allowed!

    // iterators of course works
    std::cout << "ITERATORS LOOP\n";
    for (auto it = zip_map.begin(); it != zip_map.end(); ++it)
    {
        // 'it' is a pair of string and long! https://en.cppreference.com/w/cpp/container/map
        std::pair<std::string, long> value = *it;
        std::cout << "city: " << value.first << " cap: " << value.second << "\n";
    }

#if (__cplusplus >= 201703L)
    // Thanks to cpp17, we can use structural-binding in ranged-based loop
    std::cout << "RANGE-BASED LOOP\n";
    for (auto [city, cap] : zip_map)
    {
        std::cout << "city: " << city << " cap: " << cap << "\n";
    }
#endif

    // How to find in map?
    // We can use std::find, but find wants a map element, which is a pair!
    auto it = std::find(zip_map.begin(), zip_map.end(), std::pair<const std::string, long>{"lecco", 23900});

    // Maybe we want to find a value given a key! For that, there is the method std::map::find method
    auto mandello_zip_it = zip_map.find("mandello del lario");
    if (mandello_zip_it == zip_map.end())
    {
        std::cout << "Not found\n";
    }
    else
    {
        std::cout << mandello_zip_it->first << " has zip code " << mandello_zip_it->second << "\n";
    }

    // std array are the natural evolution of C-array!
    int c_array[3] = {4, 1, 3};

    std::array<int, 3> cpp_array = {4, 1, 3};       // we need to indicate type and length!
    std::sort(cpp_array.begin(), cpp_array.end());  // we can apply algorithms on arrays

    // for range-based loop
    std::cout << "STD::ARRAY LOOP AFTER SORTING:\n";
    for (auto& i : cpp_array)
    {
        std::cout << i << "\n";
    }

    // we can use std::algorithms by applying std::begin and std::end to c_array to obtain iterators
    std::sort(std::begin(c_array), std::end(c_array));

    // c array are 'extended' to allow range-based loop
    std::cout << "SORTED C ARRAY\n";
    for (auto& i : c_array)
    {
        std::cout << i << "\n";
    }
}