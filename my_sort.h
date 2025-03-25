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

    double stupid(std::vector<int>& nums);
    double bubble(std::vector<int>& nums);
    double cocktail(std::vector<int>& nums);

};



} // End of 'my' namespace

#endif // SORT_H
