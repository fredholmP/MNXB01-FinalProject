# MNXB01-FinalProject
Final Project for the course MNXB01 at Lund University 2022.
The draft report is the file "draftReport.pdf", placed both in the top directory and in the "Latex" directory.
--------------------------------
How to Generate Philip's Plots
-------------------------------
To make sure that everything works, use Ubuntu 20 and run
"source /localRoot/rootUbuntu20/bin/thisroot.sh"
to make sure root is running properly. Then, cd into the directory "PhilipCode". There, run 
"make all" in the terminal to generate datafiles starting with "hotCold-" and "summerStart-" necessary for the root plots.
Then, copy and paste these files into the directory "rootmacros". 

After this, type "root" in the terminal to begin using root. In root, run 
".L rootmacros/hot.C+",
".L rootmacros/cold.C+" and
".L rootmacros/summer.C+"

to load the functions "hot()", "cold()" and "summer()". Running these functions will create the used plots.


Please note that using Aurora's root (and c++) versions may cause issues. It has been found that things like using strings,
accessing elements in vectors and using for loops in the style of "for (auto i: myvector) {}" can cause issues with both 
root for some things and with c++ for other things (with code working fine outside of Aurora complaining about things in the 
standard library missing).




-------------------------
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
