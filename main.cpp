#include <iostream>
#include <utility>                  // For std::move

#include "my_smartptr.hpp"
#include "my_dynamicarray.hpp"
#include <sys/resource.h>
#include <functional>               // For: std::function()



class Test {
public:
    int mb_a {};
    Test(int a):
        mb_a {a}
    {
        // Nothing to do
    }

    // Copy constructor and assignment
    Test(const Test& test) = delete;
//    Test(const Test& test)
//    {
//        mb_a = test.mb_a;
//    }


    Test& operator=(const Test& test) = delete;
//    Test& operator=(const Test& test)
//    {
//        if (this == &test) {
//            return *this;
//        }
//        else {} // Nothing to do

//        mb_a = test.mb_a;
//        return *this;
//    }

    // Move c-tor
    Test(Test&& test)
    {
        mb_a = test.mb_a;
        test.mb_a = -1;
    }

    // Move assignment
    Test& operator=(Test&& test)
    {
        if (this == &test) {
            return *this;
        }
        else {} // Nothing to do

        mb_a = test.mb_a;
        test.mb_a = -1;

        return *this;
    }
};

void foo(const std::function<int(int, int)>& fn) {
    std::cout << fn(5, 6) << std::endl;

}



int main()
{
    // A regular function pointer. Only works with an empty capture clause (empty []).
    double (*addNumbers1)(double, double){
        [](double a, double b) {
            return a + b;
        }
    };

    std::cout << addNumbers1(1, 2) << std::endl;

    // Using std::function. The lambda could have a non-empty capture clause (discussed next lesson).
    std::function addNumbers2{ // note: pre-C++17, use std::function<double(double, double)> instead
        [](double a, double b) {
            return a + b;
        }
    };

    std::cout << addNumbers2(3, 4) << std::endl;

    // Using auto. Stores the lambda with its real type.
    auto addNumbers3{
        [](double a, double b) {
            return a + b;
        }
    };

    foo(addNumbers1);

    std::cout << addNumbers3(5, 6) << std::endl;

    return 0;
}









