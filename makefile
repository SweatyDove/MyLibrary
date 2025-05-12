# Compilator
CC=g++

# ARCHIVER
ARCH=ar

# ARCHIVER flags:
# -r    - insert into archive with replacement
# -v    - be verbose
# -s    - write an object-file index into the archive, or update an existing one
ARCHFLAGS= -r -v -s

# C++ COMPILATION flags:
# -std=+11 	- standart
# -pthread	- support multithreading
# -O0		- 0-level of Optimization
# -ggdb		- adding info for debugger (personally for GDB here)
# -c		- do not invoke linker, only compile
CXXFLAGS= -std=c++23 -O0 -ggdb -c

# LINKER flags:
# -pthread	- support multithreading
# -o		- place output in a specified file
LDFLAGS= -o

# External library
# WIRING_LIB= -L/root/WiringNP -lwiringPi

# List of object files
OBJECTS= my_array.o my_dynamicarray.o my_prettyprint.o my_smartptr.o my_string.o my_utilities.o

# Name of target program/library
TARGET= MyLib.a

# Directory for the library itself
TARGET_DIR= Library

# Directory for the objects files (*.o)
OBJECTS_DIR= Library

# Directory for headers (*.h) - it should be "included" when using library
INCLUDE_DIR= Include

# Directory for sources (*.cpp and *.hpp)
SOURCES_DIR= Sources








# List of names, which are not treated as files by make
.PHONY: clean all

all: $(TARGET)

# Here we gather all *.o files into library (*.a file) and then remove *.o files (in a future need to move *.o files in
# other directory)
$(TARGET): $(OBJECTS)
	$(ARCH) $(ARCHFLAGS) $(TARGET_DIR)/$(TARGET) $(OBJECTS)
	rm $(OBJECTS)
	
# Below we compile sources into objects
my_array.o: $(SOURCES_DIR)/my_array.cpp $(INCLUDE_DIR)/my_array.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_array.cpp -I $(INCLUDE_DIR)

my_dynamicarray.o: $(SOURCES_DIR)/my_dynamicarray.cpp $(INCLUDE_DIR)/my_dynamicarray.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_dynamicarray.cpp -I $(INCLUDE_DIR)

my_prettyprint.o: $(SOURCES_DIR)/my_prettyprint.cpp $(INCLUDE_DIR)/my_prettyprint.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_prettyprint.cpp -I $(INCLUDE_DIR)

my_smartptr.o: $(SOURCES_DIR)/my_smartptr.cpp $(INCLUDE_DIR)/my_smartptr.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_smartptr.cpp -I $(INCLUDE_DIR)
	
my_string.o: $(SOURCES_DIR)/my_string.cpp $(INCLUDE_DIR)/my_string.h $(INCLUDE_DIR)/my_utilities.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_string.cpp -I $(INCLUDE_DIR)

my_utilities.o: $(SOURCES_DIR)/my_utilities.cpp $(INCLUDE_DIR)/my_utilities.h
	$(CC) $(CXXFLAGS) $(SOURCES_DIR)/my_utilities.cpp -I $(INCLUDE_DIR)


# Recursively (-r) and without asking (-f) delete previous stuff
clean:
	rm -rf $(TARGET_DIR)/$(TARGET)

