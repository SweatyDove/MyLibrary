cmake_minimum_required(VERSION 3.5)

project(MyLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyLibrary
    main.cpp main.h
    my_string.cpp my_string.h
    my_string.hpp
#    my_log.cpp my_log.h
    my_utilities.cpp my_utilities.h
#    my_queue.hpp
#    smartptr.h smartptr.cpp
my_array.cpp my_array.h my_array.hpp
)


install(TARGETS MyLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
