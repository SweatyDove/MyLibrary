#include <iostream>
#include "my_array.hpp"


/*
 * QUESTIONS:
 *
 * 1) Order of evaluation of 3-d part (incrementing) of the for-loop-statement? (Could begin from
 *      here: https://en.cppreference.com/w/cpp/language/eval_order
 */


int main()
{
//    int a {7};
//    const int b {9};

//    int* aPtr {&a};
//    const int* aConstPtr {&a};
//    int* const constAPtr {&a};
//    const int* const conAConPtr {&a};

//    aConstPtr++;
//    (*aConstPtr)++;

//    constAPtr++;
//    (*constAPtr)++;

//    conAConPtr++;
//    (*conAConPtr)++;





    my::Array<int, 5> intArray {0, 1, 2, 3, 4};


    for (int ii {0}; ii < 5; ++ii) {
        intArray[ii] = ii * 2;
    }

    std::cout << intArray << std::endl;
    return 0;
}
