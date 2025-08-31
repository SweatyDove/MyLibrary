/***************************************************************************************************
 * This file contains definitions for the TEMPLATED part of the <my::DynamicArray> class
 **************************************************************************************************/
#ifndef MY_DYNAMIC_ARRAY_HPP
#define MY_DYNAMIC_ARRAY_HPP

#include "../my_dynamicarray.h"            // For IDE visibility




//==================================================================================================
//          TYPE:   Default constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
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
//                      Боюсь, что работать с сырой памятью не получится, так как у оператора
//                      присваивания/перемещаения, которые в таком случае нужны, могут быть нетривиальные
//                      реализации, в зависимости от содержимого левого операнда - то есть я не могу
//                      просто взять и привести память к нужному мне типу, а потом инициализировать
//                      нулями - то есть могу, но это будет неверно, так как я не знаю, как
//                      инициализировать объект правильно. Но это знает конструктор объекта.
//
//                      В общем, как ни крути - нужно использовать конструктор в каком-то виде.
//
//==================================================================================================
template <typename Type>
//my::DynamicArray<Type>::DynamicArray() :  mb_capacity {mb_capacityChunk}          // Optional
my::DynamicArray<Type>::DynamicArray()
{
    //    mb_output.debug("DEFAULT CONSTRUCTOR of the <DynamicArray> class has been called.");
    //    std::cout << "[DEBUG]: DEFAULT CONSTRUCTOR of the <DynamicArray> class has been called." << std::endl;

    try {
        mb_capacity = mb_capacityChunk;
        mb_dataPtr = static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }


    // # 'Конструирование' (ака зануление) объекта ручками. Тут я вызываю специальный метод для этого
    // # дела (но тогда придётся этот метод пихать во все мои классы), т.к. в классическом варианте
    // # используется конструктор класса
    //    for (int ii {0}; ii < mb_capacity; ++ii) {
    //        (mb_dataPtr + ii)->nullify();
    //    }

    // # Зануление по-жёсткому
    this->nullify(0, mb_capacity);

    /***********************************************************************************************
     * А теперь предположим, что <Type> - это класс и его дефолтный конструктор инициализирует
     * члены класса НЕ НУЛЯМИ! То есть нужно всё равно вызывать placement new()... То есть конструктор
     * же для того и нужен, чтобы как-то инициализировать объект. И не всегда такая инициализация
     * тривиальна (ака зануление).
     *
     * Если я хочу инициализировать объект (память, которую привёл к типу данного объекта, т.е.
     * трактую её как 'объект'), возможно, я должен провести какие-то вычислительныые операции -
     * которые указаны, например, в теле конструктора. И как иначе это сделать, не вызывая тело
     * конструктора (функцию по сути). Вроде как для POD-типов можно что-то придумать, т.к. там
     * просто набор данных.
     *
     * Тогда пока остановлюсь на placement new().
     *
     * Или же можно установить требование, чтобы тип <Type> был копируемый - затем просто создавать
     * временный объект и копировать его содержимое в выделенную память. Или же не оставить память
     * инициализируемой нулями - и пока size() = 0, нам не важно, что там внутри вектора. А когда
     * захотим что-то поместить - просто это что-то скопируем.
     * Но опять же, если мы хотим СКОПИРОВАТЬ, то мы предполагаем, что слева объект УЖЕ имеется (
     * если речь идёт об operator=()). Но тут опять же - вдруг копирование нетривиально и
     * ведёт себя по разному в зависимости от каких-то значений слева. Поэтому, всё-равно нужно
     * вызывать конструктор - нельзя обойтись копированием НЕ для POD-типов.
     **********************************************************************************************/

    // # Конструирование объекта через 'placement new()' (но надо потом вызывать деструктор для типа
    // # в явном виде). То есть помимо освобождения памяти (через delete) вызвать предварительно
    // # на этой памяти ~Type().
//    for (int ii {0}; ii < mb_capacity; ++ii) {
//        new(mb_dataPtr + ii) Type();
//    }
}



