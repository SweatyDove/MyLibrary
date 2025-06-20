#include <iostream>
#include "my_exception.h"

class BaseA {
private:
    int mb_a {};
public:
    BaseA() {}
};

class BaseB{
private:
    int mb_b {2};
public:
    BaseB() {}
};


class DerivedAB : public BaseA, public BaseB {
private:
    int mb_d {12};
public:
    DerivedAB() {}
};



int main()
{
    try {
        throw DerivedAB();
    }
//    catch (const BaseA& baseA) {
//        std::cout << "Caught BaseA" << std::endl;
//    }
    catch (const BaseB& baseB) {
        std::cout << "Caught BaseB" << std::endl;
    }
    catch (const DerivedAB& derivedAB) {
        std::cout << "Caught DerivedAB" << std::endl;
    }

    return 0;
}
