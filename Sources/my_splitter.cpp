#include "my_splitter.h"


//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
my::Splitter::Splitter(const std::string& buffer, std::ostream& logStream) :
    mb_buffer {buffer},
    mb_logStream {logStream}
{
    mb_stringList.push_back("");        // Первый эл-т будет путой строкой (для удобства)

//    std::cout << "[DEBUG]: Object of <my::Splitter> class has been created!" << std::endl;
}



//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Шаблон деструктора класса
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
my::Splitter::~Splitter()
{    
//    std::cout << "[DEBUG]: Object of <my::Splitter> class has been destroyed!" << std::endl;
}



//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Установка флагов в значение (true)
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void my::Splitter::setFlag(my::Splitter::Flag flag)
{
    switch (flag) {
    case Flag::ACCUR_START:
        mb_accurateStart = true;
        break;
    case Flag::ACCUR_END:
        mb_accurateEnd = true;
        break;
    case Flag::SKIP_LEAD_SPACE:
        mb_skipLeadingWhitespaces = true;
        break;
    case Flag::SKIP_QUOTE:
        mb_skipQuote = true;
        break;
    case Flag::ALL:
        mb_accurateStart = true;
        mb_accurateEnd = true;
        mb_skipLeadingWhitespaces = true;
        mb_skipQuote = true;
        break;
    }

}





//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Сброс флагов (установка в значение false)
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void my::Splitter::resetFlag(my::Splitter::Flag flag)
{
    switch (flag) {
    case Flag::ACCUR_START:
        mb_accurateStart = false;
        break;
    case Flag::ACCUR_END:
        mb_accurateEnd = false;
        break;
    case Flag::SKIP_LEAD_SPACE:
        mb_skipLeadingWhitespaces = false;
        break;
    case Flag::SKIP_QUOTE:
        mb_skipQuote = false;
        break;
    case Flag::ALL:
        mb_accurateStart = false;
        mb_accurateEnd = false;
        mb_skipLeadingWhitespaces = false;
        mb_skipQuote = false;
        break;
    }

}



//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Получение значения флага
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
bool my::Splitter::getFlag(my::Splitter::Flag flag) const
{

    switch (flag) {
    case Flag::ACCUR_START:
        return mb_accurateStart;
        break;
    case Flag::ACCUR_END:
        return mb_accurateEnd;
        break;
    case Flag::SKIP_LEAD_SPACE:
        return mb_skipLeadingWhitespaces;
        break;
    case Flag::SKIP_QUOTE:
        return mb_skipQuote;
        break;
    case Flag::ALL:
        assert(false && "Warning: can't return the state of all flags simultaneously.");
        break;
    }

    return false;
}


//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::Splitter::getDelimList(DelimList list) const
{
    const std::vector<char>* delimList {nullptr};

    switch (list) {
    case my::Splitter::DelimList::BEGIN:
        delimList = &mb_delimBeginList;
        break;
    case my::Splitter::DelimList::END:
        delimList = &mb_delimEndList;
        break;
    }

    for (char ch : *delimList) {
        std::cout << ch << ' ';
    }
    std::cout << std::endl;
}






//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
void my::Splitter::addDelim(std::vector<char> arrayOfDelims, my::Splitter::DelimList list)
{
    std::vector<char>* delimList {nullptr};
    // # Выбор списка, куда закидываем символ-разделитель
    switch (list) {
    case my::Splitter::DelimList::BEGIN:
        delimList = &mb_delimBeginList;
        break;
    case my::Splitter::DelimList::END:
        delimList = &mb_delimEndList;
        break;
    }

    for (auto ch : arrayOfDelims) {
        delimList->push_back(ch);
    }
}



