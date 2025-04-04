#include "my_string.h"
#include "my_utilities.h"


//==================================================================================================
//         TYPE:    Constructor
//  DESCRIPTION:    Construct <my::String> object from <const char*>.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    Didn't mark it is as explicit, because it is often used for the implicit
//                  conversions from <const char*>.
//==================================================================================================
my::String::String(const char* line)
{

    // # Determine the length of the input line
    int length {0};
    for (const char* p {line}; *p != '\0'; ++p) {
        ++length;
    }
    mb_length = length;

    // #### Allocate memory in the heap
    mb_capacity = mb_allocationDataChunk + ((mb_length - 1) / mb_allocationDataChunk) * mb_allocationDataChunk;
    mb_firstElementAdress = new char[mb_capacity];

    // # Copy line into allocated memory
    char* thisString {mb_firstElementAdress};
    for (int ii {0}; ii < mb_length; ++ii) {
        thisString[ii] = line[ii];
    }

    // # Other space of the string fill with '\0' for the convenience purpose.
    for (int ii {mb_length}; ii < mb_capacity; ++ii) {
        thisString[ii] = '\0';
    }

}


//===============================================================================
// TYPE: Copy constructor
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
// TYPE: Destructor
// GOAL: Destruct @this object with the deallocation of memory.
//==============================================================================
my::String::~String()
{
    delete[] mb_firstElementAdress;
    mb_firstElementAdress = nullptr;
}




//==============================================================================
// TYPE: Friend binary [operator+] for <my::String> and <my::String>
// GOAL: Create new <my::String> object via concatenation its arguments.
//==============================================================================
my::String& my::operator+(const my::String& leftString, const my::String& rightString)
{
    my::String* string {new my::String("")};
    *string << leftString.mb_firstElementAdress << rightString.mb_firstElementAdress;

    return *string;


}

//==============================================================================
// TYPE: Member function
// GOAL: Clear the <my::String> object without deallocation memory.
//       Just write '\0' in each significant symbol.
//==============================================================================
void my::String::clear()
{
    char*   tempPtr {mb_firstElementAdress};

    for (int ii {0}; ii < mb_length; ++ii) {
        *tempPtr++ = '\0';
    }
    mb_length = 0;
}




//==============================================================================
// TYPE: Overloaded [operator<<] for <int> type.
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
// TYPE: Overloaded [operator<<] for <const char*> type.
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
// TYPE: Friend function.
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
// TYPE: Overloaded [operator<<] for <const my::String&> type.
// GOAL:
//==============================================================================
my::String& my::operator<<(my::String& string, const my::String& inputString)
{
    string << inputString.getFirstElementAdress();

    return string;
}



//==============================================================================
// TYPE: Copy assignment via overloaded [operator=].
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
    delete[] mb_firstElementAdress;
    mb_firstElementAdress = nullptr;


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
// TYPE: Move assignment via overloaded [operator=].
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
    mb_firstElementAdress = nullptr;

    mb_firstElementAdress = rString.mb_firstElementAdress;
    rString.mb_firstElementAdress = nullptr;

    mb_length = rString.mb_length;
    mb_capacity = rString.mb_capacity;

    return *this;
}



//==============================================================================
// TYPE: Assignment overloaded [operator=] for <const char*> type.
// GOAL:
//==============================================================================
my::String& my::String::operator=(const char* stringLiteral)
{
    // #### Clear the current <my::String> object
    this->clear();

    // #### Write [stringLiteral] to [*this]
    *this << stringLiteral;

    return *this;
}


//==================================================================================================
//         TYPE:    Overloaded operator
//  DESCRIPTION:    Compares <my::String> object and C-Style string (terminated with '\0'). Firstly,
//                  String(const char*) constructor is called. Then, two <my::String> objects are
//                  compared.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
//bool my::String::operator==(const char* stringLiteral) const
//{
//
//}


//==================================================================================================
//         TYPE:    Overloaded operator
//  DESCRIPTION:    Compares two <my::String> objects, using their length as limit.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
bool my::String::operator==(const my::String& myString) const
{
    // # Check the length
    if (mb_length != myString.getLength()) {
        return false;
    }
    else {
        const char* leftStr {mb_firstElementAdress};
        const char* rightStr {myString.getFirstElementAdress()};

        // ## Compare two strings
        for (int ii {0}; ii < mb_length; ++ii) {
            if (leftStr[ii] != rightStr[ii]) {
                return false;
            }
            else {}
        }
    }

    return true;
}


