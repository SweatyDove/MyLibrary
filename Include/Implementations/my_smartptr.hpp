/***************************************************************************************************
 * This file contains definitions for the TEMPLATED part of the <my::SmartPtr> class
 **************************************************************************************************/
#ifndef MY_SMARTPTR_HPP
#define MY_SMARTPTR_HPP

#include "my_smartptr.h"            // For IDE visibility

//==================================================================================================
//          TYPE:   Default constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr() :
    mb_ptr {nullptr}
{
    //    mb_output.debug("Smart pointer has been created!");
    //    std::cout << "[DEBUG]: Smart pointer has been created!" << std::endl;
}



//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(Type* resource) :
    mb_ptr {resource}
{
    //    mb_output.debug("Smart pointer has been created!");
    //    std::cout << "[DEBUG]: Smart pointer has been created!" << std::endl;
}




//==============================================================================================
//          TYPE:   Move-constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==============================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(my::SmartPtr<Type>&& smartPtr)
{
    //    mb_output.debug("Move-constructor has been called");
    //    std::cout << "[DEBUG]: Move-constructor has been called!" << std::endl;


    // # Can access private member because "private" is on per-class basis, not per-object
    mb_ptr = smartPtr.mb_ptr;

    smartPtr.mb_ptr = nullptr;

}




//==================================================================================================
//          TYPE:   Destructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::~SmartPtr()
{
    //    mb_output.debug("Destructor of the smart pointer has been called!");
    //    std::cout << "[DEBUG]: Destructor of the smart pointer has been called!" << std::endl;

    //    mb_count = mb_count + 1;              // Debug

    // Вызывать delete над nullptr можно, и здесь, наверное, избыточно
    if (mb_ptr != nullptr) {
        delete mb_ptr;
        mb_ptr = nullptr;
    }
    else {} // Nothing to do

}



//==================================================================================================
//          TYPE:   Move-assignment
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>& my::SmartPtr<Type>::operator=(my::SmartPtr<Type>&& smartPtr)
{
    // # А нужно ли проводить проверку на самоприсваивание? То есть если справа у нас rvalue, то оно
    // # в принципе не может быть равно lvalue, которое слева... Теоретически...
    if (this == &smartPtr) {
        return *this;
    }
    else {}

    /*
     * Тут выскакивает ошибка сегментации, т.к. я пытаюсь вызвать delete с указателем на ненулевую
     * память, которая выделена динамически, однако не занулена. То есть когда динмаический массив
     * умных указателей создается, он просто выделяет память под них (без конструирования). Эта
     * память содержит мусор. И когда я пытаюсь сделать move в эту память, возникает попытка
     * удалить ненулевой (мусорный) указатель.
     */
    if (mb_ptr != nullptr) {
        delete mb_ptr;
    }
    else {}


    mb_ptr = smartPtr.mb_ptr;
    smartPtr.mb_ptr = nullptr;

    return *this;
}



//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::operator bool() const
{
    return (mb_ptr != nullptr);
}




//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Стоит ли проверять mb_ptr на равенство nullptr?
//                  Наверное, стоит кидать исключение при нулевом указателе... Подумать...
//==================================================================================================
template <typename Type>
Type& my::SmartPtr<Type>::operator*()
{
    if (mb_ptr != nullptr) {
        return *mb_ptr;
    }
    else {
        assert(false && "[ERROR]: can't dereference nullptr. Abort.");
    }
}



//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
Type* my::SmartPtr<Type>::operator->()
{
    if (mb_ptr != nullptr) {
        return mb_ptr;
    }
    else {
        assert(false && "[ERROR]: can't get access to the class member, when class addr is nullptr. Abort.");
    }

}


//==================================================================================================
//          TYPE:   Public method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
Type* my::SmartPtr<Type>::release()
{
    Type* retVal {mb_ptr};
    mb_ptr = nullptr;

    return retVal;

}



//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   It makes null-initialization of raw memory, that is destined for the using as
//                  <my::SmartPtr<Type>> memory.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
void my::SmartPtr<Type>::nullify()
{
    mb_ptr = nullptr;
}










#endif
