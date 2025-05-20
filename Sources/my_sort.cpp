#include "my_sort.h"


//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
my::Sort::Sort()
{

}




//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
//my::Sort::Sort(const std::vector<int>& randomArray, const std::vector<int>& sortedArray, const std::vector<int>& reversedArray) :
//    mb_randomArray {randomArray},
//    mb_sortedArray {sortedArray},
//    mb_reversedArray {reversedArray}
//{

//}

//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Swap 2 elements
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
inline void my::Sort::swap(int& a, int& b)
{
    int temp {a};
    a = b;
    b = temp;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Test specified algo on different arrays
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
void my::Sort::test(const std::vector<int>& randomArray, const std::vector<int>& sortedArray, const std::vector<int>& almostSortedArray, const std::vector<int>& reversedArray, double (my::Sort::*fn)(std::vector<int>& nums), const char* algoName)
{
    std::vector<int> testArray;
    double time;

    testArray = randomArray;
    // fn - это АДРЕС функции сортировки, поэтому *fn - сама функция. А ещё нужен объект для её вызова
    // и поэтому перед *fn стоит this-> (можно (*this).)
    time = ((*this).*fn)(testArray);
    if (testArray == sortedArray) {
        std::cout << '\n' << algoName << " sort time of RANDOM array:         " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << '\n' << algoName << " sort of RANDOM array wasn't correct!" << std::endl;
    }

    testArray = sortedArray;
    time = (this->*fn)(testArray);
    if (testArray == sortedArray) {
        std::cout << algoName << " sort time of SORTED array:         " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << algoName << " sort of SORTED array wasn't correct!" << std::endl;
    }


    testArray = almostSortedArray;
    time = (this->*fn)(testArray);
    if (testArray == sortedArray) {
        std::cout << algoName << " sort time of ALMOST sorted array:  " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << algoName << " sort of ALMOST sorted array wasn't correct!" << std::endl;
    }


    testArray = reversedArray;
    time = (this->*fn)(testArray);
    if (testArray == sortedArray) {
        std::cout << algoName << " sort time of REVERSED array:       " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << algoName << " sort of REVERSED array wasn't correct!" << std::endl;
    }

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Realization of "stupid sort" algorithm
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Replacing @temp variable with XOR is NOT faster!
//                  2) Usage of pointers versus indexes is NOT faster!
//                  3) Taking expression "size - 1" outside the for-loop is NOT faster!
//==================================================================================================
double my::Sort::stupid(std::vector<int>& nums)
{
    int size    {static_cast<int>(nums.size())};

    mb_stopwatch.reset();
    for (int ii {0}; ii < size - 1; ++ii) {
        if (nums[ii] > nums[ii + 1]) {
            this->swap(nums[ii], nums[ii + 1]);
            ii = -1;
        }
        else {}
    }
    mb_timeInterval = mb_stopwatch.elapsed();

    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
double my::Sort::bubble(std::vector<int>& nums)
{

    int size    {static_cast<int>(nums.size())};

    mb_stopwatch.reset();
    for (int kk {size - 1}; kk > 0; --kk) {
        for (int ii {0}; ii < kk; ++ii) {
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii + 1]);
            }
            else {} // Nothing to do
        }
    }
    mb_timeInterval = mb_stopwatch.elapsed();

    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
double my::Sort::cocktail(std::vector<int>& nums)
{

    int     size        {static_cast<int>(nums.size())};
    bool    isSorted    {false};

    mb_stopwatch.reset();

    for (int start {0}, end {size - 1}; isSorted == false; ++start, --end) {

        // # Think, that array is sorted
        isSorted = true;

        // # Forward
        for (int ii {start}; ii < end; ++ii) {
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii + 1]);
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
            if (nums[ii] < nums[ii - 1]) {
                this->swap(nums[ii], nums[ii - 1]);
                isSorted = false;
            }
            else {} // Nothing to do
        }
    }

    mb_timeInterval = mb_stopwatch.elapsed();

    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
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
double my::Sort::oddEven(std::vector<int>& nums)
{
    int     size        {static_cast<int>(nums.size())};
    int     clearPass   {0};              // Num of passes through @nums without changes
    bool    isSwapped   {false};

    mb_stopwatch.reset();

    for (int startIndex {0}; clearPass < 2; startIndex = (startIndex % 2) ? 0 : 1) {
        isSwapped = false;
        for (int ii {startIndex}; ii < size - 1; ii += 2) {
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii+1]);
                isSwapped = true;
            }
            else {}
        }

        clearPass = (isSwapped == true) ? 0 : clearPass + 1;
    }


    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Two loop version of oddEven sort algorithm.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   About 4-5% faster than base version (but need to compile with -O3 option)
