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

void NLO_plot()
{

TFile* file_wjets = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/data/merged_kfactors_wjets.root");
TH1D *h1_wjets = (TH1D*)file_wjets->Get("kfactor_monojet_qcd_ewk");

TFile* file_zjets = new  TFile("/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/data/merged_kfactors_zjets.root");
TH1D *h1_zjets = (TH1D*)file_zjets->Get("kfactor_monojet_qcd_ewk");
 
h1_wjets->SetLineColor(4);
h1_wjets->SetTitle("");
h1_wjets->GetXaxis()->SetTitle("p_{T}^{V} GeV");
h1_wjets->GetYaxis()->SetTitle("NLO correction factor");

h1_zjets->GetXaxis()->SetTitle("p_{T}^{V} GeV");
h1_zjets->GetYaxis()->SetTitle("NLO correction factor");
 
h1_zjets->SetLineColor(2);
h1_zjets->SetLineWidth(3);
h1_zjets->SetMarkerStyle(21);

TCanvas *c1 = new TCanvas("c1");
c1->cd();

h1_wjets->Draw("");
h1_zjets->Draw("same");

auto legend = new TLegend(0.5,0.7,0.9,0.9);
legend->SetHeader("QCD+EWK corrections","C"); // option "C" allows to center the header
legend->AddEntry(h1_wjets,"W + Jets","f");
legend->AddEntry(h1_zjets,"DY + Jets","f");
legend->Draw("same");
 

c1->SaveAs("NLO_plot.pdf");
 

}
