#ifndef CLS_SPLITTER_H
#define CLS_SPLITTER_H

#include <iostream>
#include <cassert>
#include <vector>
#include <string>
#include <array>

#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

namespace my {

// # Простой парсер условной "строки", делящий её на условные "столбцы".
class Splitter {
public:
    enum class Flag {
        ACCUR_START,
        ACCUR_END,
        SKIP_LEAD_SPACE,
        SKIP_QUOTE,
        ALL,
    };

    enum class DelimList {
        BEGIN,
        END
    };

private:

    enum class RetCode {
        NO_ERROR,
        STRING_NOT_FOUND,

        MAX_RET_CODE
    };


    std::vector<char>   mb_delimBeginList;
    std::vector<char>   mb_delimEndList;

    // # Флаги, регулирующие поведение парсера в разных ситуациях
    bool mb_beginIsPart {false};                // Символ разделитель НАЧАЛА является частью элемента
    bool mb_endIsPart {false};                  // Символ разделитель КОНЦА является частью элемента
    bool mb_accurateStart {false};             // Флаг аккуратного начала считывания строки (только по наличию символа из списка)
    bool mb_accurateEnd {false};               // Флаг аккуратного окончания считывания строки (только по наличию символа из списка)
    bool mb_severalDelimIsDelim {false};        // Считать ли несколько разделителей подряд одним разделителем или же рассматривать их как разделители пустых элементов.
                                                // Например, для случая "a,b,,d,e" всё выглядит так, будто между запятыми есть пустой эл-т. Но в случае, когда разделителем
                                                // является симрол пробела - это может быть незаметно.
    bool mb_skipLeadingWhitespaces {false};
    bool mb_skipQuote {false};                  // Учитывать ли кавычки как часть ячейки или скипывать их и учитывать только то, что внутри
    //bool mb_anyLineDelim {true};                // Любой символ считается за начало строки (кроме символов конца строки)



    const std::string&          mb_buffer;
    std::vector<std::string>    mb_stringList;

    RetCode                     mb_retCode {my::Splitter::RetCode::NO_ERROR};

    bool                        isQuote(int bufferPosition) const;
    bool                        isDelim(char symbol, const std::vector<char>& delimList);


    std::ostream&           mb_logStream;

public:
    explicit Splitter(const std::string& buffer, std::ostream& logStream = std::cout);
    ~Splitter();

    const std::string&      getBuffer() const {return mb_buffer;}
    void                    setFlag(Flag flag);
    void                    resetFlag(my::Splitter::Flag flag);
    bool                    getFlag(my::Splitter::Flag flag) const;

    void                    splitIt();
    const std::string&      getItem(unsigned int itemNumber) const;
    unsigned int            getNumOfItems() const;

    void                    addDelim(std::vector<char> arrayOfDelims, DelimList list);
    void                    getDelimList(DelimList list) const;


    static void                    ltrim(std::string& string, std::vector<unsigned char>& trimList);
    static void                    rtrim(std::string& string, std::vector<unsigned char>& trimList);
    static void                    trim(std::string& string, std::vector<unsigned char>& trimList);


    //my::Splitter&   operator=(const std::string& target);

};




} // my

#endif // CLS_SPLITTER_H
