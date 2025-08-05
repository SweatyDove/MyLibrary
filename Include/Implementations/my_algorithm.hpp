#ifndef MY_ALGORITHM_HPP
#define MY_ALGORITHM_HPP

#include "../my_algorithm.h"            // For IDE visibility




//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   Realization of "stupid sort" algorithm
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Replacing @temp variable with XOR is NOT faster!
//                  2) Usage of pointers versus indexes is NOT faster!
//                  3) Taking expression "size - 1" outside the for-loop is NOT faster!
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::stupid(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
//    using pType = IteratorType::pointer;          // Can use it instead of 'typename IteratorType::pointer' below...

    typename IteratorType::pointer begin     {beginIt.operator ->()};
    typename IteratorType::pointer end       {endIt.operator ->()};
    typename IteratorType::pointer arg       {begin};

    int size = end - begin;
    for (int ii {0}; ii < size - 1; ++ii) {
        if (compare(arg[ii + 1], arg[ii])) {
            my::swap<int>(arg[ii + 1], arg[ii]);
            ii = -1;
        }
        else {}
    }
}






//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::bubble(IteratorType beginIt, IteratorType endIt, CompareType compare)
{

    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};

    int size = end - begin;
    for (int kk {size - 1}; kk > 0; --kk) {
        for (int ii {0}; ii < kk; ++ii) {
            if (compare(arg[ii + 1], arg[ii])) {
                my::swap(arg[ii + 1], arg[ii]);
            }
            else {} // Nothing to do
        }
    }

}



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::cocktail(IteratorType beginIt, IteratorType endIt, CompareType compare)
{

    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    bool    isSorted    {false};

    int size = end - begin;
    for (int start {0}, end {size - 1}; isSorted == false; ++start, --end) {

        // # Think, that array is sorted
        isSorted = true;

        // # Forward
        for (int ii {start}; ii < end; ++ii) {
            if (compare(arg[ii + 1], arg[ii])) {
                my::swap(arg[ii + 1], arg[ii]);
                isSorted = false;                   // Oh, we were wrong...
            }
            else {} // Nothing to do
        }

        // # If nothing was change in forward pass, then array is sorted!
        if (isSorted == true) {
            break;
        }
        else {
            isSorted = true;            // Again think that array is sorted
        }

        // # Backward
        for (int ii {end - 1}; ii > start; --ii) {
            if (compare(arg[ii], arg[ii - 1])) {
                my::swap(arg[ii], arg[ii - 1]);
                isSorted = false;
            }
            else {} // Nothing to do
        }
    }

}



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   There is a version from wiki, that works a little bit faster:
//
//                  for (int ii {0}; ii < size - 1; ++ii) {
//                      for (int jj {(ii % 2) ? 1 : 0}; jj < size - 1; jj += 2) {
//                          if (nums[jj] > nums[jj + 1]) {
//                              this->swap(nums[jj], nums[jj + 1]);
//                          }
//                      }
//                  }
//
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::oddEven(IteratorType beginIt, IteratorType endIt, CompareType compare)
{

    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int     clearPass   {0};              // Num of passes through @nums without changes
    bool    isSwapped   {false};

    int size = end - begin;
    for (int startIndex {0}; clearPass < 2; startIndex = (startIndex % 2) ? 0 : 1) {
        isSwapped = false;
        for (int ii {startIndex}; ii < size - 1; ii += 2) {
            if (compare(arg[ii + 1], arg[ii])) {
                my::swap(arg[ii], arg[ii+1]);
                isSwapped = true;
            }
            else {}
        }

        clearPass = (isSwapped == true) ? 0 : clearPass + 1;
    }

}



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   Two loop version of oddEven sort algorithm.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   About 4-5% faster than base version (but need to compile with -O3 option)
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::oddEvenV2(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int     size        {end - begin};
    int     clearPass   {0};              // Num of passes through 'input range' without changes
    int     halfSize    {size / 2};
    int     halfEdge    {(halfSize % 2 == 0) ? halfSize : halfSize + 1};

    for (int kk {1}; clearPass < 2; kk = (kk % 2) ? 0 : 1) {

        int     edge            {halfEdge + kk};
        bool    firstLoopSwap   {false};
        bool    secondLoopSwap  {false};

        // # First loop handles left (first) part of the source vector
        for (int jj {kk}; jj < edge; jj += 2) {
            if (compare(arg[jj + 1], arg[jj])) {
                my::swap(arg[jj + 1], arg[jj]);
                firstLoopSwap = true;
            }
            else {}
        }

        // # Second loop handles right (second) part of the source vector
        for (int ii {edge}; ii < size - 1; ii += 2) {
            if (compare(arg[ii + 1], arg[ii])) {
                my::swap(arg[ii + 1], arg[ii]);
                secondLoopSwap = true;
            }
            else {}
        }

        clearPass = (firstLoopSwap || secondLoopSwap) ? 0 : clearPass + 1;
    }

}




