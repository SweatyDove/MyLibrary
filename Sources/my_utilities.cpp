/***************************************************************************************************
 * This file contains definitions for the NON-TEMPLATED part of 'my utilities'
 **************************************************************************************************/


#include "my_utilities.h"



//==============================================================================
// Function reads an input line (till '\n' inclusively) into the
// buffer [buffer].
//
// If there is not enough space for whole line in the buffer - just end it with
// the null-terminator. In the future it will allow us to concatenate line with
// the next one(s).
//
// Else we will end up with the line, that is terminated by symbols:
// '\n' and '\0'.
//
// Function returns 0 in case of success.
//==============================================================================
int my::readLineToBuffer(char* buffer, int sizeOfBuffer)
{
    char*   bufferPtr   {buffer};
    char    ch          {'\0'};

    bool    skipLeadingSpaces {true};

    while (((ch = static_cast<char>(std::cin.get())) != '\n') && (!std::cin.eof())) {

        // #1 Skip the leading whitespaces
        if (skipLeadingSpaces && (ch == ' ' || ch == '\t')) {
            continue;
        }
        else {} // Nothing to do
        skipLeadingSpaces = false;

        // #2 Have to reserve 2 positions in the buffer (for '\n' and '\0').
        if (--sizeOfBuffer - 1 <= 0) {
            std::cerr << "\n[WARNING]::[my::readLineToBuffer()]:"
                      << "\nFree space in the buffer is over. Perhaps, not all data from the input stream"
                      << "\nwere written..."
                      << std::endl;
            // # In the case of the buffer overflowing - return an extracted
            // # character back into the <std::istream> object.
            std::cin.unget();
            break;
        }
        else {
            *bufferPtr++ = ch;
        }
    }

    // #### If the new line is finished by the '\n' symbol - it's OK.
    if (ch == '\n') {
        *bufferPtr++ = '\n';
        *bufferPtr = '\0';
    }
    // #### Else if not enough space in the [buffer] - just add '\0'.
    else {
        *bufferPtr = '\0';
    }

    return 0;
}













//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Convert integer number @intNumber into the set of chars, that represent all
//                  number's digits. That set is placed into the @buffer of size @sizeOfBuffer.
//                  Also add '\0' at the end of buffer.
//   PARAMETERS:    ........
// RETURN VALUE:    Number of digits of the @intNumber or -1, if there isn't enough space in buffer
//                  (including null-terminator).
//     COMMENTS:    There is a question... Should I add '\0' at the end of buffer? Should I add 1
//                  to the return value (number of digits + '\0')?
//==================================================================================================
int my::intToChar(int intNumber, char* buffer, int sizeOfBuffer)
{
    int quotient    {intNumber};                    //
    int base        {10};
    char* bufferPtr {buffer};

    int ii {0};

    // # Have to reserve two positions in the @buffer (for the last "remainder" and '\0').
    while ((ii < sizeOfBuffer - 2) && (quotient >= base)) {
        bufferPtr[ii] = static_cast<char>((quotient % base) + '0');
        quotient /= base;
        ++ii;
    }

    // # It's OK if we exit for-loop by 2-nd condition and have 2 free space in buffer.
    if ((ii < sizeOfBuffer - 1) && quotient < base) {
        bufferPtr[ii] = static_cast<char>(quotient + '0');
        bufferPtr[ii + 1] = '\0';
        invertBuffer(buffer, 0, ii);
        return ii + 1;
    }
    else {
        std::cerr << "\n[ERROR]::[my::intToChar()]:"
                  << "\nBuffer can't fit all number's digits and null-terminator."
                  << std::endl;
        return -1;
    }
}


//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Invert elements of <char*> @buffer. Both edges are included. It is up to user to
//                  pass correct indexes.
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
void my::invertBuffer(char* buffer, int fromIndex, int toIndex)
{
    char temp {'\0'};
    for (int ii {fromIndex}, jj {toIndex}; ii < jj; ++ii, --jj) {
        temp = buffer[ii];
        buffer[ii] = buffer[jj];
        buffer[jj] = temp;
    }

}


