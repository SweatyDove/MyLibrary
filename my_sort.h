#ifndef SORT_H
#define SORT_H

#include <vector>
#include <iostream>
#include "my_utilities.h"


namespace my {


class Sort {
public:

    my::Timer mb_stopwatch;
    double mb_timeInterval {};

    Sort();

    inline void swap(int& a, int& b);

    // # Сортировки обменом
    double stupid(std::vector<int>& nums);
    double bubble(std::vector<int>& nums);
    double cocktail(std::vector<int>& nums);
    double oddEven(std::vector<int>& nums);
    double oddEven_1(std::vector<int>& nums);
    double oddEven_2(std::vector<int>& nums);

    double comb(std::vector<int>& nums);


};



} // End of 'my' namespace

#endif // SORT_H
