#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

void hot() { 
    std::vector<int> hottestDay;
    std::ifstream data {"hotCold-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;

    while (getline(data,helpstring)) {
        int warmday = std::stoi(helpstring.substr(0,helpstring.find(",")));
        hottestDay.push_back(warmday);
    }

    double meanWarmDay = std::accumulate(hottestDay.begin(), hottestDay.end(),0);
    meanWarmDay /= static_cast<double>(hottestDay.size());


    TCanvas* c1 = new TCanvas("c1", "Warmest Day of the Year", 800,800);
    //Bin 0 is the underflow, and the final one is the overflow. For 366 days we thus need 368 bins.
    TH1D* warmhist = new TH1D("warmhist", "Warmest Day of the Year; Day of the Year; Number of Events", 368,0,366);
    for (int n = 0; n < static_cast<int>(hottestDay.size()); n++) {
        warmhist->AddBinContent(hottestDay[n]+2); //+1 for the overflow bin and +1 for that day 1 has index 0.


    }
    warmhist->SetLineColor(kRed+1);
    warmhist->SetFillColor(kRed+1);
    TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->AddEntry(warmhist, "Warmest Day of the Year","F");
    warmhist->Draw();
    leg->Draw();    

    std::cout << "The warmest day is (on average) " << meanWarmDay << "." << std::endl; 
    //If I wasn't so short on time a Gaussian fit would be better (and give me a standard deviation.)

}