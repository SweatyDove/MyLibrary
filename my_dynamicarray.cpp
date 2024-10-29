#include "my_dynamicarray.h"


//==================================================================================================
//          TYPE:    Default constructor
//    PARAMETERS:    --------
//  RETURN VALUE:    --------
//   DESCRIPTION:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray():
    mb_capacity {mb_capacityChunk},
    mb_size {0},
    mb_dataPtr {static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity))}
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
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   Добавить обработку исключений при ошибке выделения памяти оператором new[]
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::pushBack(Type value)
{
    // # Сперва проверяем наличие свободной памяти (здесь можно вызывать и оператор[] наверное, но
    // # пока в явном виде)

    // # Случай, когда нужно выделить дополнительную память в куче (и скопировать туда содержимое
    // # "текущего" массива)
    if (mb_size == mb_capacity) {
        this->reallocate(mb_capacity + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Добавляем новый элемент в массив и увеличиваем его размер
    *(mb_dataPtr + mb_size) = value;
    mb_size++;
}



//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   What should I do with the extracted element? Should I pop it via
//                  reference? - NOPE, cause the memory, where it is storing can be rewrited by the
//                  *this object.
//==================================================================================================
template <typename Type>
Type my::DynamicArray<Type>::popBack()
{
    assert(mb_size > 0 && "Can't pop_back the last element from the empty array. Abort.");

    return mb_dataPtr[--mb_size];
}




//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::reallocate(int newCapacity)
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
//          TYPE:    Getter
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
//          TYPE:    Getter
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::getCapacity() const
{
    return mb_capacity;
}

//==================================================================================================
//          TYPE:    Getter
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::getCapacityChunk() const
{
    return mb_capacityChunk;
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



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
const Type* my::DynamicArray<Type>::begin() const
{
    return mb_dataPtr;
}


//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
Type* my::DynamicArray<Type>::begin()
{
    return mb_dataPtr;
}



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
Type* my::DynamicArray<Type>::end()
{
    return (mb_dataPtr + mb_size);
}



//==================================================================================================
//          TYPE:    --------
//    PARAMETERS:    --------
//   DESCRIPTION:    --------
//  RETURN VALUE:    --------
// COMMENTS/BUGS:    --------
//==================================================================================================
template <typename Type>
const Type* my::DynamicArray<Type>::end() const
{
    return (mb_dataPtr + mb_size);
}



//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   Функция расширяет текущий массив с использованием данных из аргумента такого же
//                  типа (my::DynamicArray<Type>)
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::extend(const my::DynamicArray<Type>& dynArr)
{
    int newSize {mb_size + dynArr.getSize()};

    // # Если массив может вместить данные из другого массива, то просто расширяем его. Хотя, можно,
    // # наверное и не расширять, т.к. он автоматически расширится при копировании (если я
    // # предоставлю соответствующий оператор).
    if (mb_capacity < newSize) {
        this->reallocate(newSize + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Copy (or move) elements from rh-operand to *this object
    for (auto& element: dynArr) {
        // (mb_dataPtr + mb_size++) = element;
        mb_dataPtr[mb_size++] = element;
    }

}



//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   Функция расширяет текущий массив с использованием данных из аргумента типа
//                  (my::Array<Type, size>)
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
template <typename Type>
template <int size>
void my::DynamicArray<Type>::extend(const my::Array<Type, size>& staticArr)
{
    // # Reallocate *this if not enough capacity for the extending with @staticArr
    int newSize {mb_size + staticArr.getSize()};
    if (newSize < mb_capacity) {
        this->reallocate(newSize + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Copy data from @staticArray to *this array
    for (const auto& element: staticArr) {
        // (mb_dataPtr + mb_size++) = element;        // Just an option
        mb_dataPtr[mb_size++] = element;
    }

}




//==================================================================================================
//          TYPE:   Copy assignment
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   Perhaps, there are some situations, where I should/shouldn't call delete[].
//                  For example, if this->mb_size == 100500 and dynArr->mb_size == 10, it is better
//                  to free the memory in the heap. Otherwise, I can reuse already allocated memory...
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>& my::DynamicArray<Type>::operator=(const my::DynamicArray<Type>& dynArr)
{
    // # Self-assignment checking
    if (this == &dynArr) {
        return *this;
    }
    else {} // Nothing to do

    // # Clear the content of *this array.
    delete[] mb_dataPtr;
    mb_dataPtr = nullptr;

    mb_capacity = dynArr.getCapacity();
    mb_capacityChunk = dynArr.getCapacityChunk();
    mb_size = dynArr.getSize();

    mb_dataPtr = static_cast<Type*>(mb_capacity);
    for (int ii {0}; ii < mb_size; ++ii) {
        *(mb_dataPtr + ii) = dynArr[ii];
    }

    return *this;
}


//==================================================================================================
//          TYPE:   Copy constructor
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   Такой вопрос. А нужно ли мне в данном случае выделять память в куче? Или же
//                  можно "украсть" указатель на данные из аргумента? Тут тогда такой вопрос
//                  возникает, а является ли аргумент "временным обектом"?
//                  Ещё вопрос, можно ли выделять память в куче не в фигурных скобках? Наверное,
//                  можно, но тогда придётся ловить исключения вне*.
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(const my::DynamicArray<Type>& dynArr):
    mb_size {dynArr.getSize()},
    mb_capacity {dynArr.getCapacity()},
    mb_capacityChunk {dynArr.getCapacityChunk()},
    mb_dataPtr {static_cast<Type*>(sizeof(Type) * mb_capacity)}
{
    for (int ii {0}; ii < mb_size; ++ii) {
        *(mb_dataPtr + ii) = dynArr[ii];
    }

}





