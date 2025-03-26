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
my::PrettyPrint::PrettyPrint(std::array<bool, static_cast<int>(Level::TOTAL)> levels,
                             bool time,
                             bool funcName,
                             bool levelType,
                             int hardMargin) :
    mb_level {levels},

    mb_timeDisplay {time},
    mb_funcNameDisplay {funcName},
    mb_levelTypeDisplay {levelType},

    mb_hardMargin {hardMargin}
{
//    this->selfTest();
}






//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Set displayed information levels.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::displayLevel(bool displayLevelType)
{
    mb_levelTypeDisplay = displayLevelType;
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
//   DESCRIPTION:   Form a time string and place it into @mb_header
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::formTime()
{
    if (mb_timeDisplay == true) {

        std::time_t     timeStamp;
        int             buffSize {32};
        char            timeBuff[buffSize];

        std::memset(timeBuff, '\0', buffSize);


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

        // ## Push time into @mb_header
        mb_header.push_back('[');
        mb_header.append(timeBuff);
        mb_header.push_back(']');
    }
    else {} // Nothing to do
}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Form a level of the message and place it into @mb_header
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::formLevel(Level level)
{

    if (mb_levelTypeDisplay == true) {
        mb_header.push_back('[');

        switch (level) {
        case Level::DEBUG:
            mb_header.append("DEBUG");
            break;
        case Level::INFO:
            mb_header.append(" INFO");
            break;
        case Level::WARN:
            mb_header.append(" WARN");
            break;
        case Level::ERROR:
            mb_header.append("ERROR");
            break;
        }

        mb_header.push_back(']');
    }
    else {} // Nothing to do

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Forming the name of the caller function
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   At this moment I'm using placeholder for the function name.
//                  Unfortunately, I couldn't get caller name with the usage of backtrace()/backtrace_symbols()
//                  functions - thats why they are commented out.
//                  But simple realization requires of independent initialization in each function -
//                  it is too complicated I suppose.
//==================================================================================================
void my::PrettyPrint::formCallerName()
{
    if (mb_funcNameDisplay == true) {

        mb_header.push_back('[');
        mb_header.append("FUNC: ");
        mb_header.append(mb_callerName);
//        mb_header.append("()");
        mb_header.push_back(']');

    }
    else {} // Nothing to do



//    if (mb_levelDisplay == true) {
//        mb_header.push_back('[');

//        int         stackLevel {4};                            // Stack level to climb to
//        void*       buffer[stackLevel] {nullptr};
//        int         retValue {0};
//        char**      strings {};

//        retValue = backtrace(buffer, stackLevel);

//        int minSize = (stackLevel < retValue) ? stackLevel : retValue;



//        strings = backtrace_symbols(buffer, minSize);
//        for (int ii {0}; ii < minSize; ++ii) {
//            std::cout << strings[ii] << std::endl;
//        }

//        std::string callerName {strings[stackLevel - 1]};
//        int nameStart {callerName.find_first_of('(', 0) + 1};
//        int nameEnd {callerName.find_first_of('+', nameStart)};

//        std::string caller {callerName.substr(nameStart, nameEnd - nameStart)};



//        mb_header.append(caller);
//        mb_header.push_back(']');

//        free(strings);

//    }
//    else {} // Nothing to do


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
void my::PrettyPrint::setTopBorder(const char* border)
{
    mb_topBorder = border;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::setBottomBorder(const char* border)
{
    mb_bottomBorder = border;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::setCallerName(const char* callerName)
{
    mb_callerName = callerName;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::setFiller(const char filler)
{
    mb_filler = filler;
}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::setLevels(std::array<bool, static_cast<int>(Level::TOTAL)> outputLevels)
{
    mb_level = outputLevels;

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
//   DESCRIPTION:   Output message with "DEBUG" prefix
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::debug(const char* formatLine, ...)
{
    std::va_list    argList;                               // List of optional arguments (under ellipsis)
    int             level {static_cast<int>(Level::DEBUG)};

    if (mb_level[level] == true) {

        va_start(argList, formatLine);                      // Set up argList on first optional argument
        this->formOutput(Level::DEBUG, formatLine, argList);
        va_end(argList);

        std::cout << mb_output << std::endl;

    }
    else {} // Nothing to do

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Output message with "DEBUG" prefix
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::info(const char* formatLine, ...)
{
    std::va_list    argList;                               // List of optional arguments (under ellipsis)
    int             level {static_cast<int>(Level::INFO)};

    if (mb_level[level] == true) {

        va_start(argList, formatLine);                      // Set up argList on first optional argument
        this->formOutput(Level::INFO, formatLine, argList);
        std::cout << mb_output << std::endl;
        va_end(argList);


    }
    else {} // Nothing to do

}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Output message with "DEBUG" prefix
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::warn(const char* formatLine, ...)
{
    std::va_list    argList;                               // List of optional arguments (under ellipsis)
    int             level {static_cast<int>(Level::WARN)};

    if (mb_level[level] == true) {

        va_start(argList, formatLine);                      // Set up argList on first optional argument
        this->formOutput(Level::WARN, formatLine, argList);
        std::cout << mb_output << std::endl;
        va_end(argList);

    }
    else {} // Nothing to do

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Output message with "DEBUG" prefix
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::error(const char* formatLine, ...)
{
    std::va_list    argList;                               // List of optional arguments (under ellipsis)
    int             level {static_cast<int>(Level::ERROR)};

    if (mb_level[level] == true) {

        va_start(argList, formatLine);                      // Set up argList on first optional argument
        this->formOutput(Level::ERROR, formatLine, argList);
        std::cout << mb_output << std::endl;
        va_end(argList);

    }
    else {} // Nothing to do

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Form the header part of the message
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
int my::PrettyPrint::formHeader(Level level)
{
    // # Remove last data
    mb_header.clear();

    // # Form the current time of the message and place it into the @mb_header
    if (mb_timeDisplay == true) {
        formTime();
    }
    else {} // Nothing to do


    // # Form the caller function name
    if (mb_funcNameDisplay == true) {
        // ## Check last header element to figure out if it is needed to print @mb_separator
        if (mb_timeDisplay == true) {
            mb_header.append(mb_separator);
        }
        else {} // Nothing to do
        formCallerName();
    }
    else {} // Nothing to do


    // # Form the message output level
    if (mb_levelTypeDisplay == true) {
        // ## Check last header element to figure out if it is needed to print @mb_separator
        if (mb_funcNameDisplay == true || mb_timeDisplay == true) {
            mb_header.append(mb_separator);
        }
        else {} // Nothing to do
        formLevel(level);
    }
    else {} // Nothing to do


    // # Form end of the header line
    if (mb_separateHeader == true) {
        for (int ii {mb_header.size()}; ii < mb_hardMargin; ++ii) {
            mb_header.push_back(':');
        }
    }
    else {
        mb_header.append(": ");
    }

    return mb_header.size();

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Form the base message for different output levels
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
int my::PrettyPrint::formMessage(const char* formatLine, std::va_list argList)
{

    bool    leftAlign {false};                          // Left alignment of the argument
    int     fieldWidth {0};                             // Field width for the argument
    int     precision {-1};                               // Required precision
    int     floatDefaultPrecision {6};                  // Default precision for float number
    int     length {0};                                 // Length of the optional argument
    int     tempVal {0};

    int intArg {0};
    double doubleArg {0.0};
    char *cStrArg {nullptr};



    // # Clear the mb_message string from old data
    mb_message.clear();

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

                // ######## Other space in field fill with @mb_filler
                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
                    --fieldWidth;
                }
            }
            // #### Right allignment
            else {
                // ######## Left some space for the @intArg with the given @precision and fill other
                // ######## space with @mb_filler
                if (precision > 0) {
                    fieldWidth = (precision > length) ? fieldWidth - precision : fieldWidth - length;
                }
                else {
                    fieldWidth = fieldWidth - length;
                }


                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
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

            //## FLOAT ARGUMENT
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

                // ######## Fill the left space with @mb_filler
                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
                    --fieldWidth;
                }
            }
            // #### RIGHT ALIGNMENT
            else {
                precision = (precision < 0) ? floatDefaultPrecision : precision;
                fieldWidth -= (length + precision + ((precision > 0) ? 1 : 0)); // Last member for '.'
                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
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

            // #### LEFT ALIGNMENT (not sure if this is correct to increment original pointer to the
            // #### @cStrArg). Maybe better to use separate pointer (like 'q' above).
            if (leftAlign) {

                // ######## Print the whole string
                if (precision < 0) {
                    while (*cStrArg) {
                        mb_message.push_back(*cStrArg);
                        ++cStrArg;
                        --fieldWidth;
                    }
                }
                // ######## Print @precision symbols or full string if @precision > string length
                else if (precision > 0) {
                    while (*cStrArg && precision > 0) {
                        mb_message.push_back(*cStrArg);
                        ++cStrArg;
                        --fieldWidth;
                        --precision;
                    }
                }
                // ######## Do not print string at all
                else {} // Nothing to do

                // ######## The left space fill with @mb_filler symbol
                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
                    --fieldWidth;
                }
            }
            // #### RIGHT ALIGNMENT
            else {
                // ######## Calculate the amount of symbols, that have to be filled with @mb_filler
                if (precision < 0) {
                    fieldWidth = fieldWidth - length;
                }
                else if (precision > 0) {
                    fieldWidth = fieldWidth - ((precision < length) ? precision : length);
                }
                else {} // Nothing to do

                // ######## Fill the 'free' space with @mb_filler
                while (fieldWidth > 0) {
                    mb_message.push_back(mb_filler);
                    --fieldWidth;
                }

                // ######## Print the whole string
                if (precision < 0) {
                    while (*cStrArg != '\0') {
                        mb_message.push_back(*cStrArg);
                        ++cStrArg;
                    }
                }
                // ######## Print @precision symbols or full string if @precision > string length
                else if (precision > 0) {
                    for (int ii {0}; ii < ((precision < length) ? precision : length); ++ii) {
                        mb_message.push_back(*(cStrArg + ii));
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

    return mb_message.size();

}

//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Form output message taking into account the soft/hard margin
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::PrettyPrint::formOutput(Level level, const char* fmtLine, std::va_list argList)
{
    int                 leftSpace       {};
    int                 headerSize      {this->formHeader(level)};
    int                 messageSize     {this->formMessage(fmtLine, argList)};
    const std::string   delimeter       {" \t"};


    // # At this moment do not consider cases, where header length is to high
    assert (headerSize <= mb_hardMargin && "Length of header is larger than hard margin. Abort");

    mb_output.clear();

    int borderEdge {mb_topBorder.size()};
    borderEdge = (borderEdge < mb_hardMargin) ? borderEdge : mb_hardMargin;
    if (borderEdge > 0) {
        mb_output.push_back('\n');
    }
    else {} // Nothing to do

    for (int ii {0}; ii < borderEdge; ++ii) {
        mb_output.push_back(mb_topBorder[ii]);
    }

    /*
     * In the abcence of the header at all I got an empty string...
     */
    mb_output.push_back('\n');
    mb_output += mb_header;


    if (mb_separateHeader == true) {
        mb_output.push_back('\n');
        leftSpace = mb_hardMargin;
    }
    else {
        leftSpace = mb_hardMargin - headerSize;
    }



    int startPos {0};
    int lastValidPos {0};            // Last position lower than margin
    int newPos {0};

    while (newPos != std::string::npos) {

        // # Find of the next occurrence of the delimeter
        newPos = mb_message.find_first_of(delimeter, lastValidPos + 1);

        if (newPos == std::string::npos) {
            mb_output += mb_message.substr(startPos, messageSize);
        }
        else if (newPos - startPos < leftSpace) {
            lastValidPos = newPos;
        }
        else {
            mb_output += mb_message.substr(startPos, lastValidPos - startPos);
            mb_output.push_back('\n');                  // Replace last space/tab with new-line character
            startPos = lastValidPos + 1;
            leftSpace = mb_hardMargin;
        }
    }

    borderEdge = mb_bottomBorder.size();
    borderEdge = (borderEdge < mb_hardMargin) ? borderEdge : mb_hardMargin;
    if (borderEdge > 0) {
        mb_output.push_back('\n');
    }
    else {} // Nothing to do

    for (int ii {0}; ii < borderEdge; ++ii) {
        mb_output.push_back(mb_bottomBorder[ii]);
    }


}





//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Есть ли способ как-то объединить в структуре <test> сразу три типа значения и потом
//                  по разному инициализировать каждую такую структуру в массиве testArray? Пока такого
//                  сделать не получилось у меня (по крайней мере, через использование 'объединений').
//==================================================================================================
bool my::PrettyPrint::selfTest()
{
    int a {759};
    double d {3.1415};
    char* cString {"Hello, world!"};

//    struct test {
//        const char* fmtStr;
//        union param {
//            int intParam;
//            float floatParam;
//            const char* cStrParam;
//        } parameter;
//    };

    struct intTest {
        const char* fmtStr;
        int arg;
    };

    struct floatTest {
        const char* fmtStr;
        double arg;
    };

    struct cStrTest {
        const char* fmtStr;
        char* arg;
    };




    std::array<intTest, 7> intTestArray = {
        {
            {"%%d %d", a},
            {"%15d", a},
            {"%-15d", a},
            {"%.d", a},
            {"%15.7d", a},
            {"%15.0d", a},
            {"%-15.4d", a},
        }
    };


    std::array<floatTest, 7> floatTestArray = {
        {
            {"%%f %f", d},
            {"%f", d},
            {"%15f", d},
            {"%-15f", d},
            {"%.f", d},
            {"%15.0f", d},
            {"%-15.4f", d},
        }
    };


    std::array<cStrTest, 7> cStrTestArray = {
        {
            {"%%s %s", cString},
            {"%s", cString},
            {"%15s", cString},
            {"%-15s", cString},
            {"%.s", cString},
            {"%15.0s", cString},
            {"%-15.4s", cString},
        }
    };



    bool result {true};

    int resSize {256};
    char expectedResult[resSize];
    std::memset(expectedResult, '\0', resSize);


    // # Group of <int> tests
    for (int ii {0}; ii < intTestArray.size(); ++ii) {

        int n {0};

        n = std::sprintf(expectedResult, intTestArray[ii].fmtStr, intTestArray[ii].arg);
        this->debug(intTestArray[ii].fmtStr, intTestArray[ii].arg);

        if (mb_message.compare(expectedResult) != 0) {
            result = false;
            std::cout << "\n[PrettyPrint]::[int group]: test #" << ii << " is FAILED" << std::endl;
            std::cout << "         [Expected result]: \"" << expectedResult << '\"' << std::endl;
            std::cout << "         [Obtained result]: \"" << mb_message << '\"' << std::endl;
        }
        else {
            std::cout << "\n[PrettyPrint]::[int group]: test #" << ii << " is PASSED" << std::endl;
        } // Nothing to do

        std::memset(expectedResult, '\0', n);
        mb_message.clear();
    }

    // # Group of <float> tests
    for (int ii {0}; ii < floatTestArray.size(); ++ii) {

        int n {0};

        n = std::sprintf(expectedResult, floatTestArray[ii].fmtStr, floatTestArray[ii].arg);
        this->debug(floatTestArray[ii].fmtStr, floatTestArray[ii].arg);

        if (mb_message.compare(expectedResult) != 0) {
            result = false;
            std::cout << "\n[PrettyPrint]::[float group]: test #" << ii << " is FAILED" << std::endl;
            std::cout << "           [Expected result]: \"" << expectedResult << '\"' << std::endl;
            std::cout << "           [Obtained result]: \"" << mb_message << '\"' << std::endl;
        }
        else {
            std::cout << "\n[PrettyPrint]::[float group]: test #" << ii << " is PASSED" << std::endl;
        } // Nothing to do

        std::memset(expectedResult, '\0', n);
        mb_message.clear();
    }

    // # Group of <const char*> tests
    for (int ii {0}; ii < cStrTestArray.size(); ++ii) {

        int n {0};

        n = std::sprintf(expectedResult, cStrTestArray[ii].fmtStr, cStrTestArray[ii].arg);
        this->debug(cStrTestArray[ii].fmtStr, cStrTestArray[ii].arg);

        if (mb_message.compare(expectedResult) != 0) {
            result = false;
            std::cout << "\n[PrettyPrint]::[c-string group]: test #" << ii << " is FAILED" << std::endl;
            std::cout << "              [Expected result]: \"" << expectedResult << '\"' << std::endl;
            std::cout << "              [Obtained result]: \"" << mb_message << '\"' << std::endl;
        }
        else {
            std::cout << "\n[PrettyPrint]::[c-string group]: test #" << ii << " is PASSED" << std::endl;
        } // Nothing to do

        std::memset(expectedResult, '\0', n);
        mb_message.clear();
    }


    return result;
}



















