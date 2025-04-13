#include "my_utilities.h"



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
//                  Also add '\0' at the end of buffer.
//   PARAMETERS:    ........
// RETURN VALUE:    Number of digits of the @intNumber or -1, if there isn't enough space in buffer
//                  (including null-terminator).
//     COMMENTS:    There is a question... Should I add '\0' at the end of buffer? Should I add 1
//                  to the return value (number of digits + '\0')?
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
        return ii;
    }
    else {
        std::cerr << "\n[ERROR]::[my::intToChar()]:"
                  << "\nBuffer can't fit all number's digits and null-terminator."
                  << std::endl;
        return -1;
    }
}


//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Invert elements of <char*> @buffer. Both edges are included. It is up to user to
//                  pass correct indexes.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
void my::invertBuffer(char* buffer, int fromIndex, int toIndex)
{
    char temp {'\0'};
    for (int ii {fromIndex}, jj {toIndex}; ii < jj; ++ii, --jj) {
        temp = buffer[ii];
        buffer[ii] = buffer[jj];
        buffer[jj] = temp;
    }

}


//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Copy string (substring) from the @from address into the string (substring) at
//                  the @to address.
//
//                  1) If nums <= 0, then copy all symbols untill the meeting '\0' in the @from string.
//                  2) If nums > 0, then copy @nums of symbols plus null-terminator '\0'.
//   PARAMETERS:    @from   - address of 'copy from' data;
//                  @to     - address of 'copy to' data;
//                  @num    - number of chars to copy;
// RETURN VALUE:    ........
//     COMMENTS:    If specified incorrect pointer to destination - this funnction can override
//                  "title" of the block of memory, that is needed for delete[] operator.
//                  In this case - delete[] will cause an error.
//==================================================================================================
int my::copyString(const char *from, char *to, const int num)
{

    int ii {0};


    // # Lambda definition, that equivalent to that: (num > 0 && ii < num) || (num <= 0 && from[ii] != '\0').
    // # Decided to use lambda for practice, but instead may use macro or just expression above.
    auto condition
    {
        [=, &ii]() {return ((num > 0) ? (ii < num) : (from[ii] != '\0'));}
    };

    // #### Copy @num number of symbols
    while(condition()) {
        to[ii] = from[ii];
        ++ii;
    }
    to[ii] = '\0';

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



