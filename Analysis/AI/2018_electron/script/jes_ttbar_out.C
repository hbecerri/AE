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

void jes_ttbar_out(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{
  
TFile out("Input_undfolding_data_jes_out.root","recreate");
string texts[]={"ttbar_out","ttbar_out_JECdown","ttbar_out_JERdown"};

Float_t nominal_1_1 = 0, nominal_1_2 = 0, nominal_1_3 = 0, nominal_1_4 = 0, nominal_1_5 = 0, nominal_1_6 = 0, nominal_1_7 = 0, nominal_1_8 = 0, nominal_1_9 = 0, nominal_1_10 = 0,
        nominal_1_11 = 0, nominal_1_12 = 0, nominal_1_13 = 0, nominal_1_14 = 0, nominal_1_15 = 0, nominal_1_16 = 0, nominal_1_17 = 0, nominal_1_18 = 0, nominal_1_19 = 0, nominal_1_20 = 0;

Float_t nominal_2_1 = 0, nominal_2_2 = 0, nominal_2_3 = 0, nominal_2_4 = 0, nominal_2_5 = 0, nominal_2_6 = 0, nominal_2_7 = 0, nominal_2_8 = 0, nominal_2_9 = 0, nominal_2_10 = 0,
        nominal_2_11 = 0, nominal_2_12 = 0, nominal_2_13 = 0, nominal_2_14 = 0, nominal_2_15 = 0, nominal_2_16 = 0, nominal_2_17 = 0, nominal_2_18 = 0, nominal_2_19 = 0, nominal_2_20 = 0;

Float_t nominal_3_1 = 0, nominal_3_2 = 0, nominal_3_3 = 0, nominal_3_4 = 0, nominal_3_5 = 0, nominal_3_6 = 0, nominal_3_7 = 0, nominal_3_8 = 0, nominal_3_9 = 0, nominal_3_10 = 0,
        nominal_3_11 = 0, nominal_3_12 = 0, nominal_3_13 = 0, nominal_3_14 = 0, nominal_3_15 = 0, nominal_3_16 = 0, nominal_3_17 = 0, nominal_3_18 = 0, nominal_3_19 = 0, nominal_3_20 = 0;

Float_t nominal_4_1 = 0, nominal_4_2 = 0, nominal_4_3 = 0, nominal_4_4 = 0, nominal_4_5 = 0, nominal_4_6 = 0, nominal_4_7 = 0, nominal_4_8 = 0, nominal_4_9 = 0, nominal_4_10 = 0,
        nominal_4_11 = 0, nominal_4_12 = 0, nominal_4_13 = 0, nominal_4_14 = 0, nominal_4_15 = 0, nominal_4_16 = 0, nominal_4_17 = 0, nominal_4_18 = 0, nominal_4_19 = 0, nominal_4_20 = 0;


Float_t variation_1_1 = 0, variation_1_2 = 0, variation_1_3 = 0, variation_1_4 = 0, variation_1_5 = 0, variation_1_6 = 0, variation_1_7 = 0, variation_1_8 = 0, variation_1_9 = 0, variation_1_10 = 0,
        variation_1_11 = 0, variation_1_12 = 0, variation_1_13 = 0, variation_1_14 = 0, variation_1_15 = 0, variation_1_16 = 0, variation_1_17 = 0, variation_1_18 = 0, variation_1_19 = 0, variation_1_20 = 0;

Float_t variation_2_1 = 0, variation_2_2 = 0, variation_2_3 = 0, variation_2_4 = 0, variation_2_5 = 0, variation_2_6 = 0, variation_2_7 = 0, variation_2_8 = 0, variation_2_9 = 0, variation_2_10 = 0,
        variation_2_11 = 0, variation_2_12 = 0, variation_2_13 = 0, variation_2_14 = 0, variation_2_15 = 0, variation_2_16 = 0, variation_2_17 = 0, variation_2_18 = 0, variation_2_19 = 0, variation_2_20 = 0;

Float_t variation_3_1 = 0, variation_3_2 = 0, variation_3_3 = 0, variation_3_4 = 0, variation_3_5 = 0, variation_3_6 = 0, variation_3_7 = 0, variation_3_8 = 0, variation_3_9 = 0, variation_3_10 = 0,
        variation_3_11 = 0, variation_3_12 = 0, variation_3_13 = 0, variation_3_14 = 0, variation_3_15 = 0, variation_3_16 = 0, variation_3_17 = 0, variation_3_18 = 0, variation_3_19 = 0, variation_3_20 = 0;

Float_t variation_4_1 = 0, variation_4_2 = 0, variation_4_3 = 0, variation_4_4 = 0, variation_4_5 = 0, variation_4_6 = 0, variation_4_7 = 0, variation_4_8 = 0, variation_4_9 = 0, variation_4_10 = 0,
        variation_4_11 = 0, variation_4_12 = 0, variation_4_13 = 0, variation_4_14 = 0, variation_4_15 = 0, variation_4_16 = 0, variation_4_17 = 0, variation_4_18 = 0, variation_4_19 = 0, variation_4_20 = 0;


Float_t difference_1_1 = 0, difference_1_2 = 0, difference_1_3 = 0, difference_1_4 = 0, difference_1_5 = 0, difference_1_6 = 0, difference_1_7 = 0, difference_1_8 = 0, difference_1_9 = 0, difference_1_10 = 0,
        difference_1_11 = 0, difference_1_12 = 0, difference_1_13 = 0, difference_1_14 = 0, difference_1_15 = 0, difference_1_16 = 0, difference_1_17 = 0, difference_1_18 = 0, difference_1_19 = 0, difference_1_20 = 0;

Float_t difference_2_1 = 0, difference_2_2 = 0, difference_2_3 = 0, difference_2_4 = 0, difference_2_5 = 0, difference_2_6 = 0, difference_2_7 = 0, difference_2_8 = 0, difference_2_9 = 0, difference_2_10 = 0,
        difference_2_11 = 0, difference_2_12 = 0, difference_2_13 = 0, difference_2_14 = 0, difference_2_15 = 0, difference_2_16 = 0, difference_2_17 = 0, difference_2_18 = 0, difference_2_19 = 0, difference_2_20 = 0;

Float_t difference_3_1 = 0, difference_3_2 = 0, difference_3_3 = 0, difference_3_4 = 0, difference_3_5 = 0, difference_3_6 = 0, difference_3_7 = 0, difference_3_8 = 0, difference_3_9 = 0, difference_3_10 = 0,
        difference_3_11 = 0, difference_3_12 = 0, difference_3_13 = 0, difference_3_14 = 0, difference_3_15 = 0, difference_3_16 = 0, difference_3_17 = 0, difference_3_18 = 0, difference_3_19 = 0, difference_3_20 = 0;

Float_t difference_4_1 = 0, difference_4_2 = 0, difference_4_3 = 0, difference_4_4 = 0, difference_4_5 = 0, difference_4_6 = 0, difference_4_7 = 0, difference_4_8 = 0, difference_4_9 = 0, difference_4_10 = 0,
        difference_4_11 = 0, difference_4_12 = 0, difference_4_13 = 0, difference_4_14 = 0, difference_4_15 = 0, difference_4_16 = 0, difference_4_17 = 0, difference_4_18 = 0, difference_4_19 = 0, difference_4_20 = 0;
  
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//array for variable 

    Float_t new_rec[]  = {0,0.2,0.4,0.6,0.8,1};
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "ttbar_out"){

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2018_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1  = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2  = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3  = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4  = new TH1F("Back_4","",newrec,new_rec);

           string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

           TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",newrec*4,0,20);
           for (int i = 1; i <= 5; ++i) {
                Ttbar_1_nominal->SetBinContent(i,Back_1->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+5,Back_2->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+10,Back_3->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+15,Back_4->GetBinContent(i));
           }


	nominal_1_1 = Ttbar_1_nominal->GetBinContent(1); 
	nominal_1_2 = Ttbar_1_nominal->GetBinContent(2); 
	nominal_1_3 = Ttbar_1_nominal->GetBinContent(3); 
	nominal_1_4 = Ttbar_1_nominal->GetBinContent(4); 
	nominal_1_5 = Ttbar_1_nominal->GetBinContent(5); 
	nominal_1_6 = Ttbar_1_nominal->GetBinContent(6); 
	nominal_1_7 = Ttbar_1_nominal->GetBinContent(7); 
	nominal_1_8 = Ttbar_1_nominal->GetBinContent(8); 
	nominal_1_9 = Ttbar_1_nominal->GetBinContent(9); 
	nominal_1_10 = Ttbar_1_nominal->GetBinContent(10);
        nominal_1_11 = Ttbar_1_nominal->GetBinContent(11);
        nominal_1_12 = Ttbar_1_nominal->GetBinContent(12);
        nominal_1_13 = Ttbar_1_nominal->GetBinContent(13);
        nominal_1_14 = Ttbar_1_nominal->GetBinContent(14);
        nominal_1_15 = Ttbar_1_nominal->GetBinContent(15);
        nominal_1_16 = Ttbar_1_nominal->GetBinContent(16);
        nominal_1_17 = Ttbar_1_nominal->GetBinContent(17);
        nominal_1_18 = Ttbar_1_nominal->GetBinContent(18);
        nominal_1_19 = Ttbar_1_nominal->GetBinContent(19);
        nominal_1_20 = Ttbar_1_nominal->GetBinContent(20);

        delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Ttbar_1_nominal;

     }else{

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2018_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1  = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2  = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3  = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4  = new TH1F("Back_4","",newrec,new_rec);

           string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

           TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",newrec*4,0,20);
           for (int i = 1; i <= 5; ++i) {
                Ttbar_1_nominal->SetBinContent(i,Back_1->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+5,Back_2->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+10,Back_3->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+15,Back_4->GetBinContent(i));
           }

        variation_1_1 = Ttbar_1_nominal->GetBinContent(1);
        variation_1_2 = Ttbar_1_nominal->GetBinContent(2);
        variation_1_3 = Ttbar_1_nominal->GetBinContent(3);
        variation_1_4 = Ttbar_1_nominal->GetBinContent(4);
        variation_1_5 = Ttbar_1_nominal->GetBinContent(5);
        variation_1_6 = Ttbar_1_nominal->GetBinContent(6);
        variation_1_7 = Ttbar_1_nominal->GetBinContent(7);
        variation_1_8 = Ttbar_1_nominal->GetBinContent(8);
        variation_1_9 = Ttbar_1_nominal->GetBinContent(9);
        variation_1_10 = Ttbar_1_nominal->GetBinContent(10);
        variation_1_11 = Ttbar_1_nominal->GetBinContent(11);
        variation_1_12 = Ttbar_1_nominal->GetBinContent(12);
        variation_1_13 = Ttbar_1_nominal->GetBinContent(13);
        variation_1_14 = Ttbar_1_nominal->GetBinContent(14);
        variation_1_15 = Ttbar_1_nominal->GetBinContent(15);
        variation_1_16 = Ttbar_1_nominal->GetBinContent(16);
        variation_1_17 = Ttbar_1_nominal->GetBinContent(17);
        variation_1_18 = Ttbar_1_nominal->GetBinContent(18);
        variation_1_19 = Ttbar_1_nominal->GetBinContent(19);
        variation_1_20 = Ttbar_1_nominal->GetBinContent(20);

 difference_1_1 = TMath::Abs(nominal_1_1 - variation_1_1);
 difference_1_2 = TMath::Abs(nominal_1_2 - variation_1_2);
 difference_1_3 = TMath::Abs(nominal_1_3 - variation_1_3);
 difference_1_4 = TMath::Abs(nominal_1_4 - variation_1_4);
 difference_1_5 = TMath::Abs(nominal_1_5 - variation_1_5);
 difference_1_6 = TMath::Abs(nominal_1_6 - variation_1_6);
 difference_1_7 = TMath::Abs(nominal_1_7 - variation_1_7);
 difference_1_8 = TMath::Abs(nominal_1_8 - variation_1_8);
 difference_1_9 = TMath::Abs(nominal_1_9 - variation_1_9);
 difference_1_10 = TMath::Abs(nominal_1_10 - variation_1_10);
 difference_1_11 = TMath::Abs(nominal_1_11 - variation_1_11);
 difference_1_12 = TMath::Abs(nominal_1_12 - variation_1_12);
 difference_1_13 = TMath::Abs(nominal_1_13 - variation_1_13);
 difference_1_14 = TMath::Abs(nominal_1_14 - variation_1_14);
 difference_1_15 = TMath::Abs(nominal_1_15 - variation_1_15);
 difference_1_16 = TMath::Abs(nominal_1_16 - variation_1_16);
 difference_1_17 = TMath::Abs(nominal_1_17 - variation_1_17);
 difference_1_18 = TMath::Abs(nominal_1_18 - variation_1_18);
 difference_1_19 = TMath::Abs(nominal_1_19 - variation_1_19);
 difference_1_20 = TMath::Abs(nominal_1_20 - variation_1_20);

        TH1D* Ttbar_1_down = new TH1D("Ttbar_1_down", "Merged histogram", newrec*4, 0, 20);
        TH1D* Ttbar_1_up   = new TH1D("Ttbar_1_up",   "Merged histogram", newrec*4, 0, 20);

Ttbar_1_down->SetBinContent(1, nominal_1_1 - difference_1_1);
Ttbar_1_down->SetBinContent(2, nominal_1_2 - difference_1_2);
Ttbar_1_down->SetBinContent(3, nominal_1_3 - difference_1_3);
Ttbar_1_down->SetBinContent(4, nominal_1_4 - difference_1_4);
Ttbar_1_down->SetBinContent(5, nominal_1_5 - difference_1_5);
Ttbar_1_down->SetBinContent(6, nominal_1_6 - difference_1_6);
Ttbar_1_down->SetBinContent(7, nominal_1_7 - difference_1_7);
Ttbar_1_down->SetBinContent(8, nominal_1_8 - difference_1_8);
Ttbar_1_down->SetBinContent(9, nominal_1_9 - difference_1_9);
Ttbar_1_down->SetBinContent(10, nominal_1_10 - difference_1_10);
Ttbar_1_down->SetBinContent(11, nominal_1_11 - difference_1_11);
Ttbar_1_down->SetBinContent(12, nominal_1_12 - difference_1_12);
Ttbar_1_down->SetBinContent(13, nominal_1_13 - difference_1_13);
Ttbar_1_down->SetBinContent(14, nominal_1_14 - difference_1_14);
Ttbar_1_down->SetBinContent(15, nominal_1_15 - difference_1_15);
Ttbar_1_down->SetBinContent(16, nominal_1_16 - difference_1_16);
Ttbar_1_down->SetBinContent(17, nominal_1_17 - difference_1_17);
Ttbar_1_down->SetBinContent(18, nominal_1_18 - difference_1_18);
Ttbar_1_down->SetBinContent(19, nominal_1_19 - difference_1_19);
Ttbar_1_down->SetBinContent(20, nominal_1_20 - difference_1_20);

Ttbar_1_up->SetBinContent(1, nominal_1_1 + difference_1_1);
Ttbar_1_up->SetBinContent(2, nominal_1_2 + difference_1_2);
Ttbar_1_up->SetBinContent(3, nominal_1_3 + difference_1_3);
Ttbar_1_up->SetBinContent(4, nominal_1_4 + difference_1_4);
Ttbar_1_up->SetBinContent(5, nominal_1_5 + difference_1_5);
Ttbar_1_up->SetBinContent(6, nominal_1_6 + difference_1_6);
Ttbar_1_up->SetBinContent(7, nominal_1_7 + difference_1_7);
Ttbar_1_up->SetBinContent(8, nominal_1_8 + difference_1_8);
Ttbar_1_up->SetBinContent(9, nominal_1_9 + difference_1_9);
Ttbar_1_up->SetBinContent(10, nominal_1_10 + difference_1_10);
Ttbar_1_up->SetBinContent(11, nominal_1_11 + difference_1_11);
Ttbar_1_up->SetBinContent(12, nominal_1_12 + difference_1_12);
Ttbar_1_up->SetBinContent(13, nominal_1_13 + difference_1_13);
Ttbar_1_up->SetBinContent(14, nominal_1_14 + difference_1_14);
Ttbar_1_up->SetBinContent(15, nominal_1_15 + difference_1_15);
Ttbar_1_up->SetBinContent(16, nominal_1_16 + difference_1_16);
Ttbar_1_up->SetBinContent(17, nominal_1_17 + difference_1_17);
Ttbar_1_up->SetBinContent(18, nominal_1_18 + difference_1_18);
Ttbar_1_up->SetBinContent(19, nominal_1_19 + difference_1_19);
Ttbar_1_up->SetBinContent(20, nominal_1_20 + difference_1_20);


        string sys = "";
        if(text == "ttbar_out_JECdown") sys = "JEC";
        if(text == "ttbar_out_JERdown") sys = "JER";
  
        Ttbar_1_up->Write(Form("ttbar_out_%sUp",sys.c_str()));
        Ttbar_1_down->Write(Form("ttbar_out_%sDown",sys.c_str()));

        delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Ttbar_1_up; delete Ttbar_1_down;
     
     }



  }
}