//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   Two if-else version of oddEven sort algorithm.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   About 8-10% faster than base version, but with MUCH MORE difficult logic... And
//                  I'm not sure, that it is all correct.
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::oddEvenV3(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int     size        {end - begin};
    int     clearPass   {0};              // Num of passes through 'input range' without changes
    int     halfSize    {size / 2};

    bool    sizeIsEven      {(size % 2) ? false : true};
    bool    halfSizeIsEven  {(halfSize % 2) ? false : true};

    int     oddEdge {};
    int     evenEdge {};


    // # Set the half edge in such way that the first part of the array has the SAME or FEWER elements,
    // # than the second part. And then compare last part after the inner cycle.
    if (sizeIsEven == true && halfSizeIsEven == true) {
        oddEdge = halfSize - 1;
        evenEdge = halfSize;
    }
    else if (sizeIsEven == false && halfSizeIsEven == true) {
        oddEdge = halfSize + 1;
        evenEdge = halfSize;
    }
    else {
        oddEdge = halfSize;
        evenEdge = halfSize - 1;
    }


    // # Main loop that switches the type of pass (odd or even) and check if the last two passes were
    // # without swapping.
    for (int kk {1}; clearPass < 2; kk = (kk % 2) ? 0 : 1) {

        int     edge            {(kk == 1) ? oddEdge : evenEdge};
        bool    firstPartSwap   {false};
        bool    secondPartSwap  {false};
        int     jj              {0};

        for (int ii {kk}; ii < edge; ii += 2) {

            // ## Handle the left part of the array
            if (compare(arg[ii + 1], arg[ii])) {
                my::swap(arg[ii + 1], arg[ii]);
                firstPartSwap = true;
            }
            else {}

            // ## Handle the right part
            jj = ii + edge - kk;
            if (compare(arg[jj + 1], arg[jj])) {
                my::swap(arg[jj + 1], arg[jj]);
                secondPartSwap = true;
            }
            else {}
        }

        // ## Тут я должен учесть, было ли сравнение последней пары и, если не было - выполнить её.
        // ## Расположение индекса левого эл-та последней пары зависит от чётности размера массива
        // ## и типа прохода (чётный/нечётный).
        jj += 2;
        int lastEdge {sizeIsEven ? size - 1 - kk : size - 2 + kk};
        if (sizeIsEven && jj < lastEdge && compare(arg[jj + 1], arg[jj])) {
            my::swap(arg[jj], arg[jj + 1]);
            secondPartSwap = true;
        }
        else {}


        clearPass = (firstPartSwap || secondPartSwap) ? 0 : clearPass + 1;
    }


}



////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   ........
////==================================================================================================
//double my::Sort::comb(my::DynamicArray<int>& nums)
//{
//    int     size        {static_cast<int>(nums.size())};
//    double  factor      {1.247};                                    // Constant (why "1.247" look wiki)
//    int     gap         {static_cast<int>(size / factor)};
//    bool    isSwapped   {true};

//    mb_stopwatch.reset();

//    while (gap > 1 || isSwapped == true) {

//        isSwapped = false;
//        for (int ii {0}; ii < size - gap; ++ii) {
//            if (nums[ii] > nums[ii + gap]) {
//                this->swap(nums[ii], nums[ii + gap]);
//                isSwapped = true;
//            }
//            else {} // Nothing to do
//        }
//        gap /= factor;
//        gap = (gap > 1) ? gap : 1;
//    }

//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;

//}


////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   1) Падает в случае массива, отсортированного в обратном порядке, размера 100'000
////                  элементов (слишком много рекурсивных вызовов, переполняется стек?)
////                  2) Не работает с pivot = a[(start + end) / 2] из-за неверного выставления
////                  параметра 'edge' для такого случая.
////                  3) Работает быстрее 'классического' исполнения (quickClassic())
////==================================================================================================
//void my::Sort::quick(my::DynamicArray<int>& a, int start, int end)
//{
//    // Exit if subarray has 1 element or 0
//    if (start >= end) {
//        return;
//    }
//    else {} // Nothing to do

////    int     pivot       {a[(start + end) / 2]};
//    int     pivot       {a[start]};
//    int     ii          {start};
//    int     jj          {end};
//    bool    isSwapped   {false};                 // Used, when all elements in subarray are higher than @pivot
//                                            // and there aren't any swaps.

