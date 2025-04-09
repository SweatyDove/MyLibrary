#ifndef MY_SMARTPTR_H
#define MY_SMARTPTR_H

#include <iostream>
#include <cassert>

#include "my_prettyprint.h"

//extern my::PrettyPrint output;


//==================================================================================================
//          TYPE:    Namespace
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
// COMMENTS/BUGS:    ........
//==================================================================================================
namespace my {


//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   This class is my analog to std::unique_ptr from STL
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Should I use PrettyPrint here? It is an additional resource, that I should move
//                  with <Type*> resource. Moreover, I'm not sure, that I need instances of <PrettyPrint>
//                  in every object of <SmartPtr>. I will exclude it for now... But what kind of options
//                  I have here?
//
//                  1) Per object basis (like now)
//                  2) Per class basis (make static or declare/define in the h/cpp files).
//                  3) Per library basis (delcare in main.h and define in main.cpp?)
//                  4) Add a pointer to <my::SmartPtr> (and others classes). And pass this pointer
//                     in call time (if nullptr - then use std::cout, if not - use <my::SmartPtr)
//==================================================================================================
template <typename Type>
class SmartPtr {
private:
    Type* mb_ptr {nullptr};

    inline static int mb_count {0};

//    my::PrettyPrint mb_output {{ENABLE_DEBUG_MES, ENABLE_INFO_MES, ENABLE_WARN_MES, ENABLE_ERROR_MES}, true, false, true, 100};

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
