#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

void cold() { 
    std::vector<int> coldestDay;
    std::ifstream data {"hotCold-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;


    while (getline(data,helpstring)) {
        int coldday = std::stoi(helpstring.substr(helpstring.find(",")+1));
        if (coldday >= 180) { //180 is fine since the coldest day is probably not in June.
            coldday -= 365; //Shifts as back to negative values to have a continous histogram.
        }
        coldestDay.push_back(coldday);
    }

    double meanColdDay = std::accumulate(coldestDay.begin(), coldestDay.end(),0);
    meanColdDay /= static_cast<double>(coldestDay.size());



    TCanvas* c1 = new TCanvas("c1", "Coldest Day of the Year", 800,800);
    //One overflow bin and one overflow bin => 402 bins is effectively 400 bins.
    TH1D* coldhist = new TH1D("coldhist", "Coldest Day of the Year; Day of the Year; Number of Events", 402, -200, 199);
    for (int n = 0; n < static_cast<int>(coldestDay.size()); n++) {
        coldhist->AddBinContent(coldestDay[n]+202); //+1 for the underflow bin, +1 since day 1 has index 0 and +200
                                                    //to compensate for the shift of -200.

    }
    

    coldhist->SetLineColor(kBlue+1);
    coldhist->SetFillColor(kBlue+1);
    TLegend *leg = new TLegend(0.65, 0.75, 0.92, 0.92, "", "NDC");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->AddEntry(coldhist, "Coldest Day of the Year","F");
    coldhist->Draw();
    leg->Draw();    

    std::cout << "The coldest day is (on average) " << meanColdDay << "." << std::endl; 
    //If I wasn't so short on time a Gaussian fit would be better (and give me a standard deviation.)



}