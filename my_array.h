#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <initializer_list>
#include <iostream>
#include <cassert>
#include <type_traits>              // For std::enable_if_t

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
    // Constructors and destructors
    Array();
    Array(std::initializer_list<Type> list);

    // Subscriprion operators
    Type& operator[](int index);
    const Type& operator[](int index) const;

    // Copy assignment
    template <unsigned int otherSize>
    Array<Type, size>& operator=(const Array<Type, otherSize>& otherArray);

    // Copy constructor
//    Array& operator=(const Array&);


    // Interface
    unsigned int getSize() const;

};


/***************************************************************************************************
 * I couldn't declare operator<< inside the class declaration 'cause some errors - need to sort out
 * this issue
 **************************************************************************************************/
template <typename Type, unsigned int size>
std::ostream& operator<<(std::ostream& out, const Array<Type, size>& array);


//template <typename Type, unsigned int thisSize, unsigned int argSize>
//Array<Type, thisSize>& operator=(Array<Type, thisSize>& thisArr, const Array<Type, argSize>& argArr);






} // End of "my" namespace


#endif // MY_ARRAY_H
