#ifndef MY_ITERATOR_H
#define MY_ITERATOR_H


namespace my {

//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   Base class for representing iterator objects
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
class Iterator {
//public:
//    // # The tags below are needed for the functions from <std::algorithms> and allow to provide
//    // # optimal choices when choosing specific function (for sorting and etc)
//    using iterator_category = std::forward_iterator_tag;        // Can scan the container mutiple times and read/write data it points to
//    using difference_type = std::ptrdiff_t;                      // Difference between two pointers (on current machine). Not sure that should use <std::ptrdiff_t>.
//    using value_type = Type;
//    using pointer = Type*;
//    using reference = Type&;
private:
    Type* mb_ptr;

public:

    // Contructor
    explicit Iterator(Type* ptr) :
        mb_ptr {ptr}
    {
        // Nothing to do
    }

    Type& operator*() const
    {
        return *mb_ptr;
    }

    Type* operator->() const
    {
        return mb_ptr;
    }

    // # Prefix
    Iterator& operator++()
    {
        mb_ptr++;
        return *this;
    }

    // # Postfix
    Iterator operator++(Type)
    {
        auto temp {*this};
        ++(*this);
        return temp;
    }


    friend bool operator==(const Iterator& a, const Iterator& b)
    {
        return a.mb_ptr == b.mb_ptr;
    }

    friend bool operator!=(const Iterator& a, const Iterator& b)
    {
        return a.mb_ptr != b.mb_ptr;
    }


//    Iterator begin()
//    {
//        return Iterator(&mb_dataPtr[0]);
//    }


//    Iterator end()
//    {
//        return Iterator(&mb_dataPtr[mb_size]);
//    }




}; // End of <my::Iterator> class





} // End of 'my' namespace




#endif // MY_ITERATOR_H
