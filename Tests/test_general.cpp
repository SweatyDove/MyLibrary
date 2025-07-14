/***************************************************************************************************
 * Prototype of the file that should contain tests for the all classes of MyLibrary
 **************************************************************************************************/


#include <iostream>


#include "my_string.h"
#include "my_array.h"
#include "my_dynamicarray.h"
#include "my_utilities.h"
#include "my_smartptr.h"

#include "vector"



class Base {
private:
    int mb_a {};
    int mb_b {};
public:
    Base(int x) :
        mb_a {x}, mb_b {x * 2}
    {

    }
//    Base() = default;

//    Base(int a = 2, int b = 3) : mb_a {a}, mb_b {b}
//    {
//        // Nothing to do
//    }

    Base& operator=(const Base& that)
    {
        this->mb_a = that.mb_a;
        this->mb_b = that.mb_b;

        return *this;
    }


    void print() const
    {
        std::cout << "mb_a = " << mb_a << '\n'
                  << "mb_b = " << mb_b << '\n'
                  << std::endl;
    }
};


int main()
{

    my::DynamicArray<int> a {1, 2, 3, 4, 5};
    std::cout << a << std::endl;

    a.resize(10);
    std::cout << a << std::endl;




//    my::DynamicArray intArr {10};

//    my::SmartPtr<int> p (new int(1));
////    my::SmartPtr<int> pp = new int(1);            // не сработает, т.к. нужно неявно сконструировать временный объект типа my::SmartPtr<int> справа, однако конструктор у меня explicit

//    std::cout << typeid(new double(1.1)).name() << std::endl;

//    my::String string {" d123 "};
//    int a {0};

//    try {
//        a = string.toInt();
//    }
//    catch (const char* exception){
//        std::cout << "EXCEPTION: " << exception << std::endl;
//    }

//    my::String string {"Hello, "};
//    my::Array<char, 6> a {'w', 'o', 'r', 'l', 'd', '!'};
//    std::cout << string << a << std::endl;

//    my::DynamicArray d {1, 2, 3};
//    d.pushBack(my::getRandomNumber(1, 100));
//    d.pushBack(my::getRandomNumber(1, 100));
//    std::cout << d << std::endl;

    return 0;
}


