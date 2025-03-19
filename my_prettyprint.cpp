#include "my_prettyprint.h"




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
//   DESCRIPTION:   Form the base message for different output levels
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
//void my::PrettyPrint::formMessage()
//{

//}


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




