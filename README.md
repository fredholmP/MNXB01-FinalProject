# MNXB01-FinalProject
Final Project for the course MNXB01 at Lund University 2022.



 {TH1I* hist = new TH1I("hist", "Temperature of 23/8 from 1962 to 2020;[#circC];Entries", 500, -3.2, 40);
ifstream infile;
infile.open("8-23Temp.txt");
double tmp;
while (infile>>tmp) {hist->Fill(tmp);}
hist->SetFillColor(kRed + 1);

double mean = hist->GetMean(); //The mean of the distribution
double stdev = hist->GetRMS(); //The standard deviation
TCanvas* can = new TCanvas();
hist->Draw();}
