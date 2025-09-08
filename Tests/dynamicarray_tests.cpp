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
//          TYPE:   Test fixture
//   DESCRIPTION:   Данный класс представляет собой фикстуру - сущность, которая будет какждый раз
//                  автоматически создаваться с нуля для каждого конкретного теста.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
class MyDynamicArrayTest : public testing::Test {
public:
//    my::DynamicArray<int>* mb_dynArrPtr {nullptr};
    my::DynamicArray<int> mb_dynArr {1, 2, 3};


    // # Аналог конструктора
//    void SetUp()
//    {
//        mb_dynArrPtr = new my::DynamicArray<int> {1, 2, 3};
//    }

    // # Аналог деструктора
//    void TearDown()
//    {
//        delete mb_dynArrPtr;
//    }

};



//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST_F(MyDynamicArrayTest, TestInsertionOperator)
{
    // # Arrange

    ::testing::internal::CaptureStdout();
    std::cout << mb_dynArr << std::endl;


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
TEST_F(MyDynamicArrayTest, TestPushBackSize)
{
    // # Arrange
    int size {mb_dynArr.size()};

    // # Act
    mb_dynArr.pushBack(11);
    int newSize = mb_dynArr.size();

    // # Assert
    EXPECT_EQ(size + 1, newSize);
}


//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST_F(MyDynamicArrayTest, TestPushBackElement)
{
    // # Arrange
    int newElement {11};

    // # Act
    mb_dynArr.pushBack(newElement);
    int newSize = mb_dynArr.size();

    // # Assert
    EXPECT_EQ(mb_dynArr[newSize - 1], newElement);
}


//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST_F(MyDynamicArrayTest, TestSubscriptionOperator)
{
    // # Arrange

    // # Act
    int value0 = mb_dynArr[0];

    // # Assert
    EXPECT_EQ(value0, 1);
}




//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST_F(MyDynamicArrayTest, TestPopBackFinalSize)
{
    // # Arrange
    int size {mb_dynArr.size()};

    // # Act
    mb_dynArr.popBack();

    // # Assert
    EXPECT_EQ(mb_dynArr.size(), size - 1);
}




//==================================================================================================
//          TYPE:   Test
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
TEST_F(MyDynamicArrayTest, TestPopBackElement)
{
    // # Arrange
    int size {mb_dynArr.size()};
    int lastElement {mb_dynArr[size - 1]};

    // # Act
    int value = mb_dynArr.popBack();

    // # Assert
    EXPECT_EQ(value, lastElement);
}



//void    nullify(int start, int end);
//void    insert(Type* pos, Type* copyFrom, Type* copyTo);
//void    extend(const my::DynamicArray<Type>& dynArr);


