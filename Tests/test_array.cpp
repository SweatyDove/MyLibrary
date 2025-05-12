/***************************************************************************************************
 * Prototype of the file that should contain tests for <my::Array> class
 **************************************************************************************************/

#include <iostream>
#include "my_array.h"





int main()
{
    my::Array<int, 5> a {1, 2, 3, 4, 5};
    std::cout << a << std::endl;

    return 0;
}
