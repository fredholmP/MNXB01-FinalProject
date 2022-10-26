#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include "TH1.h"
#include "TCanvas.h"

void cold() { 
    std::vector<int> coldestDay;
    std::ifstream data {"hotCold-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;


    while (getline(data,helpstring)) {
        int coldday = std::stoi(helpstring.substr(helpstring.find(",")+1));
        if (coldday >= 180) {
            coldday -= 365;
        }
        coldestDay.push_back(coldday);
    }


    TCanvas* c1 = new TCanvas("c1", "Canvas", 800,800);
    TH1D* coldhist = new TH1D("coldhist", "Coldest Day of the year; Day Number; Number of events", 400, -200, 200);
    for (int n = 0; n < static_cast<int>(coldestDay.size()); n++) {
        coldhist->AddBinContent(coldestDay[n]+200); //If the day is 0, this without +200 would add 1 to the -200 bin.

    }
    
    coldhist->Draw();

    






}