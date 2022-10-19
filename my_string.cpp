
#include "my_string.h"
#include "my_utilities.h"


//===============================================================================
// NAME: Constructor
// GOAL: Construct a my::String object from a raw buffer of characters
//===============================================================================
my::String::String(const char* bufferOfChars)
{

    // #### Determine the length of the input buffer
    const char* bufferPtr       {bufferOfChars};
    int         bufferLength    {0};

    while (*bufferPtr++ != '\0') {
        ++bufferLength;
    }
    mb_length = bufferLength;

    // #### Allocate memory in the heap (with a margin)
    mb_capacity = (((mb_length + 1) / mb_allocationDataChunk) + 1) * mb_allocationDataChunk;
    mb_firstElementAdress = new char[mb_capacity];

    // #### Copy source string @str into @this object
    // #1 Reinitialize dynamic pointers
    char* thisPtr {mb_firstElementAdress};
    bufferPtr = bufferOfChars;

    // #2 Fill @this string with data from @bufferOfChars. Remeining space fill
    // ## with '\0'.
    for (int ii {0}; ii < mb_capacity; ++ii) {
        *thisPtr++ = (ii < mb_length) ? *bufferPtr++ : '\0';
    }
}


//===============================================================================
// NAME: Copy constructor
// GOAL: CREATING a new object (in case of assignment - new object already EXISTS)
//       and copy input @string into created (@this) string.
//===============================================================================
my::String::String(const my::String& string)
{
    const char* inputStringPtr  {string.mb_firstElementAdress};
    char*       thisPtr         {nullptr};

    // #### Copy all member variables into new object
    mb_length = string.mb_length;
    mb_capacity = string.mb_capacity;

    // #### Allocate memory in the heap and copy data
    thisPtr = mb_firstElementAdress = new char[mb_capacity];
    for (int ii {0}; ii < mb_capacity; ++ii) {
        *thisPtr++ = *inputStringPtr++;
    }
}


//==============================================================================
// NAME: Destructor
// GOAL: Destruct @this object with the deallocation of memory.
//==============================================================================
my::String::~String()
{
    delete[] mb_firstElementAdress;
}




//==============================================================================
// NAME: Friend binary [operator+] for <my::String> and <my::String>
// GOAL: Create new <my::String> object via concatenation its arguments.
//==============================================================================
my::String& my::operator+(const my::String& leftString, const my::String& rightString)
{
    my::String* string {new my::String("")};
    *string << leftString.mb_firstElementAdress << rightString.mb_firstElementAdress;

    return *string;


}

//==============================================================================
// NAME: Member function
// GOAL: Soft clear the string
//==============================================================================
void my::String::softClear()
{
    *mb_firstElementAdress = '\0';
    mb_length = 0;

    return;
}




//==============================================================================
// NAME: Overloaded [operator<<] for <int> type.
// GOAL: Writing integer @intNumber as char data into the my::String object.
//==============================================================================
my::String& my::operator<<(my::String& string, int intNumber)
{
    constexpr int   bufSize_128 {128};
    char            tempBuffer[bufSize_128] = {'\0'};
    int ii          {0};

    bool isNegative {(intNumber < 0)};

    int positiveNumber {(isNegative) ? -intNumber : intNumber};



    // #### Convert intNumber to char
    if (isNegative) {
        tempBuffer[ii++] = '-';
    }
    else {} // Nothing to do
    my::intToChar(positiveNumber, &tempBuffer[ii], 128);

    // #### Calculate number of digits (or signs) in the buffer
    int numberOfSymbols {0};
    for (ii = 0; ii < bufSize_128; ++ii) {
        if (tempBuffer[ii] != '\0') {
            ++numberOfSymbols;
        }
        else {
            break;
        }
    }

    // #### If my::String object has enough space for the new data
    // #1 Set new string's length.
    string.setLength(string.getLength() + numberOfSymbols);

    // #2 Allocate memory if the new string length is higher than
    // ## string's capacity.
    if (string.getCapacity() < string.getLength() + 1) {
        int newCapacity {(((string.getLength() + 1) / string.getAllocationDataChunk()) + 1) * string.getAllocationDataChunk()};
        string.setCapacity(newCapacity);
    }
    else {} // Nothing to do

    // #3 Copy digits in string
    my::copyString(tempBuffer, (string.mb_firstElementAdress + string.mb_length - numberOfSymbols), numberOfSymbols);

    return string;

}


