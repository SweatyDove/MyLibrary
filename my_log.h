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
    //std::stringstream           mb_stringStream {};
    std::fstream                mb_logFile {};              // Файл для записи лога
    //std::string*                mb_string {nullptr};               // Указатель на очередную строку
    //std::queue <std::string*>   mb_stringPtrQueue {};       // Очередь указателей на строки для записи в файл

    my::String*                 mb_record {nullptr};
    std::queue <my::String*>    mb_recordPtrQueue {};       // Очередь указателей на строки для записи в файл

public:
    /***********************************************************************************
     * Конструкторы и деструкторы
     ***********************************************************************************/
    Log(const char* fileName = nullptr, std::ios_base::openmode fileMode = std::ios_base::out);
    ~Log();


    /*****************************************************************************
     * Оператор вставки для моего класса. Получает данные и записывает их в динамически
     * выделенную строку. Текущая строка заканчивается при передаче std::endl.
     * Затем эта строка может быть записана в файл. Для этой записи планируется
     * использовать отдельный поток.
     *****************************************************************************/
//    template<typename inputDataType>
//    friend my::Log& operator<<(my::Log& log, const inputDataType& inputData)
//    {
//        //std::cout << "Invoke template version\n";
//        log.mb_stringStream << inputData;
//        std::cout << "\n[DEBUG]: Current stringstream: \n" << log.mb_stringStream.str() << std::endl;


//        return log;
//    }

    void endString(void);
    void printLog(void);



//    friend Log& operator<<(Log& log, const int& intData)
//    {
//        std::cout << "Invoke int version\n";

//        log.mb_string->

//    }


}; // #### End of Log-class ####


} // ######## End of NAMESPACE_MY ########


#endif  // MY_LOG_H
