#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TH1.h"
#include "TCanvas.h"

void summer() { 
    std::vector<int> summerstart;
    std::ifstream data {"summerStart-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;

    while (getline(data,helpstring)) {
        int summerday = std::stoi(helpstring);
        summerstart.push_back(summerday);
    }


    TCanvas* c1 = new TCanvas("c1", "Canvas", 800,800);
    TH1D* summerhist = new TH1D("warmhist", "The first day of summer; Day Number; Number of Events", 366,0,366);
    for (int n = 0; n < static_cast<int>(summerstart.size()); n++) {
        summerhist->AddBinContent(summerstart[n]);

    }
    
    summerhist->Draw();


    






}