#include "../include/dataReader.h"
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
        std::cout << "hej" << std::endl;
        //std::getline(dataFile, helpString);
    }
    
    //Store the lines in lineStorage
    while (std::getline(dataFile, helpString)) {
        lineStorage.push_back(helpString);
    }
    
    //Separates the columns by ;
    int endLoc;
    std::string tempStorage;
    std::vector<std::vector<std::string>> columnStorage;

    //Creates a vector with nCols subvectors to store the columns
    for (int n = 0; n < nCols; n++) {
        std::vector<std::string> newVec;
        columnStorage.push_back(newVec);
    }

    for (std::string line : lineStorage) {
        for (int j = 0; j < nCols ; j++) {
            endLoc = line.find(";"); //Finds the next semicolon
            tempStorage = line.substr(0, endLoc); //Stores the things before it in a new variable.
            columnStorage[j].push_back(tempStorage); //Stores it to the relevant vector
            line = line.substr(endLoc+1); //Cuts off what was stored and the semicolon.
        }
    }
 

    //We now what to separate year, month and time into a column each.
    //Let's make a vector with 5 columns.
    std::vector<std::vector<std::string>> detailtedData;
    for (int n = 0; n < nCols+2; n++) {
        std::vector<std::string> tempVector;
        detailtedData.push_back(tempVector);
    }

    for (std::string yearLine : columnStorage[0]) {
        for (int j = 0; j < 3; j++) {
            endLoc = yearLine.find("-");
            tempStorage = yearLine.substr(0, endLoc);
            detailtedData[j].push_back(tempStorage);
            yearLine = yearLine.substr(endLoc+1);
        }
    }
    

    //Add the remaining columns from columnStorage.
    for (int n = 0; n < nCols-1; n++) {
        detailtedData[n+3] = columnStorage[n+1];
    }



    
    //Store the first and last year with entries as separate variables. Assumes that entries are in increasing order of year.
    std::vector<std::string> years = detailtedData[0];
    std::string stringYear = years[2];
    //int firstYear = std::stoi(stringYear); //It needs to be stoi and not std::stoi or it doesn't work 
    std::cout << stringYear << std::endl;
    //this->_firstYear  = firstYear;
    //this->_lastYear = detailtedData[0].back();

    //std::vector<std::vector<std::vector<std::vector<std::string>>>> mainData;


    //We know want a main vector containing a vector for each, which contains a vector
    //for each month, which each contains a vector for each day which contains the mean temperature.


    
    
    auto column = detailtedData[0];
    std::cout << column[0] << std::endl;
    //this->_mainVector = detailtedData;
    dataFile.close();



}


std::vector<std::vector<std::string>> readData::getAll() {
    return this->_mainVector;

}