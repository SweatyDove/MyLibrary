/***************************************************************************************************
 * This file contains definitions for the NON-TEMPLATED part of the <my::SmartPtr> class
 **************************************************************************************************/
#include "my_smartptr.h"


//==================================================================================================
//          TYPE:    Constructor
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
my::SmartPtrException::SmartPtrException(const char* description) :
    my::Exception(description)
{
    // Nothing to do
}


//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
const char* my::SmartPtrException::what() const
{
    return mb_description;
}
