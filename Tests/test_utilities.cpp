/***************************************************************************************************
 * This file contains tests of functions from 'my_utilities'
 **************************************************************************************************/

#include <iostream>
#include "my_utilities.h"



int main()
{
    int a {125};
    int b {999};

    int c {23};
    int d {17};

    my::swap(a, b);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    my::swap(my::move(c), my::move(d));
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;


    return 0;
}









