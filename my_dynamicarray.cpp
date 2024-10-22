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
//          TYPE:   List-initialized constructor
//    PARAMETERS:   --------
//  RETURN VALUE:   --------
//   DESCRIPTION:   --------
// COMMENTS/BUGS:   1) <std::initializer_list> doesn't have overloaded subscription operator "[]"
//                      -- that is why need to use initializer_list::begin() function.
//                  2) Добавить обработку исключений при ошибке выделения памяти оператором new[]
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

    // # Выделил память под нужный мне тип (с небольшим запасом)
    auto listSize = list.size();
    mb_capacity = listSize + mb_capacityChunk;
    mb_dataPtr = static_cast<Type*>(operator new[] (sizeof(Type) * mb_capacity));

    // # Затем я конструирую на этой памяти объекты данного типа и копирую/перемещаю туда объекты из
    // # списка инициализации
    int ii {0};
    while (ii < listSize) {
        *(mb_dataPtr + ii) = list.begin()[ii];
        ++ii;
    }
    mb_size = ii;
}





//==================================================================================================
//          TYPE:    Destructor
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    Не уверен, что здесь имеет смысл присваивать nullptr после освобождения памяти
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::~DynamicArray()
{
    std::cout << "[DEBUG]: DESTRUCTOR of <DynamicArray> has been called" << std::endl;

    delete[] mb_dataPtr;
    mb_dataPtr = nullptr;

}




//==================================================================================================
//          TYPE:   Method
//    PARAMETERS:   --------
//   DESCRIPTION:   Overloaded subscription operator that returns "const reference" (aka "reference
//                  to const")
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
template <typename Type>
const Type& my::DynamicArray<Type>::operator[](int ii) const
{
    return *(mb_dataPtr + ii);

}

//==================================================================================================
//          TYPE:   Method
//    PARAMETERS:   --------
//   DESCRIPTION:   Overloaded subscription operator that returns reference to specified element
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
template <typename Type>
Type& my::DynamicArray<Type>::operator[](int ii)
{
    return *(mb_dataPtr + ii);
}



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    Добавить обработку исключений при ошибке выделения памяти оператором new[]
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::pushBack(Type value)
{
    // # Сперва проверяем наличие свободной памяти (здесь можно вызывать и оператор[] наверное, но
    // # пока в явном виде)

    // # Случай, когда нужно выделить дополнительную память в куче (и скопировать туда содержимое
    // # "текущего" массива)
    if (mb_size == mb_capacity) {
        this->setCapacity(mb_capacity + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Добавляем новый элемент в массив и увеличиваем его размер
    *(mb_dataPtr + mb_size) = value;
    mb_size++;
}




//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::setCapacity(int newCapacity)
{
    assert(newCapacity > mb_capacity && "New capacity must be higher than the old one");

    Type* newDataPtr = static_cast<Type*>(operator new[](sizeof(Type) * newCapacity));
    mb_capacity = newCapacity;

    // ## Копируем старые данные в новую область памяти
    for (int ii {0}; ii < mb_size; ++ii) {
        *(newDataPtr + ii) = *(mb_dataPtr + ii);
    }
    // ## Удаляем старые данные
    delete[] mb_dataPtr;

    mb_dataPtr = newDataPtr;
}




//==================================================================================================
//          TYPE:    General function
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::getSize() const
{
    return mb_size;
}




//==================================================================================================
//          TYPE:    General function
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
std::ostream& my::operator<<(std::ostream& out, const my::DynamicArray<Type>& dynArr)
{
    out << '[';

    int ii {0};
    while (ii < dynArr.getSize() - 1) {
        out << dynArr[ii] << ", ";
        ++ii;
    }
    out << dynArr[ii] << ']';

    return out;
}

