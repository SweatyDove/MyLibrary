#ifndef MY_PRETTYPRINT_H
#define MY_PRETTYPRINT_H

// # IO-libraries
#include <iostream>


// # Standart cotainers
#include <array>
#include <string>


// # C-libraries
#include <ctime>
#include <cstring>                  // For: strncpy(), memset()
#include <cstdarg>                  // For: ellipsis
#include <cstdio>                   // For: std::sprintf

#include <execinfo.h>               // For: backtrace()


namespace my {

//#define caller  __FUNCTION__

/*
 * ПЛАН:
 *
 * -- Функция должна иметь возможность отображать:
 *      1) Время сообщения
 *      2) Тип сообщения (INFO, DEBUG, ERROR, WARNING, FATAL/CRITICAL)
 *      3) Функцию, которая сообщение вызывает
 *      4) Кастомный вид сообщения, который формируется заранее (всякие отступы и т.п.)
 *      5) Среду вывода сообщения (файл, stdout/stderr, сокет)
 *
 * -- Так же нужно уметь работать со списком аргументов переменной длинны. Или как-то использовать
 *      стандартный функционал (sprintf() например)
 *
 * -- Добавить функцию автотестирования в каком-то виде
 *
 */




//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
class PrettyPrint {
public:

    // # Levels of output
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR,

        TOTAL
    };
    std::array<bool, static_cast<int>(Level::TOTAL)> mb_level {true, true, true, true};

    bool            mb_timeDisplay {true};
    bool            mb_funcNameDisplay {true};
    bool            mb_levelDisplay {true};

    const char*     mb_separator {"::"};
    const char*     mb_callerName {"unknown"};
    int             mb_softMargin {80};                 // Soft right edge, after which we can finish to print word on the current line and then have to move to the next line
    int             mb_hardNargin {100};                // Hard right edge, after which we have to move current word on the new line
    char            mb_filler {'_'};

    std::string     mb_header {};
    std::string     mb_message {};




    PrettyPrint();


    void displayLevel(bool debug, bool info, bool warning, bool error);
    void displayTime(bool);
    void displayFuncName(bool);


    void setSeparator(const char* sep);
    void printSeparator();

    void setFiller(const char filler);
    void setSoftMargin(int n);
    void setHardMargin(int n);
    void setCallerName(const char* callerName);


    void formTime();
    void formLevel(Level level);
    void formCallerName();

    void formHeader(Level level);
    void formMessage(const char* fmtLine, std::va_list argList);


//#define foo(fmtLine, ...) debug(__FUNCTION__, const char* fmtLine, ...)

    void debug(const char* fmtLine, ...);
    void info(const char* fmtLine, ...);
    void warn(const char* fmtLine, ...);
    void error(const char* fmtLine, ...);


    bool selfTest();



}; // PrettyPrint


bool isDigit(char ch);


} // End of 'my' namespace


#endif // MY_PRETTYPRINT_H
