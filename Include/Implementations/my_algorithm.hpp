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



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::comb(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int     size        {end - begin};
    double  factor      {1.247};                                    // Constant (why "1.247" look wiki)
    int     gap         {static_cast<int>(size / factor)};
    bool    isSwapped   {true};

    while (gap > 1 || isSwapped == true) {

        isSwapped = false;
        for (int ii {0}; ii < size - gap; ++ii) {
            if (compare(arg[ii + gap], arg[ii])) {
                my::swap(arg[ii + gap], arg[ii]);
                isSwapped = true;
            }
            else {} // Nothing to do
        }
        gap /= factor;
        gap = (gap > 1) ? gap : 1;
    }

}


//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Падает в случае массива, отсортированного в обратном порядке, размера 100'000
//                  элементов (слишком много рекурсивных вызовов, переполняется стек?)
//                  2) Не работает с pivot = a[(start + end) / 2] из-за неверного выставления
//                  параметра 'edge' для такого случая.
//                  3) Работает быстрее 'классического' исполнения (quickClassic())
//==================================================================================================
//template <typename IteratorType, typename CompareType>
//void my::sort::quick(IteratorType beginIt, IteratorType endIt, CompareType compare)
//{
//    using pType = IteratorType::pointer;

//    pType begin     {beginIt.operator ->()};
//    pType end       {endIt.operator ->()};

//    // Exit if subarray has 1 element or 0
//    if (begin >= end) {
//        return;
//    }
//    else {} // Nothing to do


//    pType   arg         {begin};
//    int     size        {end - begin};
//    int     pivot       {arg[0]};               // Or pivot = a[(start + end) / 2];
//    int     ii          {0};
//    int     jj          {size - 1};
//    bool    isSwapped   {false};                 // Used, when all elements in subarray are higher than @pivot
//                                            // and there aren't any swaps.

//    while (true) {

//        // ## Find element, that is equal or higher, than @pivot
//        while (ii < jj && compare(arg[ii], pivot)) {
//            ++ii;
//        }

//        // ## Find element, that is less than @pivot
//        while (ii < jj && !compare(arg[jj],  pivot)) {
//            --jj;
//        }

//        // ## Swap elements
//        if (ii < jj) {
//            my::swap(arg[ii], arg[jj]);
//            ++ii;
//            --jj;
//            isSwapped = true;
//        }
//        else {
//            break;
//        }
//    }

//    // # Choose which subarray arg[ii] should be part of:
//    // #    If arg[ii] less, than pivot (obviosly)
//    // #    If there are NOT any swap in array (for example [2, 3, 2]) and we need to 'take' one
//    // #    element to left part.
//    int edge = (compare(arg[ii], pivot) || isSwapped == false) ? ii : ii - 1;

//    std::cout << "Sorting [" <<
//    my::sort::quick(IteratorType(begin), IteratorType(begin + edge), compare);
//    my::sort::quick(IteratorType(begin + edge + 1), IteratorType(end), compare);

//}





