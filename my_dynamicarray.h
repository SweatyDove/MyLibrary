#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H


#include <initializer_list>
#include <iostream>


namespace my {

template <typename Type>
class DynamicArray {
private:
    Type* mb_dataPtr {nullptr};

public:
    DynamicArray();
    DynamicArray(std::initializer_list<Type> list);
    ~DynamicArray();
};


} // End of @my-namespace
#endif // DYNAMICARRAY_H
