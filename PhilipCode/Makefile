CXX = g++
CXXVER = -std=c++17
CXXFLAGS = -Wall -Wextra -Werror $(CXXVER)
INCLUDES = -I ../localRoot/rootUbuntu20/INCLUDES #if on WSL, might not work on Aurora.


all : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o main main.cpp



.PHONY: all