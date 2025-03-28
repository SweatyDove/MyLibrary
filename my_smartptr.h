#ifndef MY_SMARTPTR_H
#define MY_SMARTPTR_H

#include <iostream>
#include <cassert>

#include "my_prettyprint.h"


//==================================================================================================
//          TYPE:    Namespace
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
namespace my {


//==================================================================================================
//          TYPE:    Class
//   DESCRIPTION:    This class is my analog to std::unique_ptr from STL
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
template <typename Type>
class SmartPtr {
private:
    Type* mb_ptr {nullptr};

    my::PrettyPrint mb_output {{true, true, true, true}, true, false, true, 100};

public:
    SmartPtr(Type* resource);
    ~SmartPtr();

    // # Delete copy constructor and copy assignment 'cause it is assumed, that ONLY one object owns
    // # the resource. And it is allowed only to move ownership.
    SmartPtr(const my::SmartPtr<Type>& smartPtr) = delete;
    my::SmartPtr<Type>& operator=(const my::SmartPtr<Type>& smartPtr) = delete;



    // # Move-constructor
    SmartPtr(my::SmartPtr<Type>&& smartPtr);

    // # Move-assignment
    my::SmartPtr<Type>& operator=(my::SmartPtr<Type>&& smartPtr);

    // # Dereference operator
    Type& operator*();

    // # Access to the class member operator
    Type* operator->();


    operator bool() const;

    /* Should I have two versions of dereference operator: const and non-const? */
//    const Type& operator*();

    // # Release the OWNERSHIP under the resource and transfer OWNERSHIP to the caller.
    Type* release();
};




} // End of "my" namespace

#endif // SMARTPTR_H
