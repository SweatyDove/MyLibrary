/***************************************************************************************************
 * This file contains tests of functions from 'my_utilities'
 **************************************************************************************************/

#include <iostream>
#include "my_utilities.h"





int main()
{
    char buffer[256] {0};

    my::readLineToBuffer(buffer, 256);
    int a {5};
    auto b = my::move(a);
    std::cout << my::getRandomNumber(1, 100) << std::endl;

//    int     intToChar(int intNumber, char* buffer, int sizeOfBuffer);
//    void    invertBuffer(char* buffer, int fromElement, int toElement);
//    int     copyString(const char *sourceAdress, char *destinationAdress, const int numberOfSymbols);




    return 0;
}









