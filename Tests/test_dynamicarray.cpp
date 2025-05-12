/***************************************************************************************************
 * Prototype of the file that should contain tests for the <my::DynamicArray> class
 **************************************************************************************************/

#include <iostream>
#include "my_dynamicarray.h"





int main()
{
    my::DynamicArray<int> d {1, 2, 3};
    std::cout << d << std::endl;

    d.pushBack(4);
    d.pushBack(5);
    std::cout << d << std::endl;

    return 0;
}
