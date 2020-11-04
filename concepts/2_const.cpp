/* 
 --- CONST ---
		Const indicates that something cannot change, in other words "the object is read-only".
        It is useful in variables and in class methods (see future concepts).
        It is good pratice to use const everywhere is possible: if a variable cannot change, qualify it as const.
        This generally helps the complier to improve performance and to optimize the generated assembly.

        For ones who comes from C, const is particullary useful to replace preprocessors #define.
        In C++, you should always try to avoid preprocessor operations: they are not part of the language, they are
        simple text-replacement which can create problem and that are always used paying attention.
*/

/*
	More info:
	https://www.youtube.com/watch?v=4fJBrditnJU&t=627s
*/

namespace my_defines
{
const int kValue1 = 1;
const int kValue2 = 2;
const int kValue3 = 3;
}  // namespace my_defines

int main(int argc, const char* argv[])
{
    const int value = 3;  // here we declare value as const.

    // THIS IS A COMPILE ERROR
    // value = 4; -> assignment of read-only variable 'value'
    // we cannot modify a variable declared const, it is read-only

    // compile-time defined const, can be used in switch cases:
    int my_value = 2;
    switch (my_value)
    {
        case my_defines::kValue1:
            /* magic stuff here */
            break;
        case my_defines::kValue2:
            /* other magic */
            break;
        case my_defines::kValue3:
            /* more magic! */
            break;
        default:
            break;
    }
    // Note: in this case my_defines::kValue1 is a 'constant-expression' since it is known at compile time.

    // In this case instead, we can define a const value which is const but it's not a constant-expression (i.e. not know at compile time):
    // THIS IS A COMPILE ERROR
    // const int argc_value = argc;
    // int my_value = 2;
    // switch (my_value)
    // {
    //     case argc_value: ->  the value of 'argc_value' is not usable in a constant expression
    //         /* magic stuff here */
    //         break;
    //     default:
    //         break;
    // }

    return 0;
}
