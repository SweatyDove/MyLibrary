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

    my::DynamicArray<my::SmartPtr<int>> array {};
    my::SmartPtr<int> intPtr {new int {374}};
    array.pushBack(std::move(intPtr));




    return 0;
}