//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    Copy string (substring) from the @from address into the string (substring) at
//                  the @to address.
//
//                  1) If nums <= 0, then copy all symbols untill the meeting '\0' in the @from string.
//                  2) If nums > 0, then copy @nums of symbols plus null-terminator '\0'.
//   PARAMETERS:    @from   - address of 'copy from' data;
//                  @to     - address of 'copy to' data;
//                  @num    - number of chars to copy;
// RETURN VALUE:    ........
//     COMMENTS:    If specified incorrect pointer to destination - this funnction can override
//                  "title" of the block of memory, that is needed for delete[] operator.
//                  In this case - delete[] will cause an error.
//==================================================================================================
int my::copyString(const char *from, char *to, const int num)
{

    int ii {0};


    // # Lambda definition, that equivalent to that: (num > 0 && ii < num) || (num <= 0 && from[ii] != '\0').
    // # Decided to use lambda for practice, but instead may use macro or just expression above.
    auto condition
    {
        [=, &ii]() {return ((num > 0) ? (ii < num) : (from[ii] != '\0'));}
    };

    // #### Copy @num number of symbols
    while(condition()) {
        to[ii] = from[ii];
        ++ii;
    }
    to[ii] = '\0';

    return 0;
}



//==================================================================================================
//         TYPE:    General function
//  DESCRIPTION:    ........
//   PARAMETERS:    ........
// RETURN VALUE:    ........
//     COMMENTS:    ........
//==================================================================================================
int my::getRandomNumber(int min, int max)
{
    static constexpr double fraction {1.0 / (RAND_MAX + 1.0)};

    return min + static_cast<int>((max - min + 1) * (std::rand() * fraction));
}


//int CompareStrings(char *first_str, char *second_str, int ignore_reg)
//{
//	char f, s;

//	do {
//		f = *first_str++;
//		s = *second_str++;
//		if (ignore_reg) {
//			f = mcr__ToLow(f);
//			s = mcr__ToLow(s);
//		}

//		if (f == '\0' && s == '\0')
//			return 1;
//	} while (f == s);

//	return 0;
//}

//#define BIT_MANT				24
//#define OFFSET_FLOAT			127
//#define BIT_ORDER				8
//#define	FLOAT_LENGTH			32
//#define SIZE					100

//int BigEndian(char line[], char bin[]);



////==================================================================================================
////         TYPE:    General function
////  DESCRIPTION:    Программа переводит число, записанное в двоичном виде, в число типа float
////   PARAMETERS:    ........
//// RETURN VALUE:    ........
////     COMMENTS:    К сожалению, даже здесь используются расчеты с использованием типа float.
////                  А я бы хотел полностью в двоичном виде представить число типа float с использованием только целочисленной арифметики.
////                  Возможно, для эти целей нужно изменить функцию power(), которая дает тип float в результат, если исходная степень отрицательна.
////
////
////                  11000000 10100100 00000000 00000000	=	5.125
////                  01000101 11000101 10100010 01000111	=	6324.2845
////
////==================================================================================================
//float my::binToFloat(char str)
//{
//    int i, j;
//    char c;
//    int sign = 1;
//    int normalize_e;
//    int E = 0;
//    float number;
//    char str[SIZE] = {'0'};
//    char binary_form[FLOAT_LENGTH] = {'0'};
//    float test_number = 6324.2845;
//    float *fp;

//    fp = &test_number;
//    // Запись строки
//    printf("\nEnter binary form of the float number>\t");
//    ReadString(str, SIZE);
//    BigEndian(str, binary_form);

//    /*printf("\nChoose the form of the entered number>\t");
//    printf("\n\tPress \"B\" - if Big-endian");
//    printf("\n\tPress \"L\" - if Little-endian\n");
//    c = getchar();
//    switch(c) {
//        case 'b':
//            BigEndian(str, binary_form);
//            break;
//        default:
//            break;
//    }*/



//    // Чтение знака
//    sign = ((binary_form[0] == '0') ? 1 : -1);

//    // Чение порядка
//    for (i = BIT_ORDER, j = 0; i > 0; --i, j++)
//        if (binary_form[i] == '1')
//            E = E + 1 * (int) power(2, j);
//    normalize_e = E - OFFSET_FLOAT;

//    // Расчет числа через мантиссу и порядок
//    number = 1 * power(2, normalize_e--);						// Учитываем неявный бит мантиссы
//    for (i = BIT_ORDER + 1; i < FLOAT_LENGTH; ++i, normalize_e--)
//        if (binary_form[i] == '1')
//            number = number + 1 * power(2, normalize_e);

//    printf("\n\nnumber = %f", number * sign);

//    printf("n\nEnter any key to continue. . .");
//    getchar();
//    return;
//}








//// BigEndian(): ф-ция приводит строку line к соответствующему виду. Если все нормально - возвращает 0. В противном случае -1.
//int BigEndian(char line[], char bin[])
//{
//    int i, j;

//    for (i = 0, j = 0; j < FLOAT_LENGTH; ++i) {
//        if (line[i] == '0' || line[i] == '1')
//            bin[j++] = line[i];
//        else if (line[i] == '\n' || line[i] == '\0')
//            while (j < FLOAT_LENGTH)
//                bin[j++] = '0';
//    }

