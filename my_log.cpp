
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


    // Здесь нужно запустить поток, осуществляющий запись в файл
    mb_writeToFileThread = std::thread{&my::Log::writeLogToFile, this};



}





//==============================================================================
// WHAT: Destructor
//==============================================================================
my::Log::~Log()
{
    if (mb_allowFileWriting) {
        this->endLog();
    }
    else {} // Nothing to do

}


//==========================================================================
// NAME:
// GOAL: Write one record to the file.
//==========================================================================
void my::Log::writeRecordToFile()
{
    mb_record = mb_recordQueue.getFrontContent();
    mb_logFile.write(mb_record->getFirstElementAdress(),
                     mb_record->getLength());
    mb_recordQueue.removeFront();

    return;
}





//==============================================================================
// NAME:
// GOAL: Write available log records to the file. There is an opportunity,
//       that not all records will be written, if the last log record is
//       being handled at the same time, when main-thread is pushing a new one.
//==============================================================================
void my::Log::writeLogToFile()
{
    // #### Write all elements of list to file untill @mb_allowFileWriting
    // #### is true.
    while (mb_allowFileWriting)
    {
        // ## Write to file all available records.
        if (mb_recordQueue.getSize() > 0){
            // Free writing all records till the last one.
            while (mb_recordQueue.getSize() > 1) {
                writeRecordToFile();
            }
            // Write the last one record if it is available (there is not
            // writing to the log from main-thread).
            if (mb_lockFirstBlock.try_lock()) {
                writeRecordToFile();
                mb_lockFirstBlock.unlock();
            }
            else {} // Nothing to do
        }
        else {} // Nothing to do

        // ## Sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

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



//==============================================================================
// GOAL: Function performs actions for writing remaining records to the file
//       and closing this file.
//==============================================================================
int my::Log::endLog()
{

    // #1 Stop the file-writing-thread
    mb_allowFileWriting.store(false);
    mb_writeToFileThread.join();

    // #2 If there is some data in the [mb_record], have to write it in the
    // ## [mb_recordQueue].
    if (mb_record->getLength() > 0) {
        my::endRecord(*this);
    }
    else {} // Nothing to do

    // #3 Write to the [mb_logFile] remaining records and close this file.
    while (mb_recordQueue.getSize() > 0) {
        writeRecordToFile();
    }
    mb_logFile.close();


    return 0;
}


