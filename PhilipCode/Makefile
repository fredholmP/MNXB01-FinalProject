CXX = g++
CXXVER = -std=c++17
CXXFLAGS = -Wall -Wextra -Werror $(CXXVER)
INCLUDEROOT = -I ../localRoot/rootUbuntu20/INCLUDES
INCLUDES = -I external/include/fast-cpp-csv-parser -lpthread $(INCLUDEROOT)

all : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -o main main.cpp




hotCold : hotCold.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o hotCold hotCold.cpp

.PHONY: all