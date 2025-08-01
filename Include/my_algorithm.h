#ifndef MY_ALGORITHM_H
#define MY_ALGORITHM_H

//#include <vector>
#include <iostream>
#include <sys/resource.h>
#include <functional>               // Fot std::function

#include "my_utilities.h"
#include "my_iterator.h"
#include "my_dynamicarray.h"


namespace my {


//==================================================================================================
//          TYPE:   Class
//   DESCRIPTION:   Custom realization of different sorting algorithms
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
class Sort {
public:

//    const my::DynamicArray<int>& mb_randomArray;
//    const my::DynamicArray<int>& mb_sortedArray;
//    const my::DynamicArray<int>& mb_reversedArray;

    my::Timer   mb_stopwatch;
    double      mb_timeInterval {};

    Sort();

    void test(const my::DynamicArray<int>& randomArray,
              const my::DynamicArray<int>& sortedArray,
              const my::DynamicArray<int>& almostSortedArray,
              const my::DynamicArray<int>& reversedArray,
              double (my::Sort::*fn)(my::DynamicArray<int>& nums),
              const char* algoName);

    // # Сортировки обменом
//    double stupid(my::Iterator begin, my::Iterator begin end,  ;
//    double stupid(my::DynamicArray<int>& nums);
//    double bubble(my::DynamicArray<int>& nums);
//    double cocktail(my::DynamicArray<int>& nums);
//    double oddEven(my::DynamicArray<int>& nums);
//    double oddEvenVer1(my::DynamicArray<int>& nums);
//    double oddEvenVer2(my::DynamicArray<int>& nums);
//    double comb(my::DynamicArray<int>& nums);
//    void quick(my::DynamicArray<int>& a, int start, int end);
//    void quickClassic(my::DynamicArray<int>& a, int start, int end);

//    // # Сортировки выбором
//    double selection(my::DynamicArray<int>& a);
//    double heap(my::DynamicArray<int>& a);

//    // # Сортировки вставками
//    double insertion(my::DynamicArray<int>& a);
//    double shell(my::DynamicArray<int>& a);
//    double shellClassic(my::DynamicArray<int>& a);

//    // # Сортировки слиянием
//    double mergeUpDown(my::DynamicArray<int>& a);






};



} // End of 'my' namespace

#endif // MY_ALGORITHM_H
