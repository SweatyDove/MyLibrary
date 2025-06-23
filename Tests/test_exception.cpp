#include <iostream>
#include "my_exception.h"
#include "my_dynamicarray.h"
#include "my_string.h"




int main()
{

    bool mainLoop {true};

    while (mainLoop) {

        int a {0};

        std::cout << "Enter a integer:" << std::endl;
        my::String testString {};
        std::cin >> testString;

        try {
            a = testString.toInt();
        }
        catch (const my::StringException& exception) {
            std::cerr << "Incorrect input!" << std::endl;
            continue;
        }

        std::cout << "Your integer: " << a << std::endl;
        mainLoop = false;
    }


    return 0;
}
