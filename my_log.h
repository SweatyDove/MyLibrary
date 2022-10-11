#ifndef MY_LOG_H
#define MY_LOG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "my_string.h"
#include <queue>

//#include <typeinfo>

/*
 * Нужно создать класс, реализующий лог. То есть имеется какая-то информация в главном
 * потоке. Она передается в этот лог. А вспомогательный поток уже работает с этим логом,
 * т.е. пишет его в файл и т.п.
 *
 * Как работает лог? По-идее, для каждого входящего сообщения выделяется строка в динамической
 * памяти. И записывается указатель на эту строку в массив указателей.
 *
 * Затем, как только появляется возможность, производится запись на диск очередной строки.
 *
 */


// ######## Start of NAMESPACE_MY ########
namespace my {

class Log;

// Попытка реализовать аналог std::endl
//void endString(my::Log& log);

class Log {
public:

private:

    std::fstream                mb_logFile {};              // Файл для записи лога
    my::String*                 mb_record {nullptr};
    std::queue <my::String*>    mb_recordQueue {};          // Очередь указателей на строки для записи в файл

    int                         mb_numberOfRecord {1};

public:
    //==========================================================================
    // Конструкторы и деструкторы
    //==========================================================================
    Log(const char* fileName = nullptr, std::ios_base::openmode fileMode = std::ios_base::out);
    ~Log();

    //==========================================================================
    // Overloaded operators
    //==========================================================================
    template<typename InputType>
    friend my::Log& operator<<(my::Log& log, InputType inputValue)
    {
        *(log.mb_record) << inputValue;

        return log;
    }


//    friend my::Log& operator<<(my::Log& log, const char symbol);
//    friend my::Log& operator<<(my::Log& log, const char* string);


    //==========================================================================
    // Other functions
    //==========================================================================
    void endString();
    void printLog();



}; // #### End of Log-class ####


template<typename InputType>
my::Log& operator<<(my::Log& log, InputType input);

//my::Log& operator<<(my::Log& log, int intNumber);
//my::Log& operator<<(my::Log& log, const char symbol);
//my::Log& operator<<(my::Log& log, const char* string);



} // ######## End of NAMESPACE_MY ########


#endif  // MY_LOG_H
