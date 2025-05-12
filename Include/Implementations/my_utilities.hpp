/***************************************************************************************************
 * This file contains definitions for the TEMPLATED part of 'my utilities'
 **************************************************************************************************/
#ifndef MY_UTILITIES_HPP
#define MY_UTILITIES_HPP

#include "my_utilities.h"            // For IDE visibility




//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Cast l-value reference into the r-value reference
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Couldn't place definition in cpp file because, in such case need to create new
//                  file (my_utilities.hpp) and place h/cpp-defines in it. But it causes errors with
//                  multiple definitions.
//==================================================================================================
template <typename Type>
Type&& my::move(Type& value)
{
    return static_cast<Type&&>(value);
}


#endif