//==================================================================================================
double my::Sort::oddEvenVer1(std::vector<int>& nums)
{
    int     size        {static_cast<int>(nums.size())};
    int     clearPass   {0};              // Num of passes through @nums without changes
    int     halfSize    {size / 2};
    int     halfEdge    {(halfSize % 2 == 0) ? halfSize : halfSize + 1};


    mb_stopwatch.reset();

    for (int kk {1}; clearPass < 2; kk = (kk % 2) ? 0 : 1) {

        int     edge            {halfEdge + kk};
        bool    firstLoopSwap   {false};
        bool    secondLoopSwap  {false};

        // # First loop handles left (first) part of the source vector
        for (int jj {kk}; jj < edge; jj += 2) {
            if (nums[jj] > nums[jj + 1]) {
                this->swap(nums[jj], nums[jj + 1]);
                firstLoopSwap = true;
            }
            else {}
        }

        // # Second loop handles right (second) part of the source vector
        for (int ii {edge}; ii < size - 1; ii += 2) {
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii + 1]);
                secondLoopSwap = true;
            }
            else {}
        }

        clearPass = (firstLoopSwap || secondLoopSwap) ? 0 : clearPass + 1;
    }



    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Two if-else version of oddEven sort algorithm.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   About 8-10% faster than base version, but with MUCH MORE difficult logic... And
//                  I'm not sure, that is all correct.
//==================================================================================================
double my::Sort::oddEvenVer2(std::vector<int>& nums)
{
    int     size        {static_cast<int>(nums.size())};
    int     clearPass   {0};              // Num of passes through @nums without changes
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


    mb_stopwatch.reset();

    // # Main loop that switches the type of pass (odd or even) and check if the last two passes were
    // # without swapping.
    for (int kk {1}; clearPass < 2; kk = (kk % 2) ? 0 : 1) {

        int     edge            {(kk == 1) ? oddEdge : evenEdge};
        bool    firstPartSwap   {false};
        bool    secondPartSwap  {false};
        int     jj              {0};

        for (int ii {kk}; ii < edge; ii += 2) {

            // ## Handle the left part of the array
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii + 1]);
                firstPartSwap = true;
            }
            else {}

            // ## Handle the right part
            jj = ii + edge - kk;
            if (nums[jj] > nums[jj + 1]) {
                this->swap(nums[jj], nums[jj + 1]);
                secondPartSwap = true;
            }
            else {}
        }

        // ## Тут я должен учесть, было ли сравнение последней пары и, если не было - выполнить её.
        // ## Расположение индекса левого эл-та последней пары зависит от чётности размера массива
        // ## и типа прохода (чётный/нечётный).
        jj += 2;
        int lastEdge {sizeIsEven ? size - 1 - kk : size - 2 + kk};
        if (sizeIsEven && jj < lastEdge && nums[jj] > nums[jj + 1]) {
                this->swap(nums[jj], nums[jj + 1]);
                secondPartSwap = true;
        }
        else {}


        clearPass = (firstPartSwap || secondPartSwap) ? 0 : clearPass + 1;
    }



    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
