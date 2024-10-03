#ifndef MY_ARRAY_H
#define MY_ARRAY_H

#include <initializer_list>
#include <iostream>
#include <cassert>
#include <type_traits>              // For std::enable_if_t

namespace my {


//==================================================================================================
//         TYPE:    Class
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//  DESCRIPTION:    Class, representing my version of <std::array>
//                  --------
//     COMMENTS:    1)  There is a problem, that I can't use "constexpr" qualifier before <my::Array>
//                      class. As I understand, in order to use constexpr qualifier - I should make
//                      <my::Array> class type a LITERAL type. There are some conditions that i need
//                      to sutisfy (constexpr functions, constructors and etc - but I'm not sure).
//                      Going to leave this issue for the future...
//                  2)  ........
//
//==================================================================================================
template <typename Type, unsigned int size>
class Array {
private:
    Type mb_data[size] {};

public:
    // ######## Constructors and destructors
    Array();
    Array(std::initializer_list<Type> list);

    ~Array();

    // ######## Subscriprion operators
    Type& operator[](int index);
    const Type& operator[](int index) const;

    // ######## Copy assignment
    template <unsigned int otherSize>
    Array& operator=(const Array<Type, otherSize>& otherArray);

    // ######## Copy assignment_2
    Array& operator=(const Array& otherArray);

    // ######## Copy constructor
//    template <unsigned int otherSize>
    Array(const Array& otherArray);

    // ######## For using in iteration algorithms
    Type* begin() const;
    Type* end() const;
    Type* begin();
    Type* end();

    // ######## Move assignment -- deleted 'cause I'm not sure, that <my::Array> should choose
    // ######## semantics - it is concern of <Type> object under this array, perhapse...
//    template <unsigned int otherSize>
//    Array& operator=(Array<Type, otherSize>&& otherArray) = delete;

//    // ######## Move constructor -- deleted for the same reason I mentioned above
//    template <unsigned int otherSize>
//    Array(Array&& otherArray) = delete;



    // ######## Interface
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
