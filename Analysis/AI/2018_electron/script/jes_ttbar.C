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
string texts[]={"Ttbar_in","Ttbar_in_JECdown","Ttbar_in_JERdown"};

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

    int len = 3, len_rec = 3;
    Float_t new_rec[]  = {0,0.2,0.4,0.6,0.8,1};
    
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "Ttbar_in"){

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2018_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1  = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2  = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3  = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4  = new TH1F("Back_4","",newrec,new_rec);
            TH1F *Back_5  = new TH1F("Back_5","",newrec,new_rec);
            TH1F *Back_6  = new TH1F("Back_6","",newrec,new_rec);
            TH1F *Back_7  = new TH1F("Back_7","",newrec,new_rec);
            TH1F *Back_8  = new TH1F("Back_8","",newrec,new_rec);
            TH1F *Back_9  = new TH1F("Back_9","",newrec,new_rec);
            TH1F *Back_10 = new TH1F("Back_10","",newrec,new_rec);
            TH1F *Back_11 = new TH1F("Back_11","",newrec,new_rec);
            TH1F *Back_12 = new TH1F("Back_12","",newrec,new_rec);
            TH1F *Back_13 = new TH1F("Back_13","",newrec,new_rec);
            TH1F *Back_14 = new TH1F("Back_14","",newrec,new_rec);
            TH1F *Back_15 = new TH1F("Back_15","",newrec,new_rec);
            TH1F *Back_16 = new TH1F("Back_16","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_5 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_6 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_7 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_8 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_9 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_10 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_11 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_12 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_13 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_14 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_15 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_16 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_5","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_5.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_6","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_6.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_7","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_7.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_8","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_8.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_9","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_9.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_10","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_10.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_11","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_11.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_12","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_12.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_13","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_13.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_14","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_14.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_15","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_15.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_16","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_16.c_str(),syst.c_str()));

            TH1F* Back_bin1 = new TH1F("Back_bin1", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin1->SetBinContent(i,Back_1->GetBinContent(i));
                Back_bin1->SetBinContent(i+5,Back_2->GetBinContent(i));
                Back_bin1->SetBinContent(i+10,Back_3->GetBinContent(i));
                Back_bin1->SetBinContent(i+15,Back_4->GetBinContent(i));
            }

            TH1F* Back_bin2 = new TH1F("Back_bin2", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin2->SetBinContent(i,Back_5->GetBinContent(i));
                Back_bin2->SetBinContent(i+5,Back_6->GetBinContent(i));
                Back_bin2->SetBinContent(i+10,Back_7->GetBinContent(i));
                Back_bin2->SetBinContent(i+15,Back_8->GetBinContent(i));
            }

            TH1F* Back_bin3 = new TH1F("Back_bin3", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin3->SetBinContent(i,Back_9->GetBinContent(i));
                Back_bin3->SetBinContent(i+5,Back_10->GetBinContent(i));
                Back_bin3->SetBinContent(i+10,Back_11->GetBinContent(i));
                Back_bin3->SetBinContent(i+15,Back_12->GetBinContent(i));
            }

            TH1F* Back_bin4 = new TH1F("Back_bin4", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin4->SetBinContent(i,Back_13->GetBinContent(i));
                Back_bin4->SetBinContent(i+5,Back_14->GetBinContent(i));
                Back_bin4->SetBinContent(i+10,Back_15->GetBinContent(i));
                Back_bin4->SetBinContent(i+15,Back_16->GetBinContent(i));
            }


	nominal_1_1 = Back_bin1->GetBinContent(1); 
	nominal_1_2 = Back_bin1->GetBinContent(2); 
	nominal_1_3 = Back_bin1->GetBinContent(3); 
	nominal_1_4 = Back_bin1->GetBinContent(4); 
	nominal_1_5 = Back_bin1->GetBinContent(5); 
	nominal_1_6 = Back_bin1->GetBinContent(6); 
	nominal_1_7 = Back_bin1->GetBinContent(7); 
	nominal_1_8 = Back_bin1->GetBinContent(8); 
	nominal_1_9 = Back_bin1->GetBinContent(9); 
	nominal_1_10 = Back_bin1->GetBinContent(10);
        nominal_1_11 = Back_bin1->GetBinContent(11);
        nominal_1_12 = Back_bin1->GetBinContent(12);
        nominal_1_13 = Back_bin1->GetBinContent(13);
        nominal_1_14 = Back_bin1->GetBinContent(14);
        nominal_1_15 = Back_bin1->GetBinContent(15);
        nominal_1_16 = Back_bin1->GetBinContent(16);
        nominal_1_17 = Back_bin1->GetBinContent(17);
        nominal_1_18 = Back_bin1->GetBinContent(18);
        nominal_1_19 = Back_bin1->GetBinContent(19);
        nominal_1_20 = Back_bin1->GetBinContent(20);

        nominal_2_1 = Back_bin2->GetBinContent(1);
        nominal_2_2 = Back_bin2->GetBinContent(2);
        nominal_2_3 = Back_bin2->GetBinContent(3);
        nominal_2_4 = Back_bin2->GetBinContent(4);
        nominal_2_5 = Back_bin2->GetBinContent(5);
        nominal_2_6 = Back_bin2->GetBinContent(6);
        nominal_2_7 = Back_bin2->GetBinContent(7);
        nominal_2_8 = Back_bin2->GetBinContent(8);
        nominal_2_9 = Back_bin2->GetBinContent(9);
        nominal_2_10 = Back_bin2->GetBinContent(10);
        nominal_2_11 = Back_bin2->GetBinContent(11);
        nominal_2_12 = Back_bin2->GetBinContent(12);
        nominal_2_13 = Back_bin2->GetBinContent(13);
        nominal_2_14 = Back_bin2->GetBinContent(14);
        nominal_2_15 = Back_bin2->GetBinContent(15);
        nominal_2_16 = Back_bin2->GetBinContent(16);
        nominal_2_17 = Back_bin2->GetBinContent(17);
        nominal_2_18 = Back_bin2->GetBinContent(18);
        nominal_2_19 = Back_bin2->GetBinContent(19);
        nominal_2_20 = Back_bin2->GetBinContent(20);

        nominal_3_1 = Back_bin3->GetBinContent(1);
        nominal_3_2 = Back_bin3->GetBinContent(2);
        nominal_3_3 = Back_bin3->GetBinContent(3);
        nominal_3_4 = Back_bin3->GetBinContent(4);
        nominal_3_5 = Back_bin3->GetBinContent(5);
        nominal_3_6 = Back_bin3->GetBinContent(6);
        nominal_3_7 = Back_bin3->GetBinContent(7);
        nominal_3_8 = Back_bin3->GetBinContent(8);
        nominal_3_9 = Back_bin3->GetBinContent(9);
        nominal_3_10 = Back_bin3->GetBinContent(10);
        nominal_3_11 = Back_bin3->GetBinContent(11);
        nominal_3_12 = Back_bin3->GetBinContent(12);
        nominal_3_13 = Back_bin3->GetBinContent(13);
        nominal_3_14 = Back_bin3->GetBinContent(14);
        nominal_3_15 = Back_bin3->GetBinContent(15);
        nominal_3_16 = Back_bin3->GetBinContent(16);
        nominal_3_17 = Back_bin3->GetBinContent(17);
        nominal_3_18 = Back_bin3->GetBinContent(18);
        nominal_3_19 = Back_bin3->GetBinContent(19);
        nominal_3_20 = Back_bin3->GetBinContent(20);
 
        nominal_4_1 = Back_bin4->GetBinContent(1);
        nominal_4_2 = Back_bin4->GetBinContent(2);
        nominal_4_3 = Back_bin4->GetBinContent(3);
        nominal_4_4 = Back_bin4->GetBinContent(4);
        nominal_4_5 = Back_bin4->GetBinContent(5);
        nominal_4_6 = Back_bin4->GetBinContent(6);
        nominal_4_7 = Back_bin4->GetBinContent(7);
        nominal_4_8 = Back_bin4->GetBinContent(8);
        nominal_4_9 = Back_bin4->GetBinContent(9);
        nominal_4_10 = Back_bin4->GetBinContent(10);
        nominal_4_11 = Back_bin4->GetBinContent(11);
        nominal_4_12 = Back_bin4->GetBinContent(12);
        nominal_4_13 = Back_bin4->GetBinContent(13);
        nominal_4_14 = Back_bin4->GetBinContent(14);
        nominal_4_15 = Back_bin4->GetBinContent(15);
        nominal_4_16 = Back_bin4->GetBinContent(16);
        nominal_4_17 = Back_bin4->GetBinContent(17);
        nominal_4_18 = Back_bin4->GetBinContent(18);
        nominal_4_19 = Back_bin4->GetBinContent(19);
        nominal_4_20 = Back_bin4->GetBinContent(20);

            delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Back_5; delete Back_6; delete Back_7; delete Back_8; delete Back_9; delete Back_10; delete Back_11; delete Back_12; delete Back_13; delete Back_14; delete Back_15; delete Back_16; delete Back_bin1; delete Back_bin2; delete Back_bin3; delete Back_bin4; 

     }else{

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2018_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1  = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2  = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3  = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4  = new TH1F("Back_4","",newrec,new_rec);
            TH1F *Back_5  = new TH1F("Back_5","",newrec,new_rec);
            TH1F *Back_6  = new TH1F("Back_6","",newrec,new_rec);
            TH1F *Back_7  = new TH1F("Back_7","",newrec,new_rec);
            TH1F *Back_8  = new TH1F("Back_8","",newrec,new_rec);
            TH1F *Back_9  = new TH1F("Back_9","",newrec,new_rec);
            TH1F *Back_10 = new TH1F("Back_10","",newrec,new_rec);
            TH1F *Back_11 = new TH1F("Back_11","",newrec,new_rec);
            TH1F *Back_12 = new TH1F("Back_12","",newrec,new_rec);
            TH1F *Back_13 = new TH1F("Back_13","",newrec,new_rec);
            TH1F *Back_14 = new TH1F("Back_14","",newrec,new_rec);
            TH1F *Back_15 = new TH1F("Back_15","",newrec,new_rec);
            TH1F *Back_16 = new TH1F("Back_16","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_5 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_6 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_7 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_8 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_9 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_10 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_11 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_12 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            string selcuts_boosted_central_13 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_14 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity<0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_15 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) <0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";
            string selcuts_boosted_central_16 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && Gen_ttj_Rapidity>0 && TMath::Cos(Gen_angle_phi) >0 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";


            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_5","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_5.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_6","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_6.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_7","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_7.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_8","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_8.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_9","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_9.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_10","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_10.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_11","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_11.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_12","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_12.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_13","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_13.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_14","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_14.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_15","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_15.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_16","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_16.c_str(),syst.c_str()));

            TH1F* Back_bin1 = new TH1F("Back_bin1", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin1->SetBinContent(i,Back_1->GetBinContent(i));
                Back_bin1->SetBinContent(i+5,Back_2->GetBinContent(i));
                Back_bin1->SetBinContent(i+10,Back_3->GetBinContent(i));
                Back_bin1->SetBinContent(i+15,Back_4->GetBinContent(i));
            }

            TH1F* Back_bin2 = new TH1F("Back_bin2", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin2->SetBinContent(i,Back_5->GetBinContent(i));
                Back_bin2->SetBinContent(i+5,Back_6->GetBinContent(i));
                Back_bin2->SetBinContent(i+10,Back_7->GetBinContent(i));
                Back_bin2->SetBinContent(i+15,Back_8->GetBinContent(i));
            }

            TH1F* Back_bin3 = new TH1F("Back_bin3", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin3->SetBinContent(i,Back_9->GetBinContent(i));
                Back_bin3->SetBinContent(i+5,Back_10->GetBinContent(i));
                Back_bin3->SetBinContent(i+10,Back_11->GetBinContent(i));
                Back_bin3->SetBinContent(i+15,Back_12->GetBinContent(i));
            }

            TH1F* Back_bin4 = new TH1F("Back_bin4", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin4->SetBinContent(i,Back_13->GetBinContent(i));
                Back_bin4->SetBinContent(i+5,Back_14->GetBinContent(i));
                Back_bin4->SetBinContent(i+10,Back_15->GetBinContent(i));
                Back_bin4->SetBinContent(i+15,Back_16->GetBinContent(i));
            }

        variation_1_1 = Back_bin1->GetBinContent(1);
        variation_1_2 = Back_bin1->GetBinContent(2);
        variation_1_3 = Back_bin1->GetBinContent(3);
        variation_1_4 = Back_bin1->GetBinContent(4);
        variation_1_5 = Back_bin1->GetBinContent(5);
        variation_1_6 = Back_bin1->GetBinContent(6);
        variation_1_7 = Back_bin1->GetBinContent(7);
        variation_1_8 = Back_bin1->GetBinContent(8);
        variation_1_9 = Back_bin1->GetBinContent(9);
        variation_1_10 = Back_bin1->GetBinContent(10);
        variation_1_11 = Back_bin1->GetBinContent(11);
        variation_1_12 = Back_bin1->GetBinContent(12);
        variation_1_13 = Back_bin1->GetBinContent(13);
        variation_1_14 = Back_bin1->GetBinContent(14);
        variation_1_15 = Back_bin1->GetBinContent(15);
        variation_1_16 = Back_bin1->GetBinContent(16);
        variation_1_17 = Back_bin1->GetBinContent(17);
        variation_1_18 = Back_bin1->GetBinContent(18);
        variation_1_19 = Back_bin1->GetBinContent(19);
        variation_1_20 = Back_bin1->GetBinContent(20);

        variation_2_1 = Back_bin2->GetBinContent(1);
        variation_2_2 = Back_bin2->GetBinContent(2);
        variation_2_3 = Back_bin2->GetBinContent(3);
        variation_2_4 = Back_bin2->GetBinContent(4);
        variation_2_5 = Back_bin2->GetBinContent(5);
        variation_2_6 = Back_bin2->GetBinContent(6);
        variation_2_7 = Back_bin2->GetBinContent(7);
        variation_2_8 = Back_bin2->GetBinContent(8);
        variation_2_9 = Back_bin2->GetBinContent(9);
        variation_2_10 = Back_bin2->GetBinContent(10);
        variation_2_11 = Back_bin2->GetBinContent(11);
        variation_2_12 = Back_bin2->GetBinContent(12);
        variation_2_13 = Back_bin2->GetBinContent(13);
        variation_2_14 = Back_bin2->GetBinContent(14);
        variation_2_15 = Back_bin2->GetBinContent(15);
        variation_2_16 = Back_bin2->GetBinContent(16);
        variation_2_17 = Back_bin2->GetBinContent(17);
        variation_2_18 = Back_bin2->GetBinContent(18);
        variation_2_19 = Back_bin2->GetBinContent(19);
        variation_2_20 = Back_bin2->GetBinContent(20);

        variation_3_1 = Back_bin3->GetBinContent(1);
        variation_3_2 = Back_bin3->GetBinContent(2);
        variation_3_3 = Back_bin3->GetBinContent(3);
        variation_3_4 = Back_bin3->GetBinContent(4);
        variation_3_5 = Back_bin3->GetBinContent(5);
        variation_3_6 = Back_bin3->GetBinContent(6);
        variation_3_7 = Back_bin3->GetBinContent(7);
        variation_3_8 = Back_bin3->GetBinContent(8);
        variation_3_9 = Back_bin3->GetBinContent(9);
        variation_3_10 = Back_bin3->GetBinContent(10);
        variation_3_11 = Back_bin3->GetBinContent(11);
        variation_3_12 = Back_bin3->GetBinContent(12);
        variation_3_13 = Back_bin3->GetBinContent(13);
        variation_3_14 = Back_bin3->GetBinContent(14);
        variation_3_15 = Back_bin3->GetBinContent(15);
        variation_3_16 = Back_bin3->GetBinContent(16);
        variation_3_17 = Back_bin3->GetBinContent(17);
        variation_3_18 = Back_bin3->GetBinContent(18);
        variation_3_19 = Back_bin3->GetBinContent(19);
        variation_3_20 = Back_bin3->GetBinContent(20);

        variation_4_1 = Back_bin4->GetBinContent(1);
        variation_4_2 = Back_bin4->GetBinContent(2);
        variation_4_3 = Back_bin4->GetBinContent(3);
        variation_4_4 = Back_bin4->GetBinContent(4);
        variation_4_5 = Back_bin4->GetBinContent(5);
        variation_4_6 = Back_bin4->GetBinContent(6);
        variation_4_7 = Back_bin4->GetBinContent(7);
        variation_4_8 = Back_bin4->GetBinContent(8);
        variation_4_9 = Back_bin4->GetBinContent(9);
        variation_4_10 = Back_bin4->GetBinContent(10);
        variation_4_11 = Back_bin4->GetBinContent(11);
        variation_4_12 = Back_bin4->GetBinContent(12);
        variation_4_13 = Back_bin4->GetBinContent(13);
        variation_4_14 = Back_bin4->GetBinContent(14);
        variation_4_15 = Back_bin4->GetBinContent(15);
        variation_4_16 = Back_bin4->GetBinContent(16);
        variation_4_17 = Back_bin4->GetBinContent(17);
        variation_4_18 = Back_bin4->GetBinContent(18);
        variation_4_19 = Back_bin4->GetBinContent(19);
        variation_4_20 = Back_bin4->GetBinContent(20);

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

 difference_2_1 = TMath::Abs(nominal_2_1 - variation_2_1);
 difference_2_2 = TMath::Abs(nominal_2_2 - variation_2_2);
 difference_2_3 = TMath::Abs(nominal_2_3 - variation_2_3);
 difference_2_4 = TMath::Abs(nominal_2_4 - variation_2_4);
 difference_2_5 = TMath::Abs(nominal_2_5 - variation_2_5);
 difference_2_6 = TMath::Abs(nominal_2_6 - variation_2_6);
 difference_2_7 = TMath::Abs(nominal_2_7 - variation_2_7);
 difference_2_8 = TMath::Abs(nominal_2_8 - variation_2_8);
 difference_2_9 = TMath::Abs(nominal_2_9 - variation_2_9);
 difference_2_10 = TMath::Abs(nominal_2_10 - variation_2_10);
 difference_2_11 = TMath::Abs(nominal_2_11 - variation_2_11);
 difference_2_12 = TMath::Abs(nominal_2_12 - variation_2_12);
 difference_2_13 = TMath::Abs(nominal_2_13 - variation_2_13);
 difference_2_14 = TMath::Abs(nominal_2_14 - variation_2_14);
 difference_2_15 = TMath::Abs(nominal_2_15 - variation_2_15);
 difference_2_16 = TMath::Abs(nominal_2_16 - variation_2_16);
 difference_2_17 = TMath::Abs(nominal_2_17 - variation_2_17);
 difference_2_18 = TMath::Abs(nominal_2_18 - variation_2_18);
 difference_2_19 = TMath::Abs(nominal_2_19 - variation_2_19);
 difference_2_20 = TMath::Abs(nominal_2_20 - variation_2_20);

 difference_3_1 = TMath::Abs(nominal_3_1 - variation_3_1);
 difference_3_2 = TMath::Abs(nominal_3_2 - variation_3_2);
 difference_3_3 = TMath::Abs(nominal_3_3 - variation_3_3);
 difference_3_4 = TMath::Abs(nominal_3_4 - variation_3_4);
 difference_3_5 = TMath::Abs(nominal_3_5 - variation_3_5);
 difference_3_6 = TMath::Abs(nominal_3_6 - variation_3_6);
 difference_3_7 = TMath::Abs(nominal_3_7 - variation_3_7);
 difference_3_8 = TMath::Abs(nominal_3_8 - variation_3_8);
 difference_3_9 = TMath::Abs(nominal_3_9 - variation_3_9);
 difference_3_10 = TMath::Abs(nominal_3_10 - variation_3_10);
 difference_3_11 = TMath::Abs(nominal_3_11 - variation_3_11);
 difference_3_12 = TMath::Abs(nominal_3_12 - variation_3_12);
 difference_3_13 = TMath::Abs(nominal_3_13 - variation_3_13);
 difference_3_14 = TMath::Abs(nominal_3_14 - variation_3_14);
 difference_3_15 = TMath::Abs(nominal_3_15 - variation_3_15);
 difference_3_16 = TMath::Abs(nominal_3_16 - variation_3_16);
 difference_3_17 = TMath::Abs(nominal_3_17 - variation_3_17);
 difference_3_18 = TMath::Abs(nominal_3_18 - variation_3_18);
 difference_3_19 = TMath::Abs(nominal_3_19 - variation_3_19);
 difference_3_20 = TMath::Abs(nominal_3_20 - variation_3_20);

 difference_4_1 = TMath::Abs(nominal_4_1 - variation_4_1);
 difference_4_2 = TMath::Abs(nominal_4_2 - variation_4_2);
 difference_4_3 = TMath::Abs(nominal_4_3 - variation_4_3);
 difference_4_4 = TMath::Abs(nominal_4_4 - variation_4_4);
 difference_4_5 = TMath::Abs(nominal_4_5 - variation_4_5);
 difference_4_6 = TMath::Abs(nominal_4_6 - variation_4_6);
 difference_4_7 = TMath::Abs(nominal_4_7 - variation_4_7);
 difference_4_8 = TMath::Abs(nominal_4_8 - variation_4_8);
 difference_4_9 = TMath::Abs(nominal_4_9 - variation_4_9);
 difference_4_10 = TMath::Abs(nominal_4_10 - variation_4_10);
 difference_4_11 = TMath::Abs(nominal_4_11 - variation_4_11);
 difference_4_12 = TMath::Abs(nominal_4_12 - variation_4_12);
 difference_4_13 = TMath::Abs(nominal_4_13 - variation_4_13);
 difference_4_14 = TMath::Abs(nominal_4_14 - variation_4_14);
 difference_4_15 = TMath::Abs(nominal_4_15 - variation_4_15);
 difference_4_16 = TMath::Abs(nominal_4_16 - variation_4_16);
 difference_4_17 = TMath::Abs(nominal_4_17 - variation_4_17);
 difference_4_18 = TMath::Abs(nominal_4_18 - variation_4_18);
 difference_4_19 = TMath::Abs(nominal_4_19 - variation_4_19);
 difference_4_20 = TMath::Abs(nominal_4_20 - variation_4_20);


        TH1F* Ttbar_1_down = new TH1F("Ttbar_1_down", "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_2_down = new TH1F("Ttbar_2_down", "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_1_up   = new TH1F("Ttbar_1_up",   "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_2_up   = new TH1F("Ttbar_2_up",   "Merged histogram", newrec*4, 0, 20); 
        TH1F* Ttbar_3_down = new TH1F("Ttbar_3_down", "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_4_down = new TH1F("Ttbar_4_down", "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_3_up   = new TH1F("Ttbar_3_up",   "Merged histogram", newrec*4, 0, 20);
        TH1F* Ttbar_4_up   = new TH1F("Ttbar_4_up",   "Merged histogram", newrec*4, 0, 20);

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

Ttbar_2_down->SetBinContent(1, nominal_2_1 - difference_2_1);
Ttbar_2_down->SetBinContent(2, nominal_2_2 - difference_2_2);
Ttbar_2_down->SetBinContent(3, nominal_2_3 - difference_2_3);
Ttbar_2_down->SetBinContent(4, nominal_2_4 - difference_2_4);
Ttbar_2_down->SetBinContent(5, nominal_2_5 - difference_2_5);
Ttbar_2_down->SetBinContent(6, nominal_2_6 - difference_2_6);
Ttbar_2_down->SetBinContent(7, nominal_2_7 - difference_2_7);
Ttbar_2_down->SetBinContent(8, nominal_2_8 - difference_2_8);
Ttbar_2_down->SetBinContent(9, nominal_2_9 - difference_2_9);
Ttbar_2_down->SetBinContent(10, nominal_2_10 - difference_2_10);
Ttbar_2_down->SetBinContent(11, nominal_2_11 - difference_2_11);
Ttbar_2_down->SetBinContent(12, nominal_2_12 - difference_2_12);
Ttbar_2_down->SetBinContent(13, nominal_2_13 - difference_2_13);
Ttbar_2_down->SetBinContent(14, nominal_2_14 - difference_2_14);
Ttbar_2_down->SetBinContent(15, nominal_2_15 - difference_2_15);
Ttbar_2_down->SetBinContent(16, nominal_2_16 - difference_2_16);
Ttbar_2_down->SetBinContent(17, nominal_2_17 - difference_2_17);
Ttbar_2_down->SetBinContent(18, nominal_2_18 - difference_2_18);
Ttbar_2_down->SetBinContent(19, nominal_2_19 - difference_2_19);
Ttbar_2_down->SetBinContent(20, nominal_2_20 - difference_2_20);

Ttbar_2_up->SetBinContent(1, nominal_2_1 + difference_2_1);
Ttbar_2_up->SetBinContent(2, nominal_2_2 + difference_2_2);
Ttbar_2_up->SetBinContent(3, nominal_2_3 + difference_2_3);
Ttbar_2_up->SetBinContent(4, nominal_2_4 + difference_2_4);
Ttbar_2_up->SetBinContent(5, nominal_2_5 + difference_2_5);
Ttbar_2_up->SetBinContent(6, nominal_2_6 + difference_2_6);
Ttbar_2_up->SetBinContent(7, nominal_2_7 + difference_2_7);
Ttbar_2_up->SetBinContent(8, nominal_2_8 + difference_2_8);
Ttbar_2_up->SetBinContent(9, nominal_2_9 + difference_2_9);
Ttbar_2_up->SetBinContent(10, nominal_2_10 + difference_2_10);
Ttbar_2_up->SetBinContent(11, nominal_2_11 + difference_2_11);
Ttbar_2_up->SetBinContent(12, nominal_2_12 + difference_2_12);
Ttbar_2_up->SetBinContent(13, nominal_2_13 + difference_2_13);
Ttbar_2_up->SetBinContent(14, nominal_2_14 + difference_2_14);
Ttbar_2_up->SetBinContent(15, nominal_2_15 + difference_2_15);
Ttbar_2_up->SetBinContent(16, nominal_2_16 + difference_2_16);
Ttbar_2_up->SetBinContent(17, nominal_2_17 + difference_2_17);
Ttbar_2_up->SetBinContent(18, nominal_2_18 + difference_2_18);
Ttbar_2_up->SetBinContent(19, nominal_2_19 + difference_2_19);
Ttbar_2_up->SetBinContent(20, nominal_2_20 + difference_2_20);


Ttbar_3_down->SetBinContent(1, nominal_3_1 - difference_3_1);
Ttbar_3_down->SetBinContent(2, nominal_3_2 - difference_3_2);
Ttbar_3_down->SetBinContent(3, nominal_3_3 - difference_3_3);
Ttbar_3_down->SetBinContent(4, nominal_3_4 - difference_3_4);
Ttbar_3_down->SetBinContent(5, nominal_3_5 - difference_3_5);
Ttbar_3_down->SetBinContent(6, nominal_3_6 - difference_3_6);
Ttbar_3_down->SetBinContent(7, nominal_3_7 - difference_3_7);
Ttbar_3_down->SetBinContent(8, nominal_3_8 - difference_3_8);
Ttbar_3_down->SetBinContent(9, nominal_3_9 - difference_3_9);
Ttbar_3_down->SetBinContent(10, nominal_3_10 - difference_3_10);
Ttbar_3_down->SetBinContent(11, nominal_3_11 - difference_3_11);
Ttbar_3_down->SetBinContent(12, nominal_3_12 - difference_3_12);
Ttbar_3_down->SetBinContent(13, nominal_3_13 - difference_3_13);
Ttbar_3_down->SetBinContent(14, nominal_3_14 - difference_3_14);
Ttbar_3_down->SetBinContent(15, nominal_3_15 - difference_3_15);
Ttbar_3_down->SetBinContent(16, nominal_3_16 - difference_3_16);
Ttbar_3_down->SetBinContent(17, nominal_3_17 - difference_3_17);
Ttbar_3_down->SetBinContent(18, nominal_3_18 - difference_3_18);
Ttbar_3_down->SetBinContent(19, nominal_3_19 - difference_3_19);
Ttbar_3_down->SetBinContent(20, nominal_3_20 - difference_3_20);

Ttbar_3_up->SetBinContent(1, nominal_3_1 + difference_3_1);
Ttbar_3_up->SetBinContent(2, nominal_3_2 + difference_3_2);
Ttbar_3_up->SetBinContent(3, nominal_3_3 + difference_3_3);
Ttbar_3_up->SetBinContent(4, nominal_3_4 + difference_3_4);
Ttbar_3_up->SetBinContent(5, nominal_3_5 + difference_3_5);
Ttbar_3_up->SetBinContent(6, nominal_3_6 + difference_3_6);
Ttbar_3_up->SetBinContent(7, nominal_3_7 + difference_3_7);
Ttbar_3_up->SetBinContent(8, nominal_3_8 + difference_3_8);
Ttbar_3_up->SetBinContent(9, nominal_3_9 + difference_3_9);
Ttbar_3_up->SetBinContent(10, nominal_3_10 + difference_3_10);
Ttbar_3_up->SetBinContent(11, nominal_3_11 + difference_3_11);
Ttbar_3_up->SetBinContent(12, nominal_3_12 + difference_3_12);
Ttbar_3_up->SetBinContent(13, nominal_3_13 + difference_3_13);
Ttbar_3_up->SetBinContent(14, nominal_3_14 + difference_3_14);
Ttbar_3_up->SetBinContent(15, nominal_3_15 + difference_3_15);
Ttbar_3_up->SetBinContent(16, nominal_3_16 + difference_3_16);
Ttbar_3_up->SetBinContent(17, nominal_3_17 + difference_3_17);
Ttbar_3_up->SetBinContent(18, nominal_3_18 + difference_3_18);
Ttbar_3_up->SetBinContent(19, nominal_3_19 + difference_3_19);
Ttbar_3_up->SetBinContent(20, nominal_3_20 + difference_3_20);

Ttbar_4_down->SetBinContent(1, nominal_4_1 - difference_4_1);
Ttbar_4_down->SetBinContent(2, nominal_4_2 - difference_4_2);
Ttbar_4_down->SetBinContent(3, nominal_4_3 - difference_4_3);
Ttbar_4_down->SetBinContent(4, nominal_4_4 - difference_4_4);
Ttbar_4_down->SetBinContent(5, nominal_4_5 - difference_4_5);
Ttbar_4_down->SetBinContent(6, nominal_4_6 - difference_4_6);
Ttbar_4_down->SetBinContent(7, nominal_4_7 - difference_4_7);
Ttbar_4_down->SetBinContent(8, nominal_4_8 - difference_4_8);
Ttbar_4_down->SetBinContent(9, nominal_4_9 - difference_4_9);
Ttbar_4_down->SetBinContent(10, nominal_4_10 - difference_4_10);
Ttbar_4_down->SetBinContent(11, nominal_4_11 - difference_4_11);
Ttbar_4_down->SetBinContent(12, nominal_4_12 - difference_4_12);
Ttbar_4_down->SetBinContent(13, nominal_4_13 - difference_4_13);
Ttbar_4_down->SetBinContent(14, nominal_4_14 - difference_4_14);
Ttbar_4_down->SetBinContent(15, nominal_4_15 - difference_4_15);
Ttbar_4_down->SetBinContent(16, nominal_4_16 - difference_4_16);
Ttbar_4_down->SetBinContent(17, nominal_4_17 - difference_4_17);
Ttbar_4_down->SetBinContent(18, nominal_4_18 - difference_4_18);
Ttbar_4_down->SetBinContent(19, nominal_4_19 - difference_4_19);
Ttbar_4_down->SetBinContent(20, nominal_4_20 - difference_4_20);

Ttbar_4_up->SetBinContent(1, nominal_4_1 + difference_4_1);
Ttbar_4_up->SetBinContent(2, nominal_4_2 + difference_4_2);
Ttbar_4_up->SetBinContent(3, nominal_4_3 + difference_4_3);
Ttbar_4_up->SetBinContent(4, nominal_4_4 + difference_4_4);
Ttbar_4_up->SetBinContent(5, nominal_4_5 + difference_4_5);
Ttbar_4_up->SetBinContent(6, nominal_4_6 + difference_4_6);
Ttbar_4_up->SetBinContent(7, nominal_4_7 + difference_4_7);
Ttbar_4_up->SetBinContent(8, nominal_4_8 + difference_4_8);
Ttbar_4_up->SetBinContent(9, nominal_4_9 + difference_4_9);
Ttbar_4_up->SetBinContent(10, nominal_4_10 + difference_4_10);
Ttbar_4_up->SetBinContent(11, nominal_4_11 + difference_4_11);
Ttbar_4_up->SetBinContent(12, nominal_4_12 + difference_4_12);
Ttbar_4_up->SetBinContent(13, nominal_4_13 + difference_4_13);
Ttbar_4_up->SetBinContent(14, nominal_4_14 + difference_4_14);
Ttbar_4_up->SetBinContent(15, nominal_4_15 + difference_4_15);
Ttbar_4_up->SetBinContent(16, nominal_4_16 + difference_4_16);
Ttbar_4_up->SetBinContent(17, nominal_4_17 + difference_4_17);
Ttbar_4_up->SetBinContent(18, nominal_4_18 + difference_4_18);
Ttbar_4_up->SetBinContent(19, nominal_4_19 + difference_4_19);
Ttbar_4_up->SetBinContent(20, nominal_4_20 + difference_4_20);


        string sys = "";
        if(text == "Ttbar_in_JECdown") sys = "JEC";
        if(text == "Ttbar_in_JERdown") sys = "JER";
  
        Ttbar_1_up->Write(Form("Ttbar_in_1_%sUp",sys.c_str()));
        Ttbar_2_up->Write(Form("Ttbar_in_2_%sUp",sys.c_str()));
        Ttbar_1_down->Write(Form("Ttbar_in_1_%sDown",sys.c_str()));
        Ttbar_2_down->Write(Form("Ttbar_in_2_%sDown",sys.c_str()));
        Ttbar_3_up->Write(Form("Ttbar_in_3_%sUp",sys.c_str()));
        Ttbar_4_up->Write(Form("Ttbar_in_4_%sUp",sys.c_str()));
        Ttbar_3_down->Write(Form("Ttbar_in_3_%sDown",sys.c_str()));
        Ttbar_4_down->Write(Form("Ttbar_in_4_%sDown",sys.c_str()));


        delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Back_5; delete Back_6; delete Back_7; delete Back_8; delete Back_9; delete Back_10; delete Back_11; delete Back_12; delete Back_13; delete Back_14; delete Back_15; delete Back_16; delete Back_bin1; delete Back_bin2; delete Back_bin3; delete Back_bin4; 
        delete Ttbar_1_up; delete Ttbar_1_down; delete Ttbar_2_up; delete Ttbar_2_down; delete Ttbar_3_up; delete Ttbar_3_down; delete Ttbar_4_up; delete Ttbar_4_down;
     
     }



  }
}
