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
    std::cout << "[DEBUG]: default constructor of <my::Array> has been called." << std::endl;
}





//==================================================================================================
//          TYPE:    Constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    1) <std::initializer_list> doesn't have overloaded subscription operator "[]" --
//                      that is why need to use initializer_list::begin() function.
//                   2) Here we can pass initializer list with size lower than array's size - in such
//                      case I just copy values from list in array and do not change array's left
//                      values. But may be it will be better to accept only 2 options: initializer
//                      list of exactly the same size and 1-elemnt size (for all array's elements).
//==================================================================================================
template <typename Type, unsigned int size>
my::Array<Type, size>::Array(std::initializer_list<Type> list)
{
    auto listSize {list.size()};

    assert(size >= listSize && "[ERROR]: initializer list's size must be no more than array's size ");

    for (int ii {0}; ii < listSize; ++ii) {
        mb_data[ii] = list.begin()[ii];
    }

}



//==================================================================================================
//          TYPE:    Non-const version of subscription operator
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
//          TYPE:    Non-const version of subscription operator
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

