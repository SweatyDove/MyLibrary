#ifndef MY_DYNAMIC_ARRAY_H
#define MY_DYNAMIC_ARRAY_H

#include "my_array.h"                   // Circular dependencies? Should I exclude it?
#include "my_utilities.h"
#include "my_exception.h"

#include <initializer_list>
#include <iostream>
#include <cassert>
#include <iterator>         // For std::forward_iterator_tag
#include <cstddef>          // For std::ptrdiff_t


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
//
//                  2 - Нужно что-то сделать с move-семантикой, т.к. в проекте RPG используется
//                      данный оператор над элементами массива. Хотя я не уверен, что проблема именно здесь. Зачем
//                      нужна move-семантика? Чтобы вместо копирования (которое нежелательно или в принципе ошибочно_
//                      использовать перемещение. Но что это для данного класса? Перемещение одного массива в другой.
//                      Но я не вижу смысла, т.к. сам массив является статическим объектом, а не выделяется динамически.
//                      Динамически выделяется память под содержимое данного массива, следовательно, думать о том,
//                      перемещать или копировать, должны классы (типы), элементы которых содержатся в массиве.
//
//                      Но при попытке использовать std::unique_ptr в качестве "типа" - тот говорит, что:
//                      "error: use of deleted function 'std::unique_ptr...". Возможно, дело в том, что конкретная связка
//                      стандартного std::vector и std::unique_ptr работают вместе, а с моим классом нужно что-то делать, как-то
//                      допилить его. ПОпробую написать свой умный указатель, а там видно будет.
//==================================================================================================
template <typename Type>
class DynamicArray {
private:
    int mb_capacityChunk {4};
    int mb_capacity {};
    int mb_size {};
    Type* mb_dataPtr {nullptr};


//    my::PrettyPrint mb_output {{ENABLE_DEBUG_MES, ENABLE_INFO_MES, ENABLE_WARN_MES, ENABLE_ERROR_MES}, true, false, true, 100};




    // Функция костыль на смещение элементов массива
//    void displace(int position, int shift);


public:

    // #############################################################################################
    // ################################### Constructors and Destructors  ###########################
    // #############################################################################################

    DynamicArray();
    DynamicArray(std::initializer_list<Type> list);
    DynamicArray(const char* string);

    // # Copy/Move constructors
    DynamicArray(const DynamicArray<Type>& that);
    //DynamicArray(DynamicArray<Type>&& dynArr);



    ~DynamicArray();

    // #############################################################################################
    // ################################### Overloaded Operators ####################################
    // #############################################################################################

    // # Copy/Move assignment
    DynamicArray<Type>&     operator=(const DynamicArray<Type>& that);
   //DynamicArray<Type>& operator=(DynamicArray<Type>&& dynArr);


    const Type&             operator[](int ii) const;
    Type&                   operator[](int ii);




    // #############################################################################################
    // ################################### Interface  ##############################################
    // #############################################################################################


    int     getSize() const;
    int     size() const;
    int     getCapacity() const;
    int     getCapacityChunk() const;
    void    reallocate(int newCapacity);
    void    pushBack(const Type& value);
    void    pushBack(Type&& value);
    void    push_back(const Type& value);
    void    push_back(Type&& value);
    Type    popBack();
    void    extend(const my::DynamicArray<Type>& dynArr);
    void    nullify();
    void    insert(Type* pos, Type* copyFrom, Type* copyTo);



    // ######## For using in iteration algorithms
    const Type*     cbegin() const;
    const Type*     cend() const;
    Type*           begin();
    Type*           end();

//    template <int size>
//    void extend(const my::Array<Type, size>& staticArr);


    template <int length>
    void extend(const my::Array<Type, length>& staticArr);



    //==================================================================================================
    //          TYPE:   Class
    //   DESCRIPTION:   Represents iterator objects for the <my::DynamicArray>
    //    PARAMETERS:   ........
    //  RETURN VALUE:   ........
    //      COMMENTS:   ........
    //==================================================================================================
    class Iterator {
    public:
        // # The tags below are needed for the functions from <algorithms> and allow to provide
        // # optimal choices when choosing specific function (for sorting and etc)
        using iterator_category = std::forward_iterator_tag;        // Can scan the container mutiple times and read/write data it points to
        using difference_type = std::ptrdiff_t;                      // Difference between two pointers (on current machine). Not sure that should use <std::ptrdiff_t>.
        using value_type = Type;
        using pointer = Type*;
        using reference = Type&;

        // Contructor
        Iterator(pointer ptr) : mb_ptr {ptr} {}

        reference operator*() const { return *mb_ptr; }
        pointer operator->() { return mb_ptr; }

        Iterator& operator++() { mb_ptr++; return *this; }
        Iterator operator++(Type) {auto temp {*this}; ++(*this); return temp; }

        friend bool operator==(const Iterator& a, const Iterator& b) {return a.mb_ptr == b.mb_ptr;}
        friend bool operator!=(const Iterator& a, const Iterator& b) {return a.mb_ptr != b.mb_ptr;}


        Iterator begin()    {return Iterator(&mb_dataPtr[0]);}
        Iterator end()      {return Iterator(&mb_dataPtr[mb_size]);}



    private:
        pointer mb_ptr;

    }; // End of <DynamicArray::Iterator> class


}; // End of <DynamicArray> class


template <typename Type>
std::ostream& operator<<(std::ostream& out, const my::DynamicArray<Type>& dynArr);

template <typename Type>
std::ostream& operator<<(std::ostream& out, my::DynamicArray<Type>& dynArr);


//==================================================================================================
//         TYPE:    Class
//  DESCRIPTION:    Exception class for <String> objects
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    Do I need <Type> here?
//==================================================================================================
class DynamicArrayException : public Exception {

public:
    explicit DynamicArrayException(const char* description);
    const char* what() const override;


}; // End of <StringException> class





} // End of @my-namespace


// # Templated part implementations
#include "Implementations/my_dynamicarray.hpp"


#endif // DYNAMICARRAY_H
