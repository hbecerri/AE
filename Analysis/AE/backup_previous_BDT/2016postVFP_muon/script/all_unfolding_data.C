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
  
TFile out("Input_undfolding_data_all.root","recreate");
string texts[]={"TTToSemiLeptonic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/muon//uhh2.AnalysisModuleRunner.MC.TTToJets_UL16postVFP.root/AnalysisTree",text.c_str()));
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
       chreco_data->Add("/nfs/dust/cms/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016postVFP.root/AnalysisTree");
       TTree *treereco_data = (TTree*) chreco_data;
 
       TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
       string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459 )";
       treereco_data->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s",selcuts_boosted_central_1.c_str()));
       Back_1->Write("data_obs");
       delete Back_1;


       }else if(text == "TTToSemiLeptonic"){

//       string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight", "hdamp_up", "hdamp_down"};

        string systs[] = {"1"};
   
        for(const string &syst : systs){

            cout << syst << endl; 
  
            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen); 
            string Mttbar_gen_energia = "TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3], 2)";
            string Mttbar_gen_p1 = "TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p2 = "TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p3 = "TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]), 2)";
            string Mttbar_gen = Form("TMath::Sqrt(%s - %s - %s - %s)", Mttbar_gen_energia.c_str(), Mttbar_gen_p1.c_str(), Mttbar_gen_p2.c_str(), Mttbar_gen_p3.c_str());
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459  && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0   )";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));

            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);

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

            Ttbar_1_nominal->SetBinError(1,Ttbar_1_nominal->GetBinError(1)/1.44); Ttbar_1_nominal->SetBinError(2,Ttbar_1_nominal->GetBinError(2)/1.44);
            Ttbar_2_nominal->SetBinError(1,Ttbar_2_nominal->GetBinError(1)/1.44); Ttbar_2_nominal->SetBinError(2,Ttbar_2_nominal->GetBinError(2)/1.44);

            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str())); 
            
            if(syst == "1"){
                auto c1    = new TCanvas("c1","c1",600,400);
                c1->cd();
                Migration_Matrix_1->Draw("COLZ");
                TLatex latex;
                latex.SetTextSize(0.045);
                latex.SetTextAlign(11);  //align at top
                latex.DrawLatex(-2000,20099.5,"CMS preliminary");
                TLatex latex2;
                latex2.SetTextSize(0.045);
                latex2.SetTextAlign(11);  //align at top
                latex2.DrawLatex(12000,20099.5,"58.8 fb^{-1} (13 TeV)");
                c1->Print("Migration_Matrix_Mapp_2016postVFP_muon.pdf");

             TH2F *Stability_Matrix = new TH2F("Stability_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);
             TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);

             for(int a=1;a<=binnum_gen;a++){
                 for(Int_t b=1;b<=binnum_gen;b++){
                    Stability_Matrix->SetBinContent(a,b,Migration_Matrix_1->GetBinContent(a,b)/Migration_Matrix_1->Integral(1,binnum_gen,b,b));
                    Purity_Matrix->SetBinContent(a,b,Migration_Matrix_1->GetBinContent(a,b)/Migration_Matrix_1->Integral(a,a,1,binnum_gen));
                    Stability_Matrix->SetBinError(a,b,Migration_Matrix_1->GetBinError(a,b)/Migration_Matrix_1->Integral(1,binnum_gen,b,b));
                    Purity_Matrix->SetBinError(a,b,Migration_Matrix_1->GetBinError(a,b)/Migration_Matrix_1->Integral(a,a,1,binnum_gen));
                 }
              }


                TH1F *Stability = new TH1F("Stability","",binnum_gen,bins_gen);
                TH1F *Purity = new TH1F("Purity","",binnum_gen,bins_gen);

                for(Int_t m=1;m<=binnum_gen;m++){
                        Stability->SetBinContent(m,Stability_Matrix->GetBinContent(m,m));
                        Purity->SetBinContent(m,Purity_Matrix->GetBinContent(m,m));
                        Stability->SetBinError(m,Stability_Matrix->GetBinError(m,m));
                        Purity->SetBinError(m,Purity_Matrix->GetBinError(m,m));
                }

                Stability->GetYaxis()->SetRangeUser(0,1);
                Stability->GetYaxis()->SetTitle("P&S");
                Stability->GetXaxis()->SetLabelSize(0);
                Purity->SetLineColor(kRed);
                Purity->SetLineWidth(2);
                Stability->SetLineColor(kBlue);
                Stability->SetLineWidth(2);

                TCanvas* cc = new TCanvas("cc","",2400,1200);
                cc->Divide(1,1);
                cc->cd(1);
                Stability->Draw("samei e");
                Purity->Draw("same e");

                Float_t a = Stability->GetMaximum();

                TLegend leg(.55, .7, .75, .85, "");
                leg.SetFillColor(0);
                leg.AddEntry(Purity, "Purity");
                leg.AddEntry(Stability, "Stability");
                leg.SetBorderSize(0);
                leg.Draw("Same");

                TLatex latex3;
                latex3.SetTextSize(0.045);
                latex3.SetTextAlign(11);
                latex3.DrawLatex(-19999.0,1.02,"CMS preliminary");

                TLatex latex4;
                latex4.SetTextSize(0.045);
                latex4.SetTextAlign(11);
                latex4.DrawLatex(12000,1.02,"16.81 fb^{-1} (13 TeV)");

                cc->Print("PS_2016postVFP_muon.pdf");


             }

             delete Ttbar_1_nominal; delete Ttbar_2_nominal;
             delete Migration_Matrix_1;
            
         }

         for(int k=1;k<=5;k++){

            string syst="wgtMC__PDF["+std::to_string(k)+"]";
            cout << syst << endl;
 
            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            string Mttbar_gen_energia = "TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3], 2)";
            string Mttbar_gen_p1 = "TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p2 = "TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p3 = "TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]), 2)";
            string Mttbar_gen = Form("TMath::Sqrt(%s - %s - %s - %s)", Mttbar_gen_energia.c_str(), Mttbar_gen_p1.c_str(), Mttbar_gen_p2.c_str(), Mttbar_gen_p3.c_str());
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459  && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0   )";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);
            string sys = "PDF"+std::to_string(k)+"Up";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Ttbar_2_nominal;
            delete Migration_Matrix_1;
         } 

         for(int k=1;k<=5;k++){

            string syst="1";
            cout << syst << endl;
 
            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            string Mttbar_gen_energia = "TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3], 2)";
            string Mttbar_gen_p1 = "TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p2 = "TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]), 2)";
            string Mttbar_gen_p3 = "TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]), 2)";
            string Mttbar_gen = Form("TMath::Sqrt(%s - %s - %s - %s)", Mttbar_gen_energia.c_str(), Mttbar_gen_p1.c_str(), Mttbar_gen_p2.c_str(), Mttbar_gen_p3.c_str());
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459  && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0   )";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);
            string sys = "PDF"+std::to_string(k)+"Down";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Ttbar_2_nominal;
            delete Migration_Matrix_1;
         }

        for(const string &syst : systs){

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459  && !(leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0   ))";
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
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
            Back_1->Write(Form("%s_outfiducial_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

 
       } else{


        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

        for(const string &syst : systs){

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459 )";
  
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
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
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

        for(int k=1;k<=5;k++){       
     
            string syst="wgtMC__PDF["+std::to_string(k)+"]"+"/"+"wgtMC__PDF[1]";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459 )";
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Up";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;
   
        } 

        for(int k=1;k<=5;k++){

            string syst="1";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",newrec,new_rec);
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459 )";
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Down";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

    }  
     
}
 
}


