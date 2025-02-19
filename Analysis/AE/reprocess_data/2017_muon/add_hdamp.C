#include <fstream>
#include <algorithm>
#include <cstring>
#include <iterator>
#include <TROOT.h>
#include <TStyle.h>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "THStack.h"
#include "TRandom.h"
#include "TUnfoldDensity.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"
#include <iostream>
#include <vector>

void add_hdamp(string var_name = "", string var_gen = "", string region = "", string year = "2016")
{

 
//cout << "1" << endl;
vector<Float_t> g1;
Float_t w;

std::ifstream ifs(Form("/nfs/dust/cms/user/hugobg/hdamp/CMSSW_11_2_5_patch2/src/muon_2017_up/%s.txt",var_name.c_str()));

std::string line;

while(std::getline(ifs, line))
{
     w = std::stof(line); 
    g1.push_back(w); 
}

//cout << "2" << endl;

TFile *fin=TFile::Open(Form("/nfs/dust/cms/user/hugobg/analysis/muon/hdamp_17/uhh2.AnalysisModuleRunner.MC.%s.root",var_name.c_str()),"UPDATE"); 
TTree *t = (TTree*)fin->Get("AnalysisTree");
Float_t hdamp_up;
TBranch * _hdamp_up = t->Branch("hdamp_up",&hdamp_up,"grid/F");

//cout << "2.5" << endl;

for(int ev=0; ev < t->GetEntries() ; ++ev) {

//cout << "2.5" << endl;

         if(ev < g1.size()) hdamp_up = g1.at(ev);
         else hdamp_up = g1.at(ev%g1.size());
	_hdamp_up->Fill();
} 
 

//cout << "3" << endl;

t->Write("", TObject::kOverwrite);
fin->Close();


vector<Float_t> g2;
Float_t w2;

std::ifstream ifs2(Form("/nfs/dust/cms/user/hugobg/hdamp/CMSSW_11_2_5_patch2/src/muon_2017_down/%s.txt",var_name.c_str()));

std::string line2;

while(std::getline(ifs2, line2))
{
    w2 = std::stof(line2);
    g2.push_back(w2);
}

TFile *fin2=TFile::Open(Form("/nfs/dust/cms/user/hugobg/analysis/muon/hdamp_17/uhh2.AnalysisModuleRunner.MC.%s.root",var_name.c_str()),"UPDATE");
TTree *t2 = (TTree*)fin2->Get("AnalysisTree");
Float_t hdamp_down;
TBranch * _hdamp_down = t2->Branch("hdamp_down",&hdamp_down,"grid/F");

for(int ev=0; ev < t2->GetEntries() ; ++ev) {

         if(ev < g2.size()) hdamp_down = g2.at(ev);
         else hdamp_down = g2.at(ev%g2.size());
        _hdamp_down->Fill();
}


t2->Write("", TObject::kOverwrite);
fin2->Close();

}


