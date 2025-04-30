#ifndef SORT_H
#define SORT_H

#include <vector>
#include <iostream>
#include <sys/resource.h>
#include "my_utilities.h"
#include <functional>               // Fot std::function



namespace my {


class Sort {
public:

//    const std::vector<int>& mb_randomArray;
//    const std::vector<int>& mb_sortedArray;
//    const std::vector<int>& mb_reversedArray;

    my::Timer   mb_stopwatch;
    double      mb_timeInterval {};

    Sort();


    inline void swap(int& a, int& b);

    void test(const std::vector<int>& randomArray,
              const std::vector<int>& sortedArray,
              const std::vector<int>& reversedArray,
              double (*fn)(std::vector<int>& nums),
              const char* algoName);

    // # Сортировки обменом
    double stupid(std::vector<int>& nums);
    double bubble(std::vector<int>& nums);
    double cocktail(std::vector<int>& nums);
    double oddEven(std::vector<int>& nums);
    double oddEvenVer1(std::vector<int>& nums);
    double oddEvenVer2(std::vector<int>& nums);
    double comb(std::vector<int>& nums);
    void quick(std::vector<int>& a, int start, int end);
    void quickClassic(std::vector<int>& a, int start, int end);

    // # Сортировки выбором
    double selection(std::vector<int>& a);
    double heap(std::vector<int>& a);

    // # Сортировки вставками
    double insertion(std::vector<int>& a);
    double shell(std::vector<int>& a);
    double shellClassic(std::vector<int>& a);






};



} // End of 'my' namespace

#endif // SORT_H
