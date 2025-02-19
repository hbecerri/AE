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

void jes_ttbar_out(string var_name = "", string var_gen = "", string region = "", string year = "2016post")
{
  
TFile out("Input_undfolding_data_jes_out.root","recreate");
string texts[]={"ttbar_out","ttbar_out_JECdown","ttbar_out_JERdown"};

Float_t nominal_1_1 = 0, nominal_1_2 = 0, nominal_1_3 = 0, nominal_1_4 = 0, nominal_1_5 = 0, nominal_1_6 = 0, nominal_1_7 = 0, nominal_1_8 = 0, nominal_1_9 = 0, nominal_1_10 = 0;
Float_t variation_1_1 = 0, variation_1_2 = 0, variation_1_3 = 0, variation_1_4 = 0, variation_1_5 = 0, variation_1_6 = 0, variation_1_7 = 0, variation_1_8 = 0, variation_1_9 = 0, variation_1_10 = 0;
Float_t difference_1_1 = 0, difference_1_2 = 0, difference_1_3 = 0, difference_1_4 = 0, difference_1_5 = 0, difference_1_6 = 0, difference_1_7 = 0, difference_1_8 = 0, difference_1_9 = 0, difference_1_10 = 0;
   
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//array for variable 

    int len = 3, len_rec = 3;
    Float_t new_rec[]  = {0,0.2,0.4,0.6,0.8,1};
    
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "ttbar_out"){

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2016post_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && (Boost_top_E - Boost_antitop_E < 0) && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && (Boost_top_E - Boost_antitop_E > 0) && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));

            TH1F* Back = new TH1F("Back", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back->SetBinContent(i, Back_1->GetBinContent(i));
              Back->SetBinError(i, Back_1->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back->SetBinContent(i + 5, Back_2->GetBinContent(i));
              Back->SetBinError(i + 5, Back_2->GetBinError(i));
            }

            nominal_1_1  = Back->GetBinContent(1); 
	    nominal_1_2  = Back->GetBinContent(2); 
  	    nominal_1_3  = Back->GetBinContent(3); 
 	    nominal_1_4  = Back->GetBinContent(4); 
	    nominal_1_5  = Back->GetBinContent(5); 
	    nominal_1_6  = Back->GetBinContent(6); 
	    nominal_1_7  = Back->GetBinContent(7); 
	    nominal_1_8  = Back->GetBinContent(8); 
	    nominal_1_9  = Back->GetBinContent(9); 
	    nominal_1_10 = Back->GetBinContent(10);
 
            delete Back_1; delete Back_2; delete Back; 

     }else{

            string syst = "1";

            TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
            chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2016post_electron/%s.root/Events",text.c_str()));
            TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && (Boost_top_E - Boost_antitop_E < 0) && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && (Boost_top_E - Boost_antitop_E > 0) && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";

            treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));

            TH1F* Back = new TH1F("Back", "Merged histogram", newrec*2, 0, 10);
            for (int i = 1; i <= 5; ++i) {
              Back->SetBinContent(i, Back_1->GetBinContent(i));
              Back->SetBinError(i, Back_1->GetBinError(i));
            }
            for (int i = 1; i <= 5; ++i) {
              Back->SetBinContent(i + 5, Back_2->GetBinContent(i));
              Back->SetBinError(i + 5, Back_2->GetBinError(i));
            }

	    variation_1_1 = Back->GetBinContent(1); 
	    variation_1_2 = Back->GetBinContent(2); 
	    variation_1_3 = Back->GetBinContent(3); 
 	    variation_1_4 = Back->GetBinContent(4); 
	    variation_1_5 = Back->GetBinContent(5); 
	    variation_1_6 = Back->GetBinContent(6); 
	    variation_1_7 = Back->GetBinContent(7); 
	    variation_1_8 = Back->GetBinContent(8); 
	    variation_1_9 = Back->GetBinContent(9); 
	    variation_1_10 = Back->GetBinContent(10);
 
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

        TH1F* Ttbar_1_down = new TH1F("Ttbar_1_down", "Merged histogram", newrec*2, 0, 10);
        TH1F* Ttbar_1_up   = new TH1F("Ttbar_1_up",   "Merged histogram", newrec*2, 0, 10);

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

        for (int i = 1; i <= 10; ++i) {
            Ttbar_1_down->SetBinError(i,Ttbar_1_down->GetBinError(i)/30);
            Ttbar_1_up->SetBinError(i,Ttbar_1_down->GetBinError(i)/30);
        }

        string sys = "";
        if(text == "ttbar_out_JECdown") sys = "JEC";
        if(text == "ttbar_out_JERdown") sys = "JER";

        Ttbar_1_up->Write(Form("ttbar_out_%sUp",sys.c_str()));
        Ttbar_1_down->Write(Form("ttbar_out_%sDown",sys.c_str()));
  
        delete Back_1; delete Back_2; delete Back; delete Ttbar_1_up; delete Ttbar_1_down;
    
     }

  }
}
