#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <variant>

//#include "my_iterator.h"
#include "my_algorithm.h"
#include "my_utilities.h"
#include <bits/stdc++.h>




#define ARRAY_SIZE              10'000



#define TEST_STUPID_SORT        false                   // В районе 11 минут у меня на 10'000
#define TEST_BUBBLE_SORT        true
#define TEST_COCKTAIL_SORT      true
#define TEST_ODDEVEN_SORT       true
#define TEST_COMB_SORT          true
#define TEST_SELECTION_SORT     true
#define TEST_HEAP_SORT          true
#define TEST_INSERTION_SORT     true
#define TEST_SHELL_SORT         true




//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Test specified algo on different arrays
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   А на сколько правильно (и можно) просто копировать сюда указатель на функцию.
//                  Нет ли здесь подводных камней? А если в качестве <CompareType> передаётся
//                  лямбда-функция или же std::function?
//
//                  Добавить таблицу для сравнения сортировок
//==================================================================================================
template <typename ContainerType, typename CompareType>
class Test {
public:
    using column = std::variant<const char*>;


private:
    const ContainerType&   mb_random;
    CompareType            mb_compare;


    ContainerType   mb_tested {};
    ContainerType   mb_sorted {};
    ContainerType   mb_reversed {};
    ContainerType   mb_almosted {};

    double  mb_randomTime {};
    double  mb_sortedTime {};
    double  mb_reversedTime {};
    double  mb_almostedTime {};

    my::Timer       mb_stopwatch {};

//    std::vector<std::array<3, column>> mb_table {};



public:



    // # Constructor
    Test(const ContainerType& random, CompareType compare) :
        mb_random {random},
        mb_compare {compare}
    {

        int size {random.size()};

        // # Подсчёт времени сортировки СЛУЧАЙНОГО массива
        mb_tested = mb_random;
        mb_stopwatch.reset();
        std::sort(mb_tested.begin(), mb_tested.end(), compare);
        mb_randomTime = mb_stopwatch.elapsed();



        // # Формируем отсортированный массив
        mb_sorted = mb_tested;


        // # Подсчёт времени сортировки ОТСОРТИРОВАННОГО массива (вырожденный случай)
        mb_stopwatch.reset();
        std::sort(mb_tested.begin(), mb_tested.end(), compare);
        mb_sortedTime = mb_stopwatch.elapsed();



        // # Формируем ПОЧТИ отсортированный массив
        int interval {(size / 25) > 1 ? size / 25 : 1};
        auto rng = std::default_random_engine {};
        mb_almosted = mb_sorted;
        for (int ii {interval}; ii < size; ii += interval) {
            std::ranges::shuffle(&mb_almosted[ii - interval], &mb_almosted[ii], rng);
        }

        // # Подсчёт времени сортировки ПОЧТИ отсортированного массива
        mb_tested = mb_almosted;
        mb_stopwatch.reset();
        std::sort(mb_tested.begin(), mb_tested.end(), compare);
        mb_almostedTime = mb_stopwatch.elapsed();


        // # Формируем массив, отсортированный в ОБРАТНОМ порядке
        mb_reversed = mb_random;
        for (int ii {0}; ii < size; ++ii) {
            mb_reversed[ii] = mb_sorted[size - 1 - ii];
        }

        // # Подсчёт времени сортировки ОБРАТНОГО массива (вырожденный случай)
        mb_tested = mb_reversed;
        mb_stopwatch.reset();
        std::sort(mb_tested.begin(), mb_tested.end(), compare);
        mb_reversedTime= mb_stopwatch.elapsed();

    }


    // #
    void print() const
    {
        std::cout << "-----------------------------------------------------------------------------" <<std::endl;
        std::cout << "STD::SORT        time of     RANDOM    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_randomTime << " milliseconds" << std::endl;
        std::cout << "STD::SORT        time of     SORTED    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_sortedTime << " milliseconds" << std::endl;
        std::cout << "STD::SORT        time of     ALMOST    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_almostedTime << " milliseconds" << std::endl;
        std::cout << "STD::SORT        time of     REVERS    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_reversedTime << " milliseconds" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" <<std::endl;
    }


    // # Tester
    void start(void (*fn)(typename ContainerType::Iterator, typename ContainerType::Iterator, CompareType),
               const char* sortType = "SORT")
    {
        double time {0.0};

        std::cout << "-----------------------------------------------------------------------------" <<std::endl;

        // # Sort of RANDOM container
        mb_tested = mb_random;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        time = mb_stopwatch.elapsed();

        if (mb_tested == mb_sorted) {
            std::cout << std::setw(16) << std::left << sortType << " time of     RANDOM    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
        }
        else {
            std::cout << std::setw(16) << sortType << " time of     RANDOM    container:   " << std::setw(12) << "INVALID" << std::endl;
        }


        // # Sort of SORTED container
        mb_tested = mb_sorted;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        time = mb_stopwatch.elapsed();

        if (mb_tested == mb_sorted) {
            std::cout << std::setw(16) << std::left << sortType << " time of     SORTED    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
        }
        else {
            std::cout << std::setw(16) << sortType << " time of     SORTED    container:   " << std::setw(12) << "INVALID" << std::endl;
        }

        // # Sort of ALMOST SORTED container
        mb_tested = mb_almosted;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        time = mb_stopwatch.elapsed();

        if (mb_tested == mb_sorted) {
            std::cout << std::setw(16) << std::left << sortType << " time of     ALMOST    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
        }
        else {
            std::cout << std::setw(16) << sortType << " time of     ALMOST    container:   " << std::setw(12) << "INVALID" << std::endl;
        }

        // # Sort of REVERSED container
        mb_tested = mb_reversed;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        time = mb_stopwatch.elapsed();

        if (mb_tested == mb_sorted) {
            std::cout << std::setw(16) << std::left << sortType << " time of     REVERS    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
        }
        else {
            std::cout << std::setw(16) << sortType << " time of     REVERS    container:   " << std::setw(12) << "INVALID" << std::endl;
        }

        std::cout << "-----------------------------------------------------------------------------" <<std::endl;
    }
};





