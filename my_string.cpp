
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
    int mb_capacity {mb_length / mb_defaultAllocationDataChunk + 1};
    mb_ptr = new char[mb_capacity];

    // #### Copy source string @str into @this object
    thisStrPtr = mb_ptr;
    inputStrPtr = str;
    for (int ii {0}; ii < mb_capacity; ++ii) {
        if (--inputStrlength > 0) {
            *thisStrPtr = *inputStrPtr;
            mb_lastElementPtr = thisStrPtr;         // Save adress of last not-null element
        }
        else {
            *thisStrPtr = '\0';
        }

        ++thisStrPtr;
        ++inputStrPtr;
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
my::String& operator<<(my::String& string, const int& intNumber)
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
    string.setLength(string.getLength() + numberOfDigits);
    if (string.getLength() <= string.getCapacity()) {
        // ## Copy digits in string
        my::copyString(tempBuffer, string.getLastElementPtr(), numberOfDigits);
        string.setLastElementPtr(string.getLastElementPtr() + numberOfDigits);
        *(string.getLastElementPtr() + 1) = '\0';
    }
    // #### Else if we need to allocate more memory
    else {
        string.setCapacity(string.getLength() / string.get);
        // Allocate memory
        // Copy existing string to it
    }

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
    mb_length += length;
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
    char* newAllocationPtr {nullptr};

    assert(newCapacity < mb_length && "Haven't implemented yet.");

    // #### Allocate new portion of memoty in the heap
    try {
        newAllocationPtr = new char[newCapacity];
    }
    catch (std::bad_alloc) {
        std::cerr << "\n[ERROR]::[my::String::setCapacity]:"
                  << "Couldn't allocate memory in the heap. Operator 'new' threw an exception"
                  << std::endl;
        // [QUESTION]: Should I free memory before exit?
        exit(1);
    }
    // #### Copy original string in the new location.
    for (int ii {0}; ii < newCapacity; ++ii) {
        if (ii < mb_length - 1) {
            //mb_lastElementPtr - don't changed in this case
            *newAllocationPtr++ = *mb_ptr++;
        }
        else {
            *newAllocationPtr++ = '\0';
        }
    }

    // #### Reset parameters




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