//    while (true) {

//        // ## Find element, that is equal or higher, than @pivot
//        while (ii < jj && a[ii] < pivot) {
//            ++ii;
//        }

//        // ## Find element, that is less than @pivot
//        while (ii < jj && a[jj] >= pivot) {
//            --jj;
//        }

//        // ## Swap elements
//        if (ii < jj) {
//            this->swap(a[ii], a[jj]);
//            ++ii;
//            --jj;
//            isSwapped = true;
//        }
//        else {
//            break;
//        }
//    }

//    // # Choose which subarray a[ii] should be part of:
//    // #    If a[ii] less, than pivot (obviosly)
//    // #    If there are NOT any swap in array (for example [2, 3, 2]) and we need to 'take' one
//    // #    element to left part.
//    int edge = (a[ii] < pivot || isSwapped == false) ? ii : ii - 1;
//    this->quick(a, start, edge);
//    this->quick(a, edge + 1, end);

//    return;

//}





////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   'Classic' realization
////==================================================================================================
//void my::Sort::quickClassic(my::DynamicArray<int>& a, int start, int end)
//{
//    if (start > end) {
//        return;
//    }
//    else {}

//    int pivot = a[(start + end) / 2];
//    int ii = start;
//    int jj = end;

//    while (ii <= jj) {
//        while (a[ii] < pivot) {
//            ++ii;
//        }

//        while (a[jj] > pivot) {
//            --jj;
//        }

//        if (ii <= jj) {
//            this->swap(a[ii], a[jj]);
//            ++ii;
//            --jj;
//        }
//        else {}
//    }

//    this->quickClassic(a, start, jj);
//    this->quickClassic(a, ii, end);

//    return;

//}



////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   ........
////==================================================================================================
//double my::Sort::selection(my::DynamicArray<int>& a)
//{
//    int size {a.size()};

//    mb_stopwatch.reset();

//    for (int jj {size - 1}; jj > 0; --jj) {

//        int ii {1};
//        int kk {0};

//        while (ii <= jj) {
//            kk = (a[ii] > a[kk]) ? ii : kk;
//            ++ii;
//        }

//        this->swap(a[kk], a[jj]);
//    }



//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;

//}


////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   ........
////==================================================================================================
////void my::Sort::heap(my::DynamicArray<int>& a)
////{
////    int n {a.size() - 1};           // Last element index


////    // # Лямбда-функция просейки
////    std::function<void(int)> sift {
////              [&](int parentIndex)
////        {
////            int leftChildIndex {2 * parentIndex + 1};
////            int rightChildIndex {leftChildIndex + 1};
////            int maxChildIndex {-1};


////            // ## Определяем индекс большего из потомков
////            if ((leftChildIndex > n) && (rightChildIndex <= n)) {
////                maxChildIndex = rightChildIndex;
////            }
////            else if ((leftChildIndex <= n) && (rightChildIndex > n)) {
////                maxChildIndex = leftChildIndex;
////            }
////            else if ((leftChildIndex <= n) && (rightChildIndex <= n)){
////                maxChildIndex = ((a[leftChildIndex] > a[rightChildIndex]) ? leftChildIndex : rightChildIndex);
////            }
////            // ## Нет детей - выходим
////            else {
////                return;
////            }


////            // ## Свапаем элементы и осуществляем просейку для @maxChildIndex (куда переместили родительский элемент)
////            if (a[parentIndex] < a[maxChildIndex]) {
////                this->swap(a[parentIndex], a[maxChildIndex]);
////                parentIndex = maxChildIndex;
////                sift(parentIndex);
////            }
////            else {}

////            return;
////        }
////    };


////    // # Делаем сортирующее древо (через просейку каждого его эл-та, начиная с последнего).
////    for (int ii {n}; ii >= 0; --ii) {
////        sift(ii);
////    }

////    // # Корень дерева свапнуть с последним эл-м, уменьшить размер неотсортированной части и
////    // # провести просейку для элемента в корне.
////    for (int ii {n}; ii > 0; --ii) {
////        this->swap(a[0], a[ii]);
////        --n;
////        sift(0);
////    }

////}




////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   ........
////==================================================================================================
//double my::Sort::heap(my::DynamicArray<int>& a)
//{
//    int lastUnsortedIndex {a.size() - 1};           // Last element index

//    // # Лямбда-функция просейки
//    std::function<void(int)> sift {
//        [&](int root)
//        {
//            // ## Спускаемся по дереву
//            while (true) {

