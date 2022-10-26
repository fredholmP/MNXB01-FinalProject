#include "../include/dataReader.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <numeric>
#include <algorithm>


readData::readData(const std::string filename, const int skipLines, const int nCols)  {
    try {
        int index = filename.find_last_of("/");
        this->_filename = filename.substr(index+1); 
    } catch (...) {
        this->_filename = filename;
    }
    
    std::ifstream dataFile {filename};
    std::string helpString;
    std::vector<std::string> lineStorage;
    
    
    //Skip the first skipLines lines.
    for (int n = 0; n < skipLines; n++) {
        std::getline(dataFile, helpString);
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
    std::vector<std::vector<std::string>> detailedData;
    for (int n = 0; n < nCols+2; n++) {
        std::vector<std::string> tempVector;
        detailedData.push_back(tempVector);
    }

    for (std::string yearLine : columnStorage[0]) {
        for (int j = 0; j < 3; j++) {
            endLoc = yearLine.find("-");
            tempStorage = yearLine.substr(0, endLoc); //stods converts a string to an int
            detailedData[j].push_back(tempStorage);
            yearLine = yearLine.substr(endLoc+1);
        }
    }
    

    //Add the remaining columns from columnStorage.
    for (int n = 0; n < nCols-1; n++) {
        detailedData[n+3] = columnStorage[n+1];
    }



    
    //Store the first and last year with entries as separate variables. Assumes that entries are in increasing order of year.
    std::vector<int> years;
    for (auto i : detailedData[0]) {
        years.push_back(std::stoi(i));
    }
    int minyear = *std::min_element(years.begin(), years.end());
    int maxyear = *std::max_element(years.begin(), years.end());
    int firstYear = minyear; //stoi converts a string to an int detailedData[0][0]
    this->_firstYear = firstYear;
    this->_lastYear = maxyear;
    
    

    
    std::set<std::string> yearSet = {detailedData[0].begin(), detailedData[0].end()}; 
    int numberOfYears = static_cast<int>(yearSet.size());
    //Structure is Year-Month-Day-Temperature
    std::vector<std::vector<std::vector<std::vector<double>>>> mainData;
    for (int year = 0; year < numberOfYears; year++) {
        std::vector<std::vector<std::vector<double>>> newYear;
        mainData.push_back(newYear);
        for (int month = 0; month < 12; month++) {
            std::vector<std::vector<double>> newMonth;
            mainData[year].push_back(newMonth);
            for (int day = 0; day < 31; day++) {
                std::vector<double> newDay;
                mainData[year][month].push_back(newDay);
            }
        }
    }
    
    
    //Add all measurements for each day
    int numberOfElements = static_cast<int>(detailedData[0].size());
    for (int n = 0; n < numberOfElements; n++) {
        int year = std::stoi(detailedData[0][n]) - this->_firstYear; //Year 1 has index 0
        int month = std::stoi(detailedData[1][n]) -1 ; //Month 1 has index 0
        int day = std::stoi(detailedData[2][n]) - 1 ; //Day 1 has index 0

        double temperature = std::stod(detailedData[4][n]); //Stod converts a string to a double.
        //std::cout << year << "," << month << "," << day << "," << temperature << std::endl;
        
        mainData[year][month][day].push_back(temperature); 

    
    }
    //Take the average
    
    for (auto year : mainData) {
        for (auto month : year) {
            for (auto day : month) {
                double average = std::accumulate(day.begin(), day.end(), 0);
                average /= day.size();   
                day.clear();
                day.push_back(average);
            }
        }
    }

    this->_mainVector = mainData;
    


}


std::vector<std::vector<std::vector<std::vector<double>>>> readData::getData() {
    return this->_mainVector;
}

int readData::getFirstYear() {
    return this->_firstYear;
}

int readData::getLastYear() {
    return this->_lastYear;
}

std::string readData::getFilename() {
    return this->_filename;
}