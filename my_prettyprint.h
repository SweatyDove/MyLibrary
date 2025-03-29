#ifndef MY_PRETTYPRINT_H
#define MY_PRETTYPRINT_H

// # IO-libraries
#include <iostream>
#include <cassert>

// # Standart cotainers
#include <array>
#include <string>


// # C-libraries
#include <ctime>
#include <cstring>                  // For: strncpy(), memset()
#include <cstdarg>                  // For: ellipsis
#include <cstdio>                   // For: std::sprintf

#include <execinfo.h>               // For: backtrace()



#define     ENABLE_DEBUG_MES    false
#define     ENABLE_INFO_MES     false
#define     ENABLE_WARN_MES     false
#define     ENABLE_ERROR_MES    false


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

    // # Levels of output in principle ('true' means to display such messages)
    enum class Level {
        DEBUG,
        INFO,
        WARN,
        ERROR,

        TOTAL
    };
    std::array<bool, static_cast<int>(Level::TOTAL)> mb_level {};

    // # Header part
    bool            mb_timeDisplay {};                  // Form TIME in header
    bool            mb_funcNameDisplay {};              // Form FUNC in header
    bool            mb_levelTypeDisplay {};             // Form TYPE in header


    bool            mb_separateHeader {true};

    const char*     mb_separator {"::"};
    const char*     mb_callerName {"........"};
    int             mb_softMargin {80};                 // Soft right edge, after which we can finish to print word on the current line and then have to move to the next line
    int             mb_hardMargin {80};                // Hard right edge, after which we have to move current word on the new line
    char            mb_filler {' '};

    std::string     mb_topBorder {};
    std::string     mb_bottomBorder {"::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::"};

    std::string     mb_header {};
    std::string     mb_message {};
    std::string     mb_output {};




    PrettyPrint(std::array<bool, static_cast<int>(Level::TOTAL)> levels = {true, true, true, true},
                bool displayTime = true,            // Header 'TIME' part
                bool displayFuncName = false,       // Header 'FUNC' part
                bool displayLevelType = true,       // Header 'LEVEL' part
                int hardMargin = 100);


    void displayLevel(bool);
    void displayTime(bool);
    void displayFuncName(bool);


    void setSeparator(const char* sep);
    void printSeparator();

    void setFiller(const char filler);
    void setSoftMargin(int n);
    void setHardMargin(int n);
    void setCallerName(const char* callerName);
    void setTopBorder(const char* border);
    void setBottomBorder(const char* border);
    void setLevels(std::array<bool, static_cast<int>(Level::TOTAL)> outputLevels);


    void formTime();
    void formLevel(Level level);
    void formCallerName();

    int formHeader(Level level);
    int formMessage(const char* fmtLine, std::va_list argList);
    void formOutput(Level level, const char* fmtLine, std::va_list argList);


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
