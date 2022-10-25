#ifndef DATA_READER_FREDHOLM
#define DATA_READER_FREDHOLM

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <fstream>
#include <numeric>

/*Usage information
//Input: path to a filename/filename with measurements stored with increasing time
//Member variables: 
_firstYear : Contains the value of the first year of measurements.
_lastYear : Contains the value of the last year of measurements.
_filename : Contains the filename/path to file that was read

The getData() methods returns a vector with a subvector for each year of measurements.
Each subvector contains a subvector for each month of the year.
Each month-subvector contains a subvector for each day of the year
Each day-vector is a size = 1 vector with the average temperature of measurements made that day.

//Year->Month->Day->Average of measurements.
*/

class readData {
    public:       
        std::vector<std::vector<std::vector<std::vector<double>>>> getData() {
             return this->_mainVector;
        }

        int getFirstYear() {
            return this->_firstYear;
        }

        int getLastYear() {
            return this->_lastYear;
        }

        std::string getFilename()  {
            return this->_filename;
        }
        

        readData(const std::string filename, const int skipLines, const int nCols)  {
            this->_filename = filename;
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
            int firstYear = std::stoi(detailedData[0][0]); //stoi converts a string to an int
            this->_firstYear = firstYear;
            this->_lastYear = std::stoi((detailedData[0]).back());
            
            

            
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

                mainData[year][month][day].push_back(temperature);
                
            }
            //Take the average
            int elementcounter = 0;
            for (auto year : mainData) {
                for (auto month : year) {
                    for (auto day : month) {
                        std::cout << elementcounter << std::endl;
                        try {
                        if (day.size() > 0 ) {
                            double average = std::accumulate(day.begin(), day.end(), 0);
                            average /= day.size();
                            day.clear();
                            day.push_back(average);
                            elementcounter++;
                        } } catch(...) {std::cout << day[0] << std::endl;}
                    }
                }
            }

            
            this->_mainVector = mainData;

        }

    private:
        std::string _filename; // I would had liked to mark these three first as const, 
        int _firstYear; //but I couldn't figure out to initialise them when using a custom (non-list)
        int _lastYear; //constructor without getting an error about modifying consts.

        //Year/Month/Day/Value
        std::vector<std::vector<std::vector<std::vector<double>>>> _mainVector;
};













 


#endif // DATA_READER_FREDHOLM#include "../include/dataReader.h"
