#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TH1.h"
#include "TCanvas.h"

void hot() { 
    std::vector<int> hottestDay;
    std::ifstream data {"hotCold-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;

    while (getline(data,helpstring)) {
        int warmday = std::stoi(helpstring.substr(0,helpstring.find(",")));
        hottestDay.push_back(warmday);
    }


    TCanvas* c1 = new TCanvas("c1", "Warmest Day of the Year", 800,800);
    TH1D* warmhist = new TH1D("warmhist", "test histogram; counts; temp", 366,0,366);
    for (int n = 0; n < static_cast<int>(hottestDay.size()); n++) {
        warmhist->AddBinContent(hottestDay[n]);


    }
    
    warmhist->Draw();

    






}