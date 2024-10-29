#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H


#include <initializer_list>
#include <iostream>
#include <cassert>
#include <my_array.h>


namespace my {


//==================================================================================================
//          TYPE:   Class
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   0 - Some decisions while writing this class may be not optimal. But I do all
//                      things just for the practice, to find some narrow places in my understanding
//                      of fundamental things... Sometimes I choose dangerous things (C-style arrays,
//                      pure pointers and etc.) in order to face with problems of the usage of such
//                      things.
//                  1 - Подумать над тем, какое брать значение ёмкости при увеличении размера
//                      массива (или пусть пользователь сам определяет и выделяет, если ему нужно
//                      много, а по умолчанию выделяется... 4 дополнительных места)
//==================================================================================================
template <typename Type>
class DynamicArray {
private:
    int mb_capacityChunk {4};


    Type* mb_dataPtr {nullptr};
    int mb_size {};
    int mb_capacity {};


public:
    DynamicArray();
    DynamicArray(std::initializer_list<Type> list);
    ~DynamicArray();


    const Type& operator[](int ii) const;
    Type& operator[](int ii);

    // # Setters and getters
    int getSize() const;
    int getCapacity() const;
    int getCapacityChunk() const;
    void reallocate(int newCapacity);


    // # COPY CONSTRUCTOR and COPY ASSIGNMENT operators (do not release yet)
    DynamicArray(const DynamicArray<Type>& dynArr);
    DynamicArray<Type>& operator=(const DynamicArray<Type>& dynArr);

    // # MOVE CONSTRUCTOR and MOVE ASSIGNMENT operators (do not release yet)
//    DynamicArray(const DynamicArray<Type>&& dynArr);
//    DynamicArray<Type> operator=(const DynamicArray<Type>&& dynArr);


    // # Interface
    void pushBack(Type value);
    Type popBack();


    void extend(const DynamicArray<Type>& dynArr);

    template <int size>
    void extend(const my::Array<Type, size>& staticArr);



    // ######## For using in iteration algorithms
    const Type* begin() const;
    const Type* end() const;
    Type* begin();
    Type* end();



};

template <typename Type>
std::ostream& operator<<(std::ostream& out, const my::DynamicArray<Type>& dynArr);


} // End of @my-namespace


#endif // DYNAMICARRAY_H
