#include "my_dynamicarray.h"


//==================================================================================================
//          TYPE:    Default constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray()
{
    std::cout << "[DEBUG]: DEFAULT CONSTRUCTOR of <DynamicArray> has been called" << std::endl;

}


//==================================================================================================
//          TYPE:    List-initialized constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(std::initializer_list<Type> list)
{
    std::cout << "[DEBUG]: LIST-INITIALIZED CONSTRUCTOR of <DynamicArray> has been called" << std::endl;

    // Allocate memory for the list's objects of type <Type>
    // Остановился здесь: а что мне использовать? operator new/new[] или new/new[] оператор? Первый
    // выделяет сырую память, второй выделяет память и вызывает на этой памяти конструктор указанного
    // типа. Можно ли просто выделить память и на ней уже организовать конструирование объектов <Type>?
    // И обращаться к этой памяти не по сырым указателям? То есть ручками с памятью работать. Надо
    // подумать...
    mb_dataPtr = static_cast<Type*>(operator new[] (sizeof(Type) * list.size()));



}





//==================================================================================================
//          TYPE:    Destructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::~DynamicArray()
{
    std::cout << "[DEBUG]: DESTRUCTOR of <DynamicArray> has been called" << std::endl;

}
