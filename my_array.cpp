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



//==================================================================================================
//          TYPE:    --------
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


