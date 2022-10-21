#ifndef MY_LOG_H
#define MY_LOG_H

#include <iostream>
#include <fstream>
#include "my_string.h"
#include "my_queue.hpp"

#include <chrono>
#include <thread>
#include <atomic>
#include <mutex>



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
 *
 * Проблемы:
 *
 *  1)  Разный вывод при одинаковых запусках. Скорее всего имеется состояние
 *      гонки.
 *
 */




// ######## Start of NAMESPACE_MY ########
namespace my {



class Log {
public:

private:

    std::fstream                mb_logFile {};              // File-stream connected with the file for writing
    int                         mb_recordNumber {};         // Number of current record in this log entity
    my::String                  mb_recordTitle   {};        // Just temporary object for the record-title
    my::String                  mb_recordContent {};        // Temporary object for the record-content

    my::Queue<my::String*>      mb_recordQueue {};          // <my::String*> object will be formed from the [mb_recordTitle]
                                                            // and [mb_recordContent] and pushed into this [mb_recordQueue]

    std::mutex                  mb_lastRecordMutex {};       // It manages access to the last record
    std::atomic<bool>           mb_allowFileWriting {};     // Variable for the tread synchronization

    std::thread                 mb_writeToFileThread {};    // Off-thread that is writing records to the file



public:
    //==========================================================================
    // NAME: Constructor
    //==========================================================================
    explicit Log(const char* fileName = nullptr, std::ios_base::openmode fileMode = std::ios_base::out);

    //==========================================================================
    // NAME: Destructor
    //==========================================================================
    ~Log();


    /***************************************
     ******** Overloaded operators. ********
     ***************************************/

    //==========================================================================
    // NAME: Friend overloaded [operator<<] for <char>, <const char*>, <int>.
    // GOAL: Write @inputValue of specified type in the log record.
    //==========================================================================
    template<typename InputType>
    friend my::Log& operator<<(my::Log& log, InputType inputValue)
    {
        log.mb_recordContent << inputValue;

        return log;
    }

    //==========================================================================
    // NAME: Friend overloaded [operator<<] for functions.
    // GOAL: Call the specified function with @log parameter.
    //==========================================================================
    friend my::Log& operator<<(my::Log& log, void (*functionPointer)(my::Log&))
    {
        functionPointer(log);
        return log;
    }


    //==========================================================================
    // WHAT: Function print current log to stdout and free memory.
    // WHY:  Debug
    //==========================================================================
    //void printLog();


    //==========================================================================
    //
    //==========================================================================
    void writeRecordToFile();



    //==========================================================================
    //
    //==========================================================================
    void writeLogToFile();


    //==========================================================================
    //
    //==========================================================================
    int endLog();


    //==========================================================================
    // NAME: Friend function
    // GOAL: It finishes the current record and makes preparations for the new one.
    //==========================================================================
    friend void endRecord(my::Log& log);



}; // #### End of Log-class ####


/*
 * Below, I've declared friend function of my::Log class in the "my" namespace.
 * Otherwise - these functions are not visible.
 */
template<typename InputType>
my::Log& operator<<(my::Log& log, InputType input);

my::Log& operator<<(my::Log& log, void (*functionPointer)(my::Log&));

/*
 * In the case below, my::endRecord and my::endr work with <my::Log>&, but
 * in the future, I can add other types via overloading, like a "std::endl"
 * is released.
 */
void endRecord(my::Log& log);
//void (*endr)(my::Log&) = my::endRecord;


} // ######## End of NAMESPACE_MY ########


#endif  // MY_LOG_H
