#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <iostream>
#include <chrono>




namespace my {

enum class RetCode {
	NO_ERROR = 0,

};


//==================================================================================================
// Source: https://www.learncpp.com/cpp-tutorial/timing-your-code/
//==================================================================================================
class Timer {
private:
    // # steady_clock - это аналог секундомера, нужен для измерения промежутков
    // # system_clock - это уже часы, которые показывают время (здесь не указаны).
    using Clock = std::chrono::steady_clock;

    // # Aliases for the measurement units
    using Second = std::chrono::duration<double, std::ratio<1>>;
    using Nano = std::chrono::duration<double,  std::ratio<1, 1000000000>>;
    using Micro = std::chrono::duration<double, std::ratio<1, 1000000>>;
    using Milli = std::chrono::duration<double, std::ratio<1, 1000>>;
    using Sec = std::chrono::duration<double,   std::ratio<1>>;


    std::chrono::time_point<Clock> mb_begin {};
public:
    Timer();
    void reset();
    double elapsed() const;
};


int getRandomNumber(int min, int max);

//==============================================================================
// Function reads an input line (till '\n' inclusively) into the buffer @buffer.
//==============================================================================
int readLineToBuffer(char* buffer, int sizeOfBuffer);


//===============================================================================
// Convert integer number @intNumber into the set of chars, that represent all
// number's digits. That set is placed into the @buffer of size @sizeOfBuffer.
//===============================================================================
int intToChar(int intNumber, char* buffer, int sizeOfBuffer);

//===============================================================================
// Function just invert @buffer of size @sizeOfBuffer
//===============================================================================
int invertBuffer(char* buffer, int fromElement, int toElement);

//===============================================================================
// TYPE:
// GOAL: Copy string (substring) from @sourceAdress into the string (substring)
//       @destinationAdress.
//       If (@numberOfSymbols == 0) -> copy symbols till met '\0' in the source.
//       Else -> copy @numberOfSymbols symbols.
//===============================================================================
int copyString(const char *sourceAdress, char *destinationAdress, int numberOfSymbols);

}

#endif // MY_UTILITIES_H
