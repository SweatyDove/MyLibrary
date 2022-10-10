#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cassert>
#include <new>


//==============================================================================
// Comments:
//  1) Don't need last element adress (it is equal to mb_ptr + length)
//
//==============================================================================

namespace my {

class String {

private:
    char*   mb_firstElementAdress {nullptr};        // Pointer contains adress of the first element of the string
    int     mb_length {0};                          // Number of characters in the string (without '\0' symbol)
    int     mb_capacity {0};                        // Number of characters, that string can fit without new allocation

    int     mb_allocationDataChunk {64};            // Default size of portion while allocate memory in the heap
public:
    String() = default;
    String(const char* string);
    ~String();

    String(const my::String& string);
    my::String& operator=(const my::String& string);


    int     getLength() const;
    void    setLength(int length);

    int     getCapacity() const;
    void    setCapacity(int newCapacity);


    int     getAllocationDataChunk() const;
    void    setAllocationDataChunk(int bytes);

    friend my::String& operator<<(my::String& string, int intNumber);
    friend my::String& operator<<(my::String& string, const char* charDataBuffer);



    friend std::ostream& operator<<(std::ostream& out, const String& string);
    friend std::istream& operator>>(std::istream& in, String& string);

};

my::String& operator<<(my::String& string, int intNumber);
my::String& operator<<(my::String& string, const char* charDataBuffer);



std::ostream& operator<<(std::ostream& out, const my::String& string);
std::istream& operator>>(std::istream& in, my::String& string);


} // End of namespace "my{}"


#endif  // MY_STRING_H
