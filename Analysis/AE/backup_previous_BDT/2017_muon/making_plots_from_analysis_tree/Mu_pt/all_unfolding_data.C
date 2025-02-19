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

void all_unfolding_data(float bin, float low, float high, string variable="")
{
  
TFile out("Input_undfolding_data_all.root","recreate");
string texts[]={"DATA","TTToSemiLeptonic","WJetsToLNu","ST","DYJetsToLL_M-50_HT","QCD_HT","Diboson","TTTo2L2Nu","TTToHadronic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/data/dust/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.MC.%s_2017.root/AnalysisTree",text.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//--------Unfold----------??

       if(text == "DATA"){
 
       TChain *chreco_data = new TChain("AnalysisTree","");
       chreco_data->Add("/data/dust/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2017.root/AnalysisTree");
       TTree *treereco_data = (TTree*) chreco_data;
 
       TH1F *Back_1 = new TH1F("Back_1","",bin,low,high);
       string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459)";
       treereco_data->Project("Back_1",variable.c_str(),Form("%s",selcuts_boosted_central_1.c_str()));
       Back_1->Write("data_obs");
       delete Back_1;


       }else if(text == "TTToSemiLeptonic"){

       string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "hdamp_up", "hdamp_down","prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

 
        for(const string &syst : systs){

            TH1F *Back_1 = new TH1F("Back_1","",bin,low,high);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459)";

            treereco_ttbar_semi->Project("Back_1",variable.c_str(),Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";
            if(syst == "weight_sfmu_id_up/weight_sfmu_id") sys = "muIDUp";  if(syst == "weight_sfmu_id_down/weight_sfmu_id") sys = "muIDDown";
            if(syst == "weight_sfmu_iso_up/weight_sfmu_iso") sys = "muISOUp";  if(syst == "weight_sfmu_iso_down/weight_sfmu_iso") sys = "muISODown";
            if(syst == "weight_sfmu_trigger_up/weight_sfmu_trigger") sys = "muHLTUp";  if(syst == "weight_sfmu_trigger_down/weight_sfmu_trigger") sys = "muHLTDown";
            if(syst == "weight_toptagsf_corr_up/weight_toptagsf") sys = "toptag_corrUp";  if(syst == "weight_toptagsf_corr_down/weight_toptagsf") sys = "toptag_corrDown";
            if(syst == "weight_toptagsf_uncorr_up/weight_toptagsf") sys = "toptag_uncorrUp";  if(syst == "weight_toptagsf_uncorr_down/weight_toptagsf") sys = "toptag_uncorrDown";
            if(syst == "weight_fsr_sqrt2_up") sys = "FSRUp";  if(syst == "weight_fsr_sqrt2_down") sys = "FSRDown";
            if(syst == "weight_isr_sqrt2_up") sys = "ISRUp";  if(syst == "weight_isr_sqrt2_down") sys = "ISRDown";
            if(syst == "weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst == "weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst == "weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown";
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown";
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc17Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc17Down";
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc17Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc17Down";
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring17Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring17Down";
            if(syst == "hdamp_up") sys = "hdampUp";                                         if(syst == "hdamp_down") sys = "hdampDown";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

        for(int k=1;k<=1;k++){

            string syst="wgtMC__PDF["+std::to_string(k)+"]"+"/"+"wgtMC__PDF[1]";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",bin,low,high);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459)";
            treereco_ttbar_semi->Project("Back_1",variable.c_str(),Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Up";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

        for(int k=1;k<=1;k++){

            string syst="1";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",bin,low,high);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459)";
            treereco_ttbar_semi->Project("Back_1",variable.c_str(),Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Down";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

   
       } else{


        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag"};
 

        for(const string &syst : systs){

            TH1F *Back_1 = new TH1F("Back_1","",bin,low,high);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459)";
   
            treereco_ttbar_semi->Project("Back_1",variable.c_str(),Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";  
            if(syst == "weight_sfmu_id_up/weight_sfmu_id") sys = "muIDUp";  if(syst == "weight_sfmu_id_down/weight_sfmu_id") sys = "muIDDown"; 
            if(syst == "weight_sfmu_iso_up/weight_sfmu_iso") sys = "muISOUp";  if(syst == "weight_sfmu_iso_down/weight_sfmu_iso") sys = "muISODown";  
            if(syst == "weight_sfmu_trigger_up/weight_sfmu_trigger") sys = "muHLTUp";  if(syst == "weight_sfmu_trigger_down/weight_sfmu_trigger") sys = "muHLTDown";
            if(syst == "weight_toptagsf_corr_up/weight_toptagsf") sys = "toptag_corrUp";  if(syst == "weight_toptagsf_corr_down/weight_toptagsf") sys = "toptag_corrDown"; 
            if(syst == "weight_toptagsf_uncorr_up/weight_toptagsf") sys = "toptag_uncorrUp";  if(syst == "weight_toptagsf_uncorr_down/weight_toptagsf") sys = "toptag_uncorrDown"; 
            if(syst == "weight_fsr_sqrt2_up") sys = "FSRUp";  if(syst == "weight_fsr_sqrt2_down") sys = "FSRDown";
            if(syst == "weight_isr_sqrt2_up") sys = "ISRUp";  if(syst == "weight_isr_sqrt2_down") sys = "ISRDown";
            if(syst == "weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst == "weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst == "weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown"   ;  
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown"   ;
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc17Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc17Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc17Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc17Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring17Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring17Down"  ;
 
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;


        }

    }  
     
}
 
}


