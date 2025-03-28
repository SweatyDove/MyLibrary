#include <iostream>
#include <utility>                  // For std::move

#include "my_smartptr.hpp"
#include "my_dynamicarray.hpp"



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





int main()
{
    my::DynamicArray<Test> dynArr;
    Test testA {5};
    Test& testARef {testA};

    Test testB {6};
    Test& testBRef {testB};
    Test&& testBRRef {std::move(testBRef)};

//    testARef = testBRRef;
//    Test&& rValRef {std::move(testARef)};



    dynArr.pushBack(std::move(testARef));
    dynArr.pushBack(std::move(testBRef));





    int* resPtr {new int {753}};
    my::SmartPtr smartPtr {resPtr};

    std::cout << *smartPtr << std::endl;

    return 0;
}









