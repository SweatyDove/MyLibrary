#include <iostream>
#include "my_array.hpp"


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

//    std::cout << intArray << std::endl;
    return 0;
}
