#ifndef MY_PRETTYPRINT_H
#define MY_PRETTYPRINT_H

#include <iostream>
#include <array>
#include <ctime>
#include <cstring>                  // For: strncpy(), memset()

namespace my {


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

    bool mb_timeDisplay {true};
    bool mb_funcNameDisplay {true};
    const char* mb_separator {"::"};




    PrettyPrint();


    void displayLevel(bool debug, bool info, bool warning, bool error);
    void displayTime(bool);
    void displayFuncName(bool);

    void setSeparator(const char* sep);
    void printSeparator();



    void printTime();
    void printFuncName();

//    void formMessage(char* line);
    void debug(char* line);
};


}


#endif // MY_PRETTYPRINT_H
