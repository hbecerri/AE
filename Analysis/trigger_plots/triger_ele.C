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

void triger_ele()
{

TFile* file_wjets = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/files_EleTrigger/ElecTriggerSFUL18.root");
TH1F *h1 = (TH1F*)file_wjets->Get("Central_eta_lowpt");
TH1F *h2 = (TH1F*)file_wjets->Get("Up_eta_lowpt");
TH1F *h3 = (TH1F*)file_wjets->Get("Down_eta_lowpt"); 

h1->SetMarkerColor(46);
h1->SetMarkerStyle(33);
h1->SetMarkerSize(1);
  
h1->SetStats(0);
h1->SetTitle("");
h2->SetStats(0);
h2->SetTitle("");
h3->SetStats(0);
h3->SetTitle("");

TCanvas *c1 = new TCanvas("c1");
c1->cd();
c1->SetRightMargin(0.09);
c1->SetLeftMargin(0.15);
c1->SetBottomMargin(0.15);
h1->Draw("hist p");
h2->Draw("same");
h3->Draw("same");
c1->SaveAs("2018_ele_low.pdf");


TH1F *h11 = (TH1F*)file_wjets->Get("Central_eta_midpt");
TH1F *h21 = (TH1F*)file_wjets->Get("Up_eta_midpt");
TH1F *h31 = (TH1F*)file_wjets->Get("Down_eta_midpt");
 
h11->SetMarkerColor(46);
h11->SetMarkerStyle(33);
h11->SetMarkerSize(1);
  
h11->SetStats(0);
h11->SetTitle("");
h21->SetStats(0);
h21->SetTitle("");
h31->SetStats(0);
h31->SetTitle("");

TCanvas *c11 = new TCanvas("c11");
c11->cd();
c11->SetRightMargin(0.09);
c11->SetLeftMargin(0.15);
c11->SetBottomMargin(0.15);
h11->Draw("hist p");
h21->Draw("same");
h31->Draw("same");
c11->SaveAs("2018_ele_mid.pdf");


TH1F *h12 = (TH1F*)file_wjets->Get("Central_eta_highpt");
TH1F *h22 = (TH1F*)file_wjets->Get("Up_eta_highpt");
TH1F *h32 = (TH1F*)file_wjets->Get("Down_eta_highpt");
 
h12->SetMarkerColor(46);
h12->SetMarkerStyle(33);
h12->SetMarkerSize(1);
  
h12->SetStats(0);
h12->SetTitle("");
h22->SetStats(0);
h22->SetTitle("");
h32->SetStats(0);
h32->SetTitle("");

TCanvas *c12 = new TCanvas("c12");
c12->cd();
c12->SetRightMargin(0.09);
c12->SetLeftMargin(0.15);
c12->SetBottomMargin(0.15);
h12->Draw("hist p");
h22->Draw("same");
h32->Draw("same");
c12->SaveAs("2018_ele_high.pdf");




}


