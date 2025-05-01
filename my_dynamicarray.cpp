#include "my_dynamicarray.h"


//==================================================================================================
//          TYPE:   Default constructor
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//   DESCRIPTION:   ........
//      COMMENTS:   Преимущество создания объекта на сырой памяти - это отсутствие ошибки выделения
//                  этой самой памяти (она уже есть). Но есть дальше сложность с созданием объектов
//                  кастомных классов на этой памяти.
//                  Как я понимаю, есть два пути создания объекта на сырой памяти (не обязательно
//                  выделенной в куче, можно и в стеке (а в BSS/Data сегментах?)):
//                  1) Использовать "placement new()", синтаксис такой:
//                      Type* ptr = new(rawMemoryPtr) Type();
//                      Кроме того, я должен ещё заботиться о должном выравнивании элементов класса
//                      в памяти. И ручками вызывать деструктор класса потом. Одна сплошная головная
//                      боль. Лучше использовать new operator сразу...
//                  2) Работать с сырой памятью в явном виде, то есть самому присваивать какие-то
//                      значения элементам из памяти. То есть если у нас есть класс Base и в нём
//                      имеется несколько переменных-членов класса, например int mb_a, double mb_b,
//                      то инициализировать эти переменные НЕ через конструктор, а в явном виде.
//                      Если мы ранее привели сырую память к указанному типу, то обращаться к элементам
//                      можно будет по именам, а не по адресам. Методы не влияют на размер класса,
//                      за исключением виртуальных функций (там есть доп. указатель на v_table) -
//                      возможно, это где-то может вылезти.
//
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray():
    mb_capacity {mb_capacityChunk},
    mb_size {0},
    mb_dataPtr {static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity))}
{
//    mb_output.debug("DEFAULT CONSTRUCTOR of the <DynamicArray> class has been called.");
//    std::cout << "[DEBUG]: DEFAULT CONSTRUCTOR of the <DynamicArray> class has been called." << std::endl;

    // # Конструирование объекта через 'placement new()' (но надо потом вызывать деструктор для типа
    // # в явном виде).
//    for (int ii {0}; ii < mb_capacity; ++ii) {
//        new(mb_dataPtr + ii) Type();
//    }

    // # 'Конструирование' (ака зануление) объекта ручками. Тут я вызываю специальный метод для этого
    // # дела (тогда придётся этот метод пихать во все мои классы), т.к. в классическом варианте
    // # используется конструктор класса
//    for (int ii {0}; ii < mb_capacity; ++ii) {
//        (mb_dataPtr + ii)->nullify();
//    }

    // # Зануление по-жёсткому
    this->nullify();

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
//    mb_output.debug("LIST-INITIALIZED CONSTRUCTOR of the <DynamicArray> class has been called.");
//    std::cout << "[DEBUG]: LIST-INITIALIZED CONSTRUCTOR of the <DynamicArray> class has been called." << std::endl;

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


    // # Зануление выделенной памяти
    this->nullify();

    // # Затем я как бы 'конструирую' на этой памяти объекты данного типа и копирую/перемещаю туда
    // # объекты из списка инициализации
    int ii {0};
    while (ii < listSize) {
        *(mb_dataPtr + ii) = list.begin()[ii];
        ++ii;
    }
    mb_size = ii;
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
    mb_dataPtr {static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity))}
{
    // # Зануление выделенной памяти
    this->nullify();

    for (int ii {0}; ii < mb_size; ++ii) {
        *(mb_dataPtr + ii) = dynArr[ii];
    }

}



