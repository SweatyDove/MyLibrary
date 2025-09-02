#include <iostream>
#include "my_dynamicarray.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>



TEST(GroupName, TestName)
{
//    my::DynamicArray<int> d {1, 2, 3};
//    std::cout << d << std::endl;

//    d.pushBack(4);
//    d.pushBack(5);
//    std::cout << d << std::endl;

    ASSERT_TRUE(true);
}




int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
