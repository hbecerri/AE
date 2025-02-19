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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2016preVFP")
{
  
TFile out("Input_undfolding_data_all.root","recreate");
string texts[]={"data","Ttbar_in", "ttbar_out","wjets","st","dy","qcd","diboson","ttbar_ll","ttbar_had"};


for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2016preVFP_electron/%s.root/Events",text.c_str()));

    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t new_rec[]  = {0,0.2,0.4,0.6,0.8,1};
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "data"){

       TChain *chreco_data = new TChain("Events","");
       chreco_data->Add("/nfs/dust/cms/user/hugobg/analysis/electron/BDT/2016preVFP_electron/data.root/Events");
       TTree *treereco_data = (TTree*) chreco_data;

       TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
       TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);
       TH1F *Back_3 = new TH1F("Back_3","",newrec,new_rec);
       TH1F *Back_4 = new TH1F("Back_4","",newrec,new_rec);

       string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0)";
       string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0)";
       string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0)";
       string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0)";

       treereco_data->Project("Back_1","BDT",Form("%s",selcuts_boosted_central_1.c_str()));
       treereco_data->Project("Back_2","BDT",Form("%s",selcuts_boosted_central_2.c_str()));
       treereco_data->Project("Back_3","BDT",Form("%s",selcuts_boosted_central_3.c_str()));
       treereco_data->Project("Back_4","BDT",Form("%s",selcuts_boosted_central_4.c_str()));

       TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",newrec*4,0,20);
       for (int i = 1; i <= 5; ++i) {
            Ttbar_1_nominal->SetBinContent(i,Back_1->GetBinContent(i));
            Ttbar_1_nominal->SetBinContent(i+5,Back_2->GetBinContent(i));
            Ttbar_1_nominal->SetBinContent(i+10,Back_3->GetBinContent(i));
            Ttbar_1_nominal->SetBinContent(i+15,Back_4->GetBinContent(i));
       }

       Ttbar_1_nominal->Write("data_obs");

       delete Ttbar_1_nominal; delete Back_1; delete Back_2; delete Back_3; delete Back_4;


       }

       else if(text == "Ttbar_in"){

           string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfelec_id_up/weight_sfelec_id", "weight_sfelec_id_down/weight_sfelec_id","weight_sfelec_trigger_up/weight_sfelec_trigger","weight_sfelec_trigger_down/weight_sfelec_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "hdamp_up", "hdamp_down"};

            for(const string &syst : systs){

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

            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";
            if(syst == "weight_sfelec_id_up/weight_sfelec_id") sys = "eleIDUp";  if(syst == "weight_sfelec_id_down/weight_sfelec_id") sys = "eleIDDown";
            if(syst == "weight_sfelec_trigger_up/weight_sfelec_trigger") sys = "eleHLTUp";  if(syst == "weight_sfelec_trigger_down/weight_sfelec_trigger") sys = "eleHLTDown";
            if(syst == "weight_toptagsf_corr_up/weight_toptagsf") sys = "toptag_corrUp";  if(syst == "weight_toptagsf_corr_down/weight_toptagsf") sys = "toptag_corrDown";
            if(syst == "weight_toptagsf_uncorr_up/weight_toptagsf") sys = "toptag_uncorrUp";  if(syst == "weight_toptagsf_uncorr_down/weight_toptagsf") sys = "toptag_uncorrDown";
            if(syst == "weight_fsr_sqrt2_up") sys = "FSRUp";  if(syst == "weight_fsr_sqrt2_down") sys = "FSRDown";
            if(syst == "weight_isr_sqrt2_up") sys = "ISRUp";  if(syst == "weight_isr_sqrt2_down") sys = "ISRDown";
            if(syst == "weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst == "weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst == "weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown"   ;
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown"   ;
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc18Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc18Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc18Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc18Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring18Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring18Down"  ;
            if(syst == "weight_toppt_a_up/weight_toppt_nominal") sys = "top_pt_rewUp"       ; if(syst == "weight_toppt_a_down/weight_toppt_nominal") sys = "top_pt_rewDown"  ;
            if(syst == "hdamp_up") sys = "hdampUp"; if(syst == "hdamp_down") sys = "hdampDown";


            TH1F* Back_bin1 = new TH1F("Back_bin1", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin1->SetBinContent(i,Back_1->GetBinContent(i));
                Back_bin1->SetBinContent(i+5,Back_2->GetBinContent(i));
                Back_bin1->SetBinContent(i+10,Back_3->GetBinContent(i));
                Back_bin1->SetBinContent(i+15,Back_4->GetBinContent(i));
                Back_bin1->SetBinError(i,Back_1->GetBinError(i));
                Back_bin1->SetBinError(i+5,Back_2->GetBinError(i));
                Back_bin1->SetBinError(i+10,Back_3->GetBinError(i));
                Back_bin1->SetBinError(i+15,Back_4->GetBinError(i));
            } 

            TH1F* Back_bin2 = new TH1F("Back_bin2", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin2->SetBinContent(i,Back_5->GetBinContent(i));
                Back_bin2->SetBinContent(i+5,Back_6->GetBinContent(i));
                Back_bin2->SetBinContent(i+10,Back_7->GetBinContent(i));
                Back_bin2->SetBinContent(i+15,Back_8->GetBinContent(i));
                Back_bin2->SetBinError(i,Back_5->GetBinError(i));
                Back_bin2->SetBinError(i+5,Back_6->GetBinError(i));
                Back_bin2->SetBinError(i+10,Back_7->GetBinError(i));
                Back_bin2->SetBinError(i+15,Back_8->GetBinError(i));
            }

            TH1F* Back_bin3 = new TH1F("Back_bin3", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin3->SetBinContent(i,Back_9->GetBinContent(i));
                Back_bin3->SetBinContent(i+5,Back_10->GetBinContent(i));
                Back_bin3->SetBinContent(i+10,Back_11->GetBinContent(i));
                Back_bin3->SetBinContent(i+15,Back_12->GetBinContent(i));
                Back_bin3->SetBinError(i,Back_9->GetBinError(i));
                Back_bin3->SetBinError(i+5,Back_10->GetBinError(i));
                Back_bin3->SetBinError(i+10,Back_11->GetBinError(i));
                Back_bin3->SetBinError(i+15,Back_12->GetBinError(i));
            }


            TH1F* Back_bin4 = new TH1F("Back_bin4", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin4->SetBinContent(i,Back_13->GetBinContent(i));
                Back_bin4->SetBinContent(i+5,Back_14->GetBinContent(i));
                Back_bin4->SetBinContent(i+10,Back_15->GetBinContent(i));
                Back_bin4->SetBinContent(i+15,Back_16->GetBinContent(i));
                Back_bin4->SetBinError(i,Back_13->GetBinError(i));
                Back_bin4->SetBinError(i+5,Back_14->GetBinError(i));
                Back_bin4->SetBinError(i+10,Back_15->GetBinError(i));
                Back_bin4->SetBinError(i+15,Back_16->GetBinError(i));
            }


            Back_bin1->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Back_bin2->Write(Form("%s_2_%s",text.c_str(),sys.c_str())); 
            Back_bin3->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Back_bin4->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));


            delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Back_5; delete Back_6; delete Back_7; delete Back_8; delete Back_9; delete Back_10; delete Back_11; delete Back_12; delete Back_13; delete Back_14; delete Back_15; delete Back_16; delete Back_bin1; delete Back_bin2; delete Back_bin3; delete Back_bin4;

          
            }


         for(int k=1;k<=99;k++){

            string syst="1";

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

            string sys = "LHEPdfWeight_"+std::to_string(k)+"Down";

            TH1F* Back_bin1 = new TH1F("Back_bin1", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin1->SetBinContent(i,Back_1->GetBinContent(i));
                Back_bin1->SetBinContent(i+5,Back_2->GetBinContent(i));
                Back_bin1->SetBinContent(i+10,Back_3->GetBinContent(i));
                Back_bin1->SetBinContent(i+15,Back_4->GetBinContent(i));
                Back_bin1->SetBinError(i,Back_1->GetBinError(i));
                Back_bin1->SetBinError(i+5,Back_2->GetBinError(i));
                Back_bin1->SetBinError(i+10,Back_3->GetBinError(i));
                Back_bin1->SetBinError(i+15,Back_4->GetBinError(i));
            }

            TH1F* Back_bin2 = new TH1F("Back_bin2", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin2->SetBinContent(i,Back_5->GetBinContent(i));
                Back_bin2->SetBinContent(i+5,Back_6->GetBinContent(i));
                Back_bin2->SetBinContent(i+10,Back_7->GetBinContent(i));
                Back_bin2->SetBinContent(i+15,Back_8->GetBinContent(i));
                Back_bin2->SetBinError(i,Back_5->GetBinError(i));
                Back_bin2->SetBinError(i+5,Back_6->GetBinError(i));
                Back_bin2->SetBinError(i+10,Back_7->GetBinError(i));
                Back_bin2->SetBinError(i+15,Back_8->GetBinError(i));
            }

            TH1F* Back_bin3 = new TH1F("Back_bin3", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin3->SetBinContent(i,Back_9->GetBinContent(i));
                Back_bin3->SetBinContent(i+5,Back_10->GetBinContent(i));
                Back_bin3->SetBinContent(i+10,Back_11->GetBinContent(i));
                Back_bin3->SetBinContent(i+15,Back_12->GetBinContent(i));
                Back_bin3->SetBinError(i,Back_9->GetBinError(i));
                Back_bin3->SetBinError(i+5,Back_10->GetBinError(i));
                Back_bin3->SetBinError(i+10,Back_11->GetBinError(i));
                Back_bin3->SetBinError(i+15,Back_12->GetBinError(i));
            }

            TH1F* Back_bin4 = new TH1F("Back_bin4", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin4->SetBinContent(i,Back_13->GetBinContent(i));
                Back_bin4->SetBinContent(i+5,Back_14->GetBinContent(i));
                Back_bin4->SetBinContent(i+10,Back_15->GetBinContent(i));
                Back_bin4->SetBinContent(i+15,Back_16->GetBinContent(i));
                Back_bin4->SetBinError(i,Back_13->GetBinError(i));
                Back_bin4->SetBinError(i+5,Back_14->GetBinError(i));
                Back_bin4->SetBinError(i+10,Back_15->GetBinError(i));
                Back_bin4->SetBinError(i+15,Back_16->GetBinError(i));
            }

            Back_bin1->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Back_bin2->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            Back_bin3->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Back_bin4->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));

            delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Back_5; delete Back_6; delete Back_7; delete Back_8; delete Back_9; delete Back_10; delete Back_11; delete Back_12; delete Back_13; delete Back_14; delete Back_15; delete Back_16; delete Back_bin1; delete Back_bin2; delete Back_bin3; delete Back_bin4;

         }

         for(int k=1;k<=99;k++){

            string syst="LHEPdfWeight_"+std::to_string(k);

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


            string sys = "LHEPdfWeight_"+std::to_string(k)+"Up";

            TH1F* Back_bin1 = new TH1F("Back_bin1", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin1->SetBinContent(i,Back_1->GetBinContent(i));
                Back_bin1->SetBinContent(i+5,Back_2->GetBinContent(i));
                Back_bin1->SetBinContent(i+10,Back_3->GetBinContent(i));
                Back_bin1->SetBinContent(i+15,Back_4->GetBinContent(i));
                Back_bin1->SetBinError(i,Back_1->GetBinError(i));
                Back_bin1->SetBinError(i+5,Back_2->GetBinError(i));
                Back_bin1->SetBinError(i+10,Back_3->GetBinError(i));
                Back_bin1->SetBinError(i+15,Back_4->GetBinError(i));
            }

            TH1F* Back_bin2 = new TH1F("Back_bin2", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin2->SetBinContent(i,Back_5->GetBinContent(i));
                Back_bin2->SetBinContent(i+5,Back_6->GetBinContent(i));
                Back_bin2->SetBinContent(i+10,Back_7->GetBinContent(i));
                Back_bin2->SetBinContent(i+15,Back_8->GetBinContent(i));
                Back_bin2->SetBinError(i,Back_5->GetBinError(i));
                Back_bin2->SetBinError(i+5,Back_6->GetBinError(i));
                Back_bin2->SetBinError(i+10,Back_7->GetBinError(i));
                Back_bin2->SetBinError(i+15,Back_8->GetBinError(i));
            }

            TH1F* Back_bin3 = new TH1F("Back_bin3", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin3->SetBinContent(i,Back_9->GetBinContent(i));
                Back_bin3->SetBinContent(i+5,Back_10->GetBinContent(i));
                Back_bin3->SetBinContent(i+10,Back_11->GetBinContent(i));
                Back_bin3->SetBinContent(i+15,Back_12->GetBinContent(i));
                Back_bin3->SetBinError(i,Back_9->GetBinError(i));
                Back_bin3->SetBinError(i+5,Back_10->GetBinError(i));
                Back_bin3->SetBinError(i+10,Back_11->GetBinError(i));
                Back_bin3->SetBinError(i+15,Back_12->GetBinError(i));
            }

            TH1F* Back_bin4 = new TH1F("Back_bin4", "Merged histogram", newrec*4, 0, 20);
            for (int i = 1; i <= 5; ++i) {
                Back_bin4->SetBinContent(i,Back_13->GetBinContent(i));
                Back_bin4->SetBinContent(i+5,Back_14->GetBinContent(i));
                Back_bin4->SetBinContent(i+10,Back_15->GetBinContent(i));
                Back_bin4->SetBinContent(i+15,Back_16->GetBinContent(i));
                Back_bin4->SetBinError(i,Back_13->GetBinError(i));
                Back_bin4->SetBinError(i+5,Back_14->GetBinError(i));
                Back_bin4->SetBinError(i+10,Back_15->GetBinError(i));
                Back_bin4->SetBinError(i+15,Back_16->GetBinError(i));
            }


            Back_bin1->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Back_bin2->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            Back_bin3->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Back_bin4->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));


            delete Back_1; delete Back_2; delete Back_3; delete Back_4; delete Back_5; delete Back_6; delete Back_7; delete Back_8; delete Back_9; delete Back_10; delete Back_11; delete Back_12; delete Back_13; delete Back_14; delete Back_15; delete Back_16; delete Back_bin1; delete Back_bin2; delete Back_bin3; delete Back_bin4;


         }




       }else if(text == "ttbar_out"){

        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfelec_id_up/weight_sfelec_id", "weight_sfelec_id_down/weight_sfelec_id","weight_sfelec_trigger_up/weight_sfelec_trigger","weight_sfelec_trigger_down/weight_sfelec_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "hdamp_up", "hdamp_down", "hdamp_up", "hdamp_down", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal"};

        for(const string &syst : systs){

           TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
           TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);
           TH1F *Back_3 = new TH1F("Back_3","",newrec,new_rec);
           TH1F *Back_4 = new TH1F("Back_4","",newrec,new_rec);

           string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))";
           string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0 && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0))"; 
  

           treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";
            if(syst == "weight_sfelec_id_up/weight_sfelec_id") sys = "eleIDUp";  if(syst == "weight_sfelec_id_down/weight_sfelec_id") sys = "eleIDDown";
            if(syst == "weight_sfelec_trigger_up/weight_sfelec_trigger") sys = "eleHLTUp";  if(syst == "weight_sfelec_trigger_down/weight_sfelec_trigger") sys = "eleHLTDown";
            if(syst == "weight_toptagsf_corr_up/weight_toptagsf") sys = "toptag_corrUp";  if(syst == "weight_toptagsf_corr_down/weight_toptagsf") sys = "toptag_corrDown";
            if(syst == "weight_toptagsf_uncorr_up/weight_toptagsf") sys = "toptag_uncorrUp";  if(syst == "weight_toptagsf_uncorr_down/weight_toptagsf") sys = "toptag_uncorrDown";
            if(syst == "weight_fsr_sqrt2_up") sys = "FSRUp";  if(syst == "weight_fsr_sqrt2_down") sys = "FSRDown";
            if(syst == "weight_isr_sqrt2_up") sys = "ISRUp";  if(syst == "weight_isr_sqrt2_down") sys = "ISRDown";
            if(syst == "weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst == "weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst == "weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown"   ;
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown"   ;
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc18Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc18Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc18Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc18Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring18Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring18Down"  ;


           TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",newrec*4,0,20);
           for (int i = 1; i <= 5; ++i) {
                Ttbar_1_nominal->SetBinContent(i,Back_1->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+5,Back_2->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+10,Back_3->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+15,Back_4->GetBinContent(i));
                Ttbar_1_nominal->SetBinError(i,Back_1->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+5,Back_2->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+10,Back_3->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+15,Back_4->GetBinError(i));
           }

           Ttbar_1_nominal->Write(Form("%s_%s",tt.c_str(),sys.c_str()));

           delete Ttbar_1_nominal; delete Back_1; delete Back_2; delete Back_3; delete Back_4;



        }


       }else{


        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfelec_id_up/weight_sfelec_id", "weight_sfelec_id_down/weight_sfelec_id","weight_sfelec_trigger_up/weight_sfelec_trigger","weight_sfelec_trigger_down/weight_sfelec_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

        for(const string &syst : systs){

           TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
           TH1F *Back_2 = new TH1F("Back_2","",newrec,new_rec);
           TH1F *Back_3 = new TH1F("Back_3","",newrec,new_rec);
           TH1F *Back_4 = new TH1F("Back_4","",newrec,new_rec);

           string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) < 0)";
           string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity<0 && TMath::Cos(angle_phi) > 0)";
           string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) < 0)";
           string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && ttj_rapidity>0 && TMath::Cos(angle_phi) > 0)";


           treereco_ttbar_semi->Project("Back_1","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_2","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_3","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
           treereco_ttbar_semi->Project("Back_4","BDT",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";
            if(syst == "weight_sfelec_id_up/weight_sfelec_id") sys = "eleIDUp";  if(syst == "weight_sfelec_id_down/weight_sfelec_id") sys = "eleIDDown";
            if(syst == "weight_sfelec_trigger_up/weight_sfelec_trigger") sys = "eleHLTUp";  if(syst == "weight_sfelec_trigger_down/weight_sfelec_trigger") sys = "eleHLTDown";
            if(syst == "weight_toptagsf_corr_up/weight_toptagsf") sys = "toptag_corrUp";  if(syst == "weight_toptagsf_corr_down/weight_toptagsf") sys = "toptag_corrDown";
            if(syst == "weight_toptagsf_uncorr_up/weight_toptagsf") sys = "toptag_uncorrUp";  if(syst == "weight_toptagsf_uncorr_down/weight_toptagsf") sys = "toptag_uncorrDown";
            if(syst == "weight_fsr_sqrt2_up") sys = "FSRUp";  if(syst == "weight_fsr_sqrt2_down") sys = "FSRDown";
            if(syst == "weight_isr_sqrt2_up") sys = "ISRUp";  if(syst == "weight_isr_sqrt2_down") sys = "ISRDown";
            if(syst == "weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst == "weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst == "weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown"   ;
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown"   ;
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc18Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc18Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc18Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc18Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring18Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring18Down"  ;


           TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",newrec*4,0,20);
           for (int i = 1; i <= 5; ++i) {
                Ttbar_1_nominal->SetBinContent(i,Back_1->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+5,Back_2->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+10,Back_3->GetBinContent(i));
                Ttbar_1_nominal->SetBinContent(i+15,Back_4->GetBinContent(i));
                Ttbar_1_nominal->SetBinError(i,Back_1->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+5,Back_2->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+10,Back_3->GetBinError(i));
                Ttbar_1_nominal->SetBinError(i+15,Back_4->GetBinError(i));
           }

           Ttbar_1_nominal->Write(Form("%s_%s",tt.c_str(),sys.c_str()));

           delete Ttbar_1_nominal; delete Back_1; delete Back_2; delete Back_3; delete Back_4;


      }
   }
}
}
