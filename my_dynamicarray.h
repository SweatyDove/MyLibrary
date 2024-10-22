#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H


#include <initializer_list>
#include <iostream>
#include <cassert>


namespace my {


//==================================================================================================
//          TYPE:    Class
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    1) Подумать над тем, какое брать значение ёмкости при увеличении размера
//                      массива (или пусть пользователь сам определяет и выделяет, если ему нужно
//                      много, а по умолчанию выделяется... 4 дополнительных места)
//==================================================================================================
template <typename Type>
class DynamicArray {
private:
    Type* mb_dataPtr {nullptr};
    int mb_size {};
    int mb_capacity {};

    int mb_capacityChunk {4};

public:
    DynamicArray();
    DynamicArray(std::initializer_list<Type> list);
    ~DynamicArray();


    const Type& operator[](int ii) const;
    Type& operator[](int ii);



    void pushBack(Type value);
    void setCapacity(int size);
    int getSize() const;


};

template <typename Type>
std::ostream& operator<<(std::ostream& out, const my::DynamicArray<Type>& dynArr);


} // End of @my-namespace


#endif // DYNAMICARRAY_H