int main()
{
    my::DynamicArray<int> randomArray(ARRAY_SIZE);

    auto compLambda {
        [](const auto& a, const auto& b) -> bool { return (a < b); }
    };


    // # Устанавливаем зерно для std::rand() и затем вызываем 1 раз std::rand() для того, чтобы
    // # отбросить 1-ое значение.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    for (int ii {0}; ii < ARRAY_SIZE - 1; ++ii) {
        randomArray[ii] = my::getRandomNumber(-ARRAY_SIZE, ARRAY_SIZE);
    }

    Test test {randomArray, compLambda};
    test.print();




    if (TEST_STUPID_SORT)
        test.start(my::sort::stupid, "STUPID SORT");

    if (TEST_BUBBLE_SORT)
        test.start(my::sort::bubble, "BUBBLE SORT");

    if (TEST_COCKTAIL_SORT)
        test.start(my::sort::cocktail, "COCKTAIL SORT");

    if (TEST_ODDEVEN_SORT)
        test.start(my::sort::oddEven, "ODDEVEN SORT");

    if (TEST_COMB_SORT)
        test.start(my::sort::comb, "COMB SORT");

    if (TEST_SELECTION_SORT)
        test.start(my::sort::selection, "SELECTION SORT");

    if (TEST_HEAP_SORT)
        test.start(my::sort::heap, "HEAP SORT");

    if (TEST_INSERTION_SORT)
        test.start(my::sort::insertion, "INSERTION SORT");

    if (TEST_SHELL_SORT)
        test.start(my::sort::shell, "SHELL SORT");



//    ##############################################################################################
//    ###################################        my::Sort       ####################################
//    ##############################################################################################

//    if (TEST_BUBBLE_SORT) {
//        test(randomArray, sortedArray, &my::sort::bubble, "RANDOM ARRAY", "BUBBLE SORT");
//    }
//    else {}
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::cocktail, "COCKTAIL");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::oddEven, "ODD_EVEN");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::comb, "COMB");

//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::selection, "SELECTION");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::heap, "HEAP");


//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::insertion, "INSERTION");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::shell, "SHELL");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::shellClassic, "SHELL CLASSIC");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::mergeUpDown, "MERGE");


//    std::cout << "\n\n";


//    testArray = randomArray;
//    timer.reset();
//    mergeSort(testArray, 0, size);
//    time = timer.elapsed();
//    std::cout << "CLASSIC MERGE time of RANDOM array:       " << time << " milliseconds" << std::endl;

//    testArray = sortedArray;
//    timer.reset();
//    mergeSort(testArray, 0, size);
//    time = timer.elapsed();
//    std::cout << "CLASSIC MERGE time of SORTED array:       " << time << " milliseconds" << std::endl;

//    testArray = almostSortedArray;
//    timer.reset();
//    mergeSort(testArray, 0, size);
//    time = timer.elapsed();
//    std::cout << "CLASSIC MERGE time of ALMOST SORTED array:       " << time << " milliseconds" << std::endl;

//    testArray = reversedArray;
//    timer.reset();
//    mergeSort(testArray, 0, size);
//    time = timer.elapsed();
//    std::cout << "CLASSIC MERGE time of REVERSED array:       " << time << " milliseconds" << std::endl;

    return 0;
}












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





/***************************************************************************************************
 * А в чём разница между использованием шаблонов и использованием наследования? То есть в интернете
 * пишут, что итераторы реализованы именно на базе шаблонов, НЕ наследования (как я пытаюсь сейчас).
 * И там меняется именно тип аргумента (т.е. у меня сейчас предполагается, что функция sort() принимает
 * референс на итератор, в то время как стандартная библиотека использует шаблон <typename Iterator>...
 *
 * Дальше, как я понимаю, хоть реализация типов разная (для разных типов контейнеров), т.к. у каждого
 * из этих типов есть фиксированный набор операций (инкрементирование, разименование и т.д.), то и конфликта
 * не возникает - аргументы используют функции с одинаковыми именами. То есть ШАБЛОН - это ШАБЛОН функции,
 * а не функция. Компилятор при необходимости создаёт экземпляр функции для указанного типа. И если
 * полученная функция имеет внутри валидные вызовы других функций (а в нашем случае они валидные, так как
 * есть стандртный набор) - то никаких конфликтов не возникнет.
 *
 * Единственное, IDE тебе не покажет ошибку, если функция указана невалидная, т.к. он не знает, тип
 * значения и какой у него интерфейс - нужно сперва скомпилировать.
 **************************************************************************************************/

//template <typename UndefIterator>
//void stupid(UndefIterator beginIt, UndefIterator endIt)
//{
//    using tempType = UndefIterator::pointer;

//    tempType begin = beginIt.operator ->();
//    tempType end = endIt.operator ->();

//    int size = end - begin;

//    tempType num = begin;

//    for (int ii {0}; ii < size - 1; ++ii) {
//        if (num[ii] > num[ii + 1]) {
//            my::swap<int>(num[ii], num[ii + 1]);
//            ii = -1;
//        }
//        else {}
//    }
//}

