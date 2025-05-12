#include "my_sort.h"


//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
my::Sort::Sort()
{

}


//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
inline void my::Sort::swap(int& a, int& b)
{
    int temp {a};
    a = b;
    b = temp;
}



//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Realization of "stupid sort" algorithm
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   1) Replacing @temp variable with XOR is NOT faster!
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
// COMMENTS/BUGS:   ........
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
// COMMENTS/BUGS:   ........
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
// COMMENTS/BUGS:   There is a version from wiki, that works a little bit faster:
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
// COMMENTS/BUGS:   About 10% faster than base version (but need to compile with -O3 option)
//==================================================================================================
double my::Sort::oddEven_1(std::vector<int>& nums)
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
// COMMENTS/BUGS:   ........
//==================================================================================================
double my::Sort::oddEven_2(std::vector<int>& nums)
{
    int     size        {static_cast<int>(nums.size())};
    int     clearPass   {0};              // Num of passes through @nums without changes
    int     halfSize    {size / 2};
    int     halfEdge    {(halfSize % 2 == 0) ? halfSize : halfSize + 1};


    mb_stopwatch.reset();

    for (int kk {1}; clearPass < 2; kk = (kk % 2) ? 0 : 1) {

        int     edge            {halfEdge + kk};
        bool    firstPartSwap   {false};
        bool    secondPartSwap  {false};

        for (int ii {kk}; ii < edge; ii += 2) {
            if (nums[ii] > nums[ii + 1]) {
                this->swap(nums[ii], nums[ii + 1]);
                firstPartSwap = true;
            }
            else {}

            // # УХОЖУ ЗА ГРАНИЦЫ!
            if (nums[ii + edge] > nums[ii + edge + 1]) {
                this->swap(nums[ii + edge], nums[ii + edge + 1]);
                secondPartSwap = true;
            }
            else {}
        }

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
// COMMENTS/BUGS:   ........
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