//                // ## Предполагаем только 1-го потомка (и считаем его наибольшим пока что)
//                int child {root * 2 + 1};

//                // ## Левого потомка не существует (следовательно и правого тоже, а потому выходим)
//                if (child > lastUnsortedIndex) {
//                    break;
//                }
//                // ## Существуют оба потомка и правый больше левого
//                else if (child + 1 <= lastUnsortedIndex && a[child] < a[child + 1]) {
//                    child += 1;
//                }
//                else {}

//                // ## Свапаем родителя и потомка и устанавливаем новый индекс родителя
//                if (a[root] < a[child]) {
//                    this->swap(a[root], a[child]);
//                    root = child;
//                }
//                else {
//                    break;
//                }

//            } // while

//            return;
//        }
//    };

//    mb_stopwatch.reset();

//    // # Делаем сортирующее древо (через просейку каждого его эл-та, начиная с последнего).
//    for (int ii {lastUnsortedIndex}; ii >= 0; --ii) {
//        sift(ii);
//    }

//    // # Корень дерева свапнуть с последним эл-м, уменьшить размер неотсортированной части и
//    // # провести просейку для элемента в корне.
//    for (int ii {lastUnsortedIndex}; ii > 0; --ii) {
//        this->swap(a[0], a[ii]);
//        --lastUnsortedIndex;
//        sift(0);
//    }

//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;

//}


////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   Не ОБМЕНЫ, а СДВИГ!
////==================================================================================================
//double my::Sort::insertion(my::DynamicArray<int>& a)
//{
//    int n {a.size()};

//    mb_stopwatch.reset();

//    for (int ii {0}; ii < n; ++ii) {

//        int temp {a[ii]};
//        int kk {ii};
//        while (kk > 0 && temp < a[kk - 1]) {
//            a[kk] = a[kk - 1];                      // Здесь СДВИГ! Не нужно использовать swap()
//            --kk;
//        } // O(n)

//        a[kk] = temp;       // O(3) -> O(1)

//    } // O(n)

//    // # Сложность: O(n) * [O(1) + O(n)] -> O(n) * O(n) = O(n^2)

//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;
//}



////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   1) Замена вызова функции swap() (что изначально было 'некорректно') на сдвиг решило
////                  проблему со скоростью работы.
////                  2) Можно улучшить работу, если не прыгать между подмассивами, а идти линейно
////                  по каждому элементу, начиная с gap и дальше запускать цикл сравнения с элементами,
////                  отстающими от текущего на gap, 2gap и т.д. Так сделано в shellClassic().
////==================================================================================================
//double my::Sort::shell(my::DynamicArray<int>& a)
//{
//    int size    {   a.size()    };

//    mb_stopwatch.reset();


//    // # Тут определяем дистанцию между соседними элементами 'подмассива'
//    for (int gap {size / 2}; gap >= 1; gap /= 2) {

//        // ## Тут уже проходимся по полученным 'подмассивам'
//        for (int ii {0}; ii < gap; ++ii) {

//            // #### Тут уже сортируем непосредственно "подмассив" методом сортировки вставками
//            for (int jj {ii}; jj < size; jj += gap) {

//                int temp = a[jj];
//                int kk = jj;

//                while (kk - gap >= 0 && temp < a[kk - gap]) {
//                    a[kk] = a[kk - gap];
//                    kk -= gap;
//                } // O(n/gap) -> O(n)

//                a[kk] = temp;


//            } // O(n/gap + 1), где единица за счёт холостого 0-го эл-та

//        } // O(gap) -> O(n/2) в худшем случае (1-ая итерация), т.е. этот член убывает для каждого следующего gap, т.е. как бы можно gap сократить будет при расчёте общего O-большого

//    } // O(log n), т.к. в 2 раза уменьшаем каждый раз



//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;
//}



////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   From https://www.programiz.com/dsa/shell-sort
////                  Принцип работы для данной реализации смотри выше в описании my::Sort::shell()
////==================================================================================================
//double my::Sort::shellClassic(my::DynamicArray<int>& array) {

//    int n = array.size();

//    mb_stopwatch.reset();


//    // Rearrange elements at each n/2, n/4, n/8, ... gaps
//    for (int gap = n / 2; gap > 0; gap /= 2) {
//        for (int ii = gap; ii < n; ii += 1) {
//            int temp = array[ii];
//            int jj = ii;
//            while (jj >= gap && array[jj - gap] > temp) {
//                array[jj] = array[jj - gap];
//                jj -= gap;
//            }
//            array[jj] = temp;
//        }
//    }


//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;
//}





















#endif // MY_ALGORITHM_HPP