////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   ........
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   'Classic' realization
////==================================================================================================
//template <typename IteratorType, typename CompareType>
//void my::sort::quickClassic(IteratorType beginIt, IteratorType endIt, CompareType compare)
//
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



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::selection(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int size {end - begin};

    for (int jj {size - 1}; jj > 0; --jj) {

        int ii {1};
        int kk {0};

        while (ii <= jj) {
            kk = (compare(arg[kk], arg[ii])) ? ii : kk;
            ++ii;
        }

        my::swap(arg[kk], arg[jj]);
    }

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
//void my::Sort::heap(my::DynamicArray<int>& a)
//{
//    int n {a.size() - 1};           // Last element index


//    // # Лямбда-функция просейки
//    std::function<void(int)> sift {
//              [&](int parentIndex)
//        {
//            int leftChildIndex {2 * parentIndex + 1};
//            int rightChildIndex {leftChildIndex + 1};
//            int maxChildIndex {-1};


//            // ## Определяем индекс большего из потомков
//            if ((leftChildIndex > n) && (rightChildIndex <= n)) {
//                maxChildIndex = rightChildIndex;
//            }
//            else if ((leftChildIndex <= n) && (rightChildIndex > n)) {
//                maxChildIndex = leftChildIndex;
//            }
//            else if ((leftChildIndex <= n) && (rightChildIndex <= n)){
//                maxChildIndex = ((a[leftChildIndex] > a[rightChildIndex]) ? leftChildIndex : rightChildIndex);
//            }
//            // ## Нет детей - выходим
//            else {
//                return;
//            }


//            // ## Свапаем элементы и осуществляем просейку для @maxChildIndex (куда переместили родительский элемент)
//            if (a[parentIndex] < a[maxChildIndex]) {
//                this->swap(a[parentIndex], a[maxChildIndex]);
//                parentIndex = maxChildIndex;
//                sift(parentIndex);
//            }
//            else {}

//            return;
//        }
//    };


//    // # Делаем сортирующее древо (через просейку каждого его эл-та, начиная с последнего).
//    for (int ii {n}; ii >= 0; --ii) {
//        sift(ii);
//    }

//    // # Корень дерева свапнуть с последним эл-м, уменьшить размер неотсортированной части и
//    // # провести просейку для элемента в корне.
//    for (int ii {n}; ii > 0; --ii) {
//        this->swap(a[0], a[ii]);
//        --n;
//        sift(0);
//    }

//}




//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::heap(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;
    using Type  = IteratorType::value_type;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int size {end - begin};


    int lastUnsortedIndex {size - 1};           // Last element index

    // # Лямбда-функция просейки
    auto sift {
        [&](int root)
        {
            // ## Спускаемся по дереву
            while (true) {

                // ## Предполагаем только 1-го потомка (и считаем его наибольшим пока что)
                int child {root * 2 + 1};

                // ## Левого потомка не существует (следовательно и правого тоже, а потому выходим)
                if (child > lastUnsortedIndex) {
                    break;
                }
                // ## Существуют оба потомка и правый больше левого
                else if (child + 1 <= lastUnsortedIndex && compare(arg[child], arg[child + 1])) {
                    child += 1;
                }
                else {}

                // ## Свапаем родителя и потомка и устанавливаем новый индекс родителя
                if (compare(arg[root], arg[child])) {
                    my::swap(arg[root], arg[child]);
                    root = child;
                }
                else {
                    break;
                }

            } // while

            return;
        }
    };


    // # Делаем сортирующее древо (через просейку каждого его эл-та, начиная с последнего).
    for (int ii {lastUnsortedIndex}; ii >= 0; --ii) {
        sift(ii);
    }

    // # Корень дерева свапнуть с последним эл-м, уменьшить размер неотсортированной части и
    // # провести просейку для элемента в корне.
    for (int ii {lastUnsortedIndex}; ii > 0; --ii) {
        my::swap(arg[0], arg[ii]);
        --lastUnsortedIndex;
        sift(0);
    }

}


