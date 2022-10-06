#include "my_utilities.h"

//===============================================================================
// Convert integer number @intNumber into the set of chars, that represent all
// number's digits. That set is placed into the @buffer of size @sizeOfBuffer.
//===============================================================================
int my::intToChar(int intNumber, char* buffer, int sizeOfBuffer)
{
    int quotient    {intNumber};
    int base        {10};
    char* bufferPtr {buffer};

    int ii {0};

    // #### Have to reserve two positions in the @buffer (for the last "remainder"
    // #### and '\0').
    while ((ii < sizeOfBuffer - 2) && (quotient >= base)) {
        *bufferPtr++ = (quotient % base) + '0';

        quotient /= base;
        ++ii;
    }

    // #### It's OK if we exit for()-loop by second condition.
    if (quotient < base) {
        *bufferPtr++ = quotient + '0';
        *bufferPtr = '\0';

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



//===============================================================================
// Function just invert elements of C-buffer @buffer.
// Buffer has least one element: '\0'.
//===============================================================================
int my::invertBuffer(char* buffer, int fromIndex, int toIndex)
{
    char* a {buffer + fromIndex};
    char* b {buffer + toIndex};

    while (a < b) {
        *a ^= *b;
        *b ^= *a;
        *a ^= *b;

        ++a;
        --b;
    }

    return 0;
}

//===============================================================================
// NAME:
// GOAL: Copy string (substring) from @sourceAdress into the string (substring)
//       @destinationAdress.
//       If (@numberOfSymbols == 0) -> copy symbols till met '\0' in the source.
//       Else -> copy @numberOfSymbols symbols.
//===============================================================================
int my::copyString(char *sourceAdress, char *destinationAdress, int numberOfSymbols)
{
    // #### Copy all symbols
    if (numberOfSymbols == 0) {
        while (*destinationAdress++ = *sourceAdress++) {
            ; // Nothing to do
        }
    }
    // #### Copy @numberOfSymbols symbols
    else {
        while ((*destinationAdress++ = *sourceAdress++) && numberOfSymbols-- > 0 ) {
            ;
        }
    }

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
