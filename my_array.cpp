#include "my_array.h"



//==================================================================================================
//          TYPE:    Default constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
my::Array<Type, size>::Array()
{
    static_assert(size > 0, "Array's size must be more than 0");
    std::cout << "[DEBUG]: default constructor of <my::Array> has been called." << std::endl;
}





//==================================================================================================
//          TYPE:    Constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    1) <std::initializer_list> doesn't have overloaded subscription operator "[]" --
//                      that is why need to use initializer_list::begin() function.
//                   2)
//==================================================================================================
template <typename Type, unsigned int size>
my::Array<Type, size>::Array(std::initializer_list<Type> list)
{
    auto listSize {list.size()};


    static_assert(size > 0, "Array's size must be more than 0");
    assert(listSize == size || (listSize == 1) && "[ERROR]: incorrect initializer list's size");


    int ii {0};
    int kk {(listSize == 1) ? 0 : ii};
    while (ii < size) {
        mb_data[ii] = list.begin()[kk];
        ++ii;
        kk = (listSize == 1) ? 0 : ii;
    }


}



//==================================================================================================
//          TYPE:    NON-CONST version of subscription operator
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
Type& my::Array<Type, size>::operator[](int index)
{
    if (index >= 0) {
        assert(index < size && "[ERROR]: non-negative index must be in range [0; size)");
        return mb_data[index];
    }
    else {
        assert(index >= -size && "[ERROR]: negative index must be in range [-1; -size]");
        return mb_data[size + index];
    }
}



//==================================================================================================
//          TYPE:    CONST version of subscription operator
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
const Type& my::Array<Type, size>::operator[](int index) const
{
    if (index >= 0) {
        assert(index < size && "[ERROR]: non-negative index must be in range [0; size)");
        return mb_data[index];
    }
    else {
        assert(index >= -size && "[ERROR]: negative index must be in range [-1; -size]");
        return mb_data[size + index];
    }

}



//==================================================================================================
//          TYPE:    General function
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
std::ostream& my::operator<<(std::ostream& out, const my::Array<Type, size>& array)
{
    out << '[';
    int ii {0};
    while (ii < size - 1) {
        out << array[ii++] << ", ";
    }
    out << array[ii] << "]";

    return out;
}



//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//  RETURN VALUE:   --------
//   DESCRIPTION:   --------
// COMMENTS/BUGS:   It will be a good idea to generate compile-time warning if size != argSize, but
//                  as far as I know, without some tricks (using unused variables: https://stackoverflow.com/questions/77549920/conditional-compile-time-warning-in-c)
//                  I couldn't do this...
//==================================================================================================
template <typename Type, unsigned int size>
template <unsigned int argSize>
my::Array<Type, size>& my::Array<Type, size>::operator=(const Array<Type, argSize>& array)
{
    // ######## Just an info message (see the COMMENTS/BUGS section in the description above)
    if (size != argSize) {
        std::cout << "[WARNING]: operator= is invoked with arrays of diferent sizes. Be carefull!"
                  << std::endl;
    }
    else {};

    // ######## Evaluate maximum size of submitted arrays and copy that amount of values from
    // ######## right to left array
    unsigned int maxSize {(size < argSize) ? size : argSize};
    for (int ii {0}; ii < maxSize; ++ii) {
        (*this)[ii] = array[ii];
    }

    // ######## Return left array
    return *this;

}



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, unsigned int size>
unsigned int my::Array<Type, size>::getSize() const
{
    return size;
}