//    return 0;
//}








////==================================================================================================
////         TYPE:    General function
////  DESCRIPTION:    Возводит @base в целую степень @exp (но exp > -128)
////   PARAMETERS:    ........
//// RETURN VALUE:    ........
////     COMMENTS:    ........
////==================================================================================================
//float my::power(int base, int exp)
//{
//    assert(exp > -128 && "Exponent should be higher than -128. Abort.");

//    float temp {1.0};

//    if (n >= 0) {
//        for (n; n > 0; --n)
//            temp *= base;
//    }
//    else {
//        for (n = -n; n > 0; --n)
//            temp *= base;
//        temp = 1 / temp;
//    }

//    return temp;
//}





/* Программа переводит вещественное число типа float в его научную нотацию (экспоненциальную запись),
 * то есть представляет его в виде набора битов.
 */

//#include <stdio.h>
//#define BIT_MANT				24
//#define OFFSET_FLOAT			127
//#define BIT_ORDER				8
//#define	FLOAT_LENGTH			32

//void reverse(char s[], int size);
//int BinToHex(char bin[], char hex[]);
//int power(int base, int n);





//int main(void)
//{
//    int i, j, m, n, k;
//    int high_bit = 0;
//    float *fp;
//    float number = -525.0625;
//    int e = -1;
//    int normalize_e = 0;
//    int shifted_order = OFFSET_FLOAT + normalize_e;
//    int sign = 1;

//    char mantissa[BIT_MANT] = {'0'};
//    char order[BIT_ORDER]	= {'0'};
//    char binary_float[FLOAT_LENGTH] = {'0'};
//    char hex_float[FLOAT_LENGTH / 4] = {'0'};

//    int	integer_part = 0;
//    float fractional_part = 0.0;
//    int d;

//    fp = &number;
//    //######## Записываем знак (тут я не уверен вот в чем. Для целых чисел НЕЛЬЗЯ делать так: если number = -128, то -number = 128 и оно не помещается в
//    //######## знаковый тип и расширяется до беззнакового. А во float это так не работает. Там берется модуль числа и добавляется знак, т.е. нет расширения
//    //######## до беззнакового.
//    sign = ((number >= 0) ? 1 : -1);

//    integer_part = (int) (number * sign);
//    fractional_part = (number * sign)  - (float) integer_part;

//    //######## Костыль на правильное значение порядка
//    e = ((integer_part == 0) ? 0 : -1);

//    //######## Представление целой части числа в двоичном виде
//    for (i = BIT_MANT - 1; (integer_part > 0) && (i >= 0); --i, integer_part /= 2) {
//        mantissa[i] = integer_part % 2 + '0';
//        high_bit = i;
//        ++e;
//    }
//    while (i >= 0)
//        mantissa[i--] = '0';


//    //#### Перемещаем двоичное представление целой части в начало мантиссы.
//    //#### Если же high_bit == 0, то либо целая часть равна нулю, либо целая часть заполнила всю мантиссу. Тогда перемещать ничего не нужно.
//    for (i = high_bit, j = 0; (i != 0) && (i < BIT_MANT); ++i, ++j) {
//        mantissa[j] = mantissa[i];
//        mantissa[i] = '0';
//    }

//    //######## Представление дробной части числа в двоичном виде
//    for (j; (fractional_part != 0.0) && (j < BIT_MANT); ++j) {
//        fractional_part *= 2.0;
//        d = (int) fractional_part;
//        mantissa[j] = d + '0';
//        fractional_part -= d;
//    }

//    //######## Находим нормализованный порядок
//    for (i = 0, normalize_e = e; i < BIT_MANT; ++i) {
//        if (mantissa[i] != '1')
//            normalize_e = e - 1;
//        else
//            break;
//    }
//    if (i == BIT_MANT)
//        printf("\ntype:\t\tWarning\nsource:\t\tFloatToBin()\nmessage:\t\t The initial number is too small and can't be represent by \"float\" type");

//    //######## Находим смещенный порядок и записываем его в двоичном представлении
//    shifted_order = OFFSET_FLOAT + normalize_e;
//    for (i = BIT_ORDER - 1; (shifted_order > 0) && (i >= 0); --i, shifted_order /= 2)
//        order[i] = shifted_order % 2 + '0';
//    while (i >= 0)
//        order[i--] = '0';

