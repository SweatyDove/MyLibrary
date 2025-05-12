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





// ######## Start of NAMESPACE_MY ########
namespace my {



// Где-то ошибка с подобным описанием: "съедает первую букву в "The " и из-за этого ошибка delete[] так как не с первого символа удаление"


class Log {
public:

private:

    std::fstream                mb_logFile {};              // File-stream connected with the file for writing
    int                         mb_recordNumber {};         // Number of current record in this log entity
    my::String                  mb_recordTitle   {};        // Just temporary object for the record-title
    my::String                  mb_recordContent {};        // Temporary object for the record-content

    my::Queue<my::String*>      mb_recordQueue {};          // <my::String*> object will be formed from the [mb_recordTitle]
                                                            // and [mb_recordContent] and pushed into this [mb_recordQueue]

    std::mutex                  mb_lastRecordMutex {};      // It manages access to the last record.
    std::atomic<bool>           mb_allowFileWriting {};     // Variable for the tread synchronization.

    std::thread                 mb_writeToFileThread {};    // Off-thread that is writing records to the file.

    std::chrono::milliseconds   mb_sleepTimeMSec {};        // Time of sleep for [mb_writeToFileThread].



public:
    //==========================================================================
    // TYPE: Constructor
    //==========================================================================
    explicit Log(const char* fileName = "log_file.txt",
                 std::ios_base::openmode fileMode = std::ios_base::out);

    //==========================================================================
    // TYPE: Destructor
    //==========================================================================
    ~Log();


    /***************************************
     ******** Overloaded operators. ********
     ***************************************/

    //==========================================================================
    // TYPE: Friend overloaded [operator<<] for <char>, <const char*>, <int>.
    // GOAL: Write [inputValue] of specified type in the log record.
    //==========================================================================
    template<typename InputType>
    friend my::Log& operator<<(my::Log& log, InputType inputValue)
    {
        log.mb_recordContent << inputValue;

        return log;
    }

    //==========================================================================
    // TYPE: Friend overloaded [operator<<] for functions.
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
    // TYPE: Friend function
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
