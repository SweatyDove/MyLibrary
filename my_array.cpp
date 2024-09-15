#include "my_array.h"



//==================================================================================================
//         TYPE:    Constructor
//   PARAMETERS:    --------
// RETURN VALUE:    --------
//  DESCRIPTION:    --------
//     COMMENTS:    --------
//==================================================================================================
template <typename Type, int size>
my::Array<Type, size>::Array(int length):
    mb_length {length}
{
    mb_data[length];
}





//==================================================================================================
//         TYPE:    Constructor
//   PARAMETERS:    --------
// RETURN VALUE:    --------
//  DESCRIPTION:    --------
//     COMMENTS:    <std::initializer_list> doesn't have overloaded subscription operator "[]" --
//                  that is why need to use initializer_list::begin() function.
//==================================================================================================
template <typename Type, int size>
my::Array<Type, size>::Array(std::initializer_list<Type> list):
    Array(static_cast<int>(list.size()))
{
    for (int ii {0}; ii < mb_length; ++ii) {
//        mb_data[ii] = list[ii];
        mb_data[ii] = list.begin()[ii];
    }

}
