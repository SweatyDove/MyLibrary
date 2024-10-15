#include "my_array.h"



//==================================================================================================
//          TYPE:    Default constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
my::Array<Type, size>::Array()
{
    static_assert(size > 0, "Array's size must be more than 0");
//    std::cout << "[DEBUG]: default constructor of <my::Array> has been called." << std::endl;
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
template <typename Type, int size>
my::Array<Type, size>::Array(std::initializer_list<Type> list)
{
    auto listSize {list.size()};

    static_assert(size > 0, "Array's size must be more than 0");
    assert((listSize == size || (listSize == 1)) && "[ERROR]: incorrect initializer list's size");

//    std::cout << "[DEBUG]: array constructor with initializer_list has been called" << std::endl;

    int ii {0};
    int kk {(listSize == 1) ? 0 : ii};
    while (ii < size) {
        mb_data[ii] = list.begin()[kk];
        ++ii;
        kk = (listSize == 1) ? 0 : ii;
    }
}


//==================================================================================================
//          TYPE:    Destructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
my::Array<Type, size>::~Array()
{
//    std::cout << "[DEBUG]: array destructor has been called" << std::endl;
}



//==================================================================================================
//          TYPE:    NON-CONST version of subscription operator
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
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
template <typename Type, int size>
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
template <typename Type, int size>
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
//          TYPE:   Copy assignment operator with argument of the SAME @size as *this array
//   DESCRIPTION:   --------
//    PARAMETERS:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
template <typename Type, int size>
my::Array<Type, size>& my::Array<Type, size>::operator=(const my::Array<Type, size>& otherArray)
{
//    std::cout << "[my::Array]:[DEBUG]: copy assignment operator for the arrays of the SAME sizes"
//              << " has been called" << std::endl;


    for (int ii {0}; ii < size; ++ii) {
        mb_data[ii] = otherArray[ii];
    }

    // ######## Return left array
    return *this;


}


//==================================================================================================
//          TYPE:   Copy assignment operator with argument of OTHER size
//--------------------------------------------------------------------------------------------------
//    PARAMETERS:   ********
//--------------------------------------------------------------------------------------------------
//  RETURN VALUE:   ********
//--------------------------------------------------------------------------------------------------
//   DESCRIPTION:   ********
//--------------------------------------------------------------------------------------------------
// COMMENTS/BUGS:   It will be a good idea to generate compile-time warning if size != argSize, but
//                  as far as I know, without some tricks (using unused variables: https://stackoverflow.com/questions/77549920/conditional-compile-time-warning-in-c)
//                  I couldn't do this...
//==================================================================================================
template <typename Type, int size>
template <int otherSize>
my::Array<Type, size>& my::Array<Type, size>::operator=(const Array<Type, otherSize>& other)
{
//    std::cout << "[my::Array]:[DEBUG]: copy assignment operator for the arrays of DIFFERENT sizes"
//              << " has been called" << std::endl;

    // ######## Just an info message (see the COMMENTS/BUGS section in the description above)
    if (size != otherSize) {
        std::cout << "[WARNING]: operator= is invoked with arrays of diferent sizes. Be carefull!"
                  << std::endl;
    }
    else {};

    // ######## Evaluate maximum size of submitted arrays and copy that amount of values from
    // ######## right to left array
    int maxSize {(size < otherSize) ? size : otherSize};
    for (int ii {0}; ii < maxSize; ++ii) {
        (*this)[ii] = other[ii];
    }

    // ######## Return left array
    return *this;

}






//==================================================================================================
//          TYPE:    Copy constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
//template <int otherSize>
my::Array<Type, size>::Array(const my::Array<Type, size>& otherArray)
{
    // ######## Here *this array already created - constructor doesn't create or allocate
    // ######## space (in stack?) for the object - only initialize it's data
//    int maxSize {(size < otherSize) ? size : otherSize};
//    std::cout << "[DEBUG]: copy constructor of <my::Array> has been called." << std::endl;

    for (int ii {0}; ii < size; ++ii) {
        (*this)[ii] = otherArray[ii];
    }
}


//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
Type* my::Array<Type, size>::begin() const
{
    return mb_data;
}


//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
Type* my::Array<Type, size>::begin()
{
    return mb_data;
}


//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
Type* my::Array<Type, size>::end() const
{
    return (mb_data + size);
}

//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
Type* my::Array<Type, size>::end()
{
    return (mb_data + size);
}



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type, int size>
int my::Array<Type, size>::getSize() const
{
    return size;
}





