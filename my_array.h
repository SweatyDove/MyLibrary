#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <initializer_list>
#include <iostream>
#include <cassert>

namespace my {


//==================================================================================================
//         TYPE:    Class
//   PARAMETERS:    --------
// RETURN VALUE:    --------
//  DESCRIPTION:    Class, representing my version of <std::array>
//     COMMENTS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
class Array {
private:
    Type mb_data[size] {};

public:
    Array();
    Array(std::initializer_list<Type> list);


    Type& operator[](int index);
    const Type& operator[](int index) const;

};


/***************************************************************************************************
 * I couldn't declare operator<< inside the class declaration 'cause some errors - need to sort out
 * this issue
 **************************************************************************************************/
template <typename Type, unsigned int size>
std::ostream& operator<<(std::ostream& out, const Array<Type, size>& array);



} // End of "my" namespace


#endif // MY_ARRAY_H
