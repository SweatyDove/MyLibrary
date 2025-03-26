#include "main.h"
#include "my_smartptr.hpp"





int main()
{

    int* resPtr {new int {753}};
    my::SmartPtr smartPtr {resPtr};

    std::cout << *smartPtr << std::endl;

    return 0;
}









