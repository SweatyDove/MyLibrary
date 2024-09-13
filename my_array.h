#ifndef MY_ARRAY_H
#define MY_ARRAY_H


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
    int mb_length {0};
    Type* mb_data {nullptr};

public:
    Array();
};




} // End of "my" namespace


#endif // MY_ARRAY_H
