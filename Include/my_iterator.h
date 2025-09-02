#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H



/***************************************************************************************************
 * А в чём разница между использованием шаблонов и использованием наследования? То есть в интернете
 * пишут, что итераторы реализованы именно на базе шаблонов, НЕ наследования (как я пытаюсь сейчас).
 * И там меняется именно тип аргумента (т.е. у меня сейчас предполагается, что функция sort() принимает
 * референс на итератор, в то время как стандартная библиотека использует шаблон <typename Iterator>...
 *
 * Дальше, как я понимаю, хоть реализация типов разная (для разных типов контейнеров), т.к. у каждого
 * из этих типов есть фиксированный набор операций (инкрементирование, разыменование и т.д.), то и конфликта
 * не возникает - аргументы используют функции с одинаковыми именами. То есть ШАБЛОН - это ШАБЛОН функции,
 * а не функция. Компилятор при необходимости создаёт экземпляр функции для указанного типа. И если
 * полученная функция имеет внутри валидные вызовы других функций (а в нашем случае они валидные, так как
 * есть стандртный набор) - то никаких конфликтов не возникнет.
 *
 * Единственное, IDE тебе не покажет ошибку, если функция указана невалидная, т.к. он не знает, тип
 * значения и какой у него интерфейс - нужно сперва скомпилировать.
 **************************************************************************************************/


namespace my {

//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   Base class for representing iterator objects
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Меня смущает вот что... Должен ли я в явном виде описывать, что должна делать та
//                  или иная функция? По идее, итератор - это штука, которая предоставляет
//                  универсальный интерфейс для взаимодействия с различными контейнерами (массив,
//                  динамический массив, строка и т.д.). А реализацию этого интерфейса должен уже
//                  сам контейнер предоставлять.
//==================================================================================================
template <typename Type>
class Iterator {
public:

    // Contructor
    explicit Iterator() { /* Nothing to do */}
    virtual ~Iterator() { /* Nothing to do */}
    virtual Type& operator*() const = 0;
//    virtual Type* operator->() const = 0;
//    virtual Iterator& operator++() = 0;                         // Prefix
//    virtual Iterator operator++(Type) = 0;                      // Postfix

//    virtual Iterator begin() = 0;
//    virtual Iterator end() = 0;


//    friend bool operator==(const Iterator& a, const Iterator& b)
//    {
//        return a.mb_ptr == b.mb_ptr;
//    }

//    friend bool operator!=(const Iterator& a, const Iterator& b)
//    {
//        return a.mb_ptr != b.mb_ptr;
//    }





}; // End of <my::Iterator> class





} // End of 'my' namespace




#endif // MY_ITERATOR_H






////==================================================================================================
////          TYPE:   ........
////   DESCRIPTION:   Reference
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   ........
////==================================================================================================
//class Iterator {
//public:

//    // # The tags below are needed for the functions from <algorithms> and allow to provide
//    // # optimal choices when choosing specific function (for sorting and etc)
//    using iterator_category = std::forward_iterator_tag;        // Can scan the container mutiple times and read/write data it points to
//    using difference_type = std::ptrdiff_t;                      // Difference between two pointers (on current machine). Not sure that should use <std::ptrdiff_t>.
//    using value_type = Type;
//    using pointer = Type*;
//    using reference = Type&;

//    // Contructor
//    Iterator(pointer ptr) : mb_ptr {ptr} {}

//    reference operator*() const { return *mb_ptr; }
//    pointer operator->() { return mb_ptr; }

//    Iterator& operator++() { mb_ptr++; return *this; }
//    Iterator operator++(Type) {auto temp {*this}; ++(*this); return temp; }

//    friend bool operator==(const Iterator& a, const Iterator& b) {return a.mb_ptr == b.mb_ptr;}
//    friend bool operator!=(const Iterator& a, const Iterator& b) {return a.mb_ptr != b.mb_ptr;}


//    Iterator begin()    {return Iterator(&mb_dataPtr[0]);}
//    Iterator end()      {return Iterator(&mb_dataPtr[mb_size]);}



//private:
//    pointer mb_ptr;

//}; // End of <my::DynamicArray::Iterator> class


//}; // End of <DynamicArray> class
