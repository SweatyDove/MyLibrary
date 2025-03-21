#ifndef MY_SMARTPTR_H
#define MY_SMARTPTR_H

#include <iostream>
#include <cassert>

namespace my {

template <typename Type>
class SmartPtr {
private:
    Type* mb_ptr {nullptr};

public:
    SmartPtr(Type* resource);
    ~SmartPtr();

    // # По-идее, мне не нужна семантика копирования здесь, т.к. умный указатель нужен для единоличного
    // # (если это не shared_ptr) управления ресурсом. Тут нельзя копировать куда-то его (ресурс),
    // # а можно только перемещать
    SmartPtr(const my::SmartPtr<Type>& smartPtr) = delete;
    my::SmartPtr<Type>& operator=(const my::SmartPtr<Type>& smartPtr) = delete;



    // # Move-constructor
    SmartPtr(const my::SmartPtr<Type>&& smartPtr);


    //==============================================================================================
    // # Move-assignment
    //==============================================================================================
    my::SmartPtr<Type>& operator=(const my::SmartPtr<Type>&& smartPtr);

    //==============================================================================================
    //          TYPE:    Dereference operator
    //    PARAMETERS:    ........
    //   DESCRIPTION:    ........
    //  RETURN VALUE:    ........
    // COMMENTS/BUGS:    Возможно, стоит иметь две версии, const и non-const
    //==============================================================================================
    Type& operator*();
};




} // End of "my" namespace

#endif // SMARTPTR_H
