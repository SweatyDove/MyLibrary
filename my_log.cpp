
//#include "my_log.h"

///*****************************************************************************
// * Конструктор класса. Открывает указанный файл @fileName для работы в режиме
// * @fileMode. По-умолчанию, режим "только для записи".
// ******************************************************************************/
//my::Log::Log(const char* fileName, std::ios_base::openmode fileMode) :
//    mb_logFile {fileName, fileMode}
//    //mb_string {new std::string}
//{
//    // #### Error handling
//    // ##########
//    if (!mb_logFile.good()) {
//        std::cerr << "\n[ERROR]::[my::log::log()]: Openning file \"" << fileName
//                  << "\" failed." << std::endl;
//    }
//    else {} // Nothing to do


//}



///*****************************************************************************
// * Деструктор класса.
// *****************************************************************************/
//my::Log::~Log()
//{
//    mb_logFile.close();
//}

///*****************************************************************************
// * Функция обозначает конец текущей строки и запись её в массив элементов.
// *****************************************************************************/
//void my::Log::endString()
//{
//    // #### Add end-line symbol in the end of the data, stored in
//    // #### std::stringstream object
//    mb_stringStream.putback('\n');
//    //mb_stringStream.putback('\0');
//    std::cout << "\n[DEBUG]: Current stringstream: \n" << mb_stringStream.str() << std::endl;



//    // #### Allocate new std::string object in the heap and write data to it
//    // #### from std::stringstream object
//    mb_string = new std::string;
//    *mb_string = mb_stringStream.str();
//    std::cout << "\n[DEBUG]: Current string: \n" << *mb_string << std::endl;
//    mb_stringStream.str("1");

//    mb_stringPtrQueue.push(mb_string);
//    mb_string = nullptr;

//    //std::cout << *mb_string << std::endl;

//}




//void my::Log::printlog()
//{
//    while (!mb_stringPtrQueue.empty()) {
//        // Выводим первую строку из очереди
//        std::cout << "\nCurrent log size = " << mb_stringPtrQueue.size() << std::endl;
//        mb_string = mb_stringPtrQueue.front();
//        std::cout << *mb_string << std::endl;

//        // Очищаем память, которая выделена под первую строку
//        mb_stringPtrQueue.pop();
//        if (mb_string != nullptr) {
//            delete mb_string;
//        }
//        else {} // Nothing to do
//    }
//}


