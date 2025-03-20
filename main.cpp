

#include "main.h"
#include "attribute.h"



/*
 * COMMENTS:
 * 1) Add autotest somewhere (maybe try to use github functionality or smth else).
 *
 * QUESTIONS:
 *
 * 1) Order of evaluation of 3-rd part (incrementing) of the for-loop-statement? (Could begin from
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


//    inline static const ArrayClass<my::String,  static_cast<unsigned int>(Name::TOTAL)> mb_strArray = {
//        "Hello",
//        "Beautifull",
//        "World!"
//    };

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

//    static const my::String& getStringName(Base::Name name)
//    {
//        return mb_strArray[static_cast<unsigned int>(name)];
//    }



};

std::ostream& operator<<(std::ostream& out, const Base& base)
{
    out << base.mb_data;
    return out;
}






int main()
{
//    Base a {5};
//    Base b {7};
//    int ii {0};

    // Тут происходит две вещи. Как я понимаю, сперва создаётся пустой массив <my::Array>, каждый
    // элемент которого создаётся при помощи дефолтного конструктора (здесь Base()). Затем происходит
    // копирование a и b в элементы массива.
    // Единственное, что при вызове деструктора массива, почему-то вызывается деструктор только для
    // одного элемента <Base>...
    my::Array<my::String, 2> temp {
        "Hello",
        "World"
    };

    ArrayClass<StringClass, 3> foo {
        "Hello",
        "my",
        "world!"
    };


    /*
     * А почему он создается ещё на этапе компиляции?
     * Тут вроде бы всё нормально.
     * 1 -- Сперва конструируются временные объекты <Base>, содержащие 5 и 7
     * соответственно (сами "результаты" выражений (5) и (7) имеют тип int и являются rvalue).
     * 2 -- Затем сам массив bar конструирует два "свободных" места <Base> под вычисленные элементы -
     * используя для этого дефолтный конструктор <Base>.
     * 3 -- Ну и на третем шаге происходит копирование временных объектов в объекты из массивы.
     * 4 -- Потом временные обьекты уничтожаются.
     */
//    my::Array<Base, 2> bar {5, 7};





//    Attribute attr_1 = Attribute(Attr::Name::DODGE_CHANCE, Attribute::Type::RATING, -1, -1, -1);
//    Attribute attr_2 {Attr::Name::CRIT_CHANCE, Attribute::Type::RATING, -1, -1, -1};
//    Attribute attr_3 {Attribute(Attr::Name::ESCAPE_CHANCE, Attribute::Type::RATING, 66, 66, 66)};

//    ArrayClass<Attribute, 3> mb_ratings = {attr_1, attr_2, attr_3};
//    ArrayClass<Attribute, 3> mb_ratings = {
//        {
//            {Attr::Name::DODGE_CHANCE, Attribute::Type::RATING, -1, -1, -1},
//            {Attr::Name::CRIT_CHANCE, Attribute::Type::RATING, -1, -1, -1},
//            {Attr::Name::ESCAPE_CHANCE, Attribute::Type::RATING, 66, 66, 66}
//        }
//    };
//    std::array<Attribute, 1> mb_ratingsClassic {attr_1};

    /*
     * По идее, выбор семантики (копирование или перемещение), зависит не от массива, а от типа
     * элементов, которые находятся внутри него. То есть когда arrB[0] = arrA[0] - это оператор
     * присваивания, относящийся НЕПОСРЕДСТВЕННО к элементам массива - и именно эти элементы
     * ответственны за выбор семантики. А пользователь массива? МОжет ли он указать, что элементы
     * нужно перемещать, а не копировать (и наоборот)?
     */


    return 0;
}









