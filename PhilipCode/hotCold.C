#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TH1.h"

void mymacro() {
    std::vector<int> hottestDay;
    std::ifstream data {"hotCold-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;

    while (getline(data,helpstring)) {
        int warmday = std::stoi(helpstring.substr(0,helpstring.find(",")));
        hottestDay.push_back(warmday);
    }



    TH1D* myHist = new TH1D("myHist", "test histogram; counts; temp", 365,0,364);
    myHist->AddBinContent(5);
    /*for (int n = 0; n < static_cast<int>(hottestDay.size()); n++) {
        myHist->AddBinContent(n);
    }*/
    
    myHist->Draw();

    






}