double my::Sort::comb(std::vector<int>& nums)
{
    int     size        {static_cast<int>(nums.size())};
    double  factor      {1.247};                                    // Constant (why "1.247" look wiki)
    int     gap         {static_cast<int>(size / factor)};
    bool    isSwapped   {true};

    mb_stopwatch.reset();

    while (gap > 1 || isSwapped == true) {

        isSwapped = false;
        for (int ii {0}; ii < size - gap; ++ii) {
            if (nums[ii] > nums[ii + gap]) {
                this->swap(nums[ii], nums[ii + gap]);
                isSwapped = true;
            }
            else {} // Nothing to do
        }
        gap /= factor;
        gap = (gap > 1) ? gap : 1;
    }

    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Падает в случае массива, отсортированного в обратном порядке, размера 100'000
//                  элементов (слишком много рекурсивных вызовов, переполняется стек?)
//                  2) Не работает с pivot = a[(start + end) / 2] из-за неверного выставления
//                  параметра 'edge' для такого случая.
//                  3) Работает быстрее 'классического' исполнения (quickClassic())
//==================================================================================================
void my::Sort::quick(std::vector<int>& a, int start, int end)
{
    // Exit if subarray has 1 element or 0
    if (start >= end) {
        return;
    }
    else {} // Nothing to do

//    int     pivot       {a[(start + end) / 2]};
    int     pivot       {a[start]};
    int     ii          {start};
    int     jj          {end};
    bool    isSwapped   {false};                 // Used, when all elements in subarray are higher than @pivot
                                            // and there aren't any swaps.

    while (true) {

        // ## Find element, that is equal or higher, than @pivot
        while (ii < jj && a[ii] < pivot) {
            ++ii;
        }

        // ## Find element, that is less than @pivot
        while (ii < jj && a[jj] >= pivot) {
            --jj;
        }

        // ## Swap elements
        if (ii < jj) {
            this->swap(a[ii], a[jj]);
            ++ii;
            --jj;
            isSwapped = true;
        }
        else {
            break;
        }
    }

    // # Choose which subarray a[ii] should be part of:
    // #    If a[ii] less, than pivot (obviosly)
    // #    If there are NOT any swap in array (for example [2, 3, 2]) and we need to 'take' one
    // #    element to left part.
    int edge = (a[ii] < pivot || isSwapped == false) ? ii : ii - 1;
    this->quick(a, start, edge);
    this->quick(a, edge + 1, end);

    return;

}





//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   'Classic' realization
//==================================================================================================
void my::Sort::quickClassic(std::vector<int>& a, int start, int end)
{
    if (start > end) {
        return;
    }
    else {}

    int pivot = a[(start + end) / 2];
    int ii = start;
    int jj = end;

    while (ii <= jj) {
        while (a[ii] < pivot) {
            ++ii;
        }

        while (a[jj] > pivot) {
            --jj;
        }

        if (ii <= jj) {
            this->swap(a[ii], a[jj]);
            ++ii;
            --jj;
        }
        else {}
    }

    this->quickClassic(a, start, jj);
    this->quickClassic(a, ii, end);

    return;

}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
double my::Sort::selection(std::vector<int>& a)
{
    int size {a.size()};

    mb_stopwatch.reset();

    for (int jj {size - 1}; jj > 0; --jj) {

        int ii {1};
        int kk {0};

        while (ii <= jj) {
            kk = (a[ii] > a[kk]) ? ii : kk;
            ++ii;
        }

        this->swap(a[kk], a[jj]);
    }



    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
//void my::Sort::heap(std::vector<int>& a)
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
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
double my::Sort::heap(std::vector<int>& a)
{
    int lastUnsortedIndex {a.size() - 1};           // Last element index

    // # Лямбда-функция просейки
    std::function<void(int)> sift {
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
                else if (child + 1 <= lastUnsortedIndex && a[child] < a[child + 1]) {
                    child += 1;
                }
                else {}

                // ## Свапаем родителя и потомка и устанавливаем новый индекс родителя
                if (a[root] < a[child]) {
                    this->swap(a[root], a[child]);
                    root = child;
                }
                else {
                    break;
                }

            } // while

            return;
        }
    };

    mb_stopwatch.reset();

    // # Делаем сортирующее древо (через просейку каждого его эл-та, начиная с последнего).
    for (int ii {lastUnsortedIndex}; ii >= 0; --ii) {
        sift(ii);
    }

    // # Корень дерева свапнуть с последним эл-м, уменьшить размер неотсортированной части и
    // # провести просейку для элемента в корне.
    for (int ii {lastUnsortedIndex}; ii > 0; --ii) {
        this->swap(a[0], a[ii]);
        --lastUnsortedIndex;
        sift(0);
    }

    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}


//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Не ОБМЕНЫ, а СДВИГ!
//==================================================================================================
double my::Sort::insertion(std::vector<int>& a)
{
    int n {a.size()};

    mb_stopwatch.reset();

    for (int ii {0}; ii < n; ++ii) {

        int temp {a[ii]};
        int kk {ii};
        while (kk > 0 && temp < a[kk - 1]) {
            a[kk] = a[kk - 1];                      // Здесь СДВИГ! Не нужно использовать swap()
            --kk;
        } // O(n)

        a[kk] = temp;       // O(3) -> O(1)

    } // O(n)

    // # Сложность: O(n) * [O(1) + O(n)] -> O(n) * O(n) = O(n^2)

    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) Замена вызова функции swap() (что изначально было 'некорректно') на сдвиг решило
