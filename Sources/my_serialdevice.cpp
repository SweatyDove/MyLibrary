#include "my_serialdevice.h"





//==================================================================================================
// NAME:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
my::SerialDevice::SerialDevice(const char* path, Mode mode, std::ostream* logFilePtr) :
    mb_path {path}, mb_mode {mode}, mb_logFilePtr {logFilePtr}
{
    //    std::cout << "[DEBUG]: Invoked constructor for serial device " << path << std::endl;
    // # Открываем последовательное устройство @path в режиме @mode
    my::SerialDevice::openDevice(path, mode);
    //    std::cout << "[DEBUG]: Serial device " << path << " has been opened in the mode " << mode << std::endl;
    assert(mb_retCode == NO_ERROR);

}




//==================================================================================================
// NAME:            --------
// PARAMETERS:      --------
// DESCRIPTION:     Функция очищает данные буффера, связанного с файловым дескриптором
//                  последовательного устройства. Может очищать как непереданные данные, так и не
//                  считанные (или и те и другие). Тут для простоты я очищаю и те, и те (использую
//                  TCIOFLUSH в вызове tcflush()).
// RETURN VALUE:    --------
// COMMENTS/BUGS:   Надо иметь ввиду, что эта функция просто обертка над системной функцией tcflush,
//                  которая работает с системным буффером, ассоциированным с дескриптором, а не с
//                  локальным буффером объекта.
//==================================================================================================
void my::SerialDevice::flushDescriptorBuffer()
{
    // # Очищаем буффер
    if (tcflush(mb_descriptor, TCIOFLUSH) != 0) {
//        std::cerr << "\n=> Error " << errno << " from tcflush: " << std::strerror(errno) << std::endl;
        *mb_logFilePtr << "\n=> Error " << errno << " from tcflush: " << std::strerror(errno) << '\n';
        mb_retCode = BAD_FLUSH;
    }
    else {} // Nothing to do
}






//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Move constructor
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
my::SerialDevice::SerialDevice(my::SerialDevice&& serialDevice) noexcept:
    mb_path {serialDevice.mb_path},
    mb_mode {serialDevice.mb_mode},
    mb_descriptor {serialDevice.mb_descriptor},                         // Важно освободить ресурс
    mb_logFilePtr {serialDevice.mb_logFilePtr},
    mb_delayBeforeReadAnswer {serialDevice.mb_delayBeforeReadAnswer},
    mb_buffer {serialDevice.mb_buffer},                                 // А есть ли у std::string move constructor?
    mb_isCanonMode {serialDevice.mb_isCanonMode},
    mb_isEcho {serialDevice.mb_isEcho}
{
//    std::cout << "[DEBUG]: Invoked move-constructor for serial device " << mb_path << std::endl;

    this->getTermiosStruct();           // Устанавливаем значение структуры mb_tty

    // # Сбрасываем дескриптор старого устройства, иначе при вызове деструктора для него - закроется
    // # последовательное устройство, и новое устройство будет работать с "закрытым"
    serialDevice.mb_descriptor = -1;


    serialDevice.~SerialDevice();
}





//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Move assignment
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        В отличии от move constructor, здесь нужно освобождать ресурс, которым владеет
//                  левый операнд. Однако, наверное, не обязательно вызывать деструктор для правого
//                  операнда...
//==================================================================================================
my::SerialDevice& my::SerialDevice::operator=(my::SerialDevice&& serialDevice) noexcept
{
//    std::cout << "[DEBUG]: Invoked move-assignment for serial devices: left-operand - " << mb_path
//              << " right-operand - " << serialDevice.mb_path << std::endl;

    // # Если НЕ самоприсваивание, то сперва освобождаем ресурсы, которыми владеем (если владеем).
    if (&serialDevice != this) {

        // #### А именно закрываем последовательное устройство и устанавливаем дескриптор в -1
        if (mb_descriptor >= 0) {

            // #### Закрываем последовательное устройство
            my::SerialDevice::closeDevice();
            if (mb_retCode == NO_ERROR) {
//                std::cout << "[DEBUG]: Serial device has been closed" << std::endl;
            }
            else {} // Nothing to do
        }
        else {} // Nothing to do

        // #### Переменные ниже можно просто скопировать
        mb_path = serialDevice.mb_path;
        mb_mode = serialDevice.mb_mode;
        mb_logFilePtr = serialDevice.mb_logFilePtr;
        mb_delayBeforeReadAnswer = serialDevice.mb_delayBeforeReadAnswer;
        mb_buffer = serialDevice.mb_buffer;                                 // А есть ли у std::string move constructor?
        mb_isCanonMode = serialDevice.mb_isCanonMode;
        mb_isEcho = serialDevice.mb_isEcho;

        // #### Устранавливаем значение дескриптора правого операнда в -1. Это связано с тем, что
        // #### владеть выбранным дескриптором должен лишь один экземпляр класса (т.к. в случае
        // #### закрытия последовательного устройства и освобождения им дескриптора, второй экземпляр
        // #### класса не будет об этом знать (на данный момент так, но потом, в теории, можно добавить
        // #### синхронизацию и реализовать подобную ситуацию)).
        mb_descriptor = serialDevice.mb_descriptor;
        serialDevice.mb_descriptor = -1;

        this->getTermiosStruct();                                           // Устанавливаем значение структуры mb_tty

    }
    else {} // Nothing to do

    return *this;

}



