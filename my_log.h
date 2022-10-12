#ifndef MY_LOG_H
#define MY_LOG_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "my_string.h"
#include <queue>



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
 *
 * 1) Заменить std::queue на список
 * 2) Добавить аналог std::endl;
 * 3) Добавить поток в конструкторе класса, осуществляющий запись в файл
 */




// ######## Start of NAMESPACE_MY ########
namespace my {



class Log {
public:

private:

    std::fstream                mb_logFile {};              // Файл для записи лога
    my::String*                 mb_record {nullptr};
    std::queue <my::String*>    mb_recordQueue {};          // Очередь указателей на строки для записи в файл

    int                         mb_numberOfRecord {1};

public:
    //==========================================================================
    // Constructors and Destructors.
    //==========================================================================
    Log(const char* fileName = nullptr, std::ios_base::openmode fileMode = std::ios_base::out);
    ~Log();

    //==========================================================================
    // Overloaded operators.
    //==========================================================================
    template<typename InputType>
    friend my::Log& operator<<(my::Log& log, InputType inputValue)
    {
        *(log.mb_record) << inputValue;

        return log;
    }

    friend my::Log& operator<<(my::Log& log, void (*functionPointer)(my::Log&))
    {
        functionPointer(log);
        return log;
    }


    //==========================================================================
    // Other functions.
    //==========================================================================
    void printLog();

    friend void endRecord(my::Log& log);



}; // #### End of Log-class ####


/*******************************************************************************
 * Below, I've declared friend function of my::Log class in the "my" namespace.
 * Otherwise - these functions are not visible.
 ******************************************************************************/
template<typename InputType>
my::Log& operator<<(my::Log& log, InputType input);

my::Log& operator<<(my::Log& log, void (*functionPointer)(my::Log&));

/*******************************************************************************
 * In the case below, my::endRecord and my::endr work with <my::Log>&, but
 * in the future, I can add other types via overloading, like "std::endl".
 ******************************************************************************/
void endRecord(my::Log& log);
void (*endr)(my::Log&) = my::endRecord;


} // ######## End of NAMESPACE_MY ########


#endif  // MY_LOG_H
