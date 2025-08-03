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
//      COMMENTS:   Запомни! my::move() - это просто штука, помогающая компилятору разрешить
//                  overload resolution. Она как бы ничего не возвращает (хоть и имеется return).
//==================================================================================================
template <typename Type>
Type&& my::move(Type& value)
{
    return static_cast<Type&&>(value);
}




//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Custom realization of 'std::forward()', that accepts forwarding reference - here
//                  it is an L-VALUE of <R-value-reference-type> or <L-value-reference-type> and
//                  then returns @value as <R-value-reference-type> of <L-value-reference-type>
//                  respectively.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <class Type>
Type&& my::forward(typename std::remove_reference<Type>::type& value)
{
    return static_cast<Type&&>(value);
}


//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Custom realization of 'std::forward()', that accepts forwarding reference - here
//                  it is an R-VALUE... other part of description is the same as description above.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <class Type>
Type&& my::forward(typename std::remove_reference<Type>::type&& value)
{
    return static_cast<Type&&>(value);
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Realization of universal swap() function,
//    PARAMETERS:   @a, @b - forwarding references
//  RETURN VALUE:   ........
//      COMMENTS:   Возможно, я вообще перемудрил с использованием forwarding reference в данном
//                  случае.
//==================================================================================================
template <typename Type>
void my::swap(Type&& a, Type&& b)
{
    /*
     * Variable @temp should be a REAL variable (not reference!). If I make it a reference - it
     * will specify on the same memory, that @a does - and in second line I got "temp = a = b"
     */
    typename std::remove_reference<Type>::type temp {my::forward<Type>(a)};
    a = my::forward<Type>(b);
    b = my::forward<Type>(temp);
}










#endif
