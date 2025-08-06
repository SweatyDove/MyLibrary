#include "my_algorithm.h"



//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
//my::Sort::Sort(const my::DynamicArray<int>& randomArray, const my::DynamicArray<int>& sortedArray, const my::DynamicArray<int>& reversedArray) :
//    mb_randomArray {randomArray},
//    mb_sortedArray {sortedArray},
//    mb_reversedArray {reversedArray}
//{

//}








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










