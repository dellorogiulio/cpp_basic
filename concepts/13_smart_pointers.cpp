/* 
 --- SMART POINTERS ---	
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdexcept>
#include <memory>

/*
    SMART POINTER
    Smart pointers are the way with which C++ tryies to help programmers to avoid memory leak.
    There exists a variety of Smart Pointer (https://en.cppreference.com/w/cpp/memory) but we will focus on the main three:
    - unique_ptr
    - shared_ptr
    - weak_ptr
*/
/* 
    More info:
    https://www.youtube.com/watch?v=UOB7-B2MfwA
*/

/*
    The main idea of smart pointer is: 'let a class handle the lifetime of an object, you don't worry about it'.
    In a C program, memory is generally handled as follows: 
*/

void CHandleMemory()
{
    double* data = (double*)malloc(5 * sizeof(double));  // now data is an array of 5 double, allocated on the heap
    // not the explicit need of cast...

    free(data);  // here we are freeing data
}

struct MyClass
{
    MyClass()
    {
        puts("Constructor");
    }

    ~MyClass()
    {
        puts("Destructor");
    }
};

void CppHandleMemory()
{
    // in Cpp malloc and free are replaced by new and delete
    double* value = new double(5);  // here we are allocating a single double initialized to 5 on the heap
    double* data = new double[5];   // here we are allocating an array of 5 double!

    delete value;   // here we are freeing value
    delete[] data;  // not the use of delete[] since data is an array!
    // A Cpp good-use rule is: every 'new' must have its 'delete'.

    // same for classes
    MyClass* my_class = new MyClass();  // prints 'Constructor'!
    delete my_class;                    // prints 'Destructor'!
}

/*
    Now that we understood everthing of classes (...), we are smart enough to think to wrap the new and delete operator in a class!
*/

class DoubleArray
{
   private:
    double* data_;
    size_t size_;

   public:
    DoubleArray(size_t size) :
        data_(new double[size]),  // here we are heap allocating the array of double
        size_(size)
    {
    }

    DoubleArray(const DoubleArray& other) :
        data_(new double[other.size_]),  // in a copy-constructor, we don't want to access the same memory as other!
        size_(other.size_)
    {
    }

    ~DoubleArray()
    {
        delete[] data_;
    }

    double operator[](size_t index) const  // since this is a const-method, we cannot edit data_ and then we return a copy of data_[i]
    {
        if (index >= size_)
            throw std::out_of_range("Index is out of range");
        return data_[index];
    }

    double& operator[](size_t index)  // note: to modify the data_ internal value, we return a reference here, since is a non-const method
    {
        if (index >= size_)
            throw std::out_of_range("Index is out of range");
        return data_[index];
    }

    size_t size() const { return size_; }
};

void useDoubleArray()
{
    DoubleArray array(12);
    array[10] = 34.12;
    for (int i = 0; i < array.size(); ++i)
    {
        printf("array[%i]=%3.2f\n", i, array[i]);
    }
    // no need to explicitly deallocate memory here since the destructor do that for us
    // we can see DoubleArray as a sort of 'smart pointer': it cares about memory for us
}

/*
    STD::UNIQUE_PTR
    'std::unique_ptr is a smart pointer that owns and manages another object through a pointer and disposes of that object when the unique_ptr goes out of scope.
    The object is disposed of, using the associated deleter when either of the following happens:
    - the managing unique_ptr object is destroyed
    - the managing unique_ptr object is assigned another pointer via operator= or reset().'

    Unique_ptr are a way to have access to a specific memory only through that unique_ptr. 
*/

void useUniquePtr()
{
    // for now, simply consider <int[]> as a shortcut for 'of int[]' -> unique_ptr<int[]>: 'create a unique_ptr of int[]>

    std::unique_ptr<int[]> data(new int[5]);  // here we create a unique_ptr by passing the allocated pointer
                                              // however this breaks the 'new-delete' rule, since we are using a new which will not be followed by a delete.

    std::unique_ptr<int[]> data2 = std::make_unique<int[]>(5);  // Cpp introduced the make_unique function which hide the new operator to do not break the above rule.

    data[2] = 12;  // here we are assigning the third value of data to 12

    // we cannot copy unique_ptr! Since the access of the pointed memory is exclusive, is it impossible to copy it!
    // THIS IS A COMPILE ERROR
    //std::unique_ptr<int> copy_of_data = data;  use of deleted function [...]

    // however, we can extract the data from a unique_ptr and bring it to another one!
    int* raw_data = data.release();              // now none has the ownership of the data!
    std::unique_ptr<int[]> same_data(raw_data);  // here we are getting the owenship of data to another unique_ptr
    printf("data: %d\n", same_data[2]);          // prints 12 since the backend data is the same!

    // no need to call delete on data or data2 since the unique_ptr destructor handles it!
}

/*
    STD::SHARED_PTR
    'std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. Several shared_ptr objects may own the same object.
    The object is destroyed and its memory deallocated when either of the following happens:
    - the last remaining shared_ptr owning the object is destroyed;
    - the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset().'

    Shared_ptr are the dual of unique_ptr: they allow to share the same resources guaranteeing that the backend data are not been destroyed! 
    A shared_ptr keeps a counter of how many pointers are pointing to the same memory! Once a pointer is deleted, the counter decrements and once it is zero,
    the memory (delete operator) is called!
*/

void useSharedPtr()
{
    std::shared_ptr<int> shared_data(new int(5));
    std::shared_ptr<int> shared_data2 = std::make_shared<int>(5);

    // we can dereference smart pointers as raw pointers
    *shared_data = 12;
    *shared_data2 = 25;

    // now we can copy shared_ptr and assign them!
    auto same_data = shared_data;
    {
        auto same_data2(shared_data2);
        // now count of shared_data2 is 2!
        printf("the counter for shared_data2 is: %d and shared_data2[2]=%d\n", shared_data2.use_count(), *shared_data2);
    }  // note: here same_data2 is destroyed and count goes back to 1

    printf("the counter for shared_data is: %d and shared_data[2]=%d\n", shared_data.use_count(), *shared_data);      // prints 'the counter for shared_data is: 2 and shared_data[2]=12'
    printf("the counter for shared_data2 is: %d and shared_data2[2]=%d\n", shared_data2.use_count(), *shared_data2);  // prints 'the counter for shared_data2 is: 1 and shared_data2[2]=25'
}

/*
    STD::WEAK_PTR
    'std::weak_ptr is a smart pointer that holds a non-owning ("weak") reference to an object that is managed by std::shared_ptr.
    It must be converted to std::shared_ptr in order to access the referenced object.'
    
    Weak pointers are a sort of shared_ptr which does not increments the counter!
    They are useful to have a view to a shared_ptr reference data without forcing to keep the data alive.
    We can check if data are expired by using the expired method
*/

void useWeakPtr()
{
    std::weak_ptr<int> weak;
    {
        std::shared_ptr<int> data = std::make_shared<int>(5);
        weak = data;
        *data = 12;
        weak.expired() ? puts("Data expired!") : printf("data are valid and is: %d\n", *weak.lock());
    }  // here data is destroyed and memory is freed. Weak can access data no more.
    weak.expired() ? puts("Data expired!") : printf("data are valid and is: %d\n", *weak.lock());
}

int main()
{
    CHandleMemory();
    CppHandleMemory();
    useDoubleArray();
    useUniquePtr();
    useSharedPtr();
    useWeakPtr();
}
