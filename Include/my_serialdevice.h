#ifndef CLS_SERIALDEVICE_H
#define CLS_SERIALDEVICE_H

/***************************************************************************************************
 * Based on sources:
 * https://blog.mbedded.ninja/programming/operating-systems/linux/linux-serial-ports-using-c-cpp/
 *
 *
 * КОММЕНТАРИЙ
 * По-хорошему, надо бы добавить отдельно флаги в сам класс, отвечающие за аналогичные флаги
 * структуры termios. И потом, наверное, как-то их инициализировать (например, при вызове
 * tcgetattr()).
 *
 **************************************************************************************************/

#include <iostream>
#include <fstream>
#include <cstring>
#include <cassert>
#include <termios.h>
#include <unistd.h>
#include <string>
#include <chrono>
#include <thread>

// Linux headers
#include <fcntl.h>                  // Contains file controls: O_RDWR...

namespace my {


//==================================================================================================
// TYPE:                Класс
// PARAMETERS:          --------
// DESCRIPTION:         Класс предоставляет методы взаимодействия с последовательными устройствами
//                      (по сути - это просто обертка над стандартными функциями)
// RETURN VALUE:        --------
// COMMENTS/BUGS:       Уйти от read/write в явном виде и использовать для чтения select()/poll(),
//                      так как на регулярной основе сталкиваюсь с блокировками.
//==================================================================================================
class SerialDevice {
public:

    enum class Flag {
        UNDEF = -1,
        TRUE = 0,
        FALSE = 1,
    };


    enum Speed {
        SPEED_115200    = B115200,
        SPEED_38400     = B38400,
    };


    enum RetCode {
        NO_ERROR,
        BAD_OPEN,
        BAD_CLOSE,
        BAD_TCGETATTR,
        BAD_TCSETATTR,
        BAD_FLUSH,
        BAD_WRITE,
        BAD_READ,

        MAX_RET_CODE
    };

    enum Mode {
        RW          =   O_RDWR,
        RO          =   O_RDONLY,
        WO          =   O_WRONLY,
        NONBLOCK    =   O_NDELAY

    };
private:
    const char*     mb_path {nullptr};
    Mode            mb_mode {Mode::RO};
    int             mb_descriptor {-1};
    termios         mb_tty;


    std::ostream*   mb_logFilePtr;

    std::chrono::milliseconds   mb_delayBeforeReadAnswer {0};


    std::string     mb_buffer;


    // # Флаги устройства
    Flag            mb_isCanonMode {Flag::UNDEF};
    Flag            mb_isEcho {Flag::UNDEF};




    // # Константы
    const int       mb_maxAttempt {3};

    RetCode         mb_retCode {NO_ERROR};
    std::string     mb_errCodeMessage {};
public:
    // #
    SerialDevice() = default;
    SerialDevice(const char* path, Mode mode = Mode::RO, std::ostream* logFilePtr = &std::cout);
    ~SerialDevice();


    // # Copy constructor/assignment
    SerialDevice(const SerialDevice& serialDevice) = delete;
    SerialDevice& operator=(const SerialDevice& serialDevice) = delete;

    // # Move constructor/assignment
    SerialDevice(SerialDevice&& serialDevice) noexcept;
    SerialDevice& operator=(SerialDevice&& serialDevice) noexcept;


    void openDevice(const char* path, Mode mode);
    void closeDevice();

    void getTermiosStruct();
    void setTermiosStruct();


    void setIOSpeed(Speed speed = SPEED_115200);
    void setCanonicalMode(bool b);

    // # Активация/деактивация различных режимов эха.
    void enableEcho(bool b);

    void flushDescriptorBuffer();
    int send(const std::string& data);
    int recv(int dataChunkSize);

    const std::string& getBuffer() const;


};




} // my
#endif // CLS_SERIALDEVICE_H
