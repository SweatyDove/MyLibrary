#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iomanip>


#include "my_sort.h"
#include "my_utilities.h"


int getRandomNumber(int min, int max);
//void foo(std::vector<int>& randomArray,
//         std::vector<int>& sortedArray,
//         std::vector<int>& reversedArray,
//         double (my::Sort::*sortFuncPtr)(std::vector<int>& array)
//         );





int main()
{
    my::Sort    sort;
    my::Timer   timer;
    double      time;


    // Устанавливаем зерно для std::rand() и затем вызываем 1 раз std::rand() для того, чтобы
    // отбросить 1-ое значение.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    int randArrSize {10'000};
    std::vector<int> testArray(randArrSize);
    std::vector<int> randomArray(randArrSize);
    std::vector<int> sortedArray(randArrSize);
    std::vector<int> reversedArray(randArrSize);

    std::vector<int> simpleArray = {1, 4, 7, 0, 5, 9, 2, 3, 2, 8};                // size = 10

//    std::vector<int> stdSortArray(randArrSize);
//    std::vector<int> customSortArray(randArrSize);

    for (int ii {0}; ii < randArrSize - 1; ++ii) {
        randomArray[ii] = my::getRandomNumber(-randArrSize, randArrSize);
    }


    std::cout << "\nArray size:  " << randArrSize << std::endl;

    //##############################################################################################
    //################################        std::sort()       ####################################
    //##############################################################################################

    // # Подсчёт времени сортировки СЛУЧАЙНОГО массива
    testArray = randomArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "\nstd::sort time of RANDOM array:    " << time << " milliseconds" << std::endl;

    // # Формируем отсортированный массив
    sortedArray = testArray;

    // # Подсчёт времени сортировки ОТСОРТИРОВАННОГО массива (вырожденный случай)
    // testArray = sortedArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "std::sort time of SORTED array:    " << time << " milliseconds" << std::endl;

    // # Формируем массив, отсортированный в ОБРАТНОМ порядке
    for (int ii {0}; ii < randArrSize; ++ii) {
        reversedArray[ii] = sortedArray[randArrSize - 1 - ii];
    }

    // # Подсчёт времени сортировки ОБРАТНОГО массива (вырожденный случай)
    testArray = reversedArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "std::sort time of REVERSED array:  " << time << " milliseconds" << std::endl;



    //##############################################################################################
    //################################        my::Sort::comb()       ###############################
    //##############################################################################################
    testArray = randomArray;
    time = sort.comb(testArray);
    if (testArray == sortedArray) {
        std::cout << "\nCOMB sort time of RANDOM array:    " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "COMB sort of RANDOM array wasn't correct!" << std::endl;
    }

    testArray = sortedArray;
    time = sort.comb(testArray);
    if (testArray == sortedArray) {
        std::cout << "COMB sort time of SORTED array:    " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "COMB sort of SORTED array wasn't correct!" << std::endl;
    }

    testArray = reversedArray;
    time = sort.comb(testArray);
    if (testArray == sortedArray) {
        std::cout << "COMB sort time of REVERSED array:  " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "COMB sort of REVERSED array wasn't correct!" << std::endl;
    }

    //##############################################################################################
    //################################        my::Sort::insertion()       ##########################
    //##############################################################################################
    testArray = randomArray;
    time = sort.insertion(testArray);
    if (testArray == sortedArray) {
        std::cout << "\nINSERTION sort time of RANDOM array:    " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "INSERTION sort of RANDOM array wasn't correct!" << std::endl;
    }
    testArray = sortedArray;
    time = sort.insertion(testArray);
    if (testArray == sortedArray) {
        std::cout << "INSERTION sort time of SORTED array:    " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "INSERTION sort of SORTED array wasn't correct!" << std::endl;
    }

    testArray = reversedArray;
    time = sort.insertion(testArray);
    if (testArray == sortedArray) {
        std::cout << "INSERTION sort time of REVERSED array:  " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "INSERTION sort of REVERSED array wasn't correct!" << std::endl;
    }



    return 0;
}


















class Solution {
public:
    std::vector<int> getAverages(std::vector<int>& nums, int k) {

        /*
         *  А разве можно создавать новый вектор и возвращать ссылку на него? Да, память
         * выделяется в куче, но разве она не должна освобождаться после выхода из функции,
         * т.к. сам вектор res - это локальная переменная, сидящая в стеке и при выходе из
         * функции эта стековая переменная должна уничтожаться (а потому там должен
         * вызываться деструктор). То есть почему он всё-таки возвращается?
         */
        std::vector<int> res;

        int numSize {static_cast<int>(nums.size())};
        int windowSize {2 * k + 1};
        int windowSum {0};


        res.resize(numSize);

        // # Граничный случай, когда размер массива nums < 2k + 1.
        if (numSize < windowSize) {
            for (int ii {0}; ii < numSize; ++ii) {
                res[ii] = -1;
            }
        }
        else {

            // Считаем сумму в окне
            for (int ii {0}; ii < windowSize; ++ii) {
                windowSum += nums[ii];
            }

            // Заполняем начало массива
            int ii {0};

            while (ii < k) {
                res[ii] = -1;
                ++ii;
            }

            // Заполняем середину массива
            while (ii < numSize - k - 1) {
                res[ii] = (windowSum / windowSize);
                windowSum = windowSum - nums[ii - k] + nums[ii + k + 1];
                ++ii;
            }
            res[ii] = (windowSum / windowSize);
            ++ii;

            // Заполняем конец массива
            while (ii < numSize) {
                res[ii] = -1;
                ++ii;
            }
        }

        return res;
    }
};


