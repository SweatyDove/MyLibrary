#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>


#include "my_sort.h"
#include "my_utilities.h"





#include <bits/stdc++.h>
using namespace std;

// Merges two subarrays of arr[].
// First subarray is arr[left..mid]
// Second subarray is arr[mid+1..right]
void merge(vector<int>& arr, int left,
           int mid, int right)
{
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temp vectors
    vector<int> L(n1), R(n2);

    // Copy data to temp vectors L[] and R[]
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0;
    int k = left;

    // Merge the temp vectors back
    // into arr[left..right]
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// begin is for left index and end is right index
// of the sub-array of arr to be sorted
void mergeSort(vector<int>& arr, int left, int right)
{
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}


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

    int size {10'000};
    std::vector<int> testArray(size);
    std::vector<int> randomArray(size);
    std::vector<int> sortedArray(size);
    std::vector<int> reversedArray(size);
    std::vector<int> almostSortedArray(size);

    std::vector<int> simpleArray = {7, 4, 2, 0, 1, 0, 3, 9, 7, 5};                // size = 10

//    std::vector<int> stdSortArray(size);
//    std::vector<int> customSortArray(size);

    for (int ii {0}; ii < size - 1; ++ii) {
        randomArray[ii] = my::getRandomNumber(-size, size);
    }



//    sort.mergeUpDown(randomArray);













    std::cout << "\nArray size:  " << size << std::endl;

    //##############################################################################################
    //################################        std::sort()       ####################################
    //##############################################################################################

    // # Подсчёт времени сортировки СЛУЧАЙНОГО массива
    testArray = randomArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "\nstd::sort time of RANDOM array:         " << time << " milliseconds" << std::endl;



    // # Формируем отсортированный массив
    sortedArray = testArray;

    // # Подсчёт времени сортировки ОТСОРТИРОВАННОГО массива (вырожденный случай)
    // testArray = sortedArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "std::sort time of SORTED array:         " << time << " milliseconds" << std::endl;



    // # Формируем ПОЧТИ отсортированный массив
    int interval {(size / 25) > 1 ? size / 25 : 1};
    auto rng = std::default_random_engine {};
    almostSortedArray = sortedArray;
    for (int ii {interval}; ii < size; ii += interval) {
        std::ranges::shuffle(&almostSortedArray[ii - interval], &almostSortedArray[ii], rng);
    }

    // # Подсчёт времени сортировки ПОЧТИ отсортированного массива
    testArray = almostSortedArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "std::sort time of ALMOST sorted array:  " << time << " milliseconds" << std::endl;




    // # Формируем массив, отсортированный в ОБРАТНОМ порядке
    for (int ii {0}; ii < size; ++ii) {
        reversedArray[ii] = sortedArray[size - 1 - ii];
    }

    // # Подсчёт времени сортировки ОБРАТНОГО массива (вырожденный случай)
    testArray = reversedArray;
    timer.reset();
    std::sort(testArray.begin(), testArray.end());
    time = timer.elapsed();
    std::cout << "std::sort time of REVERSED array:       " << time << " milliseconds" << std::endl;






    //##############################################################################################
    //###################################        my::Sort       ####################################
    //##############################################################################################

//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::bubble, "BUBBLE");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::cocktail, "COCKTAIL");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::oddEven, "ODD_EVEN");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::comb, "COMB");

//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::selection, "SELECTION");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::heap, "HEAP");


//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::insertion, "INSERTION");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::shell, "SHELL");
//    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::shellClassic, "SHELL CLASSIC");
    sort.test(randomArray, sortedArray, almostSortedArray, reversedArray, &my::Sort::mergeUpDown, "MERGE");


    std::cout << "\n\n";


    testArray = randomArray;
    timer.reset();
    mergeSort(testArray, 0, size);
    time = timer.elapsed();
    std::cout << "CLASSIC MERGE time of RANDOM array:       " << time << " milliseconds" << std::endl;

    testArray = sortedArray;
    timer.reset();
    mergeSort(testArray, 0, size);
    time = timer.elapsed();
    std::cout << "CLASSIC MERGE time of SORTED array:       " << time << " milliseconds" << std::endl;

    testArray = almostSortedArray;
    timer.reset();
    mergeSort(testArray, 0, size);
    time = timer.elapsed();
    std::cout << "CLASSIC MERGE time of ALMOST SORTED array:       " << time << " milliseconds" << std::endl;

    testArray = reversedArray;
    timer.reset();
    mergeSort(testArray, 0, size);
    time = timer.elapsed();
    std::cout << "CLASSIC MERGE time of REVERSED array:       " << time << " milliseconds" << std::endl;

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


