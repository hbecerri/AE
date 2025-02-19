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
//string texts[]={"Ttbar_in","Ttbar_in_JECdown","Ttbar_in_JECup","Ttbar_in_JERdown","Ttbar_in_JERup"};
string texts[]={"Ttbar_in","Ttbar_in_JECdown","Ttbar_in_JERdown"};

Float_t nominal_1_1 = 0, nominal_1_2 = 0, nominal_1_3 = 0, nominal_1_4 = 0, nominal_1_5 = 0, nominal_1_6 = 0, nominal_1_7 = 0, nominal_1_8 = 0, nominal_1_9 = 0, nominal_1_10 = 0;
Float_t nominal_2_1 = 0, nominal_2_2 = 0, nominal_2_3 = 0, nominal_2_4 = 0, nominal_2_5 = 0, nominal_2_6 = 0, nominal_2_7 = 0, nominal_2_8 = 0, nominal_2_9 = 0, nominal_2_10 = 0;
Float_t variation_1_1 = 0, variation_1_2 = 0, variation_1_3 = 0, variation_1_4 = 0, variation_1_5 = 0, variation_1_6 = 0, variation_1_7 = 0, variation_1_8 = 0, variation_1_9 = 0, variation_1_10 = 0;
Float_t variation_2_1 = 0, variation_2_2 = 0, variation_2_3 = 0, variation_2_4 = 0, variation_2_5 = 0, variation_2_6 = 0, variation_2_7 = 0, variation_2_8 = 0, variation_2_9 = 0, variation_2_10 = 0;
Float_t difference_1_1 = 0, difference_1_2 = 0, difference_1_3 = 0, difference_1_4 = 0, difference_1_5 = 0, difference_1_6 = 0, difference_1_7 = 0, difference_1_8 = 0, difference_1_9 = 0, difference_1_10 = 0;
Float_t difference_2_1 = 0, difference_2_2 = 0, difference_2_3 = 0, difference_2_4 = 0, difference_2_5 = 0, difference_2_6 = 0, difference_2_7 = 0, difference_2_8 = 0, difference_2_9 = 0, difference_2_10 = 0;
   
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
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2016preVFP_muon/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3 = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4 = new TH1F("Back_4","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)";
            string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)";
            string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

             TH1F* Back_neg = new TH1F("Back_neg", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back_neg->SetBinContent(i, Back_1->GetBinContent(i));
              Back_neg->SetBinError(i, Back_1->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back_neg->SetBinContent(i + 5, Back_2->GetBinContent(i));
              Back_neg->SetBinError(i + 5, Back_2->GetBinError(i));
            }

             TH1F* Back_pos = new TH1F("Back_pos", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back_pos->SetBinContent(i, Back_3->GetBinContent(i));
              Back_pos->SetBinError(i, Back_3->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back_pos->SetBinContent(i + 5, Back_4->GetBinContent(i));
              Back_pos->SetBinError(i + 5, Back_4->GetBinError(i));
            }

	nominal_1_1 = Back_neg->GetBinContent(1); 
	nominal_1_2 = Back_neg->GetBinContent(2); 
	nominal_1_3 = Back_neg->GetBinContent(3); 
	nominal_1_4 = Back_neg->GetBinContent(4); 
	nominal_1_5 = Back_neg->GetBinContent(5); 
	nominal_1_6 = Back_neg->GetBinContent(6); 
	nominal_1_7 = Back_neg->GetBinContent(7); 
	nominal_1_8 = Back_neg->GetBinContent(8); 
	nominal_1_9 = Back_neg->GetBinContent(9); 
	nominal_1_10 = Back_neg->GetBinContent(10);
 
	nominal_2_1 = Back_pos->GetBinContent(1); 
	nominal_2_2 = Back_pos->GetBinContent(2); 
	nominal_2_3 = Back_pos->GetBinContent(3); 
	nominal_2_4 = Back_pos->GetBinContent(4); 
	nominal_2_5 = Back_pos->GetBinContent(5); 
	nominal_2_6 = Back_pos->GetBinContent(6); 
	nominal_2_7 = Back_pos->GetBinContent(7); 
	nominal_2_8 = Back_pos->GetBinContent(8); 
	nominal_2_9 = Back_pos->GetBinContent(9); 
	nominal_2_10 = Back_pos->GetBinContent(10);
 
            delete Back_1; delete Back_2; ;delete Back_neg; delete Back_3; delete Back_4;  ;delete Back_pos; 

     }else{

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2016preVFP_muon/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);
            TH1F *Back_3 = new TH1F("Back_3","",newrec,new_rec);
            TH1F *Back_4 = new TH1F("Back_4","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)";
            string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)";
            string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

             TH1F* Back_neg = new TH1F("Back_neg", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back_neg->SetBinContent(i, Back_1->GetBinContent(i));
              Back_neg->SetBinError(i, Back_1->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back_neg->SetBinContent(i + 5, Back_2->GetBinContent(i));
              Back_neg->SetBinError(i + 5, Back_2->GetBinError(i));
            }

             TH1F* Back_pos = new TH1F("Back_pos", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back_pos->SetBinContent(i, Back_3->GetBinContent(i));
              Back_pos->SetBinError(i, Back_3->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back_pos->SetBinContent(i + 5, Back_4->GetBinContent(i));
              Back_pos->SetBinError(i + 5, Back_4->GetBinError(i));
            }

	variation_1_1 = Back_neg->GetBinContent(1); 
	variation_1_2 = Back_neg->GetBinContent(2); 
	variation_1_3 = Back_neg->GetBinContent(3); 
	variation_1_4 = Back_neg->GetBinContent(4); 
	variation_1_5 = Back_neg->GetBinContent(5); 
	variation_1_6 = Back_neg->GetBinContent(6); 
	variation_1_7 = Back_neg->GetBinContent(7); 
	variation_1_8 = Back_neg->GetBinContent(8); 
	variation_1_9 = Back_neg->GetBinContent(9); 
	variation_1_10 = Back_neg->GetBinContent(10);

	variation_2_1 = Back_pos->GetBinContent(1); 
	variation_2_2 = Back_pos->GetBinContent(2); 
	variation_2_3 = Back_pos->GetBinContent(3); 
	variation_2_4 = Back_pos->GetBinContent(4); 
	variation_2_5 = Back_pos->GetBinContent(5); 
	variation_2_6 = Back_pos->GetBinContent(6); 
	variation_2_7 = Back_pos->GetBinContent(7); 
	variation_2_8 = Back_pos->GetBinContent(8); 
	variation_2_9 = Back_pos->GetBinContent(9); 
	variation_2_10 = Back_pos->GetBinContent(10);
 
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

        TH1F* Ttbar_1_down = new TH1F("Ttbar_1_down", "Merged histogram", newrec*2, 0, 10);
        TH1F* Ttbar_2_down = new TH1F("Ttbar_2_down", "Merged histogram", newrec*2, 0, 10);
        TH1F* Ttbar_1_up   = new TH1F("Ttbar_1_up",   "Merged histogram", newrec*2, 0, 10);
        TH1F* Ttbar_2_up   = new TH1F("Ttbar_2_up",   "Merged histogram", newrec*2, 0, 10); 

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

        string sys = "";
        if(text == "Ttbar_in_JECdown") sys = "JEC";
        if(text == "Ttbar_in_JERdown") sys = "JER";

        for (int i = 1; i <= 10; ++i) {
            Ttbar_1_down->SetBinError(i,Ttbar_1_down->GetBinError(i)/30);
            Ttbar_1_up->SetBinError(i,Ttbar_1_down->GetBinError(i)/30);
            Ttbar_2_down->SetBinError(i,Ttbar_2_down->GetBinError(i)/30);
            Ttbar_2_up->SetBinError(i,Ttbar_2_down->GetBinError(i)/30);
        } 
 
  
        Ttbar_1_up->Write(Form("Ttbar_in_1_%sUp",sys.c_str()));
        Ttbar_2_up->Write(Form("Ttbar_in_2_%sUp",sys.c_str()));
        Ttbar_1_down->Write(Form("Ttbar_in_1_%sDown",sys.c_str()));
        Ttbar_2_down->Write(Form("Ttbar_in_2_%sDown",sys.c_str()));
 
            delete Back_1; delete Back_2; ;delete Back_neg; delete Back_3; delete Back_4;  ;delete Back_pos; delete Ttbar_1_up; delete Ttbar_1_down; delete Ttbar_2_up; delete Ttbar_2_down;
    
     }



  }
}
