#include <iostream>
#include "my_dynamicarray.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>




int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    //    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}



//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST(TestDynamicArray, TestInsertionOperator)
{
    // # Arrange

    my::DynamicArray<int> d {1, 2, 3};

    ::testing::internal::CaptureStdout();
    std::cout << d << std::endl;

//    d.pushBack(4);
//    d.pushBack(5);
//    std::cout << d << std::endl;

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_STREQ(output.c_str(), "[1, 2, 3]\n");
}



//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST(TestDynamicArray, TestPushBackFunc)
{
    // # Arrange
    my::DynamicArray<int> d {12, 7, 34};
    int size {d.size()};

    // # Act
    d.pushBack(11);
    size += 1;

    // # Assert
    EXPECT_EQ(size, 4);
    EXPECT_EQ(d[size - 1], 11);
}


//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST(TestDynamicArray, TestSubscriptionOperator)
{
    // # Arrange
    my::DynamicArray<int> d {12, 7, 34};

    // # Act
    int value0 = d[0];

    // # Assert
    EXPECT_EQ(value0, 12);
}