//==============================================================================
// NAME: Overloaded [operator<<] for <const char*> type.
// GOAL: Writing buffer of <char> into the my::String object.
//==============================================================================
my::String& my::operator<<(my::String& string, const char* charDataBuffer)
{



    // #### Calculate length of @charDataBuffer
    const char* bufferPtr       {charDataBuffer};
    int         lengthOfBuffer  {0};

    for (int ii {0}; *bufferPtr != '\0'; ++ii, ++bufferPtr) {
        ++lengthOfBuffer;
    }

    // #### If my::String object has enough space for the new data
    // #1 Set new string's length.
    string.setLength(string.getLength() + lengthOfBuffer);

    // #2 Allocate memory if the new string length is higher than
    // ## string's capacity.
    if (string.getCapacity() < string.getLength() + 1) {
        int newCapacity {(((string.getLength() + 1) / string.getAllocationDataChunk()) + 1) * string.getAllocationDataChunk()};
        string.setCapacity(newCapacity);
    }
    else {} // Nothing to do

    // #3 Copy digits in string
    my::copyString(charDataBuffer, (string.mb_firstElementAdress + string.mb_length - lengthOfBuffer), lengthOfBuffer);

    return string;
}


//==============================================================================
// NAME: Friend function.
//       Overloaded [operator<<] for <const char> type.
// GOAL: Writing single <char> into the my::String object.
//==============================================================================
my::String& my::operator<<(my::String& string, const char symbol)
{
    // #### If my::String object has enough space for the new data
    // #1 Set new string's length.
    string.setLength(string.getLength() + 1);

    // #2 Allocate memory if the new string length is higher than
    // ## string's capacity.
    if (string.getCapacity() < string.getLength() + 1) {
        int newCapacity {(((string.getLength() + 1) / string.getAllocationDataChunk()) + 1) * string.getAllocationDataChunk()};
        string.setCapacity(newCapacity);
    }
    else {} // Nothing to do

    // #3 Copy digits in string
    my::copyString(&symbol, (string.mb_firstElementAdress + string.mb_length - 1), 1);


    return string;

}


//==============================================================================
// NAME: Copy assignment via overloaded [operator=].
// GOAL: We don't need to create a new object. Just assign to the existing one
//       doing a deep copy.
//==============================================================================
my::String& my::String::operator=(const my::String& string)
{
    const char* inputStringPtr  {string.mb_firstElementAdress};
    char*       thisPtr         {nullptr};

    // #1 Self-assignment checking
    if (this == &string) {
        return *this;
    }
    else {} // Nothing to do

    // #2 Delete data in the left-string
    if (mb_firstElementAdress != nullptr) {
        delete[] mb_firstElementAdress;
    }
    else {} // Nothing to do

    // #3 Assign data from right-string to left-string
    mb_length = string.mb_length;

    if (mb_capacity < mb_length + 1) {
        mb_capacity = (((mb_length + 1) / mb_allocationDataChunk) + 1) * mb_allocationDataChunk;
    }
    else {} // Nothing to do

    thisPtr = mb_firstElementAdress = new char[mb_capacity];
    for (int ii {0}; ii < mb_capacity; ++ii) {
        *thisPtr++ = (ii < mb_length) ? *inputStringPtr++ : '\0';
    }

    return *this;
}


//==============================================================================
// NAME: Move assignment via overloaded [operator=].
// GOAL: Transfer ownership from
//==============================================================================
my::String& my::String::operator=(my::String&& rString) noexcept
{
    // #1 Self-assignment checking
    if (&rString == this) {
        return *this;
    }
    else {} // Nothing to do

    delete[] mb_firstElementAdress;

    mb_firstElementAdress = rString.mb_firstElementAdress;
    rString.mb_firstElementAdress = nullptr;

    mb_length = rString.mb_length;
    mb_capacity = rString.mb_capacity;

    return *this;
}




