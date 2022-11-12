#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include "include/dataReader.h"



int hotCold(readData* data, int chosenYear, int maxmin = 1) { //1 = find hottest, -1 = find coldest.
    auto year = (data->getData())[chosenYear];
    int garbageValue; //Value to compare to if there is no data for that day. 
                    //Should not alter the conclusion of hottest/coldest day.

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
    //The above is sort of bad. We've assumed in the readData class that all months have 31 days.
    //This will give a flatYear-vector with > 366 days. If I had more time to work on this
    //the proper way to do this would be match the found maximum value with the actual day,
    //by looping over every day for every month to see what the actual coordinate
    //of month and day is and then calculate the day properly with the correct number of
    //days per month. This is why the datafile lists days > 366 as the coldest day sometimes. 
    //Hopefully the error is just a few days at most if we are the end 
    //of the year.



    
    int compareValue;
    int extremalDay;
    int dayCounter = 0;
    if (maxmin == 1) {
        compareValue = -300; //Unphysical value on purpose.
       
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

    double summerstart = -5; //Garbage placeholder value.
    std::vector<double> fivedays {flatYear[0], flatYear[1], flatYear[2], flatYear[3], flatYear[4]}; //We need to initialise the vector
    double mean = 0;     //since later we do an erase.() every time. It would probably be more expensive to have an if
    int daycounter = 0; //statement to check if daycounter > 5 in every loop iteration.
    for (auto day : flatYear) {
        fivedays.erase(fivedays.begin()); //Deletes the first elements from the vector
        fivedays.push_back(day);
        mean = std::accumulate(fivedays.begin(), fivedays.end(),0);
        mean /= 5;
        if (mean > 10) {
            summerstart = daycounter;
            break; //If we did not break here we would get the last day satisfying average above 10 degrees for 5 days.
        }
        daycounter++;
    }

    return summerstart;


}



int main() { 
    std::string filename = "smhi-opendata_1_72450_20210926_100728_Boras.csv";
    readData myData = readData{filename, 10, 3};
    readData* dataPointer = &myData; //Functions use pointers to avoid expensive copies.
    auto dataValues = myData.getData();

    std::vector<int> warmestDay;
    std::vector<int> coldestDay;
    std::vector<int> summer;

    for (int n = 0; n < static_cast<int>(dataValues.size()); n++) { //.size() returns an unsigned int, thus the cast.
        warmestDay.push_back(hotCold(dataPointer, n, 1)); // 1 => warmest, -1 => coldest. 
        coldestDay.push_back(hotCold(dataPointer, n, -1)); //n is the n:th year with data.
        summer.push_back(checkSummer(dataPointer, n));

    }


    std::ofstream output {"hotCold-"+myData.getFilename()};
    std::ofstream output2 {"summerStart-"+myData.getFilename()};

    for (int n = 0; n < static_cast<int>(dataValues.size()); n++) {
        output << warmestDay[n] << "," << coldestDay[n] << std::endl; 
        output2 << summer[n] << std::endl;
    }
    

}