//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Не ОБМЕНЫ, а СДВИГ!
//                  Сложность: O(n) * [O(1) + O(n)] -> O(n) * O(n) = O(n^2)
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::insertion(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int size {end - begin};


    for (int ii {0}; ii < size; ++ii) {

        int temp {arg[ii]};
        int kk {ii};
        while (kk > 0 && compare(temp, arg[kk - 1])) {
            arg[kk] = arg[kk - 1];                      // Здесь СДВИГ! Не нужно использовать swap()
            --kk;
        } // O(n)

        arg[kk] = temp;       // O(3) -> O(1)

    } // O(n)

}



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Замена вызова функции swap() (что изначально было 'некорректно') на сдвиг решило
//                  проблему со скоростью работы.
//                  2) Можно улучшить работу, если не прыгать между подмассивами, а идти линейно
//                  по каждому элементу, начиная с gap и дальше запускать цикл сравнения с элементами,
//                  отстающими от текущего на gap, 2gap и т.д. Так сделано в shellClassic().
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::shell(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;
    using Type  = IteratorType::value_type;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int size {end - begin};

    // # Тут определяем дистанцию между соседними элементами 'подмассива'
    for (int gap {size / 2}; gap >= 1; gap /= 2) {

        // ## Тут уже проходимся по полученным 'подмассивам'
        for (int ii {0}; ii < gap; ++ii) {

            // #### Тут уже сортируем непосредственно "подмассив" методом сортировки вставками
            for (int jj {ii}; jj < size; jj += gap) {

                Type temp = arg[jj];
                int kk = jj;

                while (kk - gap >= 0 && compare(temp, arg[kk - gap])) {
                    arg[kk] = arg[kk - gap];
                    kk -= gap;
                } // O(n/gap) -> O(n)

                arg[kk] = temp;


            } // O(n/gap + 1), где единица за счёт холостого 0-го эл-та

        } // O(gap) -> O(n/2) в худшем случае (1-ая итерация), т.е. этот член убывает для каждого следующего gap, т.е. как бы можно gap сократить будет при расчёте общего O-большого

    } // O(log n), т.к. в 2 раза уменьшаем каждый раз

}



//==================================================================================================
//          TYPE:   Function template
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   From https://www.programiz.com/dsa/shell-sort
//                  Принцип работы для данной реализации смотри выше в описании my::Sort::shell()
//==================================================================================================
template <typename IteratorType, typename CompareType>
void my::sort::shellClassic(IteratorType beginIt, IteratorType endIt, CompareType compare)
{
    using pType = IteratorType::pointer;
    using Type  = IteratorType::value_type;

    pType begin     {beginIt.operator ->()};
    pType end       {endIt.operator ->()};
    pType arg       {begin};


    int size {end - begin};

    // Rearrange elements at each n/2, n/4, n/8, ... gaps
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int ii = gap; ii < size; ii += 1) {
            Type temp = arg[ii];
            int jj = ii;
            while (jj >= gap && compare(temp, arg[jj - gap])) {
                arg[jj] = arg[jj - gap];
                jj -= gap;
            }
            arg[jj] = temp;
        }
    }

}







//struct Pair {
//    int left;
//    int right;
//};

//// # Get sorted subarray. Here I want to MOVE content from @a to @aLeft and @aRight
//    my::DynamicArray<int> aLeft;
//    my::DynamicArray<int> aRight;



//Pair foo(my::DynamicArray<int>& a, Pair pair)
//{
//    // # If only 1 element in @a - then @a is sorted
//    if (pair.right - pair.left == 1) {
//        return pair;
//    }
//    else {}


//    // # Получаем пару идексов (начало и конец) отсортированной части
//    Pair lPair = foo(a, {pair.left, (pair.left + pair.right) / 2});
//    Pair rPair = foo(a, {(pair.left + pair.right) / 2,  pair.right});

//    // # Переносим отсортированные части из изначального массива во вспомогательные
//    for (int ii {lPair.left}; ii < lPair.right; ++ii) {
//        aLeft.push_back(std::move(a[ii]));
//    }
//    for (int ii {rPair.left}; ii < rPair.right; ++ii) {
//        aRight.push_back(std::move(a[ii]));
//    }



//    // # Form new array from 2 sorted subarrays (can use reference on proto-array as buffer)
//    int kk {pair.left};         // Proto array iterator
//    int ii {0};                 // Left subarray iterator
//    int jj {0};                 // Right subarray iterator

//    while ((ii < aLeft.size()) && (jj < aRight.size())) {
//        if (aLeft[ii] <= aRight[jj]) {
//            a[kk++] = std::move(aLeft[ii++]);
//        }
//        else {
//            a[kk++] = std::move(aRight[jj++]);
//        }
//    }

