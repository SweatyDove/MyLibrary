/***************************************************************************************************
 * This file contains definitions for the NON-TEMPLATED part of the <my::DynamicArray> class
 **************************************************************************************************/
#include "my_dynamicarray.h"


//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
my::DynamicArrayException::DynamicArrayException(const char* description) :
    my::Exception {description}
{
    // Nothing to do
}



//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
const char* my::DynamicArrayException::what() const
{
    return mb_description;
}
