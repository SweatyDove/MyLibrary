#include <iostream>
#include "my_array.hpp"
#include <string>
#include <array>


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

//    std::array a1 {1, 2, 3};
//    std::array b1 {4, 5, 6, 7};
//    a1 = b1;
//    std::cout << a1[0] << a1[1] << a1[2] << std::endl;



    my::Array<int, 5> aaa {0, 1, 2, 3, 4};

    // Copy assignment
    my::Array<int, 9> bbb {9};
    my::Array<int, 3> ccc {3};
    bbb = aaa;
    ccc = aaa;
//    my::Array<int,5> ccc {my::Array<int, 5>(9)};


    // Copy constructor




    std::cout << aaa << std::endl;
    std::cout << bbb << std::endl;
    std::cout << ccc << std::endl;

    return 0;
}









