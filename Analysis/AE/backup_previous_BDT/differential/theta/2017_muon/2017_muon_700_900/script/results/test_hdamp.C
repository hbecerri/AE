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

void test_hdamp(string var_name = "", string var_gen = "", string region = "", string year = "2017")
{
  
TFile out("Input_undfolding_data_.root","recreate");
string texts[]={"TTToSemiLeptonic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/muon_good_with_new_variables/hdamp/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL17_15.root/AnalysisTree",text.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t bins_gen[] = {-2000,0,2000};
    Float_t new_rec[]  = {-2000,0,2000};

//    int len = 10, len_rec = 10;
//    Float_t bins_gen[] = {0,100,200,300,400,700,600,700,800,900,1000};
//    Float_t new_rec[]  = {0,100,200,300,400,700,600,700,800,900,1000};
  
    
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t   binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "DATA"){
 
       TChain *chreco_data = new TChain("AnalysisTree","");
       chreco_data->Add("/nfs/dust/cms/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2017.root/AnalysisTree");
       TTree *treereco_data = (TTree*) chreco_data;
 
       TH1F *Back_1 = new TH1F("Back_1","",2,-2000,2000);
       string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 700 && chi2 < 30 && Boost_Ak4_add_pt > 0)";
       treereco_data->Project("Back_1","top_E - antitop_E",Form("%s",selcuts_boosted_central_1.c_str()));
       Back_1->Write("data_obs");
       delete Back_1;


       }else if(text == "TTToSemiLeptonic"){

//       string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

        string systs[] = {"1", "new_var", "new_var_down"};
   
        for(const string &syst : systs){

            cout << syst << endl; 
 
            TH1F *Migration_Matrix_1 = new TH1F("Migration_Matrix_1","",newrec,new_rec); 
            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 700 && chi2 < 30 && Boost_Ak4_add_pt > 0)";

           treereco_ttbar_semi->Project("Migration_Matrix_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
 
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "new_var") sys = "hdampUp"       ; if(syst == "new_var_down") sys = "hdampDown"  ; 

            Migration_Matrix_1->Write(Form("%s_%s",text.c_str(),sys.c_str()));
           
            delete Migration_Matrix_1; 
           
         }

       } 
 
}
}

