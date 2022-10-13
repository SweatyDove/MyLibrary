
#include "my_log.h"



//==============================================================================
// Конструктор класса. Открывает указанный файл @fileName для работы в режиме
// @fileMode. По-умолчанию, режим "только для записи".
//==============================================================================
my::Log::Log(const char* fileName, std::ios_base::openmode fileMode) :
    mb_logFile {fileName, fileMode}
{
    mb_record = new my::String("");

    *mb_record << "\n#" << mb_numberOfRecord++ << '\n';

    // #### Error handling
    if (!mb_logFile.good()) {
       std::cerr << "\n[ERROR]::[my::log::log()]: Openning file \"" << fileName
                << "\" failed." << std::endl;
    }
    else {} // Nothing to do


}



//==============================================================================
// WHAT: Destructor
//==============================================================================
my::Log::~Log()
{
    // #### [TEMPORARY]
    while (0 != mb_recordQueue.getSize()) {
        mb_record = mb_recordQueue.getFront();
        mb_recordQueue.removeFront();
        if (mb_record != nullptr) {
            delete mb_record;
        }
        else {} // Nothing to do
    }

    // #### Need to write in the logfile all records before closing.
    // #### Going to add it in separate thread.
    mb_logFile.close();

}


//==============================================================================
// NAME: Friend function
// GOAL: It finish the current record and makes preparations for the new one.
//==============================================================================
void my::endRecord(my::Log& log)
{
    // #### Add end-line symbol in the end of the data
    *(log.mb_record) << '\n';
    log.mb_recordQueue.pushBack(log.mb_record);

    log.mb_record = new my::String("");
    *(log.mb_record) << "\n#" << log.mb_numberOfRecord++ << '\n';

    return;
}



//==============================================================================
// WHAT: Printing the log into std::cout and free it.
//==============================================================================
void my::Log::printLog()
{
    std::cout << "########  Start Log  ########\n";

    while (0 != mb_recordQueue.getSize()) {
        // Выводим первую строку из очереди
        //std::cout << "\nCurrent log size = " << mb_stringPtrQueue.size() << std::endl;
        mb_record = mb_recordQueue.getFront();
        std::cout << *mb_record;

        // Очищаем память, которая выделена под первую строку
        mb_recordQueue.removeFront();
        if (mb_record != nullptr) {
            delete mb_record;
        }
        else {} // Nothing to do
    }

    std::cout << "\n########  Finish Log  ########" << std::endl;

}