//==================================================================================================
//         TYPE:    Method
//   PARAMETERS:    ........
//  DESCRIPTION:    Overloaded operator!=
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
bool my::String::operator!=(const char* stringLiteral)
{
    return !(*this == my::String(stringLiteral));
}



//==================================================================================================
//         TYPE:    Method
//   PARAMETERS:    ........
//  DESCRIPTION:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
bool my::String::operator!=(const my::String& myString)
{
    return (*this != myString.getFirstElementAdress());
}


//==================================================================================================
//         TYPE:    Friend function
//  DESCRIPTION:    Overloaded operator>>()
//   PARAMETERS:    --------
// RETURN VALUE:    --------
//     COMMENTS:    --------
//==================================================================================================
std::istream& my::operator>>(std::istream& in, my::String& string)
{
    char    ch     {'\0'};

    int   allocPortionSize {string.mb_allocationDataChunk};
    char* bufferAdress = new char[allocPortionSize];
    char* bufferPtr {bufferAdress};
    int   length    {0};
    int   capacity  {allocPortionSize};



    bool skipLeadingSpaces {true};
    while ((ch = static_cast<char>(in.get())) != '\n' && !in.eof()) {

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
            char* tempAdress    {nullptr};
            char* tempPtr       {nullptr};

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



//==================================================================================================
//         TYPE:    Friend function
//   PARAMETERS:    --------
//  DESCRIPTION:    --------
// RETURN VALUE:    --------
//     COMMENTS:    With simple handling of output alignment
//==================================================================================================
std::ostream& my::operator<<(std::ostream& out, const my::String& string)
{
    int     length  {string.mb_length};
    char*   thisPtr {string.mb_firstElementAdress};

    // ######## Handle the case, when "std::setw()" has been used for <my::String> object
    auto width = out.width();                       // Get required width of the output field
    if (width > length) {
        auto fillChar = out.fill();                 // Get the character-filler
        out << std::setw(0);                             // Reset "old" allignment 'cause it will be applied for the 1-st << operation
        for (int ii {0}; ii < width - length; ++ii) {
            out << fillChar;
        }
    }
    else {} // Nothing to do

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
// WHY:  Allocates new raw char buffer with new capacity, copy original data
//       into the new buffer and delete[] original buffer.
//==============================================================================
void my::String::setCapacity(int newCapacity)
{
    //assert(newCapacity < mb_length + 1 && "Haven't implemented yet.");

    // ###1 Set new capacity to [*this] object.
    mb_capacity = newCapacity;


    // ###2 Allocate new portion of memory in the heap
    char* newAdress {nullptr};                   // Pointer to the start of a new area
    char* newPtr    {nullptr};                   // Dynamic pointer of the new area

    try {
        newAdress = new char[mb_capacity];
        newPtr = newAdress;
    }
    catch (std::bad_alloc&) {
        std::cerr << "\n[ERROR]::[my::String::setCapacity]:"
                  << "Couldn't allocate memory in the heap. Operator 'new' threw an exception"
                  << std::endl;
        /******************************************************************
         * [QUESTION]: Should I free memory before exit?
         *             It seems that I haven't to catch an exception here.
         *             Only if I can/going to do smth with it.
         *             Just let the exception fall back to main.
         ******************************************************************/
        exit(1);
    }


    // ###3 Copy original data into the new area
    char* thisPtr   {mb_firstElementAdress};     // Dynamic pointer to the old area

    for (int ii {0}; ii < mb_capacity; ++ii) {
        *newPtr++ = (ii < mb_length && thisPtr != nullptr) ? *thisPtr++ : '\0';
    }

    // ###4 Delete old data
    delete[] mb_firstElementAdress;
    mb_firstElementAdress = newAdress;
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
int my::String::getAllocationDataChunk() const
{
    return mb_allocationDataChunk;
}

//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::String::setAllocationDataChunk(int bytes)
{
    mb_allocationDataChunk = bytes;
}

//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Returns address of the first (0-indexed) element of the <my::String> object.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
const char* my::String::getFirstElementAdress() const
{
    return mb_firstElementAdress;
}
