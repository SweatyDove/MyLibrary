cmake_minimum_required(VERSION 3.5)

project(MyLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MyLibrary
    main.cpp
    my_smartptr.cpp my_smartptr.h my_smartptr.hpp
    my_prettyprint.cpp my_prettyprint.h
    my_dynamicarray.cpp my_dynamicarray.h
    my_string.cpp my_string.h
#    my_log.cpp my_log.h
    my_utilities.cpp my_utilities.h my_utilities.hpp
#    my_queue.hpp
    my_array.cpp my_array.h my_array.hpp
)


install(TARGETS MyLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
