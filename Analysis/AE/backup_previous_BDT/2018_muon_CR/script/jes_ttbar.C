#include <algorithm>
#include <cstring>
#include <iterator>
#include <TROOT.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLatex.h>
#include "TCanvas.h"
#include "RooPlot.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH1F.h"
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

void jes_ttbar(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{
  
TFile out("Input_undfolding_data_jes.root","recreate");
string texts[]={"TTToSemiLeptonic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//array for variable 

    int len = 3, len_rec = 3;
    Float_t bins_gen[] = {-2000,0,2000};
    Float_t new_rec[]  = {-2000,0,2000};
    
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t   binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

       Float_t nominal_1_1 = 0;
       Float_t nominal_1_2 = 0;

       Float_t nominal_2_1 = 0;
       Float_t nominal_2_2 = 0;


       Float_t variation_1_1_up = 0;
       Float_t variation_1_2_up = 0;
       Float_t variation_2_1_up = 0;
       Float_t variation_2_2_up = 0;

       Float_t variation_1_1_down = 0;
       Float_t variation_1_2_down = 0;
       Float_t variation_2_1_down = 0;
       Float_t variation_2_2_down = 0;

       Float_t difference_1_1 = 0;
       Float_t difference_1_2 = 0;
       Float_t difference_2_1 = 0;
       Float_t difference_2_2 = 0;

       if(text == "TTToSemiLeptonic"){
       string systs[] = {"1"};

       for(const string &syst : systs){

            cout << syst << endl;

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/group/topcmsdesy/Asymmetry/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root/AnalysisTree",syst.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            string selcuts_boosted_central_1 = "(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100)";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight",selcuts_boosted_central_1.c_str()));

            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);

            nominal_1_1 = Ttbar_1_nominal->GetBinContent(1);
            nominal_1_2 = Ttbar_1_nominal->GetBinContent(2);
            nominal_2_1 = Ttbar_2_nominal->GetBinContent(1);
            nominal_2_2 = Ttbar_2_nominal->GetBinContent(2);
            

            delete Ttbar_1_nominal; delete Ttbar_2_nominal;
            delete Migration_Matrix_1;

        }
     }



       if(text == "TTToSemiLeptonic"){
       string systs[] = {"_JEREC1","_JEREC2","_PtEC1","_PtEC2","_RelativeSample","_RelativeStatEC","_RelativeStatFSR","_TimePtEta"};
   
       for(const string &syst : systs){

            cout << syst << endl; 
 
            TChain *chreco_ttbar_semi1 = new TChain("AnalysisTree","");
            chreco_ttbar_semi1->Add(Form("/nfs/dust/cms/group/topcmsdesy/Asymmetry/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018%sup.root/AnalysisTree",syst.c_str()));
            TTree *treereco_ttbar_semi1 = (TTree*) chreco_ttbar_semi1;
 
            TChain *chreco_ttbar_semi2 = new TChain("AnalysisTree","");
            chreco_ttbar_semi2->Add(Form("/nfs/dust/cms/group/topcmsdesy/Asymmetry/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018%sdown.root/AnalysisTree",syst.c_str()));
            TTree *treereco_ttbar_semi2 = (TTree*) chreco_ttbar_semi2;


            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen); 
            string selcuts_boosted_central_1 = "(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100)";
            treereco_ttbar_semi1->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight",selcuts_boosted_central_1.c_str()));

            TH2F *Migration_Matrix_2 = new TH2F("Migration_Matrix_2","",newrec,new_rec,binnum_gen,bins_gen);
            string selcuts_boosted_central_2 = "(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100)";
            treereco_ttbar_semi2->Project("Migration_Matrix_2","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight",selcuts_boosted_central_2.c_str()));
 
            TH1D* Ttbar_1_up = Migration_Matrix_1->ProjectionX("Ttbar_1_up", 1,1);
            TH1D* Ttbar_2_up = Migration_Matrix_1->ProjectionX("Ttbar_2_up", 2,2);

            TH1D* Ttbar_1_down = Migration_Matrix_2->ProjectionX("Ttbar_1_down", 1,1);
            TH1D* Ttbar_2_down = Migration_Matrix_2->ProjectionX("Ttbar_2_down", 2,2);
 
            variation_1_1_up = Ttbar_1_up->GetBinContent(1);
            variation_1_2_up = Ttbar_1_up->GetBinContent(2);
            variation_2_1_up = Ttbar_2_up->GetBinContent(1);
            variation_2_2_up = Ttbar_2_up->GetBinContent(2);    

            variation_1_1_down = Ttbar_1_down->GetBinContent(1);
            variation_1_2_down = Ttbar_1_down->GetBinContent(2);
            variation_2_1_down = Ttbar_2_down->GetBinContent(1);
            variation_2_2_down = Ttbar_2_down->GetBinContent(2); 

            difference_1_1 = TMath::Abs(variation_1_1_up - variation_1_1_down);
            difference_1_2 = TMath::Abs(variation_1_2_up - variation_1_2_down);
            difference_2_1 = TMath::Abs(variation_2_1_up - variation_2_1_down);
            difference_2_2 = TMath::Abs(variation_2_2_up - variation_2_2_down);
 
            Ttbar_1_up->SetBinContent(1,nominal_1_1+difference_1_1);
            Ttbar_1_up->SetBinContent(2,nominal_1_2+difference_1_2);
            Ttbar_2_up->SetBinContent(1,nominal_2_1+difference_2_1);
            Ttbar_2_up->SetBinContent(2,nominal_2_2+difference_2_2);
 
            Ttbar_1_down->SetBinContent(1,nominal_1_1-difference_1_1); 
            Ttbar_1_down->SetBinContent(2,nominal_1_2-difference_1_2);
            Ttbar_2_down->SetBinContent(1,nominal_2_1-difference_2_1);
            Ttbar_2_down->SetBinContent(2,nominal_2_2-difference_2_2);


            Ttbar_1_up->Write(Form("TTToSemiLeptonic_1%sUp",syst.c_str()));
            Ttbar_2_up->Write(Form("TTToSemiLeptonic_2%sUp",syst.c_str())); 
            Ttbar_1_down->Write(Form("TTToSemiLeptonic_1%sDown",syst.c_str()));
            Ttbar_2_down->Write(Form("TTToSemiLeptonic_2%sDown",syst.c_str()));


            
            delete Ttbar_1_up; delete Ttbar_2_up; Ttbar_1_down; delete Ttbar_2_down;
            delete Migration_Matrix_1;
            delete Migration_Matrix_2;
            
        }
     }
  }
}
