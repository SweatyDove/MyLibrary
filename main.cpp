#include <iostream>
#include "my_array.hpp"
#include "my_string.h"
#include <string>
#include <array>


using StringClass = my::String;

template <typename SomeType, int size>
using ArrayClass = my::Array<SomeType, size>;

/*
 * QUESTIONS:
 *
 * 1) Order of evaluation of 3-d part (incrementing) of the for-loop-statement? (Could begin from
 *      here: https://en.cppreference.com/w/cpp/language/eval_order
 */


class Base {
public:
    int* mb_data;
    enum class Name {
        HEALTH,
        STAMINA,
        MANA,

        TOTAL
    };


    inline static const ArrayClass<StringClass,  static_cast<unsigned int>(Name::TOTAL)> mb_strArray = {
        "Hello",
        "Beautifull",
        "World!"
    };

    Base()
    {
        std::cout << "[DEBUG]: Base's default ctor has been called" << std::endl;
    }

    Base(int a) :
        mb_data {new int {a} }
    {
        std::cout << "[DEBUG]: Base ctor has been called: allocate memory for mb_data" << std::endl;
    }

    Base& operator=(const Base& base)
    {
        std::cout << "[DEBUG]: <Base>'s copy assignment operator has been called" << std::endl;
        this->mb_data = base.mb_data;
        return *this;
    }

    ~Base()
    {
        std::cout << "[DEBUG]: Base dtor has been called: delete mb_data allocation" << std::endl;
        delete mb_data;
//        mb_data = nullptr;
    }

    static const StringClass& getStringName(Base::Name name)
    {
        return mb_strArray[static_cast<unsigned int>(name)];
    }



};

std::ostream& operator<<(std::ostream& out, const Base& base)
{
    out << base.mb_data;
    return out;
}






int main()
{

    Base base {};

    std::cout << base.mb_strArray << std::endl;


    /*
     * По идее, выбор семантики (копирование или перемещение), зависит не от массива, а от типа
     * элементов, которые находятся внутри него. То есть когда arrB[0] = arrA[0] - это оператор
     * присваивания, относящийся НЕПОСРЕДСТВЕННО к элементам массива - и именно эти элементы
     * ответственны за выбор семантики. А пользователь массива? МОжет ли он указать, что элементы
     * нужно перемещать, а не копировать (и наоборот)?
     */


    return 0;
}









