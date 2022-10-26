CXX = g++
CXXVER = -std=c++17
CXXFLAGS = -Wall -Wextra -Werror $(CXXVER)
INCLUDES = -I ./include -lpthread 

all : src/dataReader.o main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -o main main.cpp src/dataReader.o


dataReader.o : include/dataReader.h src/dataReader.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c include/dataReader.h src/dataReader.cpp -o src/dataReader.o 

test : test.cpp src/dataReader.o
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -o test test.cpp src/dataReader.o


.PHONY: all