//                  проблему со скоростью работы.
//                  2) Можно улучшить работу, если не прыгать между подмассивами, а идти линейно
//                  по каждому элементу, начиная с gap и дальше запускать цикл сравнения с элементами,
//                  отстающими от текущего на gap, 2gap и т.д. Так сделано в shellClassic().
//==================================================================================================
double my::Sort::shell(std::vector<int>& a)
{
    int size    {   a.size()    };

    mb_stopwatch.reset();


    // # Тут определяем дистанцию между соседними элементами 'подмассива'
    for (int gap {size / 2}; gap >= 1; gap /= 2) {

        // ## Тут уже проходимся по полученным 'подмассивам'
        for (int ii {0}; ii < gap; ++ii) {

            // #### Тут уже сортируем непосредственно "подмассив" методом сортировки вставками
            for (int jj {ii}; jj < size; jj += gap) {

                int temp = a[jj];
                int kk = jj;

                while (kk - gap >= 0 && temp < a[kk - gap]) {
                    a[kk] = a[kk - gap];
                    kk -= gap;
                } // O(n/gap) -> O(n)

                a[kk] = temp;


            } // O(n/gap + 1), где единица за счёт холостого 0-го эл-та

        } // O(gap) -> O(n/2) в худшем случае (1-ая итерация), т.е. этот член убывает для каждого следующего gap, т.е. как бы можно gap сократить будет при расчёте общего O-большого

    } // O(log n), т.к. в 2 раза уменьшаем каждый раз



    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   From https://www.programiz.com/dsa/shell-sort
//                  Принцип работы для данной реализации смотри выше в описании my::Sort::shell()
//==================================================================================================
double my::Sort::shellClassic(std::vector<int>& array) {

    int n = array.size();

    mb_stopwatch.reset();


    // Rearrange elements at each n/2, n/4, n/8, ... gaps
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int ii = gap; ii < n; ii += 1) {
            int temp = array[ii];
            int jj = ii;
            while (jj >= gap && array[jj - gap] > temp) {
                array[jj] = array[jj - gap];
                jj -= gap;
            }
            array[jj] = temp;
        }
    }


    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;
}





//==================================================================================================
// COMMENTS:    Выскакивает ошибка с 9-ой у тестового массива. Видимо где-то забываю обработать
//              последний элемент.
//==================================================================================================
std::vector<int> foo(std::vector<int>& a, int left, int right)
{
    std::vector<int> retArray;

    // # If only 1 element in @a - then @a is sorted
    if (right - left == 1) {
        retArray.push_back(a[left]);
        return retArray;
    }
    else {}



    // # Get sorted subarray
    std::vector<int> aLeft = foo(a, left, (left + right) / 2);
    std::vector<int> aRight = foo(a, (left + right) / 2, right);            // +1 ?



    // # Form new array from 2 sorted subarrays (can use reference on proto-array as buffer)
    int ii {0};         // Left subarray iterator
    int jj {0};         // Right subarray iterator

    while ((ii < aLeft.size()) && (jj < aRight.size())) {
        if (aLeft[ii] <= aRight[jj]) {
            retArray.push_back(aLeft[ii]);
            ++ii;
        }
        else {
            retArray.push_back(aRight[jj]);
            ++jj;
        }
    }

    // # Only one of below loops will work
    while (ii < aLeft.size()) {
        retArray.push_back(aLeft[ii++]);
    }
    while (jj < aLeft.size()) {
        retArray.push_back(aRight[jj++]);
    }

    return retArray;
}




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Сортировка слиянием "сверху-вниз"
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Алгоритм:
//                  0)
//                  1)  Спускаемся по массиву сверху вниз, каждый раз деля на два подмассива и
//                      применяя к каждой части данную функцию рекурсивно.
//                  2)  Если в полученном подмассиве 1 элемент - то массив отсортирован и можно
//                      выходить.
//                  3)  Как работает процедура merge: по-идее, она берёт два подмассива, каждый из
//                      каждый из которых отсортирован, мерджит их в какой-то дополнительный буффер
//                      (выделять в стеке или статическим сделать?) и возвращает результат наверх.
//==================================================================================================
double my::Sort::mergeUpDown(std::vector<int>& a)
{
    int n = a.size();

    mb_stopwatch.reset();

    foo(a, 0, a.size());




    mb_timeInterval = mb_stopwatch.elapsed();
    return mb_timeInterval;

}










