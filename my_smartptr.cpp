#include "my_smartptr.h"


//==================================================================================================
//          TYPE:    Default constructor
//    PARAMETERS:    ........
//   DESCRIPTION:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(Type* resource) :
    mb_ptr {resource}
{
    std::cout << "[DEBUG]: smart pointer has created!" << std::endl;
}




//==============================================================================================
//          TYPE:    Move-constructor
//    PARAMETERS:    ........
//   DESCRIPTION:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==============================================================================================
template <typename Type>
my::SmartPtr<Type>::SmartPtr(const my::SmartPtr<Type>&& smartPtr)
{
    // # Can access private member because "private" is on per-class basis, not per-object
    mb_ptr = smartPtr.mb_ptr;

    smartPtr.mb_ptr = nullptr;

}




//==================================================================================================
//          TYPE:    Destructor
//    PARAMETERS:    ........
//   DESCRIPTION:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
template <typename Type>
my::SmartPtr<Type>::~SmartPtr()
{
    if (mb_ptr != nullptr) {
        delete mb_ptr;
        mb_ptr = nullptr;                   // Возможно, лишнее
        std::cout << "[DEBUG]: Destructor of the smart pointer has been called and resource was "
                  << "destroyed successfully!" << std::endl;
    }
    else {} // Nothing to do

    std::cout << "[DEBUG]: Destructor of the smart pointer has been called but there isn't resource "
              << "to destroy..." << std::endl;

}



//==============================================================================================
//          TYPE:    Move-assignment
//    PARAMETERS:    ........
//   DESCRIPTION:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==============================================================================================
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

}



//==============================================================================================
//          TYPE:   Dereference operator
//    PARAMETERS:   ........
//   DESCRIPTION:   ........
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
    } //

}



