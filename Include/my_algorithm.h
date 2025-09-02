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
//          TYPE:   Namespace
//   DESCRIPTION:   Presents different sorting algorithms
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Add requirements for <CompareType> and <IteratorType> (different sort functions
//                      may need different iterator's functionality)
//==================================================================================================
namespace sort {

template <typename IteratorType, typename CompareType>
void stupid(IteratorType beginIt, IteratorType endIt, CompareType comp);

template <typename IteratorType, typename CompareType>
void bubble(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void cocktail(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void oddEven(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void oddEvenV2(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void oddEvenV3(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void comb(IteratorType beginIt, IteratorType endIt, CompareType compare);

//template <typename IteratorType, typename CompareType>
//void quick(IteratorType beginIt, IteratorType endIt, CompareType compare);

//template <typename IteratorType, typename CompareType>
//void quickClassic(IteratorType beginIt, IteratorType endIt, CompareType compare)


template <typename IteratorType, typename CompareType>
void selection(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void heap(IteratorType beginIt, IteratorType endIt, CompareType compare);


template <typename IteratorType, typename CompareType>
void insertion(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void shell(IteratorType beginIt, IteratorType endIt, CompareType compare);

template <typename IteratorType, typename CompareType>
void shellClassic(IteratorType beginIt, IteratorType endIt, CompareType compare);



} // End of 'sort' namespace




} // End of 'my' namespace


#include "Implementations/my_algorithm.hpp"

#endif // MY_ALGORITHM_H
