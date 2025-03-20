#include "my_prettyprint.h"



//==================================================================================================
//          TYPE:   General function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
bool my::isDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}






//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
my::PrettyPrint::PrettyPrint()
{
    // Nothing to do
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Set displayed information levels.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::displayLevel(bool debug, bool info, bool warning, bool error)
{
    mb_level[static_cast<int>(Level::DEBUG)] = debug;
    mb_level[static_cast<int>(Level::INFO)] = info;
    mb_level[static_cast<int>(Level::WARN)] = warning;
    mb_level[static_cast<int>(Level::ERROR)] = error;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Is it necessary to display the time?
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Add a selection of time's format.
//==================================================================================================
void my::PrettyPrint::displayTime(bool b)
{
    mb_timeDisplay = b;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Setting the display of the name of the calling function in the output.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::displayFuncName(bool b)
{
    mb_funcNameDisplay = b;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::printTime()
{
    std::time_t timeStamp;

    int buffSize {32};
    char timeBuff[buffSize];

    std::memset(timeBuff, '\0', buffSize);

    if (mb_timeDisplay == true) {
        // ## Copy current time value into buffer
        std::time(&timeStamp);
        std::strncpy(timeBuff, std::ctime(&timeStamp), buffSize);

        // ## Delete/replace last new-line character(s) with '\0'
        for (int ii {buffSize - 1}; ii > 0; --ii) {
            if (timeBuff[ii] == '\0') {
                continue;
            }
            else if (timeBuff[ii] == '\n') {
                timeBuff[ii] = '\0';
            }
            else {
                break;
            }
        }

        // ## Display time
        std::cout << '[' << timeBuff << ']';
        printSeparator();

    }
    else {} // Nothing to do
}





//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
//void my::PrettyPrint::printFuncName()
//{
//    std::

//}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::setSeparator(const char* sep)
{
    mb_separator = sep;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::printSeparator()
{
    std::cout << mb_separator;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::debug(char* line)
{
    if (mb_level[static_cast<int>(Level::DEBUG)] == true) {
        printTime();
        std::cout << "[DEBUG]=> " << line << std::endl;
    }
    else {
        // Nothing to do
    }
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Form the base message for different output levels
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Если после символа '.' ничего не стоит или стоит ноль, то в обоих случаях
//                  точность считается нулевой.
//==================================================================================================
void my::PrettyPrint::formMessage(const char* formatLine, ...)
{

    bool    leftAlign {false};                          // Left alignment of the argument
    int     fieldWidth {0};                             // Field width for the argument
    int     precision {-1};                               // Required precision
    int     floatDefaultPrecision {6};                  // Default precision for float number
    int     basePrecision {0};                          // Teporary value for precision
    int     length {0};                                 // Length of the optional argument
    int     tempVal {0};

    int intArg {0};
    double doubleArg {0.0};
    char *cStrArg {nullptr};

    std::va_list argList;                               // List of optional arguments (under ellipsis)

    va_start(argList, formatLine);                      // Set up argList on first optional argument

    // # Go through the @formatLine to find the type of the first optional argument
    for (const char* p {formatLine}; *p; ++p) {

        // ## If '%' symbol - need to check next symbol, otherwise, push it onto the @mb_message
        if (*p != '%') {
            mb_message.push_back(*p);
            continue;
        }
        else {
            ++p;
        }


        // ## Handle the output properties

        // #### Alignment
        if (*p == '-') {
            leftAlign = true;
            ++p;
        }
        else {} // Nothing to do

        // #### Field width
        while (my::isDigit(*p)) {
            fieldWidth = fieldWidth * 10 + (*p - '0');
            ++p;
        }

        // #### Precision:
        // ####   INT: -1 means display full value, 0 or nothing (after '.') has no effect, >0 - print '0' before.
        // #### FLOAT: -1 means display full value, 0 or nothing (after '.') means not to display fractional part,
        // ####        >0 - print additional values for fractional part (but maybe better to limit with 7 for float and 15 for double)
        // ####   STR: -1 means display full string, 0 or nothing (after '.') means do not display string at all,
        // ####        0 < precision <= string length - display precision symbols; precision > string length - print full string
        if (*p == '.') {
            precision = 0;
            ++p;
            // ######## Case of the presence some 'precision' value
            while (my::isDigit(*p)) {
                precision = precision * 10 + (*p - '0');
                ++p;
            }
        }
        else {} // Nothing to do


        // ## Handle the format specifier
        switch(*p) {

        // ## INTEGER ARGUMENT
        case 'd':

            // #### Read the next argument as integer and calculate its length
            intArg = va_arg(argList, int);
            length = 1;
            tempVal = intArg;
            while((tempVal /= 10) != 0) {
                ++length;
            }

            // #### Left allignment
            if (leftAlign) {

                // ######## Replace 'freespace' with '0'
                if (precision > 0) {
                    while (precision > length) {
                        mb_message.push_back('0');
                        --fieldWidth;
                        --precision;
                    }
                }
                else {} // Nothing to do

                // ######## Push @intArg to the @mb_message and reduce the remaining @fieldWidth
                mb_message += std::to_string(intArg);
                fieldWidth -= length;

                // ######## Other space in field fill with '_' symbol
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }
            }
            // #### Right allignment
            else {
                // ######## Left some space for the @intArg with the given @precision and fill other
                // ######## space with '_'
                fieldWidth = (precision > 0) ? fieldWidth - precision - length : fieldWidth - length;
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }

                // ######## At this step we need to take into account the representation @precision
                // ######## of the @intArg
                if (precision > 0) {
                    precision -= length;
                    while (precision > 0) {
                        mb_message.push_back('0');
                        --precision;
                    }
                }
                else {} // Nothing to do
                mb_message += std::to_string(intArg);
            }

            // #### Reinitialization of some parameters
            fieldWidth = 0;
            precision = -1;
            leftAlign = false;

            break;

        // ## FLOAT ARGUMENT
        case 'f':

            doubleArg = va_arg(argList, double);

            // #### Cut off left part of the @doubleArg and calculate its length (i.e. length of integer part)
            intArg = static_cast<int>(doubleArg);
            length = 1;
            tempVal = intArg;
            while ((tempVal /= 10) != 0) {
                ++length;
            }

            // #### Separately save fractional part of the @doubleArg
            doubleArg = doubleArg - intArg;

            // #### LEFT ALIGNMENT
            if (leftAlign) {
                mb_message += std::to_string(intArg);
                fieldWidth -= length;

                // ######## Display @precision elements of fractional part (do not consider float/double limits at this moment)
                if (precision != 0) {
                    precision = (precision < 0) ? floatDefaultPrecision : precision;
                    mb_message.push_back('.');
                    --fieldWidth;
                    // ######## Separate each digit of the fractional part and push_back() it
                    while (precision > 0) {
                        tempVal = static_cast<int>(doubleArg * 10);
                        mb_message.push_back('0' + tempVal);
                        --fieldWidth;
                        doubleArg = doubleArg * 10 - tempVal;
                        --precision;
                    }
                }
                // ######## Do not display fractional part at all
                else {} // Nothing to do

                // ######## Fill the left space with '_'
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }
            }
            // #### RIGHT ALIGNMENT
            else {
                precision = (precision < 0) ? floatDefaultPrecision : precision;
                fieldWidth -= (length + precision + ((precision > 0) ? 1 : 0)); // Last member for '.'
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }
                mb_message += std::to_string(intArg);
                if (precision != 0) {
                    mb_message.push_back('.');
                    // ######## Separate each digit of the fractional part and push_back() it
                    while (precision > 0) {
                        tempVal = static_cast<int>(doubleArg * 10);
                        mb_message.push_back('0' + tempVal);
                        doubleArg = doubleArg * 10 - tempVal;
                        --precision;
                    }
                }
                else {} // Nothing to do
            }

            // #### Reinitialization of some parameters
            fieldWidth = 0;
            precision = -1;
            leftAlign = false;

            break;

        // ## C-STRING ARGUMENT
        case 's':

            cStrArg = va_arg(argList, char*);

            // #### Calculate c-style-string length
            length = 0;
            for (char* q {cStrArg}; (q != nullptr) && (*q != '\0'); ++q, ++length)
                ;

            // #### Left allignment (not sure if this is correct to increment original pointer to the
            // #### @cStrArg). Maybe better to use separate pointer (like 'q' above).
            basePrecision = precision;
            if (leftAlign) {
                while (*cStrArg) {
                    mb_message.push_back(*cStrArg);
                    ++cStrArg;
                    --fieldWidth;

                    // ######## In the case of 'absence' precision - print the whole string
                    if (basePrecision == 0) {
                        // Nothing to do
                    }
                    // ######## Below @precision means number of characters to print.
                    else {
                        if (precision > 0) {
                            --precision;
                        }
                        else {
                            break;      // Exit from while-loop
                        }
                    }
                }
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }
            }
            // #### Right allignment
            else {
                fieldWidth -= ((precision == 0) ? length : precision);
                while (fieldWidth > 0) {
                    mb_message.push_back('_');
                    --fieldWidth;
                }
                while (*cStrArg != '\0') {
                    mb_message.push_back(*cStrArg);
                    ++cStrArg;
                }
                // ######## If the @basePrecision > 0 - print chars until precision > 0.
                // ######## Otherwise - print the whole string
                if (basePrecision > 0) {
                    if (precision > 0) {
                        --precision;
                    }
                    else {
                        break;      // Exit from while-loop
                    }
                }
                else {} // Nothing to do
            }

            // #### Reinitialization of some parameters
            fieldWidth = 0;
            precision = -1;
            leftAlign = false;

            break;
        // ## OTHER SYMBOL
        default:
            mb_message.push_back(*p);
            break;
        } // End of switch-operator
    } // End of for-loop

    va_end(argList);

    std::cout << "\nObtained result: \"" << mb_message << '\"' << std::endl;
    mb_message.clear();

}



























