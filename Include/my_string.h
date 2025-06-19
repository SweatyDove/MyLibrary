#ifndef MY_STRING_H
#define MY_STRING_H

#include <iostream>
#include <cassert>
#include <new>
#include <iomanip>
#include <sys/resource.h>
#include <cstring>
#include "my_exception.h"


//==================================================================================================
//         TYPE:    Namespace
//  DESCRIPTION:    ........
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
namespace my {


//==================================================================================================
//         TYPE:    Class
//  DESCRIPTION:    Represents my version of <std::string> class from STL.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
class String {


private:
    char*   mb_data {nullptr};        // Pointer contains adress of the first element of the string
    int     mb_length {0};                          // Number of characters in the string (without '\0' symbol)
    int     mb_capacity {0};                        // Number of characters, that string can fit without new allocation

    int     mb_allocationDataChunk {64};            // Default size of portion while allocate memory in the heap
public:



    // ################################### Constructors and Destructors  ###########################
    String() = default;

    String(const char* line);
    String(const my::String& string);
    ~String();

    // ################################### Overloaded Operators ####################################

    my::String& operator=(const my::String& lString);
    my::String& operator=(my::String&& rString) noexcept;
    my::String& operator=(const char* stringLiteral);


    bool operator==(const char* stringLiteral) const;
    bool operator==(const my::String& myString) const;
    bool operator!=(const char* stringLiteral);
    bool operator!=(const my::String& myString);

    char& operator[](int index);
//    const char& operator[](int index) const;

    friend my::String& operator<<(my::String& string, int intNumber);
    friend my::String& operator<<(my::String& string, const char* charDataBuffer);
    friend my::String& operator<<(my::String& string, char symbol);
    friend my::String& operator<<(my::String& string, const my::String& inputString);

    friend my::String& operator+(const my::String& lStr, const my::String& rStr);

    friend std::ostream& operator<<(std::ostream& out, const my::String& string);
    friend std::istream& operator>>(std::istream& in, my::String& string);




    // ################################### Interface  ##############################################


    void clear();
    void reallocate(int newCapacity);

    [[nodiscard]]   int     toInt() const;


    [[nodiscard]]   int     getLength() const;
                    void    setLength(int length);
    [[nodiscard]]   int     getCapacity() const;
                    void    setCapacity(int newCapacity);
    [[nodiscard]]   int     getAllocationDataChunk() const;
                    void    setAllocationDataChunk(int bytes);

    [[nodiscard]]   const char* getFirstElementAdress() const;
    [[nodiscard]]   const char* cStr() const;



}; // End of <String> class

// Prototypes of the friend functions
my::String& operator<<(my::String& string, int intNumber);
my::String& operator<<(my::String& string, const char* charDataBuffer);
my::String& operator<<(my::String& string, char symbol);
my::String& operator<<(my::String& string, const my::String& inputString);

my::String& operator+(const my::String& lStr, const my::String& rStr);

std::ostream& operator<<(std::ostream& out, const my::String& string);
std::istream& operator>>(std::istream& in, my::String& string);





//==================================================================================================
//         TYPE:    Class
//  DESCRIPTION:    Exception class for <String> objects
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
class StringException : public Exception {

public:
    StringException(const char* description);
    const char* what() const override;


}; // End of <StringException> class





} // End of <my> namespace


#endif  // MY_STRING_H