//    // # Only one of below loops will work
//    while (ii < aLeft.size()) {
//        a[kk++] = std::move(aLeft[ii++]);
//    }
//    while (jj < aRight.size()) {
//        a[kk++] = std::move(aRight[jj++]);
//    }

//    // # Тут приходится очищать временные массивы, т.к. ПЕРЕНОС != уменьшению размера, просто элемент
//    // # начинает находиться в неопределённом состоянии
//    aLeft.clear();
//    aRight.clear();

//    return pair;

//}

////==================================================================================================
////          TYPE:   Method
////   DESCRIPTION:   Сортировка слиянием "сверху-вниз"
////    PARAMETERS:   ........
////  RETURN VALUE:   ........
////      COMMENTS:   Алгоритм:
////                  0)  Выделяем память под два массива, длинной n/2
////                  1)  На каждом шаге делим исходный массив на две части до тех пор, пока длина
////                      полученной части не станет равна единице - то есть часть отсортирована. Всё
////                      это пока происходит в исходном массиве (путём индексации).
////                  2)  Возвращаем отсортированную часть и, используя move-семантику, помещаем эту
////                      часть в один из двух вспомогательных массивов (тем самым освобождается место
////                      в исходном массиве)
////                  3)  После того, как получили две отсортированые части (в двух вспомогательных
////                      массивах), сливаем эти части в исходный массив (в пределах соответствующих
////                      границ).
////                  4)  Повторяем этот шаг до тех пор, пока не поднимемся до шага, когда сливаем две
////                      отсортированные половинки.
////==================================================================================================
//double my::Sort::mergeUpDown(my::DynamicArray<int>& a)
//{
//    mb_stopwatch.reset();



////    int n {a.size()};
//    Pair pair {0, a.size()};

//    // # Create 2 additional arrays (memory == O(n))
////    my::DynamicArray<int> aLeft(n/2);
////    my::DynamicArray<int> aRight(n/2);


//    foo(a, pair);


//    // # Sort time
//    mb_timeInterval = mb_stopwatch.elapsed();
//    return mb_timeInterval;

//}









///=================================================================================================
/// Это реализация из интернета
///=================================================================================================
// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
//void merge(vector<int>& arr, int left,
//           int mid, int right)
//{
//    int n1 = mid - left + 1;
//    int n2 = right - mid;

//    // Create temp vectors
//    vector<int> L(n1), R(n2);

//    // Copy data to temp vectors L[] and R[]
//    for (int i = 0; i < n1; i++)
//        L[i] = arr[left + i];
//    for (int j = 0; j < n2; j++)
//        R[j] = arr[mid + 1 + j];

//    int i = 0, j = 0;
//    int k = left;

//    // Merge the temp vectors back
//    // into arr[left..right]
//    while (i < n1 && j < n2) {
//        if (L[i] <= R[j]) {
//            arr[k] = L[i];
//            i++;
//        }
//        else {
//            arr[k] = R[j];
//            j++;
//        }
//        k++;
//    }

//    // Copy the remaining elements of L[],
//    // if there are any
//    while (i < n1) {
//        arr[k] = L[i];
//        i++;
//        k++;
//    }

//    // Copy the remaining elements of R[],
//    // if there are any
//    while (j < n2) {
//        arr[k] = R[j];
//        j++;
//        k++;
//    }
//}

//// begin is for left index and end is right index
//// of the sub-array of arr to be sorted
//void mergeSort(vector<int>& arr, int left, int right)
//{
//    if (left >= right)
//        return;

//    int mid = left + (right - left) / 2;
//    mergeSort(arr, left, mid);
//    mergeSort(arr, mid + 1, right);
//    merge(arr, left, mid, right);
//}


//void foo(std::vector<int>& randomArray,
//         std::vector<int>& sortedArray,
//         std::vector<int>& reversedArray,
//         double (my::Sort::*sortFuncPtr)(std::vector<int>& array)
//         );
















#endif // MY_ALGORITHM_HPP
