#ifndef DATA_READER_FREDHOLM
#define DATA_READER_FREDHOLM

#include <iostream>
#include <string>
#include <vector>
#include <fstream>


class readData {
    public:
        readData(const std::string filename, const int skipLines = 0, const int nCols = 3);
        std::vector<std::vector<std::string>> getAll();



    private:
        const std::string _filename;
        int _firstYear;
        int _lastYear;
        std::vector<std::vector<std::string>> _mainVector;
};







#endif // DATA_READER_FREDHOLM