#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <iostream>
#include <cassert>



//==================================================================================================
//          TYPE:   Namespace
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
namespace my {

enum class RetCode {
	NO_ERROR = 0,

};



template <typename Type>
Type&&  move(Type& value);


int     getRandomNumber(int min, int max);
int     readLineToBuffer(char* buffer, int sizeOfBuffer);
int     intToChar(int intNumber, char* buffer, int sizeOfBuffer);
void    invertBuffer(char* buffer, int fromElement, int toElement);
int     copyString(const char *sourceAdress, char *destinationAdress, const int numberOfSymbols);

float   power(int base, int exp);
float   binToFloat(char str);


} // End of 'my' namespace




#include "Implementations/my_utilities.hpp"


#endif // MY_UTILITIES_H
