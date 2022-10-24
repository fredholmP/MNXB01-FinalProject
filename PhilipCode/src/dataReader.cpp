#include "dataReader.h"
#include "csv.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>



readData::readData(const std::string filename, const int skipLines, const int nCols) {
    std::ifstream dataFile {filename};
    std::string helpString;
    std::vector<std::string> lineStorage;
    
    
    //Skip the first skipLines lines.
    for (int n; n < skipLines; n++) {
        std::getline(dataFile, helpString);
    }
    //Store the lines in lineStorage
    while (std::getline(dataFile, helpString)) {
        lineStorage.push_back(helpString);
    }
    
    //Separates the columns by ;
    int startLoc = 0;
    int endLoc;
    std::string tempStorage;
    std::vector<std::vector<std::string>> columnStorage;

    //Creates a vector with nCols subvectors to store the columns
    for (int n = 0; n < nCols; n++) {
        std::vector<std::string> newVec;
        columnStorage.push_back(newVec);
    }
    std::cout << lineStorage.size() << std::endl;
    std::cout << columnStorage.size() << std::endl;
    for (std::string line : lineStorage) {
        for (int j = 0; j < nCols ; j++) {
            //std::cout << j << std::endl;
            try{endLoc = line.find(";");
            tempStorage = line.substr(startLoc, endLoc);} catch(...){std::cout << line << std::endl;}
            columnStorage[j].push_back(tempStorage);


            try {line = line.substr(endLoc+1);} catch(...) {continue;}
            //std::cout << line << std::endl;
            startLoc = endLoc;
        }
    }
 
    auto column = columnStorage[1];
    std::cout << std::endl;
    std::cout << column[0] << std::endl;
    this->_mainVector = columnStorage;
    dataFile.close();



}


std::vector<std::vector<std::string>> readData::getAll() {
    return this->_mainVector;

}