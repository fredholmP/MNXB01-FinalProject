#include <iostream>
#include <string>
#include <vector>

#include "include/rootDataReader.h"
#include "TH1.h"

void mymacro() {
    readData myData = readData{"../WIPData/datasets/smhi-opendata_1_72450_20210926_100728_Boras.csv", 11, 3};
    TH1D* myHist = new TH1D("myHist", "test histogram; counts; temp", 100,0,40);
    
    for (auto month : (myData.getData())[0]) {
        for (auto day : month) {
                if (day.size() != 0) {
                    myHist->AddBinContent(day[0]);
                }     
         }
    }
    
    myHist->Draw();







}