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
        readData(const std::string filename, const int skipLines = 0, const int nCols = 3);
        std::vector<std::vector<std::vector<std::vector<double>>>> getData();
        int getFirstYear();
        int getLastYear();
        std::string getFilename();



    private:
        std::string _filename; // I would had liked to mark these three first as const, 
        int _firstYear; //but I couldn't figure out to initialise them when using a custom (non-list)
        int _lastYear; //constructor without getting an error about modifying consts.

        //Year/Month/Day/Value
        std::vector<std::vector<std::vector<std::vector<double>>>> _mainVector;
};







#endif // DATA_READER_FREDHOLM