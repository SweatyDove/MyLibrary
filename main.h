#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "my_array.hpp"
#include "my_string.h"

using StringClass = my::String;

template<typename Type, unsigned int size>
using ArrayClass = my::Array<Type, size>;

#include <string>
#include <array>

#endif
