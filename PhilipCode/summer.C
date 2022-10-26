#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <algorithm>

#include "TH1.h"
#include "TCanvas.h"
#include "TLegend.h"

void summer() { 
    std::vector<int> summerstart;
    std::ifstream data {"summerStart-smhi-opendata_1_72450_20210926_100728_Boras.csv"};
    std::string helpstring;

    while (getline(data,helpstring)) {
        int summerday = std::stoi(helpstring);
        summerstart.push_back(summerday);
    }
    double meanSummerStart = std::accumulate(summerstart.begin(), summerstart.end(),0);
    meanSummerStart /= static_cast<double>(summerstart.size());




    TCanvas* c1 = new TCanvas("c1", "The First Day of Summer", 800,800);
    TH1D* summerhist = new TH1D("warmhist", "The First Day of Summer; Day of the Year; Number of Events", 366,0,366);
    for (int n = 0; n < static_cast<int>(summerstart.size()); n++) {
        summerhist->AddBinContent(summerstart[n]);

    }
    


    summerhist->SetLineColor(kGreen+1);
    summerhist->SetFillColor(kGreen+1);
    TLegend *leg = new TLegend(0.20, 0.75, 0.52, 0.92, "", "NDC");
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->AddEntry(summerhist, "The First Day of Summer","F");
    summerhist->Draw();
    leg->Draw();   
    std::cout << "The mean day for the start of summer is the " << meanSummerStart << ":th day." << std::endl;






}