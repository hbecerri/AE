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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add("/nfs/dust/cms/user/hugobg/analysis/electron/workdir_Analysis_UL16preVFP_electron/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL16preVFP_0.root/AnalysisTree");
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t bins_gen[] = {-1.,0.,1.};
    Float_t new_rec[]  = {-1.,0.,1.};
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t   binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??
 
            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_2 = new TH2F("Migration_Matrix_2","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_3 = new TH2F("Migration_Matrix_3","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_4 = new TH2F("Migration_Matrix_4","",newrec,new_rec,binnum_gen,bins_gen);
            TH2F *Migration_Matrix_Mapp = new TH2F("Migration_Matrix_Mapp","",4,0,4,4,0,4);
 

            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Ele_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && ttj_rapidity>0 && Gen_ttj_Rapidity>0 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.60*3.1459 && slimmedGenJets.m_pt[0] > 150 && slimmedGenJets.m_pt[1] > 100 && slimmedMETs_GenMET.m_pt[0] > 50)";
            string selcuts_boosted_central_2 = "(N_Ak4 >=3 && Ele_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && ttj_rapidity>0 && Gen_ttj_Rapidity<0 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.60*3.1459 && slimmedGenJets.m_pt[0] > 150 && slimmedGenJets.m_pt[1] > 100 && slimmedMETs_GenMET.m_pt[0] > 50)";
            string selcuts_boosted_central_3 = "(N_Ak4 >=3 && Ele_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && ttj_rapidity<0 && Gen_ttj_Rapidity>0 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.60*3.1459 && slimmedGenJets.m_pt[0] > 150 && slimmedGenJets.m_pt[1] > 100 && slimmedMETs_GenMET.m_pt[0] > 50)";
            string selcuts_boosted_central_4 = "(N_Ak4 >=3 && Ele_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && ttj_rapidity<0 && Gen_ttj_Rapidity<0 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.60*3.1459 && slimmedGenJets.m_pt[0] > 150 && slimmedGenJets.m_pt[1] > 100 && slimmedMETs_GenMET.m_pt[0] > 50)";


            treereco_ttbar_semi->Project("Migration_Matrix_1","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight",selcuts_boosted_central_1.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_2","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight",selcuts_boosted_central_2.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_3","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight",selcuts_boosted_central_3.c_str()));
            treereco_ttbar_semi->Project("Migration_Matrix_4","TMath::Cos(Gen_angle_phi):TMath::Cos(angle_phi)",Form("%s*eventweight",selcuts_boosted_central_4.c_str()));

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
 
            delete Ttbar_1_nominal; delete Ttbar_2_nominal; delete Ttbar_3_nominal; delete Ttbar_4_nominal;
            delete Migration_Matrix_Mapp; delete Migration_Matrix_1; delete Migration_Matrix_2; delete Migration_Matrix_3, delete Migration_Matrix_4;

 
}


