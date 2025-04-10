#include <iostream>
#include <utility>                  // For std::move

#include "my_smartptr.hpp"
#include "my_dynamicarray.hpp"
#include <sys/resource.h>



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
    my::DynamicArray<my::SmartPtr<int>> vec;

    my::SmartPtr<int> resA {new int {5}};

    vec.pushBack(std::move(resA));


    struct rlimit64 sl;
    int retVal = getrlimit64(RLIMIT_STACK, &sl);
    if (retVal != 0) {
        std::cout << "Error: " << std::strerror(errno) << std::endl;
    }
    else {
        std::cout << "Current: " << sl.rlim_cur << std::endl;
        std::cout << "Max: " << sl.rlim_max << std::endl;
    }

//    my::DynamicArray<int> a;

//    for (int ii {0}; ii < 7; ++ii) {
//        a[ii] = ii;
//    }

//    for (int ii {0}; ii < 7; ++ii) {
//        std::cout << a[ii] << std::endl;
//    }

    return 0;
}









