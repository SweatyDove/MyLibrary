#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <iostream>




namespace my {

enum class RetCode {
	NO_ERROR = 0,

};



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Cast l-value reference into the r-value reference
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Couldn't place definition in cpp file because, in such case need to create new
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


//===============================================================================
// Convert integer number @intNumber into the set of chars, that represent all
// number's digits. That set is placed into the @buffer of size @sizeOfBuffer.
//===============================================================================
int intToChar(int intNumber, char* buffer, int sizeOfBuffer);

//===============================================================================
// Function just invert @buffer of size @sizeOfBuffer
//===============================================================================
int invertBuffer(char* buffer, int fromElement, int toElement);

//===============================================================================
// TYPE:
// GOAL: Copy string (substring) from @sourceAdress into the string (substring)
//       @destinationAdress.
//       If (@numberOfSymbols == 0) -> copy symbols till met '\0' in the source.
//       Else -> copy @numberOfSymbols symbols.
//===============================================================================
int copyString(const char *sourceAdress, char *destinationAdress, int numberOfSymbols);

}

#endif // MY_UTILITIES_H
