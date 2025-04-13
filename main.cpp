#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>


#include "my_sort.h"
#include "my_utilities.h"


int getRandomNumber(int min, int max);





int main()
{

    // Устанавливаем зерно для std::rand() и затем вызываем 1 раз std::rand() для того, чтобы
    // отбросить 1-ое значение.
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::rand();

    int randArrSize {10'000};
    std::vector<int> randomArray(randArrSize);
    std::vector<int> stdSortArray(randArrSize);
    std::vector<int> customSortArray(randArrSize);

    for (int ii {0}; ii < randArrSize - 1; ++ii) {
        randomArray[ii] = my::getRandomNumber(-randArrSize, randArrSize);
    }







    std::vector<int> testArray = {1, 4, 7, 0, 5, 9, 2, 3, 2, 8};                // size = 10
    std::vector<int> testArray_2 = {2, 3, 2};
//    std::vector<int> reverseArray(randArrSize);
//    for (int ii {0}; ii < randArrSize; ++ii) {
//        stdSortArray[ii] = reverseArray[ii] = randArrSize - ii;
//    }
    //    int k = 3;
//    Solution sol {};
//    std::vector<int> res {sol.getAverages(testArray, k)};



    my::Sort    sort;
    double      time;


//    time = sort.stupid(stupidArray);
//    std::cout << "\nSTUPID sort time: " << time << " seconds" << std::endl;



    my::Timer t;
    stdSortArray = randomArray;
    std::sort(stdSortArray.begin(), stdSortArray.end());
    time = t.elapsed();
    std::cout << "\nstd::sort time: " << time << " milliseconds" << std::endl;





//    customSortArray = randomArray;
//    time = sort.bubble(customSortArray);
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nBUBBLE sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nBUBBLE sort wasn't correct!" << std::endl;
//    }


//    customSortArray = randomArray;
//    time = sort.cocktail(customSortArray);
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nCOCKTAIL sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nCOCKTAIL sort wasn't correct!" << std::endl;
//    }

//    customSortArray = randomArray;
//    time = sort.oddEven(customSortArray);
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nODD-EVEN sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nODD-EVEN sort wasn't correct!" << std::endl;
//    }


//    customSortArray = randomArray;
//    time = sort.oddEven_1(customSortArray);
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nODD-EVEN_1 sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nODD-EVEN_1 sort wasn't correct!" << std::endl;
//    }



//    customSortArray = randomArray;
//    time = sort.oddEven_2(customSortArray);
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nODD-EVEN_2 sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nODD-EVEN_2 sort wasn't correct!" << std::endl;
//    }




    customSortArray = randomArray;
    time = sort.comb(customSortArray);
    if (stdSortArray == customSortArray) {
        std::cout << "\nCOMB sort time: " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "\nCOMB sort wasn't correct!" << std::endl;
    }





//    customSortArray = randomArray;
//    t.reset();
//    sort.quick(customSortArray, 0, customSortArray.size() - 1);
//    time = t.elapsed();
//    if (stdSortArray == customSortArray) {
//        std::cout << "\nQUICK sort time: " << time << " milliseconds" << std::endl;
//    }
//    else {
//        std::cout << "\nQUICK sort wasn't correct!" << std::endl;
//    }


    customSortArray = randomArray;
    t.reset();
    sort.quickClassic(customSortArray, 0, customSortArray.size() - 1);
    time = t.elapsed();
    if (stdSortArray == customSortArray) {
        std::cout << "\nQUICK CLASSIC sort time: " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "\nQUICK CLASSIC sort wasn't correct!" << std::endl;
    }


    customSortArray = randomArray;
    t.reset();
    sort.selection(customSortArray);
    time = t.elapsed();
    if (stdSortArray == customSortArray) {
        std::cout << "\nSELECTION sort time: " << time << " milliseconds" << std::endl;
    }
    else {
        std::cout << "\nSELECTION sort wasn't correct!" << std::endl;
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


