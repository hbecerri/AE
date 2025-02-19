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

void triger_muon()
{

gStyle->SetPaintTextFormat("4.2f");

TFile* file_wjets = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/common/UHH2-data/muon_SFs_UL/UL18/Efficiencies_muon_generalTracks_Z_Run2018_UL_SingleMuonTriggers.root");
TH2F *h1 = (TH2F*)file_wjets->Get("NUM_Mu50_or_OldMu100_or_TkMu100_DEN_CutBasedIdGlobalHighPt_and_TkIsoLoose_abseta_pt");

h1->SetStats(0);
h1->SetTitle("");
 
TCanvas *c1 = new TCanvas("c1");
c1->cd();
c1->SetRightMargin(0.09);
c1->SetLeftMargin(0.15);
c1->SetBottomMargin(0.15);
h1->Draw("col text");
c1->SaveAs("2018_muon.pdf");


gStyle->SetPaintTextFormat("4.2f");

TFile* file_wjets2 = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/common/UHH2-data/muon_SFs_UL/UL17/Efficiencies_muon_generalTracks_Z_Run2017_UL_SingleMuonTriggers.root");
TH2F *h2 = (TH2F*)file_wjets2->Get("NUM_Mu50_or_OldMu100_or_TkMu100_DEN_CutBasedIdGlobalHighPt_and_TkIsoLoose_abseta_pt");

h2->SetStats(0);
h2->SetTitle("");

TCanvas *c2 = new TCanvas("c2");
c2->cd();
c2->SetRightMargin(0.09);
c2->SetLeftMargin(0.15);
c2->SetBottomMargin(0.15);
h2->Draw("col text");
c2->SaveAs("2017_muon.pdf");

 
TFile* file_wjets3 = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/common/UHH2-data/muon_SFs_UL/UL16preVFP/Efficiencies_muon_generalTracks_Z_Run2016_UL_HIPM_SingleMuonTriggers.root");
TH2F *h3 = (TH2F*)file_wjets3->Get("NUM_Mu50_or_TkMu50_DEN_CutBasedIdGlobalHighPt_and_TkIsoLoose_abseta_pt");

h3->SetStats(0);
h3->SetTitle("");

TCanvas *c3 = new TCanvas("c3");
c3->cd();
c3->SetRightMargin(0.09);
c3->SetLeftMargin(0.15);
c3->SetBottomMargin(0.15);
h3->Draw("col text");
c3->SaveAs("2016_muon.pdf");
}
