#include <iostream>
#include "my_exception.h"
#include "my_dynamicarray.h"
#include "my_string.h"
#include "my_smartptr.h"




int main()
{



    bool mainLoop {true};

    // String exception test
    while (mainLoop) {

        int a {0};

        std::cout << "Enter a integer:" << std::endl;
        my::String testString {};
        std::cin >> testString;

        try {
            a = testString.toInt();
        }
        catch (const my::StringException& exception) {
            std::cerr << exception.what() << std::endl;
            continue;
        }

        std::cout << "Your integer: " << a << std::endl;
        mainLoop = false;
    }


    // Dynamic array exception test
    mainLoop = true;
    while (mainLoop) {

        my::DynamicArray<int> dynArr {};

        std::cout << "Enter a range of integers, separated with a space:" << std::endl;
        my::String testString {};
        std::cin >> testString;

        try {
            dynArr = my::DynamicArray<int> {testString.cStr()};
        }
        catch (const my::DynamicArrayException& exception) {
            std::cerr << exception.what() << std::endl;
            continue;
        }

        std::cout << "Yours range of integers: " << dynArr << std::endl;
        mainLoop = false;
    }



    return 0;
}
