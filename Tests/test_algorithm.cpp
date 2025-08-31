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
    struct Line {
        std::string sortName {};
        double randTime {};
        double sortedTime {};
        double almostTime {};
        double reversTime {};
    };


private:
    const ContainerType&   mb_random;
    CompareType            mb_compare;


    ContainerType   mb_tested {};
    ContainerType   mb_sorted {};
    ContainerType   mb_reversed {};
    ContainerType   mb_almosted {};

    double  mb_randomTime {};
    double  mb_sortedTime {};
    double  mb_reversTime {};
    double  mb_almostTime {};

    my::Timer       mb_stopwatch {};

    std::vector<Line> mb_table {};



public:



    // # Constructor
    Test(const ContainerType& random, CompareType compare) :
        mb_random {random},
        mb_compare {compare}
    {
        std::cout << "Preparing test data via \'std::sort\' algorithm..." << std::endl;

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
        mb_almostTime = mb_stopwatch.elapsed();


        // # Формируем массив, отсортированный в ОБРАТНОМ порядке
        mb_reversed = mb_random;
        for (int ii {0}; ii < size; ++ii) {
            mb_reversed[ii] = mb_sorted[size - 1 - ii];
        }

        // # Подсчёт времени сортировки ОБРАТНОГО массива (вырожденный случай)
        mb_tested = mb_reversed;
        mb_stopwatch.reset();
        std::sort(mb_tested.begin(), mb_tested.end(), compare);
        mb_reversTime= mb_stopwatch.elapsed();


        mb_table.emplace_back("STD::SORT", mb_randomTime, mb_sortedTime, mb_almostTime, mb_reversTime);

    }


    // #
    void print()
    {
//        std::cout << "-----------------------------------------------------------------------------" <<std::endl;
//        std::cout << "STD::SORT        time of     RANDOM    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_randomTime << " milliseconds" << std::endl;
//        std::cout << "STD::SORT        time of     SORTED    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_sortedTime << " milliseconds" << std::endl;
//        std::cout << "STD::SORT        time of     ALMOST    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_almostTime << " milliseconds" << std::endl;
//        std::cout << "STD::SORT        time of     REVERS    container:   " << std::setw(12) << std::setprecision(4) << std::left << mb_reversTime << " milliseconds" << std::endl;
//        std::cout << "-----------------------------------------------------------------------------" <<std::endl;

        std::cout << "\n\n" << std::endl;

        // # Choice loop
        char choice {};
        bool choiceLoop {true};
        do {
            std::cout << "Time measurement unit:    MILLISECONDS" << std::endl;
            std::cout << "+-------------------------------+--------------+--------------+--------------+--------------+" << std::endl;
            std::cout << "| Sorting Type \\ Container Type |    RANDOM    |    SORTED    |    ALMOST    |    REVERS    |" << std::endl;
            std::cout << "+-------------------------------+--------------+--------------+--------------+--------------+" << std::endl;

            for (const auto& line: mb_table) {
                std::cout << "| " << std::setw(29) << std::left << line.sortName << " |"
                          << ' '  << std::setw(12) << std::setprecision(5) << std::left << line.randTime << " |"
                          << ' '  << std::setw(12) << std::setprecision(5) << std::left << line.sortedTime << " |"
                          << ' '  << std::setw(12) << std::setprecision(5) << std::left << line.almostTime << " |"
                          << ' '  << std::setw(12) << std::setprecision(5) << std::left << line.reversTime << " |"
                          << std::endl;

            }
            std::cout << "+-------------------------------+--------------+--------------+--------------+--------------+" << std::endl;
            std::cout << std::endl;
            std::cout << "How do you want to display output? Press an appropriate key..."
                      << "\n[1] - RANDOM"
                      << "\n[2] - SORTED"
                      << "\n[3] - ALMOST"
                      << "\n[4] - REVERS"
                      << "\n[Q] - Quit"
                      << "\n"
                      << "\nYour choice: ";
            std::cin >> choice;

            switch(choice) {
            // Create and run an exchange menu, that is responsible for the... exchange...
            case '1':
                std::sort(mb_table.begin(), mb_table.end(), [](const Line& a, const Line& b) {return (a.randTime < b.randTime);});
                std::cout << "\n\n    Sorting by column:    RANDOM" << std::endl;
                break;
            case '2':
                std::sort(mb_table.begin(), mb_table.end(), [](const Line& a, const Line& b) {return (a.sortedTime < b.sortedTime);});
                std::cout << "\n\n    Sorting by column:    SORTED" << std::endl;
                break;
            case '3':
                std::sort(mb_table.begin(), mb_table.end(), [](const Line& a, const Line& b) {return (a.almostTime < b.almostTime);});
                std::cout << "\n\n    Sorting by column:    ALMOST" << std::endl;
                break;
            case '4':
                std::sort(mb_table.begin(), mb_table.end(), [](const Line& a, const Line& b) {return (a.reversTime < b.reversTime);});
                std::cout << "\n\n    Sorting by column:    REVERS" << std::endl;
                break;
            case 'Q': case 'q':
                choiceLoop = false;
                break;
            default:
                std::cout << "Incorrect choice. Please, try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
        while (choiceLoop);

    }


    // # Tester
    void start(void (*fn)(typename ContainerType::Iterator, typename ContainerType::Iterator, CompareType),
               const char* sortType = "SORT")
    {
        std::cout << "Test of \'" << sortType << "\' sorting algorithm has started!" << std::endl;
//        std::cout << "-----------------------------------------------------------------------------" <<std::endl;

        // # Sort of RANDOM container
        mb_tested = mb_random;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        mb_randomTime = mb_stopwatch.elapsed();

//        if (mb_tested == mb_sorted) {
//            std::cout << std::setw(16) << std::left << sortType << " time of     RANDOM    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
//        }
//        else {
//            std::cout << std::setw(16) << sortType << " time of     RANDOM    container:   " << std::setw(12) << "INVALID" << std::endl;
//        }


        // # Sort of SORTED container
        mb_tested = mb_sorted;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        mb_sortedTime = mb_stopwatch.elapsed();

//        if (mb_tested == mb_sorted) {
//            std::cout << std::setw(16) << std::left << sortType << " time of     SORTED    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
//        }
//        else {
//            std::cout << std::setw(16) << sortType << " time of     SORTED    container:   " << std::setw(12) << "INVALID" << std::endl;
//        }

        // # Sort of ALMOST SORTED container
        mb_tested = mb_almosted;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        mb_almostTime = mb_stopwatch.elapsed();

//        if (mb_tested == mb_sorted) {
//            std::cout << std::setw(16) << std::left << sortType << " time of     ALMOST    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
//        }
//        else {
//            std::cout << std::setw(16) << sortType << " time of     ALMOST    container:   " << std::setw(12) << "INVALID" << std::endl;
//        }

        // # Sort of REVERSED container
        mb_tested = mb_reversed;
        mb_stopwatch.reset();
        (*fn)(mb_tested.begin(), mb_tested.end(), mb_compare);
        mb_reversTime = mb_stopwatch.elapsed();

//        if (mb_tested == mb_sorted) {
//            std::cout << std::setw(16) << std::left << sortType << " time of     REVERS    container:   " << std::setw(12) << std::setprecision(4) << std::left << time << " milliseconds" << std::endl;
//        }
//        else {
//            std::cout << std::setw(16) << sortType << " time of     REVERS    container:   " << std::setw(12) << "INVALID" << std::endl;
//        }


        mb_table.emplace_back(sortType, mb_randomTime, mb_sortedTime, mb_almostTime, mb_reversTime);
//        std::cout << "-----------------------------------------------------------------------------" <<std::endl;


    }
};





int main()
{


    //##############################################################################################
    //##################################       Debug section       #################################
    //##############################################################################################
//    my::DynamicArray<int> smallArr {1, 2, 3, 4, 5};
//    my::DynamicArray<int>::Iterator beg = smallArr.itbegin();               // Лучше использовать auto, но для отладки пока в явном виде
//    std::cout << *(beg + 2) << std::endl;

//    return 0;






    //##############################################################################################
    //##############################################################################################
    //##############################################################################################

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




    if (TEST_STUPID_SORT)
        test.start(my::sort::stupid, "MY::STUPID");

    if (TEST_BUBBLE_SORT)
        test.start(my::sort::bubble, "MY::BUBBLE");

    if (TEST_COCKTAIL_SORT)
        test.start(my::sort::cocktail, "MY::COCKTAIL");

    if (TEST_ODDEVEN_SORT)
        test.start(my::sort::oddEven, "MY::ODDEVEN");

    if (TEST_COMB_SORT)
        test.start(my::sort::comb, "MY::COMB");

    if (TEST_SELECTION_SORT)
        test.start(my::sort::selection, "MY::SELECTION");

    if (TEST_HEAP_SORT)
        test.start(my::sort::heap, "MY::HEAP");

    if (TEST_INSERTION_SORT)
        test.start(my::sort::insertion, "MY::INSERTION");

    if (TEST_SHELL_SORT)
        test.start(my::sort::shell, "MY::SHELL");

    test.print();




    return 0;
}






