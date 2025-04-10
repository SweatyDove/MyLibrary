

/******************************************************************************
 * This file describes general utilities for different things.
 ******************************************************************************/
#include "my_utilities.h"





//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Cast l-value reference into the r-value reference
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
//template <typename Type>
//Type&& my::move(Type& value)
//{
//    return static_cast<Type&&>(value);
//}



//==============================================================================
// Function reads an input line (till '\n' inclusively) into the
// buffer [buffer].
//
// If there is not enough space for whole line in the buffer - just end it with
// the null-terminator. In the future it will allow us to concatenate line with
// the next one(s).
//
// Else we will end up with the line, that is terminated by symbols:
// '\n' and '\0'.
//
// Function returns 0 in case of success.
//==============================================================================
int my::readLineToBuffer(char* buffer, int sizeOfBuffer)
{
    char*   bufferPtr   {buffer};
    char    ch          {'\0'};

    bool    skipLeadingSpaces {true};

    while (((ch = static_cast<char>(std::cin.get())) != '\n') && (!std::cin.eof())) {

        // #1 Skip the leading whitespaces
        if (skipLeadingSpaces && (ch == ' ' || ch == '\t')) {
            continue;
        }
        else {} // Nothing to do
        skipLeadingSpaces = false;

        // #2 Have to reserve 2 positions in the buffer (for '\n' and '\0').
        if (--sizeOfBuffer - 1 <= 0) {
            std::cerr << "\n[WARNING]::[my::readLineToBuffer()]:"
                      << "\nFree space in the buffer is over. Perhaps, not all data from the input stream"
                      << "\nwere written..."
                      << std::endl;
            // # In the case of the buffer overflowing - return an extracted
            // # character back into the <std::istream> object.
            std::cin.unget();
            break;
        }
        else {
            *bufferPtr++ = ch;
        }
    }

    // #### If the new line is finished by the '\n' symbol - it's OK.
    if (ch == '\n') {
        *bufferPtr++ = '\n';
        *bufferPtr = '\0';
    }
    // #### Else if not enough space in the [buffer] - just add '\0'.
    else {
        *bufferPtr = '\0';
    }

    return 0;
}













//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Convert integer number @intNumber into the set of chars, that represent all
//                  number's digits. That set is placed into the @buffer of size @sizeOfBuffer.
//                  Also add '\0' at the end of buffer, or return error.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
int my::intToChar(int intNumber, char* buffer, int sizeOfBuffer)
{
    int quotient    {intNumber};                    //
    int base        {10};
    char* bufferPtr {buffer};

    int ii {0};

    // # Have to reserve two positions in the @buffer (for the last "remainder" and '\0').
    while ((ii < sizeOfBuffer - 2) && (quotient >= base)) {
        bufferPtr[ii] = static_cast<char>((quotient % base) + '0');
        quotient /= base;
        ++ii;
    }

    // # It's OK if we exit for-loop by 2-nd condition and have 2 free space in buffer.
    if ((ii < sizeOfBuffer - 1) && quotient < base) {
        bufferPtr[ii] = static_cast<char>(quotient + '0');
        bufferPtr[ii + 1] = '\0';
        invertBuffer(buffer, 0, ii);
        return 0;
    }
    else {
        std::cerr << "\n[ERROR]::[my::intToChar()]:"
                  << "\nBuffer can't fit all digits of the number."
                  << std::endl;
        return 1;
    }
}


//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Invert elements of C-style-buffer @buffer. Buffer has at least one element '\0'.
//                  Both edges are included.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
int my::invertBuffer(char* buffer, int fromIndex, int toIndex)
{
    char* a {buffer + fromIndex};
    char* b {buffer + toIndex};

    char temp {'\0'};
    for (int ii {fromIndex}; ii <= toIndex)

    while (a < b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;

        ++a;
        --b;
    }

    return 0;
}

//==============================================================================
// What: Global function
// Why:  Copy string (substring) from the [sourceAdress] into the string
//       (substring) at the [destinationAdress].
//
//       1) If [numberOfSymbols] == 0, then copy all symbols untill  the meeting
//       '\0' in the source string.
//       2) If [numberOfSymbols] > 0, then copy specified number of symbols plus
//          null-terminator '\0'.
//
// TRAP: If specified incorrect pointer to destination - this funnction can
//       override "title" of the block of memory, that is needed for delete[]
//       operator. In this case - delete[] will cause an error.
//==============================================================================
int my::copyString(const char *sourceAdress, char *destinationAdress, int numberOfSymbols)
{
    const char* srcPtr   {sourceAdress};
    char*       destPtr  {destinationAdress};

    // #### Copy given number of symbols
    if (numberOfSymbols > 0) {
        for (int ii {0}; ii < numberOfSymbols; ++ii) {
            *destPtr = *srcPtr;
            ++destPtr;
            ++srcPtr;
        }
        *destPtr = '\0';
    }
    // #### Copy all symbols till '\0'
    else {
        *destPtr = *srcPtr;
        while (*destPtr != '\0') {
            ++destPtr;
            ++srcPtr;
            *destPtr = *srcPtr;
        }
    }

    // #### Old version
//    if (numberOfSymbols == 0) {
//        while (*destinationAdress++ = *sourceAdress++) {
//            ; // Nothing to do
//        }
//    }
//    // #### Copy @numberOfSymbols symbols
//    else {
//        while ((*destinationAdress++ = *sourceAdress++) && numberOfSymbols-- > 0 ) {
//            ;
//        }
//    }

    return 0;
}


//int CompareStrings(char *first_str, char *second_str, int ignore_reg)
//{
//	char f, s;

//	do {
//		f = *first_str++;
//		s = *second_str++;
//		if (ignore_reg) {
//			f = mcr__ToLow(f);
//			s = mcr__ToLow(s);
//		}

//		if (f == '\0' && s == '\0')
//			return 1;
//	} while (f == s);

//	return 0;
//}



