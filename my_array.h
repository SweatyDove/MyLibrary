#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <initializer_list>


namespace my {


//==================================================================================================
//         TYPE:    Class
//   PARAMETERS:    --------
// RETURN VALUE:    --------
//  DESCRIPTION:    Class, representing my version of <std::array>
//     COMMENTS:    --------
//==================================================================================================
template <typename Type, int size>
class Array {
private:
    int mb_length;
    Type mb_data[];

public:
    Array(int length);
    Array(std::initializer_list<Type> list);
};




} // End of "my" namespace


#endif // MY_ARRAY_H
