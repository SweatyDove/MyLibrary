cmake_minimum_required(VERSION 3.5)

project(MyLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyLibrary test_general.cpp
    ../Sources/my_array.cpp
    ../Sources/my_dynamicarray.cpp
    ../Sources/my_prettyprint.cpp
    ../Sources/my_smartptr.cpp
    ../Sources/my_string.cpp
    ../Sources/my_utilities.cpp
#    my_string.cpp my_string.h
#    my_smartptr.cpp my_smartptr.h my_smartptr.hpp
#    my_array.cpp my_array.h my_array.hpp
#    my_dynamicarray.cpp my_dynamicarray.h my_dynamicarray.hpp
#    my_utilities.cpp my_utilities.h my_utilities.hpp
#    my_prettyprint.cpp my_prettyprint.h
#    my_log.cpp my_log.h
#    my_queue.hpp

#    test_array.cpp
#    test_dynamicarray.cpp
#    test_smartptr.cpp
#    test_string.cpp
#    test_utilities.cpp
)

target_include_directories(MyLibrary PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../Include")

#target_link_libraries(MyLibrary "${CMAKE_CURRENT_SOURCE_DIR}/../Library/MyLib.a")


install(TARGETS MyLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