//==================================================================================================
//          TYPE:   List-initialized constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   1) <std::initializer_list> doesn't have overloaded subscription operator "[]"
//                      -- that is why need to use initializer_list::begin() function.
//                  2) Добавить обработку исключений при ошибке выделения памяти оператором new[]
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(std::initializer_list<Type> list)
{
    //    mb_output.debug("LIST-INITIALIZED CONSTRUCTOR of the <DynamicArray> class has been called.");
    //    std::cout << "[DEBUG]: LIST-INITIALIZED CONSTRUCTOR of the <DynamicArray> class has been called." << std::endl;


    // # Allocation
    auto listSize = list.size();
    mb_capacity = listSize + mb_capacityChunk;

    try {
        mb_dataPtr = static_cast<Type*>(operator new[] (sizeof(Type) * mb_capacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }


    // # Initialization
    for (int ii {0}; ii < listSize; ++ii) {
        new(mb_dataPtr + ii) Type(list.begin()[ii]);          // Calls copy-constructor
    }
    mb_size = listSize;


    // # Nullify other allocated space (for convenience)
    this->nullify(mb_size, mb_capacity);

}




//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   Forms dynamic array of <Type> entities from <const char*>. For example - array
//                  of <int>.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Draft version
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(const char* string)
{
    // # Check the acceptable type
    assert(typeid(Type) == typeid(int) && "Construction of <my::DynamicArray> from <const char*> is possible only for <int> type.");

    // # Initialization/allocation
    mb_capacity = mb_capacityChunk;
    mb_size = 0;

    try {
        mb_dataPtr = static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }


    // # Nullification
    this->nullify(0, mb_capacity);



    // # Define lambdas (instead of usage C-style macros)
    auto isSpace {
        [](char ch) -> bool {return (ch == ' ' || ch == '\t' || ch == '\n');}
    };
    auto isDigit {
        [](char ch) -> bool { return (ch >= '0' && ch <= '9');}
    };



    // # Main loop, that walks through @string
    bool skipSpaces {true};
    int  curNumber  {0};

    for (const char* strPtr {string}; *strPtr != '\0'; ++strPtr) {

        char ch {*strPtr};

        // ## Handle invalid input
        if (!isSpace(ch) && !isDigit(ch)) {
            throw DynamicArrayException("Can't handle symbol, that is not digit or space.");
        }
        else {}


        // ## Skip leading spaces
        if ((skipSpaces == true) && isSpace(ch)) {
            continue;
        }
        else {
            skipSpaces = false;
        }


        // ## Read number or push number and set @skipSpaces flag to true
        if (isDigit(ch)) {
            curNumber = curNumber * 10 + (ch - '0');
        }
        else {
            this->pushBack(curNumber);
            curNumber = 0;
            skipSpaces = true;
        }

    }


    // # Handling the last value if it presents (otherwise @skipSpaces == true)
    if (skipSpaces == false) {
        this->pushBack(curNumber);
    }
    else {}



}




//==================================================================================================
//          TYPE:   Copy constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Такой вопрос. А нужно ли мне в данном случае выделять память в куче? Или же
//                  можно "украсть" указатель на данные из аргумента? Тут тогда такой вопрос
//                  возникает, а является ли аргумент "временным обектом"? Если l-value reference,
//                  то это идентифицируемый объект, значит нельзя 'воровать'... Для воровства создан
//                  move-constructor.
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(const my::DynamicArray<Type>& that) :
    mb_capacityChunk {that.getCapacityChunk()},
    mb_capacity {that.getCapacity()},
    mb_size {that.getSize()}
{

    // # Allocation
    try {
        mb_dataPtr = static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }

    // # Нельзя использовать оператор присваивания, т.к. слева у меня НЕТ объекта, а есть сырая
    // # память, приведённая к нужному типу, а этого может быть недостаточно для корректного присваивания.
    for (int ii {0}; ii < mb_size; ++ii) {
        new(mb_dataPtr + ii) Type(that[ii]);
    }


    // # For convenience
    this->nullify(mb_size, mb_capacity);

}



//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   DIRECT-INITIALIZED constructor, that initializes dynamic array
//                  of @size default-initialized elements of type <Type>.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::DynamicArray(int size) :
    mb_capacity {size + mb_capacityChunk},
    mb_size {size}
{

    // # Allocation
    try {
        mb_dataPtr = static_cast<Type*>(operator new[](sizeof(Type) * mb_capacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }

    // # Default-initialization
    for (int ii {0}; ii < mb_size; ++ii) {
        new(mb_dataPtr + ii) Type();
    }

    // # Nullification (for convenience)
    this->nullify(mb_size, mb_capacity);

}




//==================================================================================================
//          TYPE:   Destructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::~DynamicArray()
{
    //    mb_output.debug("DESTRUCTOR of the <DynamicArray> class has been called.");
    //    std::cout << "[DEBUG]: DESTRUCTOR of the <DynamicArray> class has been called." << std::endl;

    // # Explicitly call destructor on memory before realizing it
    for (int ii {0}; ii < mb_size; ++ii) {
        (mb_dataPtr + ii)->~Type();
    }

    // Не уверен, что здесь имеет смысл присваивать nullptr после освобождения памяти.
    operator delete[](mb_dataPtr);
    mb_dataPtr = nullptr;

}





//==================================================================================================
//          TYPE:   Public member function
//   DESCRIPTION:   Set new capacity of the array and move data from old place into the new one
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::reallocate(int newCapacity)
{
    assert(newCapacity > mb_capacity && "New capacity must be higher than the old one");



    // # Allocation
    Type* newDataPtr {nullptr};
    try {
        newDataPtr = static_cast<Type*>(operator new[](sizeof(Type) * newCapacity));
    }
    catch (const std::bad_alloc& exception) {
        std::cout << exception.what();
        throw my::DynamicArrayException("Couldn't allocate memory in the heap!");
    }


    // # Move old data to the new place
    for (int ii {0}; ii < mb_size; ++ii) {
        new(newDataPtr + ii) Type(my::move(*(mb_dataPtr + ii)));
    }


    // # Explicitly calls destructor in old place
    for (int ii {0}; ii < mb_capacity; ++ii) {
        (mb_dataPtr + ii)->~Type();
    }


    // # Updating
    operator delete[] (mb_dataPtr);
    mb_dataPtr = newDataPtr;
    mb_capacity = newCapacity;


    // # Nullification
    this->nullify(mb_size, mb_capacity);
}





//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Overloaded subscription operator that returns "const reference" (aka "reference
//                  to const")
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Think about adding an option to iterate array in reverse order via [-1; -mb_size]
//==================================================================================================
template <typename Type>
const Type& my::DynamicArray<Type>::operator[](int ii) const
{
    if (ii < 0 || ii >= mb_size) {
        throw my::DynamicArrayException {"The index out of range."};
    }
    else {}

    return *(mb_dataPtr + ii);

}

//==================================================================================================
//          TYPE:   Method
//   DESCRIPTION:   Overloaded subscription operator that returns reference to specified element
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
Type& my::DynamicArray<Type>::operator[](int ii)
{
    if (ii < 0 || ii >= mb_size) {
        throw my::DynamicArrayException {"The index out of range."};
    }
    else {}

    return *(mb_dataPtr + ii);
}



//==================================================================================================
//          TYPE:   Public member function (overloaded operator)
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
bool my::DynamicArray<Type>::operator==(const my::DynamicArray<Type>& that) const
{
//    assert(false && "Do not release yet.");
    return true;
}



//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   ........
//    PARAMETERS:   Add a new element at the end of the array, using COPY-semantic
//  RETURN VALUE:   ........
//      COMMENTS:   ........
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

    // # Добавляем новый элемент в массив и увеличиваем его размер.
    new(mb_dataPtr + mb_size) Type(value);
    mb_size++;
}


//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Add a new element at the end of the array, using COPY-semantic
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   For interchangeability with std::vector
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::push_back(const Type& value)
{
    this->pushBack(value);
}



//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Add a new element at the end of the array, using MOVE-semantic
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
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
    new(mb_dataPtr + mb_size) Type(my::move(value));
    mb_size++;
}



//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Add a new element at the end of the array, using MOVE-semantic
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::push_back(Type&& value)
{
    this->pushBack(my::move(value));
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   What should I do with the extracted element? Should I pop it via
//                  reference? - NOPE, cause the memory, where it is storing can be rewrited by the
//                  *this object.
//==================================================================================================
template <typename Type>
Type my::DynamicArray<Type>::popBack()
{
    assert(mb_size > 0 && "Can't extract element from the empty array. Abort.");

    return mb_dataPtr[--mb_size];
}







//==================================================================================================
//          TYPE:    Member function
//   DESCRIPTION:    ........
//    PARAMETERS:    Returns size of the array
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::getSize() const
{
    return mb_size;
}


//==================================================================================================
//          TYPE:    Getter
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    For interchangeability with std::vector
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::size() const
{
    return mb_size;
}


//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    Resize @this object via explicitly calling default constructor Type() on memory
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::resize(int newSize)
{
    if (newSize < mb_size) {
        assert(false && "Do not release yet.");
    }
    else if (newSize == mb_size) {
        return;
    }
    else {

        // # Reallocation
        if (newSize > mb_capacity) {
            this->reallocate(newSize + mb_capacityChunk);
        }
        else {}

        // # Call default constructor
        for (int ii {mb_size}; ii < newSize; ++ii) {
            new(mb_dataPtr + ii) Type();
        }
        mb_size = newSize;
    }

}


//==================================================================================================
//          TYPE:    Getter
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
int my::DynamicArray<Type>::getCapacity() const
{
    return mb_capacity;
}

//==================================================================================================
//          TYPE:    Getter
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
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
    const my::DynamicArray<Type>& arr {dynArr};
    out << arr;
    return out;
    //    out << '[';

    //    int ii {0};
    //    while (ii < dynArr.getSize() - 1) {
    //        out << dynArr[ii] << ", ";
    //        ++ii;
    //    }
    //    out << dynArr[ii] << ']';

    //    return out;
}




//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
const Type* my::DynamicArray<Type>::cbegin() const
{
    return mb_dataPtr;
}


//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
Type* my::DynamicArray<Type>::begin()
{
    return mb_dataPtr;
}



//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
Type* my::DynamicArray<Type>::end()
{
    return (mb_dataPtr + mb_size);
}



//==================================================================================================
//          TYPE:    ........
//   DESCRIPTION:    ........
//    PARAMETERS:    ........
//  RETURN VALUE:    ........
//      COMMENTS:    ........
//==================================================================================================
template <typename Type>
const Type* my::DynamicArray<Type>::cend() const
{
    return (mb_dataPtr + mb_size);
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Функция расширяет текущий массив с использованием данных из аргумента такого же
//                  типа (my::DynamicArray<Type>). Используется copy-семантика.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Возможно, стоит добавить аналог для move-семантики.
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::extend(const my::DynamicArray<Type>& that)
{
    int newSize {mb_size + that.getSize()};

    // # Если массив может вместить данные из другого массива, то просто расширяем его. Хотя, можно,
    // # наверное и не расширять, т.к. он автоматически расширится при копировании (если я
    // # предоставлю соответствующий оператор).
    if (mb_capacity < newSize) {
        this->reallocate(newSize + mb_capacityChunk);
    }
    else {}


    // # Copy-construction of elements from rh-operand on @this object
    for (auto& element: that) {
        new(mb_dataPtr + mb_size) Type(element);
        ++mb_size;
    }

}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Функция расширяет текущий массив с использованием данных из аргумента типа
//                  (my::Array<Type, size>)
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
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
    else {}

    // # Copy-construct data from @staticArray on @this array
    for (const auto& element: staticArr) {
        new(mb_dataPtr + mb_size) Type(element);
        mb_size++;
    }

}




//==================================================================================================
//          TYPE:   Copy assignment
//   DESCRIPTION:   ........
//    PARAMETERS:   Clear @this array and copy data from @that in it.
//  RETURN VALUE:   ........
//      COMMENTS:   Perhaps, there are some situations, where I should/shouldn't call operator delete[].
//                  For example, if this->mb_size == 100500 and that->mb_size == 10, it is better
//                  to free the memory in the heap. Otherwise, I can reuse already allocated memory...
//
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>& my::DynamicArray<Type>::operator=(const my::DynamicArray<Type>& that)
{
    // # Self-assignment checking
    if (this == &that) {
        return *this;
    }
    else {} // Nothing to do


    /* Что нужно сделать?
     * Я хочу скопировать то, что справа туда, что слева. То есть и слева и справа ЕСТЬ массивы.
     * Должен ли я очистить предварительно то, что слева? Или же поверх этого присваивать? То есть
     * вдруг для присваивания важно содержимое соответствующего аргумента слева - но тогда это неочевидное
     * присваивание. Например:
     *
     * Type& operator=(const Type& that)
     *  {
     *      this->mb_a = (this->mb_a > 0) ? (that->mb_a) : -(that->mb_a);
     *  }
     *
     *  В примере выше подразумевается, что есть какое-то значение слева и в зависимости от этого
     *  значения выполняется присваивание. Но тут именно специфичное поведение для конкретного типа.
     *  Ок, значит, если данные есть - вызываем оператор копирования. Если данных нет,
     *  то конструктор копирования. Если копируемых данных меньше, то то, что есть - не трогаем,
     *  а просто переписываем только то, что есть.
     *
     *
     */

    // # Should I copy mb_capacityChunk?
    assert(mb_capacityChunk == that.mb_capacityChunk && "Do not release yet.");


    // # Reallocation to fit all data from @that
    if (mb_capacity < that.mb_size) {
        this->reallocate(that.mb_size + mb_capacityChunk);
    }
    else {}

    // # Copy-assignment
    int ii {0};     // @this index
    int jj {0};     // @that index

    while (ii < mb_size && jj < that.mb_size) {
        *(mb_dataPtr + ii) = *(that.mb_dataPtr + jj);
        ++ii;
        ++jj;
    }

    // # Reach end of @this array
    if (ii == mb_size) {

        // # Copy-construction (via placement new())
        while (jj < that.mb_size) {
            new(mb_dataPtr + ii) Type(*(mb_dataPtr + jj));
            ++ii;
            ++jj;
        }
        mb_size = that.mb_size;
    }
    else {}

    return *this;
}



//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   @pos - position in @this object where is insertion of elements begin;
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

    // # Calculate number of elements to copy
    int copySize {0};
    for (Type* ptr {copyFrom}; ptr != copyTo; ++ptr) {
        ++copySize;
    }


    // # Check if the target (*this) can or can't fit new data. Be aware that after the reallocation
    // # @pos will change!
    int newSize {mb_size + copySize};
    if (newSize > mb_capacity) {

        // ## Save @pos index, because @pos will change after reallocation
        int posIndex = static_cast<int>(pos - mb_dataPtr);
        this->reallocate(newSize + mb_capacityChunk);
        pos = &mb_dataPtr[posIndex];
    }
    else {}


    // # Displace elements in *this array (on @copySize positions to the right)
    /*
     * Остановился здесь - тут нужно посмотреть, что происходит после перемещения элементов вправо -
     * то есть что мне делать с освободившимся местом? Вызывать деструктор?
     */
    Type* thisEnd {this->end()};
    Type* thisLastElementAddr {thisEnd - 1};
    for (Type* last {thisLastElementAddr}; last >= pos; --last) {
        new(last + copySize) Type(my::move(*last));
        /* Вопрос: а что происходит с местом, ОТКУДА произошло перемещение? Остаётся ли там объект?
         * Но ведь я перемещаю не переменную (что, по сути, псевдоним для какого-то места в памяти),
         * а перемещаю её содержимое, оставляя переменную потенциально с неопределённым значением
         * (в зависимости от реализации оператора перемещения).
         *
         * Ок, тогда, наверное, стоит вызывать деструктор, так как мне нужна память в данном случае
         * и я предполагаю, что с этой памяти всё было перемещенно вправо
         */
        last->~Type();
    }


    // # Insert data from @copyFrom to @copyTo via calling copy-constructor
    for (Type* ptr {copyFrom}; ptr != copyTo; ++ptr) {
        new(pos) Type(*ptr);
        ++pos;
    }

    // # Set new size
    mb_size = newSize;

}


//==================================================================================================
//          TYPE:   Member function
//   DESCRIPTION:   Nullifying allocated, but not initialized memory (for convenience purpose).
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Perhaps, I can replace it with std::memset()
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::nullify(int start, int end)
{
    start *= sizeof(Type);
    end *= sizeof(Type);

    char* singleByte = (char*) mb_dataPtr;


    for (int ii {start}; ii < end; ++ii) {
        *(singleByte + ii) = '\0';
    }

}

//==================================================================================================
//          TYPE:   Public member function
//   DESCRIPTION:   Clears the array: calls destructors for each element, then nullify allocated
//                  memory and set @mb_size to zero.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
void my::DynamicArray<Type>::clear()
{
    // # Explicitly calls destructor
    for (int ii {0}; ii < mb_size; ++ii) {
        (mb_dataPtr + ii)->~Type();
    }

    // # Nullification
    this->nullify(0, mb_size);

    mb_size = 0;
}




//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   Функция смещает элементы массива, начиная с @position на @shift элементов вправо.
//                  Если для смещения не хватает места в массиве - будет выделена дополнительная
//                  память.
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
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




//==================================================================================================
//          TYPE:   Default Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   FORWARD: 	default-constructible
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator::Iterator() :
    mb_ptr {nullptr}
{
    // Nothing to do
}




//==================================================================================================
//          TYPE:   Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator::Iterator(Type* ptr) :
    mb_ptr {ptr}
{
    // Nothing to do
}



//==================================================================================================
//          TYPE:   Copy Constructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator::Iterator(const Iterator& that)
{
    this->mb_ptr = that.mb_ptr;
}


//==================================================================================================
//          TYPE:   Destructor
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   ........
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator::~Iterator()
{
    // Nothing to do
}


//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Copy assignment
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   INPUT
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator&   my::DynamicArray<Type>::Iterator::operator=(const Iterator& that)
{
    if (this != &that) {
        this->mb_ptr = that.mb_ptr;
    }
    else {} // Nothing to do


    return *this;

}


//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Prefix increment
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Can be incremented
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator&   my::DynamicArray<Type>::Iterator::operator++()
{
    ++mb_ptr;
    return *this;
}





//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Postfix increment
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Can be incremented
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator   my::DynamicArray<Type>::Iterator::operator++(Type)
{
    my::DynamicArray<Type>::Iterator temp {*this};

    // # Calls prefix version
    ++(*this);

    return temp;
}



//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Prefix decrement
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   BIDIRECTIONAL
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator&   my::DynamicArray<Type>::Iterator::operator--()
{
    --mb_ptr;
    return *this;
}


//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Postfix decrement
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   BIDIRECTIONAL
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator   my::DynamicArray<Type>::Iterator::operator--(Type)
{
    my::DynamicArray<Type>::Iterator temp {*this};

    // # Calls prefix version
    --(*this);

    return temp;

}





//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Supports equality comparisons
//==================================================================================================
template <typename Type>
bool operator==(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return a.mb_ptr == b.mb_ptr;
}



//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Supports inequality comparisons
//==================================================================================================
template <typename Type>
bool operator!=(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return !(a == b);
}



//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Dereference operator
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   Здесь в зависимости от того, что можно делать с итератором. Только читать (INPUT)
//                  или же читать и писать (OUTPUT).
//                  INPUT:  Can be dereferenced as an rvalue - то есть только чтение
//                  OUTPUT: Can be dereferenced as an lvalue (only for mutable iterator types)
//                  Реализация ниже поддерживает обе операции, т.к. можно как читать из массива, так
//                  и писать в него (если там mutable-data, то есть без модификатора const или т.п.)
//==================================================================================================
template <typename Type>
Type& my::DynamicArray<Type>::Iterator::operator*() const
{
    return *mb_ptr;
}


//==================================================================================================
//          TYPE:   ........
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   INPUT:  Can be dereferenced as an rvalue
//==================================================================================================
template <typename Type>
Type* my::DynamicArray<Type>::Iterator::operator->()
{
    return mb_ptr;
}


//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
typename my::DynamicArray<Type>::Iterator operator+(typename my::DynamicArray<Type>::Iterator& a, int n)
{
    /*
     * Увеличиваем значение указателя a.mb_ptr на n - в результате, в зависимости от типа mb_ptr,
     * новый адрес будет корректен (так как под капотом там такой же перегруженный оператор и, если
     * mb_ptr имеет тип <int*>, то сдвиг будет, условно, на sizeof(int) * n, а если <float*>, то,
     * соответственно, на sizeof(float) * n). И здесь нужно реализовать такую же логику, но не для
     * <int> или <float>, а для <Iterator>.
     *
     * Затем создаём временный объект и возвращаем его - вернее, возвращаем просто указатель, над
     * которым будет неявно создан объект на выходе.
     */
    return (a.mb_ptr + n);

}


//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
//template <typename Type>
//my::DynamicArray<Type>::Iterator operator+(int n, const typename my::DynamicArray<Type>::Iterator& a)
//{
//    return (a + n);
//}


//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator operator-(const typename my::DynamicArray<Type>::Iterator& a, int n)
{
    return (a.mb_ptr - n);
}

//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator::difference_type   operator-(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return (a.mb_ptr - b.mb_ptr);
}


//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
bool operator<(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return (a.mb_ptr < b.mb_ptr);
}



//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
bool operator>(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return !(a < b) && !(a == b);
}




//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
bool operator>=(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return !(a < b);
}


//==================================================================================================
//          TYPE:   Friend function
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
bool operator<=(const typename my::DynamicArray<Type>::Iterator& a, const typename my::DynamicArray<Type>::Iterator& b)
{
    return (a < b) || (a == b);
}


//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator&   my::DynamicArray<Type>::Iterator::operator+=(int n)
{
    mb_ptr += n;
    return (*this);

}


//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   ........
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
my::DynamicArray<Type>::Iterator&   my::DynamicArray<Type>::Iterator::operator-=(int n)
{
    mb_ptr -= n;
    return (*this);
}



//==================================================================================================
//          TYPE:   Overloaded operator
//   DESCRIPTION:   Subscript operator
//    PARAMETERS:   ........
//  RETURN VALUE:   ........
//      COMMENTS:   RANDOM ACCESS
//==================================================================================================
template <typename Type>
Type& my::DynamicArray<Type>::Iterator::operator[](int index)
{
    return *(mb_ptr + index);
}


#endif