//==============================================================================
// NAME: Friend function;
//       Overloaded [operator>>]
//==============================================================================
std::istream& my::operator>>(std::istream& in, my::String& string)
{
    char    ch     {'\0'};

    int   allocPortionSize {string.mb_allocationDataChunk};
    char* bufferAdress = new char[allocPortionSize];
    char* bufferPtr {bufferAdress};
    int   length    {0};
    int   capacity  {allocPortionSize};

    // #### Temporary variables that are destined for the case, when there are
    // #### not enough free space in the @inputBuffer and we need to allocate
    // #### more memory
    char* tempAdress    {nullptr};
    char* tempPtr       {nullptr};


    bool skipLeadingSpaces {true};
    while ((ch = in.get()) != '\n' && !in.eof()) {

        // #1 Skip the leading whitespaces
        if (skipLeadingSpaces && (ch == ' ' || ch == '\t')) {
            continue;
        }
        else {} // Nothing to do
        skipLeadingSpaces = false;

        // #2 Write input character in the buffer
        *bufferPtr = ch;
        ++length;

        // #3 If buffer has enough space for the NEXT character - nothing to do.
        // ## Else - allocate more memory.
        if (length < capacity) {
            ++bufferPtr;
        }
        else {
            capacity += allocPortionSize;

            tempPtr = tempAdress = bufferAdress;                // Save the old pointers
            bufferPtr = bufferAdress = new char[capacity];

            for (int ii {0}; ii < length; ++ii) {
                *bufferPtr++ = *tempPtr++;
            }
            delete[] tempAdress;
            tempPtr = tempAdress = nullptr;
        }

    }
    *bufferPtr = '\0';
    ++length;

    // ## Transfer input string (<char> data) into my::String
    string << bufferAdress;

    return in;

}


//===============================================================================
// Overloaded [operator<<]
//===============================================================================
std::ostream& my::operator<<(std::ostream& out, const String& string)
{
    int     length  {string.mb_length};
    char*   thisPtr {string.mb_firstElementAdress};

    // Output symbols except last '\0'
    while (length-- > 0) {
        out << *thisPtr++;
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
// WHAT: Member function
// WHY:  Allocates new <my::String> object with specified capacity and copies
//       primary string into the new one.
//==============================================================================
void my::String::setCapacity(int newCapacity)
{
    //assert((newCapacity < (mb_length + 1)) && "Haven't implemented yet.");

    char* newAdress {nullptr};                   // Pointer to start of new area
    char* newPtr    {nullptr};                   // Dynamic pointer of new area
    char* thisPtr   {mb_firstElementAdress};     // Dynamic pointer to old area

    mb_capacity = newCapacity;

    // #### Allocate new portion of memory in the heap
    try {
        newPtr = newAdress = new char[mb_capacity];
    }
    catch (std::bad_alloc&) {
        std::cerr << "\n[ERROR]::[my::String::setCapacity]:"
                  << "Couldn't allocate memory in the heap. Operator 'new' threw an exception"
                  << std::endl;
        /*
         * [QUESTION]: Should I free memory before exit?
         *             It seems that I haven't to catch an exception here.
         *             Only if I can/going to do smth with it.
         *             Just let the exception fall back to main.
         */
        exit(1);
    }

    // #### Copy original string in the new location.
    for (int ii {0}; ii < mb_capacity; ++ii) {
        *newPtr++ = (ii < mb_length && thisPtr != nullptr) ? *thisPtr++ : '\0';
    }

    // #### Delete old data
    delete[] mb_firstElementAdress;
    mb_firstElementAdress = newAdress;

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

//==============================================================================
// NAME:
// GOAL:
//==============================================================================
const char* my::String::getFirstElementAdress() const
{
    return mb_firstElementAdress;
}
