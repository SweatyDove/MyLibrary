
#include "my_string.h"
#include "my_utilities.h"


//===============================================================================
// Constructor
//===============================================================================
my::String::String(const char* str)
{
    const char* inputStrPtr {str};
    char* thisStrPtr {nullptr};
    int inputStrlength {1};                         // 1 - for '\0'

    // #### Determine the length of the input string
    while (*inputStrPtr++ != '\0') {
        ++inputStrlength;
    }
    mb_length = inputStrlength;

    // #### Allocate memory in the heap (with a margin)
    mb_capacity = ((mb_length / mb_allocationDataChunk) + 1) * mb_allocationDataChunk;
    mb_ptr = new char[mb_capacity];
    mb_lastElementPtr = mb_ptr;                 // At the start (mb_ptr == mb_lastElementPtr)

    // #### Copy source string @str into @this object
    // #1 Initialize dynamic pointers
    thisStrPtr = mb_ptr;
    inputStrPtr = str;
    // #2 Fill @this string with NOT NULL data
    for (int ii {0}; ii < mb_length; ++ii) {
        *thisStrPtr++ = *inputStrPtr++;
    }
    // #3 Set pointer to the first NULL element (last element of C-String)
    mb_lastElementPtr = thisStrPtr;
    // #4 Fill the remaining space with '\0'
    for (int ii {mb_length}; ii < mb_capacity; ++ii)
        *thisStrPtr++ = '\0';
    }
}


//===============================================================================
// NAME: Copy constructor
// GOAL: CREATING a new object (in case of assignment - new object already EXISTS)
//       and copy input @string into created (@this) string.
//===============================================================================
my::String::String(const String& string)
{
    // #### Copy all member variables into new object
    mb_length = string.mb_length;
    mb_capacity = string.mb_capacity;
    mb_lastElementPtr = string.mb_lastElementPtr;

    // #### Allocate memory in the heap and copy data
    mb_ptr = new char[mb_capacity];
    for (int ii {0}; ii < mb_capacity; ++ii) {
        mb_ptr[ii] = string.mb_ptr[ii];
    }
}


//===============================================================================
// NAME: Destructor
// GOAL:
//===============================================================================
my::String::~String()
{
    delete[] mb_ptr;
}



//===============================================================================
// NAME: Overloaded operator<< for <int> type.
// GOAL: Writing integer @intNumber as char data into the my::String object.
//===============================================================================
my::String& my::operator<<(my::String& string, int intNumber)
{
    constexpr int bufSize_128 {128};
    char tempBuffer[bufSize_128] = {'\0'};

    // #### Convert intNumber to char
    my::intToChar(intNumber, tempBuffer, 128);

    // #### Calculate number of digits in the buffer
    int numberOfDigits {0};
    for (int ii {0}; ii < bufSize_128; ++ii) {
        if (tempBuffer[ii] != '\0') {
            ++numberOfDigits;
        }
        else {
            break;
        }
    }

    // #### If my::String object has enough space for the new data

    // #1 Set new length
    string.setLength(string.getLength() + numberOfDigits);

    // #2 Allocate new memory if need
    if (string.getLength() > string.getCapacity()) {
        int newCapacity {((string.getLength() / string.getAllocationDataChunk()) + 1) * string.getAllocationDataChunk()};
        string.setCapacity(newCapacity);
    }
    else {} // Nothing to do

    // #3 Copy digits in string
    my::copyString(tempBuffer, string.getLastElementPtr(), numberOfDigits);
    string.setLastElementPtr(string.getLastElementPtr() + numberOfDigits);
    *(string.getLastElementPtr() + 1) = '\0';

    return string;

}


//===============================================================================
// Overloading [operator=]
// We don't need to create a new object. Just assign to the existing one.
//===============================================================================
my::String& my::String::operator=(const String& string)
{
    // ## Self-assignment checking
    if (this == &string) {
        return *this;
    }
    else { /* Nothing to do */ }

    // ## Delete data in the l-string
    if (mb_ptr != nullptr) {
        delete[] mb_ptr;
    }
    else { /* Nothing to do */ }

    // ## Assign data from r-string to l-string
    mb_length = string.mb_length;
    mb_ptr = new char[mb_length];
    for (int ii {0}; ii < mb_length; ++ii) {
        mb_ptr[ii] = string.mb_ptr[ii];
    }

    return *this;
}

