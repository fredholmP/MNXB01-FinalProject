#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "include/rootDataReader.h"



int hotCold(readData* data, int chosenYear, int maxmin = 1) { //1 = find hottest, -1 = find coldest.
    auto year = (data->getData())[chosenYear];
    int garbageValue;

    //Checks if we are to find the hottest or coldest day.
    if (maxmin == 1) {
        garbageValue = -2000;
    } else if (maxmin == -1)  {
        garbageValue = 2000;
    } else {
        throw std::invalid_argument("The third argument should be 1 (find hottest) or -1 (find coldest)!");
    }

    //Creates a vector with 365 (or 366) entries;
    std::vector<double> flatYear;
    for (auto month : year) {
        for (auto day : month) {
            if (day.size() > 0 ) {
                flatYear.push_back(day[0]);
            } else {
                flatYear.push_back(garbageValue); //Garbage to show that data is missing for that day.
            }
        }
        
    }

    
    int compareValue;
    int extremalDay;
    int dayCounter = 0;
    if (maxmin == 1) {
        compareValue = -300; //Unphysical value un purpose.
       
        for (auto n : flatYear) {
            if (n > compareValue) {
              compareValue = n;
              extremalDay = dayCounter;
            }
             dayCounter++;
        }
    } else if (maxmin == -1) {
        compareValue = 300;

        for (auto n : flatYear) {
            if (n < compareValue) {
                compareValue = n;
                extremalDay = dayCounter;
            }
            dayCounter++;
        }  
    }

    return extremalDay;
}

int checkSummer(readData *data, int chosenYear) {
    auto year = (data->getData())[chosenYear];
    std::vector<double> flatYear;
    for (auto month : year) {
        for (auto day : month) {
            if (day.size() > 0 ) {
                flatYear.push_back(day[0]);
            } else {
                flatYear.push_back(-20000); //Garbage to show that data is missing for that day.
            }
        }
    }

    double summerstart = -5;
    std::vector<double> fivedays {flatYear[0], flatYear[1], flatYear[2], flatYear[3], flatYear[4]};
    double mean = 0;
    int daycounter = 0;
    for (auto day : flatYear) {
        fivedays.erase(fivedays.begin());
        fivedays.push_back(day);
        mean = std::accumulate(fivedays.begin(), fivedays.end(),0);
        mean /= 5;
        if (mean > 10) {
            summerstart = daycounter;
        }
        daycounter++;
    }
    
    return summerstart;




}






int main() { 
    std::string filename = "smhi-opendata_1_72450_20210926_100728_Boras.csv";
    readData myData = readData{filename, 15, 3};
    readData* dataPointer = &myData;
    auto dataValues = myData.getData();

    std::vector<int> warmestDay;
    std::vector<int> coldestDay;
    std::vector<int> summer;

    for (int n = 0; n < static_cast<int>(dataValues.size()); n++) {
        warmestDay.push_back(hotCold(dataPointer, n, 1));
        coldestDay.push_back(hotCold(dataPointer, n, -1));
        summer.push_back(checkSummer(dataPointer, n));

    }


    std::ofstream output {"hotCold-"+myData.getFilename()} ;
    std::ofstream output2 {"summerStart-"+myData.getFilename()};

    for (int n = 0; n < static_cast<int>(dataValues.size()); n++) {
        output << warmestDay[n] << "," << coldestDay[n] << std::endl; 
        output2 << summer[n] << std::endl;
    }
    
    
    


    

}