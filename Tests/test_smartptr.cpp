/***************************************************************************************************
 * Prototype of the file that should contain tests for the <my::SmartPtr> class
 **************************************************************************************************/

#include <iostream>
#include "my_smartptr.h"
#include "my_utilities.h"





int main()
{
    my::SmartPtr<int> res {new int {5}};
    std::cout << *res << std::endl;

    my::SmartPtr<int> otherRes {my::move(res)};
    std::cout << *res << std::endl;

    return 0;
}
