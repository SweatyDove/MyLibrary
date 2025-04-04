#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cassert>
#include <new>
#include <iomanip>


//==============================================================================
// Comments:
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



    String(const char* line);
    ~String();

    String(const my::String& string);

    //==========================================================================
    // TYPE: Copy assignment via overloaded [operator=].
    // GOAL: We don't need to create a new object. Just assign to the existing
    //       one, doing a deep copy.
    //==========================================================================
    my::String& operator=(const my::String& lString);


    //==========================================================================
    // TYPE: Move assignment via overloaded [operator=].
    // GOAL: Transfer ownership.
    //==========================================================================
    my::String& operator=(my::String&& rString) noexcept;


    //==========================================================================
    // TYPE: Assignment overloaded [operator=] for <const char*> type.
    // GOAL:
    //==========================================================================
    my::String& operator=(const char* stringLiteral);


    bool operator==(const char* stringLiteral) const;
    bool operator==(const my::String& myString) const;
    bool operator!=(const char* stringLiteral);
    bool operator!=(const my::String& myString);







    void      clear();
    //void    softClear();
    //void    hardClear();

    [[nodiscard]]   int     getLength() const;
                    void    setLength(int length);

    [[nodiscard]]   int     getCapacity() const;
                    void    setCapacity(int newCapacity);

    [[nodiscard]]   int     getAllocationDataChunk() const;
                    void    setAllocationDataChunk(int bytes);

    [[nodiscard]]   const char* getFirstElementAdress() const;

    friend my::String& operator<<(my::String& string, int intNumber);
    friend my::String& operator<<(my::String& string, const char* charDataBuffer);
    friend my::String& operator<<(my::String& string, char symbol);
    friend my::String& operator<<(my::String& string, const my::String& inputString);

    friend my::String& operator+(const my::String& leftString, const my::String& rightString);


    /* Here we declare overloaded operators as friend functions */
    friend std::ostream& operator<<(std::ostream& out, const my::String& string);
    friend std::istream& operator>>(std::istream& in, my::String& string);

};

my::String& operator<<(my::String& string, int intNumber);
my::String& operator<<(my::String& string, const char* charDataBuffer);
my::String& operator<<(my::String& string, char symbol);
my::String& operator<<(my::String& string, const my::String& inputString);


my::String& operator+(const my::String& leftString, const my::String& rightString);


/* And here is just a PROTOTYPES */
std::ostream& operator<<(std::ostream& out, const my::String& string);
std::istream& operator>>(std::istream& in, my::String& string);


} // End of namespace "my"


#endif  // MY_STRING_H
