#ifndef MY_CLASS_H  // you must protect your h file by guards
#define MY_CLASS_H

/*  In the header file, you declare the class. The definition goes to the cpp file */
class MyClass
{
    int value_;

   public:
    MyClass(int value);
    int veryComplexMethod();
    inline int value() const { return value_; }  // for very short and basic function, you can inline it in the header file
};

#endif  // MY_CLASS_H