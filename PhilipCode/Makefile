CXX = g++
CXXVER = -std=c++17
CXXFLAGS = -Wall -Wextra -Werror $(CXXVER)
INCLUDEROOT = -I ../localRoot/rootUbuntu20/include -L ../localRoot/rootUbuntu20/libs
INCLUDES = -I ./include -lpthread $(INCLUDEROOT) 
extra= -L/home/fredholm/git/MNXB01-FinalProject/localRoot/rootUbuntu20/lib -lCore -lImt -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lROOTVecOps -lTree -lTreePlayer -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -lMultiProc -lROOTDataFrame -Wl,-rpath,/home/fredholm/git/MNXB01-FinalProject/localRoot/rootUbuntu20/lib -pthread -lm -ldl -rdynamic -pthread -std=c++14 -m64 -I/home/fredholm/git/MNXB01-FinalProject/localRoot/rootUbuntu20/include

all : main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES)  -o main main.cpp


hotCold : hotCold.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o hotCold hotCold.cpp


dataReader.o : include/dataReader.h src/dataReader.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c src/dataReader.cpp -o src/dataReader.o 

betaTest : src/dataReader.o main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o test src/dataReader.o main.cpp 
	
	


.PHONY: all