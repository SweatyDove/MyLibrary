#ifndef MY_UTILITIES_H
#define MY_UTILITIES_H



#include <iostream>
#include <cassert>
#include <chrono>


//==================================================================================================
//          TYPE:   Namespace
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
namespace my {

enum class RetCode {
	NO_ERROR = 0,

};




//==================================================================================================
//         TYPE:    Class
//  DESCRIPTION:    Provides the ability to measure time
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    Source: https://www.learncpp.com/cpp-tutorial/timing-your-code/
//==================================================================================================
class Timer {
public:
    // # Aliases for the measurement units
    using Second = std::chrono::duration<double, std::ratio<1>>;
    using Sec = std::chrono::duration<double,   std::ratio<1>>;

    using Nano = std::chrono::duration<double,  std::ratio<1, 1000000000>>;
    using Micro = std::chrono::duration<double, std::ratio<1, 1000000>>;
    using Milli = std::chrono::duration<double, std::ratio<1, 1000>>;

    enum class MeasureUnit {
        SECOND,
        MILLI,
        MICRO,
        NANO,

        TOTAL
    };

    // # steady_clock - это аналог секундомера, нужен для измерения промежутков
    // # system_clock - это уже часы, которые показывают время (здесь не указаны).
    using Clock = std::chrono::steady_clock;

private:
    MeasureUnit mb_unit {MeasureUnit::MILLI};
    std::chrono::time_point<Clock> mb_begin {};

public:
    Timer();
    void reset();
    double elapsed() const;
    void setMeasureUnit(MeasureUnit mu);

};





template <typename Type>
Type&&  move(Type& value);






template <class Type>
Type&& forward(typename std::remove_reference<Type>::type& value);

template <class Type>
Type&& forward(typename std::remove_reference<Type>::type&& value);



template <typename Type>
void swap(Type& a, Type& b);

//template <typename Type>
//void swap(Type&& a, Type&& b);






int     getRandomNumber(int min, int max);
int     readLineToBuffer(char* buffer, int sizeOfBuffer);
int     intToChar(int intNumber, char* buffer, int sizeOfBuffer);
void    invertBuffer(char* buffer, int fromElement, int toElement);
int     copyString(const char *sourceAdress, char *destinationAdress, const int numberOfSymbols);

float   power(int base, int exp);
float   binToFloat(char str);


} // End of 'my' namespace



// # For the template implementations
#include "Implementations/my_utilities.hpp"


#endif // MY_UTILITIES_H
