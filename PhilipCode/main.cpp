#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "include/rootDataReader.h"

int main() {

    readData myData = readData{"../WIPData/datasets/smhi-opendata_1_72450_20210926_100728_Boras.csv", 11, 3};
    std::cout << (myData.getData())[0][0][0][0] << std::endl;

    
}