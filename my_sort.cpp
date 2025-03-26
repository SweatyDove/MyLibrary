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

    while (clearPass < 2) {
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




