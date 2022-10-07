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
    char*   mb_ptr {nullptr};                       // Pointer contains adress of the first element of the string
    int     mb_length {0};                          // Length of the string (with end-of-line character)

    char*   mb_lastElementPtr {nullptr};            // Pointer contain adress of the last ('\0') element of the string

    int     mb_allocationDataChunk {64};            // Default size of portion while allocate memory in the heap
    int     mb_capacity {0};                        // Number of characters, that string can fit without new allocation
public:
    String() = default;
    String(const char* string);
    ~String();

    String(const String& string);
    String& operator=(const String& string);


    int     getLength() const;
    void    setLength(int length);

    int     getCapacity() const;
    void    setCapacity(int newCapacity);

    char*   getLastElementPtr() const;
    void    setLastElementPtr(char* newLastElementAdress);

    int     getAllocationDataChunk() const;
    void    setAllocationDataChunk(int bytes);

    friend String& operator<<(my::String& string, int intNumber);


    friend std::ostream& operator<<(std::ostream& out, const String& string);

    friend std::istream& operator>>(std::istream& in, String& string);
private:

};

String& operator<<(my::String& string, int intNumber);


std::ostream& operator<<(std::ostream& out, const String& string);
std::istream& operator>>(std::istream& in, String& string);


} // End of namespace "my{}"


#endif  // MY_STRING_H
