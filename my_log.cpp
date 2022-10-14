
#include "my_log.h"



//==============================================================================
// Конструктор класса. Открывает указанный файл @fileName для работы в режиме
// @fileMode. По-умолчанию, режим "только для записи".
//==============================================================================
my::Log::Log(const char* fileName, std::ios_base::openmode fileMode) :
    mb_logFile              {fileName, fileMode},
    mb_allowFileWriting     {true}
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
        mb_record = mb_recordQueue.getFrontContent();
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




//==========================================================================
// NAME:
// GOAL: Write log to file
//==========================================================================
void my::Log::writeLogToFile()
{
    int size {0};
    // #### Write all elements of list to file untill @mb_allowFileWriting
    // #### is true.
    while (mb_allowFileWriting) {

        // ## Write to file available records
        while ((size = mb_recordQueue.getSize()) > 0) {

            if (size > 1) {

                mb_record = mb_recordQueue.getFrontContent();
                mb_logFile.write(mb_record->getFirstElementAdress(),
                                 mb_record->getLength());
                mb_recordQueue.removeFront();
            }
            else if (size == 1 && )
        /*
         * Отдельно не нужно освобождать память, так как когда я вызываю
         * mb_record.removeFront -> вызывается деструктор который удаляет элемент
         * списка. А так как в этом элементе есть локальная переменная
         * <my::String> content - для неё конструктор вызовется автоматически.
         *
         * if (mb_record != nullptr) {
         *    delete[] mb_record;
         * }
         * else {} // Nothing to do
         */
    }

    // #### If @mb_recordQueue has (1) element, need to check mutex
    // #### Don't need to block this thread, it can wait.
    if (mb_lockFirstBlock.try_lock()) {
        mb_record = mb_recordQueue.getFrontContent();
        mb_logFile.write(mb_record->getFirstElementAdress(),
                         mb_record->getLength());
        mb_recordQueue.removeFront();
    }
    else {}

}

//==============================================================================
// NAME: Friend function
// GOAL: It finish the current record and makes preparations for the new one.
//==============================================================================
void my::endRecord(my::Log& log)
{
    // #### Add end-line symbol in the end of the data
    *(log.mb_record) << '\n';

    // #### Have no issues if the size of queue > 1
    if (log.mb_recordQueue.getSize() > 1) {
        log.mb_recordQueue.pushBack(log.mb_record);
    }
    // #### If there is 1 (or 0) elements in queue, we need to block writing
    // #### data in log-file, 'cause access to the first block of list is
    // #### a critical section.
    else {
        // #1 Block access to the first item of queue.
        log.mb_lockFirstBlock.lock();

        // #2 Write data and unlock mutex.
        log.mb_recordQueue.pushBack(log.mb_record);
        log.mb_lockFirstBlock.unlock();
    }

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
        mb_record = mb_recordQueue.getFrontContent();
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


