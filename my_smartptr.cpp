#include "my_smartptr.h"


//==================================================================================================
//          TYPE:   Default constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(Type* resource) :
    mb_ptr {resource}
{
    mb_output.debug("Smart pointer has been created!");
}




//==============================================================================================
//          TYPE:   Move-constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==============================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(const my::SmartPtr<Type>&& smartPtr)
{
    mb_output.debug("Move-constructor has been called");

    // # Can access private member because "private" is on per-class basis, not per-object
    mb_ptr = smartPtr.mb_ptr;

    smartPtr.mb_ptr = nullptr;

}




//==================================================================================================
//          TYPE:   Destructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::~SmartPtr()
{
    if (mb_ptr != nullptr) {
        delete mb_ptr;
        mb_ptr = nullptr;                   // Возможно, лишнее

        mb_output.debug("Destructor of the smart pointer has been called and resource was destroyed successfully!");
    }
    else {
        mb_output.debug("Destructor of the smart pointer has been called but there isn't resource to destroy...");
    }


}



//==================================================================================================
//          TYPE:   Move-assignment
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>& my::SmartPtr<Type>::operator=(const my::SmartPtr<Type>&& smartPtr)
{
    // # А нужно ли проводить проверку на самоприсваивание? То есть если справа у нас rvalue, то оно
    // # в принципе не может быть равно lvalue, которое слева... Теоретически...
    if (this == &smartPtr) {
        return *this;
    }
    else {} // Nothing to do


    if (mb_ptr != nullptr) {
        delete mb_ptr;
    }
    else {} // Nothing to do


    mb_ptr = smartPtr.mb_ptr;
    smartPtr.mb_ptr = nullptr;

    return *this;
}



//==============================================================================================
//          TYPE:   Dereference operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Стоит ли проверять mb_ptr на равенство nullptr?
//                  Наверное, стоит кидать исключение при нулевом указателе... Подумать...
//==============================================================================================
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