//==================================================================================================
// NAME:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
my::SerialDevice::~SerialDevice()
{
//    std::cout << "[DEBUG]: Invoked destructor for serial device " << mb_path << std::endl;

    // # Закрываем последовательное устройство (если оно не было закрыто ранее в явном виде)
    if (mb_descriptor >= 0) {

        my::SerialDevice::closeDevice();
        if (mb_retCode == NO_ERROR) {
//            std::cout << "[DEBUG]: serial device has been closed" << std::endl;
        }
        else {} // Nothing to do

    }
    else {} // Nothing to do

}



//==================================================================================================
// NAME:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::openDevice(const char* path, Mode mode)
{
    mb_descriptor = open(path, mode);
    if (mb_descriptor < 0) {
//        std::cerr << "\nERROR " << errno << " from open() call: '" << std::strerror(errno)
//                  << "'." << std::endl;
        *mb_logFilePtr << "\nERROR " << errno << " from open() call: '" << std::strerror(errno) << "'.\n";
        mb_retCode = BAD_OPEN;
    }
    else {
//        std::cerr << "\nSerial device '" << path << "' successfully opened!" << std::endl;
        *mb_logFilePtr << "\nSerial device '" << path << "' successfully opened!\n";
        mb_retCode = NO_ERROR;
    }

    return;
}






//==================================================================================================
// NAME:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::closeDevice()
{
    if (close(mb_descriptor) != 0) {
//        std::cerr << "\nERROR " << errno << " from close(): '" << std::strerror(errno) << "'." << std::endl;
        *mb_logFilePtr << "\nERROR " << errno << " from close(): '" << std::strerror(errno) << "'.\n";
        mb_retCode = BAD_CLOSE;
    }
    else {
        mb_descriptor = -1;
        mb_retCode = NO_ERROR;
    }

}




//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Получаем структуру, которая описывает текущие параметры (флаги) нашего
//                  последовательного устройства. Также эти флаги можно посмотреть консольной
//                  командой "stty -a -F path-to-serial-device", где префиксом '-' будут
//                  обозначаться ВЫКЛЮЧЕННЫЕ биты, а без префикса - включенные.
//
//                  Ниже приведён пример этой структуры:
//
//                  struct termios {
//                      tcflag_t c_iflag;       // INPUT mode flags
//                      tcflag_t c_oflag;       // OUTPUT mode flags
//                      tcflag_t c_cflag;       // CONTROL mode flags
//                      tcflag_t c_lflag;       // LOCAL mode flags
//                      cc_t c_line;            // Line discipline
//                      cc_t c_cc[NCCS];        // Control characters
//                  };
//
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::getTermiosStruct()
{
    if (tcgetattr(mb_descriptor, &mb_tty) != 0) {
//        std::cerr << "\nERROR " << errno << " from tcgetattr() call: '" << std::strerror(errno)
//                  << "'." << std::endl;
        *mb_logFilePtr << "\nERROR " << errno << " from tcgetattr() call: '" << std::strerror(errno) << "'.\n";
        mb_retCode = BAD_TCGETATTR;
    }
    else {
        mb_retCode = NO_ERROR;
    }

    return;
}




//==================================================================================================
// NAME:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::setTermiosStruct()
{
    if (tcsetattr(mb_descriptor, TCSANOW, &mb_tty) != 0) {
//        std::cerr << "\nERROR " << errno << " from tcsetattr() call: '" << std::strerror(errno)
//                  << "'." << std::endl;
        *mb_logFilePtr << "\nERROR " << errno << " from tcsetattr() call: '" << std::strerror(errno) << "'.\n";
        mb_retCode = BAD_TCSETATTR;
    }
    else {
        mb_retCode = NO_ERROR;
    }

    return;
}