// #### Overloaded [operator>>]
// #########
std::istream& my::operator>>(std::istream& in, String& string)
{
    int base {40};
    int bufSize{base};
    char ch {};
    char* bufPtr = new char[bufSize];
    char* bufStart {bufPtr};
    int length {0};


    bool skipLeadingSpaces {true};

    while ((ch = in.get()) != '\n' && !in.eof()) {

        // ## Skip the leading whitespaces
        if (skipLeadingSpaces && (ch == ' ' || ch == '\t')) {
            continue;
        }
        else { /* Nothing to do */ }
        skipLeadingSpaces = false;

        *bufPtr = ch;
        ++length;

        // ## Resize buffer
        if (length < bufSize) {
            ++bufPtr;
        }
        else {
            bufSize += base;
            bufPtr = new char[bufSize];
            for (int ii {0}; ii < bufSize; ++ii) {
                bufPtr[ii] = bufStart[ii];
            }
            delete[] bufStart;
            bufStart = bufPtr;
        }

    } /* End of while() */
    *bufPtr = '\0';
    ++length;

    // ## Transfer input string into my::String
    if (string.mb_ptr != nullptr)
        delete[] string.mb_ptr;
    else { /* Nothing to do */ }

    string.mb_ptr = bufStart;
    string.mb_length = length;

    bufStart = bufPtr = nullptr;

    return in;

}



// #### Overloaded [operator<<]
// #########
std::ostream& my::operator<<(std::ostream& out, const String& string)
{
    int length {string.mb_length};
    char* strPtr {string.mb_ptr};

    // Output symbols except last '\0'
    while (--length > 0) {
        out << *strPtr++;
    }

    return out;
}

//===============================================================================
//
//===============================================================================
int my::String::getLength() const
{
    return mb_length;
}

//===============================================================================
//
//===============================================================================
void my::String::setLength(int length)
{
    mb_length = length;
    return;
}

//===============================================================================
//
//===============================================================================
int my::String::getCapacity() const
{
    return mb_capacity;
}

//==============================================================================
// Member function allocate new my::String object with specified capacity and
// copy primary string into the new one.
//==============================================================================
void my::String::setCapacity(int newCapacity)
{
    assert(newCapacity < mb_length && "Haven't implemented yet.");

    char* newAllocationPtr {nullptr};       // Dynamic pointer of new area
    char* newPtr {nullptr};                 // Pointer to start of new area
    char* oldAllocationPtr {mb_ptr};        // Dynamic pointer to old area

    mb_capacity = newCapacity;

    // #### Allocate new portion of memory in the heap
    try {
        newPtr = new char[mb_capacity];
        newAllocationPtr = newPtr;

    }
    catch (std::bad_alloc) {
        std::cerr << "\n[ERROR]::[my::String::setCapacity]:"
                  << "Couldn't allocate memory in the heap. Operator 'new' threw an exception"
                  << std::endl;
        // [QUESTION]: Should I free memory before exit?
        exit(1);
    }
    // #### Copy original string in the new location.

    for (int ii {0}; ii < mb_capacity; ++ii) {
        if (ii < mb_length) {
            *newAllocationPtr++ = *oldAllocationPtr++;
        }
        else {
            *newAllocationPtr++ = '\0';
        }
    }

    // #### Delete old data
    delete[] mb_ptr;
    mb_ptr = newPtr;


    return;
}


//==============================================================================
//
//==============================================================================
char* my::String::getLastElementPtr() const
{
    return mb_lastElementPtr;
}

//==============================================================================
//
//==============================================================================
void my::String::setLastElementPtr(char* newAdressOfLastElement)
{
    mb_lastElementPtr = newAdressOfLastElement;
    return;
}

//==============================================================================
//
//==============================================================================
int my::String::getAllocationDataChunk() const
{
    return mb_allocationDataChunk;
}

//==============================================================================
//
//==============================================================================
void my::String::setAllocationDataChunk(int bytes)
{
    mb_allocationDataChunk = bytes;
    return;
}