//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Проверка на то, является ли символ - символом из списка разделителей.
//                  В том случае, когда список разделителей НАЧАЛА строки ПУСТ, разделителем считается любой символ,
//                  отличный от символа конца строки. При этом, список символов конца строки не может
//                  быть пустым (или изначально инициализировать дефолтным значением, или проверять
//                  перед вызовом той или иной функции).
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
bool my::Splitter::isDelim(char symbol, const std::vector<char>& list)
{
    // # Pointer to the function from <algorithm>
    bool (*fn)(std::vector<char>::const_iterator begin, std::vector<char>::const_iterator end, const std::function<bool(char)>& lambda);

    // # Lambda definition
    auto isSymb
    {
        [symbol](char ch) {return symbol == ch;}
    };

    // # Pointer to the used list
    const std::vector<char>* listPtr {nullptr};

    // # В том случае, когда список разделителей НАЧАЛА строки ПУСТ, разделителем считается
    // # любой символ, отличный от символа конца строки. Возможно, в этом случае нужно устанавливать
    // # флаг того, что стартовый разделитель является частью строки.
    if (list == mb_delimBeginList && list.size() == 0) {
        listPtr = &mb_delimEndList;
        mb_beginIsPart = true;
        fn = std::none_of;
    }
    // # Обычная проверка на наличие символа в указанном списке
    else {
        listPtr = &list;
        fn = std::any_of;
    }

    return fn(listPtr->begin(), listPtr->end(), isSymb);
}







//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Проверяем, является ли текущий символ в буффере - символом открывающей/закрывающей
//                  кавычки. Или же это просто 'кавычка'.
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// BUGS:            --------
//==================================================================================================
bool my::Splitter::isQuote(int bufferPosition) const
{
    int backslashNumber {0};

    // ## Если встретили кавычку, считаем кол-во слешей перед ней
    for (int kk {bufferPosition - 1}; kk >= 0; --kk) {
        if (mb_buffer[kk] == '\\') {
            ++backslashNumber;
        }
        else {
            break;
        }
    }

    // ## Если слешей чётное число, то перед нами закрывающая/открывающая кавычка
    if (backslashNumber % 2 == 0) {
        return true;
    }
    // ## Если слешей нечетное число, то перед нами просто 'символ кавычки'
    else {
        return false;
    }
}




//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     Функция сплитит строку на эл-ты и заносит их в массив @mb_stringList
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void my::Splitter::splitIt()
{
    // # Сперва находим нужную строку
    int     lineNumber {0};
    char    ch {'\0'};

    std::string currentString;

    bool isQuoted {false};
    bool isLine {false};
    bool lineHandled {true};                            // Предыдущая строка обработана (если она была)

    bool skipLeadingWhitespaces {mb_skipLeadingWhitespaces};
    bool isSkippingWS {false};                          // Флаг самого процесса пропуска символов пустого пространства

    for (unsigned int ii {0}; ii < mb_buffer.size(); ++ii) {

        // #### Считываем следующий символ
        ch = mb_buffer[ii];



        // #### Пропуск символов пустого пространства (после разделителя)
        if (skipLeadingWhitespaces == true && lineHandled == true && (ch == ' ' || ch == '\t')) {
            isSkippingWS = true;
            continue;
        }
        // #### Сбрасываем флаг пропуска только если до этого были в процессе пропуска
        else if (skipLeadingWhitespaces == true && isSkippingWS == true && lineHandled == true) {
            skipLeadingWhitespaces = false;
            isSkippingWS = false;
        }
        else {}





        // #### Проверка на открытие/закрытие кавычек
        if (ch == '\"' && my::Splitter::isQuote(ii) == true) {
            isQuoted = !isQuoted;
            if (mb_skipQuote == true) {
                continue;
            }
            else {}
        }
        else {} // Nothing to do



        // #### Встретили символ-определитель НАЧАЛА строки
        if (isLine == false && my::Splitter::isDelim(ch, mb_delimBeginList) == true) {

            ++lineNumber;
            isLine = true;
            lineHandled = false;

            // ## Проверка флагов
            if (mb_skipLeadingWhitespaces == true) {
                skipLeadingWhitespaces = true;
            }
            else {}

            // ## Если символ ОПРЕДЕЛИТЕЛЬ начала строки НЕ является её частью - скипаем его
            if (mb_beginIsPart == false) {
                continue;
            }
            else {} // Nothing to do
        }
        // #### Случай нескольких РАЗДЕЛИТЕЛЕЙ подряд, когда они считаются не вместе (работает, когда
        // #### список ОПРЕДЕЛИТЕЛЕЙ строки пуст)
        else if (isLine == false && my::Splitter::isDelim(ch, mb_delimEndList) == true && mb_delimBeginList.size() == 0) {
            ++lineNumber;
            lineHandled = false;
        }
        else {} // Nothing to do




        // #### Поиcк конца строки (а вот тут кавычки должны учитываться, т.к. конец строки В КАВЫЧКАХ
        // #### не является концом строки)
        if (isLine == true && my::Splitter::isDelim(ch, mb_delimEndList) == true && isQuoted == false) {
            isLine = false;
        }
        else {} // Nothing to do



        // #### Запись текущей строки
        if (isLine == true) {
            currentString.push_back(ch);
        }
        // #### Заносим текущую строку в массив разделенных строк
        else if (isLine == false && lineHandled == false) {
            mb_stringList.push_back(currentString);
            currentString.clear();
            lineHandled = true;
        }
        else {} // Nothing to do

    } // for


    // #### Если чтение строки закончилось НЕ символом окончания чтения, а из-за того, что закончился
    // #### буффер, то считать ли такую строку валидной?
    if (isLine == true && mb_accurateEnd == false) {
        mb_stringList.push_back(currentString);
        mb_retCode = my::Splitter::RetCode::NO_ERROR;
    }
    else {
        mb_retCode = my::Splitter::RetCode::STRING_NOT_FOUND;
    }
}





