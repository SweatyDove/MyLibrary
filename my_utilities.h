#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <iostream>




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



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Cast l-value reference into the r-value reference
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Couldn't place definition in cpp file because, in such case need to create new
//                  file (my_utilities.hpp) and place h/cpp-defines in it. But it causes errors with
//                  multiple definitions.
//==================================================================================================
template <typename Type>
Type&& move(Type& value)
{
    return static_cast<Type&&>(value);
}



//==============================================================================
// Function reads an input line (till '\n' inclusively) into the buffer @buffer.
//==============================================================================
int readLineToBuffer(char* buffer, int sizeOfBuffer);



int     intToChar(int intNumber, char* buffer, int sizeOfBuffer);
void    invertBuffer(char* buffer, int fromElement, int toElement);
int     copyString(const char *sourceAdress, char *destinationAdress, const int numberOfSymbols);


} // End of 'my' namespace



#endif // MY_UTILITIES_H