//    //######## Записываем исходное вещ. число в двоичной форме
//    binary_float[0] = ((sign == 1) ? '0': '1');
//    for (i = 1, j = 0, m = 0; i < FLOAT_LENGTH; ++i) {
//        binary_float[i] = ((m == 0) ? order[j] : mantissa[j]);
//        ++j;
//        // Переход от записи порядка к записе мантиссы (не забываем про то, что имеем спрятанную "1", то есть записываем мантиссу без единички)
//        if (m == 0 && j == BIT_ORDER) {
//            j = 1;							// Так как мантисса начинается с единицы, то эту единицу не записываем
//            m = 1;
//        }
//    }
//    //######## Записываем исходное число в шестнадцатиричной форме
//    BinToHex(binary_float, hex_float);

//    //######## Вывод в представлениях Little-Endian и Big-Endian
//    printf("\nBig-Endian:");
//    printf("\n\tbin:\t");
//    for (i = 0, n = 8; i < FLOAT_LENGTH; ++i) {
//        printf("%c", binary_float[i]);
//        --n;
//        if (n == 0) {
//            printf("  ");
//            n = 8;
//        }
//    }
//    printf("\n\thex:\t");
//    for (i = 0, n = 2; i < FLOAT_LENGTH / 4; ++i) {
//        printf("%c", hex_float[i]);
//        --n;
//        if (n == 0) {
//            printf("        ");
//            n = 2;
//        }
//    }
//    printf("\n\nLittle-Endian:");
//    printf("\n\tbin:\t");
//    for (n = 8, k = 1, i = FLOAT_LENGTH - n * k; i >= 0;) {
//        printf("%c", binary_float[i]);
//        ++i;
//        --n;
//        // Если вывели байт, переходим к выводу следующего
//        if (n == 0) {
//            printf("  ");
//            n = 8;
//            ++k;
//            i = FLOAT_LENGTH - n * k;
//        }
//    }
//    printf("\n\thex:\t");
//    for (n = 2, k = 1, i = (FLOAT_LENGTH / 4) - n * k; i >= 0;) {
//        printf("%c", hex_float[i]);
//        ++i;
//        --n;
//        // Если вывели байт, переходим к выводу следующего
//        if (n == 0) {
//            printf("        ");
//            n = 2;
//            ++k;
//            i = (FLOAT_LENGTH / 4) - n * k;
//        }
//    }

//    printf("\n\nEnter any key to continue. . .");
//    getchar();
//    return;
//}









//int BinToHex(char bin[], char hex[])
//{
//    int i = FLOAT_LENGTH - 1;
//    int j = 0;
//    int k = 0;
//    int width_of_hex_field = 4;
//    int hex_digit = 0;

//    while (i >= 0) {
//        hex_digit = hex_digit + (bin[i] - '0') * power(2, j++);
//        if (j == width_of_hex_field) {
//            hex[k++] = ((hex_digit > 9) ? hex_digit - 10 + 'A' : hex_digit + '0');
//            hex_digit = 0;
//            j = 0;
//        }
//        --i;
//    }
//    reverse(hex, FLOAT_LENGTH / 4);

//    return 0;
//}



//void reverse(char s[], int size)
//{
//    int i, j;
//    int temp;

//    for (i = 0, j = size - 1; i < j ; ++i, --j) {
//        temp = s[i];
//        s[i] = s[j];
//        s[j] = temp;
//    }
//    return;
//}

//// Функция power() возводит "base" в целую неотрицательную "n"-ую степень
//int power(int base, int n)
//{
//    int temp = 1;
//    for (n; n > 0; --n)
//        temp *= base;

//    return temp;
//}




//==================================================================================================
//          TYPE:   Timer class constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
my::Timer::Timer() :
    mb_begin {Clock::now()}
{
    // Nothing to do
}

//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::Timer::reset()
{
    mb_begin = std::chrono::steady_clock::now();
}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Подумать над тем, как сперва получить время, а потом уже его кастить.
//==================================================================================================
double my::Timer::elapsed() const
{
//    std::chrono::time_point elaps {Clock::now() - mb_begin};

    switch (mb_unit) {
    case MeasureUnit::SECOND:
        return std::chrono::duration_cast<Sec>(Clock::now() - mb_begin).count();
        break;
    case MeasureUnit::MILLI:
        return std::chrono::duration_cast<Milli>(Clock::now() - mb_begin).count();
        break;
    case MeasureUnit::MICRO:
        return std::chrono::duration_cast<Micro>(Clock::now() - mb_begin).count();
        break;
    case MeasureUnit::NANO:
        return std::chrono::duration_cast<Nano>(Clock::now() - mb_begin).count();
        break;
    default:
        assert(false && "Incorrect measure unit!");
        break;
    }

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
void my::Timer::setMeasureUnit(MeasureUnit mu)
{
    mb_unit = mu;
}
