CXX = g++
CXXVER = -std=c++17
CXXFLAGS = -Wall -Wextra -Werror $(CXXVER)
INCLUDEROOT = -I ../localRoot/rootUbuntu20/INCLUDES
INCLUDES = -I ./include -I external/include/fast-cpp-csv-parser -lpthread $(INCLUDEROOT)

all : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -o main main.cpp




hotCold : hotCold.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o hotCold hotCold.cpp


betaTest : include/dataReader.h src/dataReader.cpp testfile.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c src/dataReader.cpp -o src/dataReader.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o test src/dataReader.o testfile.cpp 
	



.PHONY: all