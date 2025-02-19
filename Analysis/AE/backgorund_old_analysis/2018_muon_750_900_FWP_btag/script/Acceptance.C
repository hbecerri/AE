#include <algorithm>
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
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void Acceptance()
{

//----obetener_toda_la_informacion_de_entrada--------??

    gStyle->SetOptStat(0);

    TChain *chreco_ttbar = new TChain("AnalysisTree","");
    chreco_ttbar->Add("/nfs/dust/cms/user/hugobg/ZPrime_102X/presel_output/Acc_2016v3_CHS/selection/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_0.root/AnalysisTree");
    TTree *treereco_ttbar = (TTree*) chreco_ttbar;

    TFile* file = TFile::Open("/nfs/dust/cms/user/hugobg/ZPrime_102X/presel_output/Acc_2016v3_CHS/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2016v3_24.root");
    TH1 *DeltaY = (TH1*)file->Get("Input_Generator/DeltaY");

    

//array for variable 

    Float_t bins_gen[] = {-2.,0.,2.};
    Float_t rec_gen[] = {-2.,-1.5,-1.0,-0.5,0.,0.5,1.0,1.5,2.};

    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;
    Int_t  binnum_rec = sizeof(bins_gen)/sizeof(Float_t) - 1;

    TH1F *Var_gen = new TH1F("Var_gen","",binnum_gen,bins_gen);
    TH1F *Acc = new TH1F("Acc","",binnum_rec,rec_gen);

    string var_gen = "";
    var_gen = "TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))))";

//    treereco_ttbar->Project("Var_gen",Form("%s < %f ? TMath::Max(%f,%s): (%s > %f ? TMath::Min(%f,%s) : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_gen.c_str()),"(ttagN <= 1 && btagN >= 1 && wtagN <= 1 &&  rec_chi2 < 30 && Mttbar > 900)"); 
    treereco_ttbar->Project("Var_gen",Form("%s",var_gen.c_str()),"(ttagN <= 1 && btagN >= 1 && wtagN <= 1 &&  rec_chi2 < 30 && Mttbar > 900)*weight"); 
 
    cout << Var_gen->GetBinContent(1)/(DeltaY->GetBinContent(1) + DeltaY->GetBinContent(2) + DeltaY->GetBinContent(3) + DeltaY->GetBinContent(4)) << endl;
    cout << Var_gen->GetBinContent(2)/(DeltaY->GetBinContent(5) + DeltaY->GetBinContent(6) + DeltaY->GetBinContent(7) + DeltaY->GetBinContent(8)) << endl;

     auto c1 = new TCanvas("c1","c1",600,400);
     Acc->SetMarkerStyle(3);
     Acc->Draw("P");
     c1->Print("Acc_Resolved.pdf");


}

 
//declare -a StringArray2=("ttagN == 1 && btagN >= 1 && wtagN == 0" "ttagN == 0 && btagN == 1 && wtagN == 0" "ttagN == 0 && btagN >= 0 && wtagN == 1")
