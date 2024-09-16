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




} // End of "my" namespace


#endif // MY_ARRAY_H
