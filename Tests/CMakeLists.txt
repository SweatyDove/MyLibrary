cmake_minimum_required(VERSION 3.5)

project(MyLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyLibrary
    ../Sources/my_array.cpp
    ../Sources/my_dynamicarray.cpp
    ../Sources/my_prettyprint.cpp
    ../Sources/my_smartptr.cpp
    ../Sources/my_string.cpp
    ../Sources/my_utilities.cpp
    ../Sources/my_exception.cpp

#    ../Sources/my_splitter.cpp
#    ../Sources/my_serialdevice.cpp

    ../Include/my_array.h
    ../Include/my_dynamicarray.h
    ../Include/Implementations/my_dynamicarray.hpp
    ../Include/my_prettyprint.h
    ../Include/my_smartptr.h
    ../Include/Implementations/my_smartptr.hpp
    ../Include/my_string.h
    ../Include/my_utilities.h
    ../Include/my_exception.h
    ../Include/my_splitter.h

#    test_exception.cpp
    test_general.cpp
    ../Sources/my_sort.cpp
    ../Include/my_sort.h
#    test_array.cpp
#    test_dynamicarray.cpp
#    test_smartptr.cpp
#    test_string.cpp
#    test_utilities.cpp
)

target_include_directories(MyLibrary PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../Include")

#target_link_libraries(MyLibrary "${CMAKE_CURRENT_SOURCE_DIR}/../Library/MyLib.a")

# Compiler optimization level
target_compile_options(MyLibrary PRIVATE -O0)



install(TARGETS MyLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