//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
const std::string& my::Splitter::getItem(unsigned int itemNumber) const
{

    if (itemNumber < mb_stringList.size()) {
        return mb_stringList[itemNumber];
    }
    else {
        mb_logStream << "[WARNING]: There is not item " << itemNumber << " in the splitted string buffer."
                     << "\nSTART-OF-BUFFER >>>>>  " << mb_buffer << "  <<<<<<<< END-OF-BUFFER" << std::endl;
        return mb_stringList[0];
    }

}



//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
unsigned int my::Splitter::getNumOfItems() const
{
    return mb_stringList.size();
}




//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void    my::Splitter::ltrim(std::string& string, std::vector<unsigned char>& trimList)
{
    // # Лямбда, возвращает true, если символ @ch НЕ находится в векторе @trimList
    auto notInTrimList {
                [&trimList](unsigned char ch) {return !(std::find(trimList.begin(), trimList.end(), ch) != trimList.end());}
    };

    // # Убираем символы из строки @string, которые находятся в списке @trimList (ниже логика
    // # такова, что мы ищем итератор первого символа, не находящегося в списке @trimList,
    // # а затем удаляем в строке @string всё до этого символа
    string.erase(string.begin(), std::find_if(string.begin(), string.end(), notInTrimList));

}


//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void    my::Splitter::rtrim(std::string& string, std::vector<unsigned char>& trimList)
{

    // # Лямбда, возвращает true, если символ @ch НЕ находится в векторе @trimList
    auto notInTrimList {
        [&trimList](unsigned char ch) {return !(std::find(trimList.begin(), trimList.end(), ch) != trimList.end());}
    };

    // # Убираем символы из строки @string, которые находятся в списке @trimList (ниже логика
    // # такова, что мы ищем итератор первого символа с конца, не находящегося в списке @trimList,
    // # а затем удаляем в строке @string всё с этого символа и до конца)
    string.erase(std::find_if(string.rbegin(), string.rend(), notInTrimList).base(), string.end());

}


//==================================================================================================
// TYPE:            --------
// DESCRIPTION:     --------
// ARGUMENTS:       --------
// RETURN VALUE:    --------
// COMMENTS:        --------
//==================================================================================================
void    my::Splitter::trim(std::string& string, std::vector<unsigned char>& trimList)
{
    my::Splitter::ltrim(string, trimList);
    my::Splitter::rtrim(string, trimList);

}

