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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2016")
{
  
TFile out("Input_undfolding_data_.root","recreate");
string texts[]={"DATA","TTToSemiLeptonic","WJetsToLNu","ST","DYJetsToLL_M-50_HT","QCD_HT","Diboson"};
//string texts[]={"TTToSemiLeptonic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.MC.%s_2016postVFP.root/AnalysisTree",text.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t bins_gen[] = {-2000,0,2000};
    Float_t new_rec[]  = {-2000,0,2000};

    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t   binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "DATA"){
 
       TChain *chreco_data = new TChain("AnalysisTree","");
       chreco_data->Add("/nfs/dust/cms/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016postVFP.root/AnalysisTree");
       TTree *treereco_data = (TTree*) chreco_data;

       TH1F *Back_1 = new TH1F("Back_1","",2,-1,1);
       TH1F *Back_2 = new TH1F("Back_2","",2,-1,1);
       string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0)";
       string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0)";

       treereco_data->Project("Back_1","TMath::Cos(angle_phi)",Form("%s",selcuts_boosted_central_1.c_str()));
       treereco_data->Project("Back_2","TMath::Cos(angle_phi)",Form("%s",selcuts_boosted_central_2.c_str()));

       TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",4,0,4);
       Ttbar_1_nominal->SetBinContent(1,Back_1->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(2,Back_1->GetBinContent(2));
       Ttbar_1_nominal->SetBinContent(3,Back_2->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(4,Back_2->GetBinContent(2));
       Ttbar_1_nominal->Write("data_obs");
       delete Ttbar_1_nominal; delete Back_1; delete Back_2;


       }else if(text == "TTToSemiLeptonic"){

       string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight", "hdamp_up", "hdamp_down"};

//        string systs[] = {"1"};
   
        for(const string &syst : systs){

            cout << syst << endl;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_2 = new TH2F("Migration_Matrix_2","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_3 = new TH2F("Migration_Matrix_3","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_4 = new TH2F("Migration_Matrix_4","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_Mapp = new TH2F("Migration_Matrix_Mapp","",4,0,4,4,0,4);

            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity<0)";
            string selcuts_boosted_central_3 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_4 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity<0)";

            treereco_ttbar_semi->Project("Migration_Matrix_1","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_2","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_3","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_4","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

            Migration_Matrix_Mapp->SetBinContent(1,1,Migration_Matrix_4->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,1,Migration_Matrix_4->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,2,Migration_Matrix_4->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,2,Migration_Matrix_4->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(1,3,Migration_Matrix_3->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,3,Migration_Matrix_3->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,4,Migration_Matrix_3->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,4,Migration_Matrix_3->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,1,Migration_Matrix_2->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,1,Migration_Matrix_2->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,2,Migration_Matrix_2->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,2,Migration_Matrix_2->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,3,Migration_Matrix_1->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,3,Migration_Matrix_1->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,4,Migration_Matrix_1->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,4,Migration_Matrix_1->GetBinContent(2,2));

            TH1D* Ttbar_1_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_2_nominal", 2,2);
            TH1D* Ttbar_3_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_3_nominal", 3,3);
            TH1D* Ttbar_4_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_4_nominal", 4,4);

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
            if(syst =="weight_murmuf_downdown") sys = "MuR_MuFDown" ; if(syst == "weight_murmuf_upup") sys = "MuR_MuFUp";
            if(syst =="weight_murmuf_downnone") sys = "MuRDown" ; if(syst == "weight_murmuf_upnone") sys = "MuRUp";
            if(syst =="weight_murmuf_nonedown") sys = "MuFDown" ; if(syst == "weight_murmuf_noneup") sys = "MuFUp";
            if(syst == "weight_btag_bc_up/weight_btag")      sys = "btag_HF_corrUp"        ; if(syst == "weight_btag_bc_down/weight_btag")      sys = "btag_HF_corrDown"   ;
            if(syst == "weight_btag_udsg_up/weight_btag")    sys = "btag_LF_corrUp"        ; if(syst == "weight_btag_udsg_down/weight_btag")    sys = "btag_LF_corrDown"   ;
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc16Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc16Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc16Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc16Down"  ;
            if(syst == "weight_toppt_a_up/weight_toppt_nominal") sys = "top_pt_rewUp"       ; if(syst == "weight_toppt_a_down/weight_toppt_nominal") sys = "top_pt_rewDown"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring16Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring16Down"  ; 
            if(syst == "hdamp_up") sys = "hdampUp";                                         if(syst == "hdamp_down") sys = "hdampDown";

            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            Ttbar_3_nominal->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Ttbar_4_nominal->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));
            
            if(syst == "1"){
                auto c1    = new TCanvas("c1","c1",600,400);
                c1->cd();
                Migration_Matrix_Mapp->Draw("COLZ");

                TLatex latex;
                latex.SetTextSize(0.045);
                latex.SetTextAlign(11);  //align at top
                latex.DrawLatex(0.1,4.05,"CMS preliminary");

                TLatex latex2;
                latex2.SetTextSize(0.045);
                latex2.SetTextAlign(11);  //align at top
                latex2.DrawLatex(3.0,4.05,"58.8 fb^{-1} (13 TeV)");

                c1->Print("Migration_Matrix_Mapp.pdf");
             } 
            delete Ttbar_1_nominal; delete Ttbar_2_nominal; delete Ttbar_3_nominal; delete Ttbar_4_nominal;
            delete Migration_Matrix_Mapp; delete Migration_Matrix_1; delete Migration_Matrix_2; delete Migration_Matrix_3, delete Migration_Matrix_4;

         }

         for(int k=1;k<=2;k++){

            string syst="wgtMC__PDF["+std::to_string(k)+"]";

            cout << syst << endl;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_2 = new TH2F("Migration_Matrix_2","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_3 = new TH2F("Migration_Matrix_3","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_4 = new TH2F("Migration_Matrix_4","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_Mapp = new TH2F("Migration_Matrix_Mapp","",4,0,4,4,0,4);

            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity<0)";
            string selcuts_boosted_central_3 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_4 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity<0)";

            treereco_ttbar_semi->Project("Migration_Matrix_1","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_2","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_3","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_4","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

            Migration_Matrix_Mapp->SetBinContent(1,1,Migration_Matrix_4->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,1,Migration_Matrix_4->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,2,Migration_Matrix_4->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,2,Migration_Matrix_4->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(1,3,Migration_Matrix_3->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,3,Migration_Matrix_3->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,4,Migration_Matrix_3->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,4,Migration_Matrix_3->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,1,Migration_Matrix_2->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,1,Migration_Matrix_2->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,2,Migration_Matrix_2->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,2,Migration_Matrix_2->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,3,Migration_Matrix_1->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,3,Migration_Matrix_1->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,4,Migration_Matrix_1->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,4,Migration_Matrix_1->GetBinContent(2,2));

            TH1D* Ttbar_1_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_2_nominal", 2,2);
            TH1D* Ttbar_3_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_3_nominal", 3,3);
            TH1D* Ttbar_4_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_4_nominal", 4,4);

            string sys = "PDF"+std::to_string(k)+"Up";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            Ttbar_3_nominal->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Ttbar_4_nominal->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));

            delete Ttbar_1_nominal; delete Ttbar_2_nominal; delete Ttbar_3_nominal; delete Ttbar_4_nominal;
            delete Migration_Matrix_Mapp; delete Migration_Matrix_1; delete Migration_Matrix_2; delete Migration_Matrix_3, delete Migration_Matrix_4;

         } 

         for(int k=1;k<=2;k++){

            string syst="1";

            cout << syst << endl;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_2 = new TH2F("Migration_Matrix_2","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_3 = new TH2F("Migration_Matrix_3","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_4 = new TH2F("Migration_Matrix_4","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_Mapp = new TH2F("Migration_Matrix_Mapp","",4,0,4,4,0,4);

            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0 && Gen_ttj_Rapidity<0)";
            string selcuts_boosted_central_3 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity>0)";
            string selcuts_boosted_central_4 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0 && Gen_ttj_Rapidity<0)";

            treereco_ttbar_semi->Project("Migration_Matrix_1","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_2","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_3","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_3.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_4","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_4.c_str(),syst.c_str()));

            Migration_Matrix_Mapp->SetBinContent(1,1,Migration_Matrix_4->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,1,Migration_Matrix_4->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,2,Migration_Matrix_4->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,2,Migration_Matrix_4->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(1,3,Migration_Matrix_3->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(2,3,Migration_Matrix_3->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(1,4,Migration_Matrix_3->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(2,4,Migration_Matrix_3->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,1,Migration_Matrix_2->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,1,Migration_Matrix_2->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,2,Migration_Matrix_2->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,2,Migration_Matrix_2->GetBinContent(2,2));

            Migration_Matrix_Mapp->SetBinContent(3,3,Migration_Matrix_1->GetBinContent(1,1)); Migration_Matrix_Mapp->SetBinContent(4,3,Migration_Matrix_1->GetBinContent(2,1));
            Migration_Matrix_Mapp->SetBinContent(3,4,Migration_Matrix_1->GetBinContent(1,2)); Migration_Matrix_Mapp->SetBinContent(4,4,Migration_Matrix_1->GetBinContent(2,2));

            TH1D* Ttbar_1_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_2_nominal", 2,2);
            TH1D* Ttbar_3_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_3_nominal", 3,3);
            TH1D* Ttbar_4_nominal = Migration_Matrix_Mapp->ProjectionX("Ttbar_4_nominal", 4,4);

            string sys = "PDF"+std::to_string(k)+"Down";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            Ttbar_3_nominal->Write(Form("%s_3_%s",text.c_str(),sys.c_str()));
            Ttbar_4_nominal->Write(Form("%s_4_%s",text.c_str(),sys.c_str()));

            delete Ttbar_1_nominal; delete Ttbar_2_nominal; delete Ttbar_3_nominal; delete Ttbar_4_nominal;
            delete Migration_Matrix_Mapp; delete Migration_Matrix_1; delete Migration_Matrix_2; delete Migration_Matrix_3, delete Migration_Matrix_4;
         }

 
       } else{


        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

        for(const string &syst : systs){

            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",2,-1,1);
            TH1F *Back_2 = new TH1F("Back_2","",2,-1,1);
            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0)";

            treereco_ttbar_semi->Project("Back_1","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),syst.c_str()));

            TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",4,0,4);
            Ttbar_1_nominal->SetBinContent(1,Back_1->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(2,Back_1->GetBinContent(2));
            Ttbar_1_nominal->SetBinContent(3,Back_2->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(4,Back_2->GetBinContent(2));
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
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc16Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc16Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc16Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc16Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring16Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring16Down"  ;


            Ttbar_1_nominal->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Back_1; delete Back_2;

        }

        for(int k=1;k<=2;k++){       
  
            string new_sys="wgtMC__PDF["+std::to_string(k)+"]"+"/"+"wgtMC__PDF[1]";

            cout << new_sys << endl;

            TH1F *Back_1 = new TH1F("Back_1","",2,-1,1);
            TH1F *Back_2 = new TH1F("Back_2","",2,-1,1);
            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0)";

            treereco_ttbar_semi->Project("Back_1","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),new_sys.c_str()));
            treereco_ttbar_semi->Project("Back_2","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),new_sys.c_str()));

            TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",4,0,4);
            Ttbar_1_nominal->SetBinContent(1,Back_1->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(2,Back_1->GetBinContent(2));
            Ttbar_1_nominal->SetBinContent(3,Back_2->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(4,Back_2->GetBinContent(2));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);

            string sys = "PDF"+std::to_string(k)+"Up";
            Ttbar_1_nominal->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Back_1; delete Back_2;
   
   
        } 

        for(int k=1;k<=2;k++){

            string new_sys="1";

            cout << new_sys << endl;

            TH1F *Back_1 = new TH1F("Back_1","",2,-1,1);
            TH1F *Back_2 = new TH1F("Back_2","",2,-1,1);
            string selcuts_boosted_central_1 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity<0)";
            string selcuts_boosted_central_2 = "(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 900 && M_tt < 9000 && chi2 < 30 && Boost_Ak4_add_pt > 0 && ttj_rapidity>0)";

            treereco_ttbar_semi->Project("Back_1","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),new_sys.c_str()));
            treereco_ttbar_semi->Project("Back_2","TMath::Cos(angle_phi)",Form("%s*eventweight*%s",selcuts_boosted_central_2.c_str(),new_sys.c_str()));

            TH1D* Ttbar_1_nominal = new TH1D("Ttbar_1_nominal","",4,0,4);
            Ttbar_1_nominal->SetBinContent(1,Back_1->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(2,Back_1->GetBinContent(2));
            Ttbar_1_nominal->SetBinContent(3,Back_2->GetBinContent(1)); Ttbar_1_nominal->SetBinContent(4,Back_2->GetBinContent(2));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);

            string sys = "PDF"+std::to_string(k)+"Down";
            Ttbar_1_nominal->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Back_1; delete Back_2;

        }

    }  
     
}
 
}