//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Установка скорости последовательного порта для ввода/вывода
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::setIOSpeed(Speed speed)
{
    getTermiosStruct();
    cfsetspeed(&mb_tty, speed);
    setTermiosStruct();
}



//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Активация/деактивация каноничного режима ввода.
//
//                  Если каноничный режим активен (true), то ввод обрабатывается только после
//                  получения символа новой строки '\n' (для Windows, в аналогичном случае, должно
//                  идти два символа '\r' и '\n', т.е. CRLF). Также имеется особая трактовка
//                  некоторых специальных символов.
//
//                  Если же режим деактивирован, то ввод обрабатывается сразу - чего, как правило,
//                  мы и хотим в случае последовательных устройств.
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::setCanonicalMode(bool b)
{
    getTermiosStruct();

    if (b) {
        mb_tty.c_lflag |= ICANON;
        mb_isCanonMode = Flag::TRUE;
    }
    else {
        mb_tty.c_lflag &= ~ICANON;
        mb_isCanonMode = Flag::FALSE;
    }

    setTermiosStruct();

}


//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Включение/выключение режима эха. Также имеются другие режимы эха
//                  (ECHOE, ECHONL...), но их пока не трогаю.
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::SerialDevice::enableEcho(bool b)
{
    getTermiosStruct();

    if (b) {
        mb_tty.c_lflag |= ECHO;
        mb_isEcho = Flag::TRUE;
    }
    else {
        mb_tty.c_lflag &= ~ECHO;
        mb_isEcho = Flag::FALSE;
    }

    setTermiosStruct();

}



//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Отправка команды в последовательное устройство (и запись ответа в буффер)
// ARGUMENTS:       @command    -   команда для отправки
// RETURN VALUE:    --------
// COMMENTS/BUGS:   Надо бы возвращать кол-во отправленных символов, но проблема в том, что данные
//                  могут форматироваться перед отправкой (добавление/удаление символа новой стоки
//                  и т.д.), поэтому надо продумать этот момент.
//==================================================================================================
int my::SerialDevice::send(const std::string& data)
{
    // # Формируем "чистую команду" без символов новой строки в конце
    std::string formatCommand = data;
    while (formatCommand.back() == '\n') {
        formatCommand.pop_back();
    }

    // # Добавляем символ новой строки в конец команды (если активен каноничный режим)
    if (mb_isCanonMode == Flag::TRUE) {
        formatCommand.push_back('\n');
    }
    else {} // Notning to do


    // # Отправляем команду
    int n {static_cast<int>(write(mb_descriptor, formatCommand.c_str(), formatCommand.size()))};
    if (n != formatCommand.size()) {
//        std::cerr << "\nERROR " << errno << " at writing command '" << data
//                  << "' in the device '" << this->mb_path << "':" << std::strerror(errno) << std::endl;
        *mb_logFilePtr << "\nERROR " << errno << " at writing command '" << data << "' in the device '"
                   << this->mb_path << "':" << std::strerror(errno) << '\n';
        mb_retCode = BAD_WRITE;
        return -1;
    }
    else {} // Nothing to do

    return 0;

}



//==================================================================================================
// NAME:            --------
// PARAMETERS:      --------
// RETURN VALUE:    --------
// DESCRIPTION:     --------
// COMMENTS/BUGS:   --------
//==================================================================================================
int my::SerialDevice::recv(int dataChunkSize)
{
    int             n {0};
    const int       bufferSize {dataChunkSize};
    int             position {0};
    int             freeSpace {bufferSize - position};
    char            buffer[bufferSize];


    std::memset(buffer, '\0', bufferSize);


    // # Считываем ответ в буффер
    int attempt {0};
    while (attempt < mb_maxAttempt) {
        n = read(mb_descriptor, buffer + position, freeSpace);
        if (n > 0) {
            position += n;
            freeSpace = bufferSize - position;
        }
        else {
            ++attempt;
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }

    /*
     * Может ниже обойтись без копирования как-то? Сразу писать в mb_buffer?
     */
    mb_buffer = buffer;

    return position + 1;
}




//==================================================================================================
// NAME:            --------
// DESCRIPTION:     Возвращает ссылку на буффер
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
const std::string& my::SerialDevice::getBuffer() const
{
    return mb_buffer;
}








