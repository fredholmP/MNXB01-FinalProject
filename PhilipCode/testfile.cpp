#include <iostream>
#include <string>
#include <vector>

#include "include/dataReader.h"
#include "TH1D.h"

int main() {
    readData mydata = readData{"../WIPData/datasets/smhi-opendata_1_72450_20210926_100728_Boras.csv", 11, 3};
}