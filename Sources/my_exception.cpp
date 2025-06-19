#include "my_exception.h"


//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
my::Exception::Exception(const char* description) :
    mb_description {description}
{
    // Nothing to do
}


//==================================================================================================
//          TYPE:   Virtual member function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
const char* my::Exception::what() const
{
    return mb_description;
}