//==================================================================================================
//          TYPE:   Destructor
//    PARAMETERS:   ........
//   DESCRIPTION:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Нужно в явном виде вызывать деструктор для типа, наверное. То есть я же создал
//                  память и сконструировал на ней объект ручками.
//
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::~DynamicArray()
{
//    mb_output.debug("DESTRUCTOR of the <DynamicArray> class has been called.");
//    std::cout << "[DEBUG]: DESTRUCTOR of the <DynamicArray> class has been called." << std::endl;

//    for (int ii {0}; ii < mb_capacity; ++ii) {
//        new(mb_dataPtr + ii) Type();
//    }

    // Не уверен, что здесь имеет смысл присваивать nullptr после освобождения памяти.
    operator delete[](mb_dataPtr);
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
// COMMENTS/BUGS:   Добавить обработку исключений при ошибке выделения памяти оператором new[].
//                  Кроме того, а может стоит передавать в качестве аргумента <const Type&>,
//                  а не передавать по значению...
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::pushBack(const Type& value)
{
    // # Сперва проверяем наличие свободной памяти (здесь можно вызывать и оператор[] наверное, но
    // # пока в явном виде)

    // # Случай, когда нужно выделить дополнительную память в куче (и скопировать туда содержимое
    // # "текущего" массива)
    if (mb_size == mb_capacity) {
        this->reallocate(mb_capacity + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Добавляем новый элемент в массив и увеличиваем его размер. Тут должна использоваться или
    // # move-семантика, или copy-семантика, в зависимости от того, предоставлена ли она классом <Type>.
    // # my::DynamicArray этим НЕ должен заниматься.
    *(mb_dataPtr + mb_size) = value;
    mb_size++;
}


//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   --------
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   For interchangeability with std::vector
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::push_back(const Type& value)
{
    this->pushBack(value);
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Тут проблема связанная с тем, что если элемента слева нет (есть только область
//                  памяти под него), то вызывать нужно не move-assignment, a move-constructor.
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::pushBack(Type&& value)
{

    if (mb_size == mb_capacity) {
        this->reallocate(mb_capacity + mb_capacityChunk);
    }
    else {} // Nothing to do

    // # Добавляем новый элемент в массив и увеличиваем его размер. Тут должна использоваться или
    // # move-семантика, или copy-семантика, в зависимости от того, предоставлена ли она классом <Type>.
    // # my::DynamicArray этим НЕ должен заниматься. Но он и не занимается, а просто рассматривает
    // # value согласно типу, который он принимает.
    *(mb_dataPtr + mb_size) = my::move(value);
    mb_size++;
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::push_back(Type&& value)
{
    this->pushBack(my::move(value));
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
//          TYPE:   ........
//   DESCRIPTION:   Set new capacity of the array and move data from old place into the new one
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
// COMMENTS/BUGS:   Здесь также нужно в явном виде вызывать оператор 'placement new()'
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::reallocate(int newCapacity)
{
    assert(newCapacity > mb_capacity && "New capacity must be higher than the old one");

    Type* newDataPtr = static_cast<Type*>(operator new[](sizeof(Type) * newCapacity));
    mb_capacity = newCapacity;

    /***********************************************************************************************
     * Добавить конструирование классов в каком-то виде на новой памяти, иначе возникнет ошибка
     * при работе с умными указателями и move-семантикой, когда те будут пытаться удалить старые
     * данные, которых нет в принципе.
     **********************************************************************************************/

    // # Перемещаем данные из старой области в новую, используя move-семантику
    for (int ii {0}; ii < mb_size; ++ii) {
        *(newDataPtr + ii) = my::move(*(mb_dataPtr + ii));
    }
    // ## Удаляем старые данные
    operator delete[] (mb_dataPtr);

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
// COMMENTS/BUGS:    For interchangeability with std::vector
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::size() const
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
//          TYPE:    Overloaded operator
//   DESCRIPTION:    Prints const *this array to <std::ostream&>
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
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
//          TYPE:    Overloaded operator
//   DESCRIPTION:    Prints non-const *this array to <std::ostream&>
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
std::ostream& my::operator<<(std::ostream& out, my::DynamicArray<Type>& dynArr)
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
const Type* my::DynamicArray<Type>::cbegin() const
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
const Type* my::DynamicArray<Type>::cend() const
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
template <int length>
void my::DynamicArray<Type>::extend(const my::Array<Type, length>& staticArr)
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
// COMMENTS/BUGS:   Perhaps, there are some situations, where I should/shouldn't call operator delete[].
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
    operator delete[] (mb_dataPtr);
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
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   @pos - position in *this object where is insertion of elements begin;
//                  @copyFrom - start position (in other object?), where is copying of elements starts (inclusive)
//                  @copyTo - end position (in OTHER object?), where is copying of elemets ends (exclusive)
//  RETURN VALUE:   ........
//      COMMENTS:   Простой вариант вставки с использованием указателей в качестве итераторов.
//                  Ещё вопрос, какой алгоритм использовать при вставке элементов внутрь массива.
//                  Пока сделаю в лоб, сперва сдвигаю на кол-во вставляемых эл-в, а там посмотрим.
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::insert(Type* pos, Type* copyFrom, Type* copyTo)
{
    assert (copyFrom <= copyTo && "ERROR, begin-adress should be less than the end-adress");

    // # Calculate number of elements for copying
    int copySize {0};
    for (Type* ptr {copyFrom}; ptr != copyTo; ++ptr) {
        ++copySize;
    }


    // # Check if the target (*this) can or can't fit new data (после реаллокации меняется фактический pos!)
    int newSize {mb_size + copySize};
    if (newSize > mb_capacity) {

        // ## Save @pos index, because @pos will change after reallocation
        int posIndex = static_cast<int>(pos - mb_dataPtr);
        this->reallocate(newSize + mb_capacityChunk);
        pos = &mb_dataPtr[posIndex];
    }
    else {} // Nothing to do



    // # Displace elements in *this array
    Type* thisEnd {this->end()};
    Type* thisLastElementAddr {thisEnd - 1};
    for (Type* last {thisLastElementAddr}; last >= pos; --last) {
        *(last + copySize) = *last;
    }


    // # Insert data from @copyFrom to @copyTo
    for (Type* ptr {copyFrom}; ptr != copyTo; ++ptr) {
        *pos = *ptr;
        ++pos;
    }

    // # Set new size
    mb_size = newSize;

}


//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Зануление выделенной памяти в стиле Си
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::nullify()
{
    char* singleByte = (char*) mb_dataPtr;
    for (int ii {0}; ii < sizeof(Type) * mb_capacity; ++ii) {
        *(singleByte + ii) = '\0';
    }

}



//==================================================================================================
//          TYPE:   --------
//    PARAMETERS:   --------
//   DESCRIPTION:   Функция смещает элементы массива, начиная с @position на @shift элементов вправо.
//                  Если для смещения не хватает места в массиве - будет выделена дополнительная
//                  память.
//  RETURN VALUE:   --------
// COMMENTS/BUGS:   --------
//==================================================================================================
//template <typename Type>
//void my::DynamicArray<Type>::displace(int position, int shift)
//{
//    // # Reallocate array to a new place
//    int newSize {mb_size + shift};
//    if (newSize > mb_capacity) {
//        this->reallocate(newSize + mb_capacityChunk);
//    }
//    else {} // Nothing to do

//    // # Displace elements
//    for (Type* ptr {this->end() - 1}; ptr >= &mb_dataPtr[position]; --ptr) {
//        *(ptr + shift) = *ptr;
//        ptr = nullptr;
//    }

//}





