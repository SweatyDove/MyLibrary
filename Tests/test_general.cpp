/***************************************************************************************************
 * Prototype of the file that should contain tests for the all classes of MyLibrary
 **************************************************************************************************/


#include <iostream>


#include "my_string.h"
#include "my_array.h"
#include "my_dynamicarray.h"
#include "my_utilities.h"
#include "my_smartptr.h"


int main()
{
    my::String string {"Hello, "};
    my::Array<char, 6> a {'w', 'o', 'r', 'l', 'd', '!'};
    std::cout << string << a << std::endl;

    my::DynamicArray d {1, 2, 3};
    d.pushBack(my::getRandomNumber(1, 100));
    d.pushBack(my::getRandomNumber(1, 100));
    std::cout << d << std::endl;

    return 0;
}
