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
#include "TUnfoldDensity.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TFrame.h"
#include "TPaveLabel.h"
#include "TPad.h"
#include "TLegend.h"
#include "TRandom3.h"

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

    //jec
    TChain *chreco_ttbar_semi_jectimeptetaup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jectimeptetaup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECTimePtEtaup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jectimeptetaup = (TTree*) chreco_ttbar_semi_jectimeptetaup;

    TChain *chreco_ttbar_semi_jectimeptetadown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jectimeptetadown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECTimePtEtadown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jectimeptetadown = (TTree*) chreco_ttbar_semi_jectimeptetadown;

    TChain *chreco_ttbar_semi_jecRelativeStatHFup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatHFup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatHFup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatHFup = (TTree*) chreco_ttbar_semi_jecRelativeStatHFup;

    TChain *chreco_ttbar_semi_jecRelativeStatHFdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatHFdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatHFdown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatHFdown = (TTree*) chreco_ttbar_semi_jecRelativeStatHFdown;

    TChain *chreco_ttbar_semi_jecRelativeStatFSRup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatFSRup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatFSRup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatFSRup = (TTree*) chreco_ttbar_semi_jecRelativeStatFSRup;

    TChain *chreco_ttbar_semi_jecRelativeStatFSRdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatFSRdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatFSRdown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatFSRdown = (TTree*) chreco_ttbar_semi_jecRelativeStatFSRdown;

    TChain *chreco_ttbar_semi_jecRelativeStatECup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatECup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatECup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatECup = (TTree*) chreco_ttbar_semi_jecRelativeStatECup;

    TChain *chreco_ttbar_semi_jecRelativeStatECdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeStatECdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeStatECdown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeStatECdown = (TTree*) chreco_ttbar_semi_jecRelativeStatECdown;

    TChain *chreco_ttbar_semi_jecRelativeJEREC1up = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeJEREC1up->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeJEREC1up/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeJEREC1up = (TTree*) chreco_ttbar_semi_jecRelativeJEREC1up;

    TChain *chreco_ttbar_semi_jecRelativeJEREC1down = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeJEREC1down->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeJEREC1down/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeJEREC1down = (TTree*) chreco_ttbar_semi_jecRelativeJEREC1down;

    TChain *chreco_ttbar_semi_jecRelativeJEREC2up = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeJEREC2up->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeJEREC2up/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeJEREC2up = (TTree*) chreco_ttbar_semi_jecRelativeJEREC2up;

    TChain *chreco_ttbar_semi_jecRelativeJEREC2down = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeJEREC2down->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeJEREC2down/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeJEREC2down = (TTree*) chreco_ttbar_semi_jecRelativeJEREC2down;

    TChain *chreco_ttbar_semi_jecRelativePtEC1up = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativePtEC1up->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativePtEC1up/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativePtEC1up = (TTree*) chreco_ttbar_semi_jecRelativePtEC1up;

    TChain *chreco_ttbar_semi_jecRelativePtEC1down = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativePtEC1down->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativePtEC1down/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativePtEC1down = (TTree*) chreco_ttbar_semi_jecRelativePtEC1down;

    TChain *chreco_ttbar_semi_jecRelativePtEC2up = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativePtEC2up->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativePtEC2up/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativePtEC2up = (TTree*) chreco_ttbar_semi_jecRelativePtEC2up;

    TChain *chreco_ttbar_semi_jecRelativePtEC2down = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativePtEC2down->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativePtEC2down/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativePtEC2down = (TTree*) chreco_ttbar_semi_jecRelativePtEC2down;

    TChain *chreco_ttbar_semi_jecRelativeSampleup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeSampleup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeSampleup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeSampleup = (TTree*) chreco_ttbar_semi_jecRelativeSampleup;

    TChain *chreco_ttbar_semi_jecRelativeSampledown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecRelativeSampledown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECRelativeSampledown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecRelativeSampledown = (TTree*) chreco_ttbar_semi_jecRelativeSampledown;

    TChain *chreco_ttbar_semi_jecAbsoluteStatup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecAbsoluteStatup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECAbsoluteStatup/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecAbsoluteStatup = (TTree*) chreco_ttbar_semi_jecAbsoluteStatup;

    TChain *chreco_ttbar_semi_jecAbsoluteStatdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_jecAbsoluteStatdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JECAbsoluteStatdown/uhh2.AnalysisModuleRunner.MC.TTT*.root/AnalysisTree",year.c_str(),year.c_str()));
    TTree *treereco_ttbar_semi_jecAbsoluteStatdown = (TTree*) chreco_ttbar_semi_jecAbsoluteStatdown;



    //jer
     TChain *chreco_ttbar_semi_jerup = new TChain("AnalysisTree","");
     chreco_ttbar_semi_jerup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JERup/uhh2.AnalysisModuleRunner.MC.TT*.root/AnalysisTree",year.c_str(),year.c_str()));
     TTree *treereco_ttbar_semi_jerup = (TTree*) chreco_ttbar_semi_jerup;

     TChain *chreco_ttbar_semi_jerdown = new TChain("AnalysisTree","");
     chreco_ttbar_semi_jerdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_%s_JERdown/uhh2.AnalysisModuleRunner.MC.TT*.root/AnalysisTree",year.c_str(),year.c_str()));
     TTree *treereco_ttbar_semi_jerdown = (TTree*) chreco_ttbar_semi_jerdown;

    //hdamp

    TChain *chreco_ttbar_semi_hdampup = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampup->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_2018_hdamp/uhh2.AnalysisModuleRunner.MC.*up*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi_hdampup = (TTree*) chreco_ttbar_semi_hdampup;

    TChain *chreco_ttbar_semi_hdampdown = new TChain("AnalysisTree","");
    chreco_ttbar_semi_hdampdown->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/fixedWP_btag_muon_2018_hdamp/uhh2.AnalysisModuleRunner.MC.*down*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi_hdampdown = (TTree*) chreco_ttbar_semi_hdampdown;


//array for variable 

    int len = 0; int len_rec = 0;
    if(var_name == "DeltaY") len = 3, len_rec = 3;
    Float_t bins_gen[len];
    Float_t new_rec[len_rec];

    if(var_name == "DeltaY"){ 
        Float_t Bins_gen[] = {-2.,0.,2.};
        Float_t New_rec[] = {-2.,0.,2.};
        std::copy(Bins_gen, Bins_gen+len, bins_gen);
        std::copy(New_rec, New_rec+len_rec, new_rec);
    }

    Int_t  newrec = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t  binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

    TH2F *Migration_Matrix = new TH2F("Migration_Matrix","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_pileupUp = new TH2F("Migration_Matrix_pileupUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muIDUp = new TH2F("Migration_Matrix_muIDUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTUp = new TH2F("Migration_Matrix_muHLTUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewUp = new TH2F("Migration_Matrix_Top_pT_rewUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagUp = new TH2F("Migration_Matrix_mistagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagUp = new TH2F("Migration_Matrix_toptagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recUp = new TH2F("Migration_Matrix_muon_recUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRUp = new TH2F("Migration_Matrix_ISRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRUp = new TH2F("Migration_Matrix_FSRUp","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_jectimeptetaUp = new TH2F("Migration_Matrix_jectimeptetaUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatHFUp = new TH2F("Migration_Matrix_jecRelativeStatHFUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatECUp = new TH2F("Migration_Matrix_jecRelativeStatECUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatFSRUp = new TH2F("Migration_Matrix_jecRelativeStatFSRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeSampleUp = new TH2F("Migration_Matrix_jecRelativeSampleUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativePtEC1Up = new TH2F("Migration_Matrix_jecRelativePtEC1Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativePtEC2Up = new TH2F("Migration_Matrix_jecRelativePtEC2Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeJEREC1Up = new TH2F("Migration_Matrix_jecRelativeJEREC1Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeJEREC2Up = new TH2F("Migration_Matrix_jecRelativeJEREC2Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecAbsoluteStatUp = new TH2F("Migration_Matrix_jecAbsoluteStatUp","",newrec,new_rec,binnum_gen,bins_gen);


    TH2F *Migration_Matrix_jerUp = new TH2F("Migration_Matrix_jerUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampUp = new TH2F("Migration_Matrix_hdampUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_HF_corrUp = new TH2F("Migration_Matrix_btag_HF_corrUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_LF_corrUp = new TH2F("Migration_Matrix_btag_LF_corrUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_HF_unc18Up = new TH2F("Migration_Matrix_btag_HF_unc18Up","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_LF_unc18Up = new TH2F("Migration_Matrix_btag_LF_unc18Up","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_pileupDown = new TH2F("Migration_Matrix_pileupDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muIDDown = new TH2F("Migration_Matrix_muIDDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTDown = new TH2F("Migration_Matrix_muHLTDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewDown = new TH2F("Migration_Matrix_Top_pT_rewDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagDown = new TH2F("Migration_Matrix_mistagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagDown = new TH2F("Migration_Matrix_toptagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recDown = new TH2F("Migration_Matrix_muon_recDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRDown = new TH2F("Migration_Matrix_ISRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRDown = new TH2F("Migration_Matrix_FSRDown","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_jectimeptetaDown = new TH2F("Migration_Matrix_jectimeptetaDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatHFDown = new TH2F("Migration_Matrix_jecRelativeStatHFDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatECDown = new TH2F("Migration_Matrix_jecRelativeStatECDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeStatFSRDown = new TH2F("Migration_Matrix_jecRelativeStatFSRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeSampleDown = new TH2F("Migration_Matrix_jecRelativeSampleDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativePtEC1Down = new TH2F("Migration_Matrix_jecRelativePtEC1Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativePtEC2Down = new TH2F("Migration_Matrix_jecRelativePtEC2Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeJEREC1Down = new TH2F("Migration_Matrix_jecRelativeJEREC1Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecRelativeJEREC2Down = new TH2F("Migration_Matrix_jecRelativeJEREC2Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecAbsoluteStatDown = new TH2F("Migration_Matrix_jecAbsoluteStatDown","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_jerDown = new TH2F("Migration_Matrix_jerDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampDown = new TH2F("Migration_Matrix_hdampDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_HF_corrDown = new TH2F("Migration_Matrix_btag_HF_corrDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_LF_corrDown = new TH2F("Migration_Matrix_btag_LF_corrDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_HF_unc18Down = new TH2F("Migration_Matrix_btag_HF_unc18Down","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_btag_LF_unc18Down = new TH2F("Migration_Matrix_btag_LF_unc18Down","",newrec,new_rec,binnum_gen,bins_gen);
 

    string  pileupUp = "(weight_sfmu_HighPtID)*(weight_pu_up)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  pileupDown = "(weight_sfmu_HighPtID)*(weight_pu_down)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  muIDUp = "(weight_sfmu_HighPtID_up)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  muIDDown = "(weight_sfmu_HighPtID_down)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  muHLTUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  muHLTDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";

    string  btag_HF_corrUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_up)*(muonrecSF_nominal)";
    string  btag_LF_corrUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_up)*(muonrecSF_nominal)";
    string  btag_HF_unc18Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_up_un)*(muonrecSF_nominal)";
    string  btag_LF_unc18Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_up_un)*(muonrecSF_nominal)";
    string  btag_HF_corrDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_down)*(muonrecSF_nominal)";
    string  btag_LF_corrDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_down)*(muonrecSF_nominal)";
    string  btag_HF_unc18Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_bc_down_un)*(muonrecSF_nominal)";
    string  btag_LF_unc18Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag_udsg_down_un)*(muonrecSF_nominal)";
 
    string  Top_pT_rewUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  Top_pT_rewDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_down_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  mistagUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*1.01";
    string  mistagDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*0.99";
    string  toptagUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  toptagDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  muon_recUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_up)";
    string  muon_recDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_down)";
    string  HTUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  HTDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  ISRUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*ISRup";
    string  ISRDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*ISRdown";
    string  FSRUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*FSRup";
    string  FSRDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*FSRdown";
    string  jecUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  jecDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  jerUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  jerDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)";
    string  hdampUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*1.1";
    string  hdampDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btag)*(muonrecSF_nominal)*1.1";

    Float_t mistag_nominal = 0.9;

    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 750 && Mttbar < 900)*%f",mistag_nominal);

//Matrices
    treereco_ttbar_semi->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_nolimit*weight_btag*muonrecSF_nominal",selcuts_boosted_central.c_str()));

    treereco_ttbar_semi->Project("Migration_Matrix_pileupUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muIDUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRUp.c_str(),selcuts_boosted_central.c_str()));

    treereco_ttbar_semi_jectimeptetaup->Project("Migration_Matrix_jectimeptetaUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatHFup->Project("Migration_Matrix_jecRelativeStatHFUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatECup->Project("Migration_Matrix_jecRelativeStatECUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatFSRup->Project("Migration_Matrix_jecRelativeStatFSRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeSampleup->Project("Migration_Matrix_jecRelativeSampleUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativePtEC1up->Project("Migration_Matrix_jecRelativePtEC1Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativePtEC2up->Project("Migration_Matrix_jecRelativePtEC2Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeJEREC1up->Project("Migration_Matrix_jecRelativeJEREC1Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeJEREC2up->Project("Migration_Matrix_jecRelativeJEREC2Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecAbsoluteStatup->Project("Migration_Matrix_jecAbsoluteStatUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));


    treereco_ttbar_semi_jerup->Project("Migration_Matrix_jerUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_hdampup->Project("Migration_Matrix_hdampUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampUp.c_str(),selcuts_boosted_central.c_str()));

///btagging 
 
    treereco_ttbar_semi->Project("Migration_Matrix_btag_HF_corrUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_HF_corrUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_LF_corrUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_LF_corrUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_HF_unc18Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_HF_unc18Up.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_LF_unc18Up",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_LF_unc18Up.c_str(),selcuts_boosted_central.c_str()));

//Down
    treereco_ttbar_semi->Project("Migration_Matrix_pileupDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muIDDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRDown.c_str(),selcuts_boosted_central.c_str()));

    treereco_ttbar_semi_jectimeptetadown->Project("Migration_Matrix_jectimeptetaDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatHFdown->Project("Migration_Matrix_jecRelativeStatHFDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatECdown->Project("Migration_Matrix_jecRelativeStatECDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeStatFSRdown->Project("Migration_Matrix_jecRelativeStatFSRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeSampleup->Project("Migration_Matrix_jecRelativeSampleDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativePtEC1up->Project("Migration_Matrix_jecRelativePtEC1Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativePtEC2up->Project("Migration_Matrix_jecRelativePtEC2Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeJEREC1up->Project("Migration_Matrix_jecRelativeJEREC1Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecRelativeJEREC2up->Project("Migration_Matrix_jecRelativeJEREC2Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_jecAbsoluteStatup->Project("Migration_Matrix_jecAbsoluteStatDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));

    treereco_ttbar_semi_jerdown->Project("Migration_Matrix_jerDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi_hdampdown->Project("Migration_Matrix_hdampDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampDown.c_str(),selcuts_boosted_central.c_str()));


//btagging

    treereco_ttbar_semi->Project("Migration_Matrix_btag_HF_corrDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_HF_corrDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_LF_corrDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_LF_corrDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_HF_unc18Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_HF_unc18Down.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_btag_LF_unc18Down",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",btag_LF_unc18Down.c_str(),selcuts_boosted_central.c_str()));


    TH1F *Ttbar_1_nominal = new TH1F("Ttbar_1_nominal","",binnum_gen,bins_gen);   Ttbar_1_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,1)); Ttbar_1_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,1));
    TH1F *Ttbar_2_nominal = new TH1F("Ttbar_2_nominal","",binnum_gen,bins_gen);   Ttbar_2_nominal->SetBinContent(1,Migration_Matrix->GetBinContent(1,2)); Ttbar_2_nominal->SetBinContent(2,Migration_Matrix->GetBinContent(2,2));
 
    TH1F *Ttbar_1_pileupUp = new TH1F("Ttbar_1_pileupUp","",newrec,new_rec);  Ttbar_1_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,1)); Ttbar_1_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,1));
    TH1F *Ttbar_2_pileupUp = new TH1F("Ttbar_2_pileupUp","",newrec,new_rec);  Ttbar_2_pileupUp->SetBinContent(1,Migration_Matrix_pileupUp->GetBinContent(1,2)); Ttbar_2_pileupUp->SetBinContent(2,Migration_Matrix_pileupUp->GetBinContent(2,2));
    TH1F *Ttbar_1_muIDUp = new TH1F("Ttbar_1_muIDUp","",newrec,new_rec);      Ttbar_1_muIDUp->SetBinContent(1,Migration_Matrix_muIDUp->GetBinContent(1,1)); Ttbar_1_muIDUp->SetBinContent(2,Migration_Matrix_muIDUp->GetBinContent(2,1));
    TH1F *Ttbar_2_muIDUp = new TH1F("Ttbar_2_muIDUp","",newrec,new_rec);      Ttbar_2_muIDUp->SetBinContent(1,Migration_Matrix_muIDUp->GetBinContent(1,2)); Ttbar_2_muIDUp->SetBinContent(2,Migration_Matrix_muIDUp->GetBinContent(2,2));
    TH1F *Ttbar_1_muHLTUp = new TH1F("Ttbar_1_muHLTUp","",newrec,new_rec);    Ttbar_1_muHLTUp->SetBinContent(1,Migration_Matrix_muHLTUp->GetBinContent(1,1)); Ttbar_1_muHLTUp->SetBinContent(2,Migration_Matrix_muHLTUp->GetBinContent(2,1));
    TH1F *Ttbar_2_muHLTUp = new TH1F("Ttbar_2_muHLTUp","",newrec,new_rec);    Ttbar_2_muHLTUp->SetBinContent(1,Migration_Matrix_muHLTUp->GetBinContent(1,2)); Ttbar_2_muHLTUp->SetBinContent(2,Migration_Matrix_muHLTUp->GetBinContent(2,2));
    TH1F *Ttbar_1_Top_pT_rewUp = new TH1F("Ttbar_1_Top_pT_rewUp","",newrec,new_rec);   Ttbar_1_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,1)); Ttbar_1_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,1));
    TH1F *Ttbar_2_Top_pT_rewUp = new TH1F("Ttbar_2_Top_pT_rewUp","",newrec,new_rec);   Ttbar_2_Top_pT_rewUp->SetBinContent(1,Migration_Matrix_Top_pT_rewUp->GetBinContent(1,2)); Ttbar_2_Top_pT_rewUp->SetBinContent(2,Migration_Matrix_Top_pT_rewUp->GetBinContent(2,2)); 
    TH1F *Ttbar_1_mistagUp = new TH1F("Ttbar_1_mistagUp","",newrec,new_rec);   Ttbar_1_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,1)); Ttbar_1_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,1));
    TH1F *Ttbar_2_mistagUp = new TH1F("Ttbar_2_mistagUp","",newrec,new_rec);   Ttbar_2_mistagUp->SetBinContent(1,Migration_Matrix_mistagUp->GetBinContent(1,2)); Ttbar_2_mistagUp->SetBinContent(2,Migration_Matrix_mistagUp->GetBinContent(2,2));
    TH1F *Ttbar_1_toptagUp = new TH1F("Ttbar_1_toptagUp","",newrec,new_rec);   Ttbar_1_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,1)); Ttbar_1_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,1));
    TH1F *Ttbar_2_toptagUp = new TH1F("Ttbar_2_toptagUp","",newrec,new_rec);    Ttbar_2_toptagUp->SetBinContent(1,Migration_Matrix_toptagUp->GetBinContent(1,2)); Ttbar_2_toptagUp->SetBinContent(2,Migration_Matrix_toptagUp->GetBinContent(2,2));
    TH1F *Ttbar_1_muon_recUp = new TH1F("Ttbar_1_muon_recUp","",newrec,new_rec);    Ttbar_1_muon_recUp->SetBinContent(1,Migration_Matrix_muon_recUp->GetBinContent(1,1)); Ttbar_1_muon_recUp->SetBinContent(2,Migration_Matrix_muon_recUp->GetBinContent(2,1));
    TH1F *Ttbar_2_muon_recUp = new TH1F("Ttbar_2_muon_recUp","",newrec,new_rec);    Ttbar_2_muon_recUp->SetBinContent(1,Migration_Matrix_muon_recUp->GetBinContent(1,2)); Ttbar_2_muon_recUp->SetBinContent(2,Migration_Matrix_muon_recUp->GetBinContent(2,2));
    TH1F *Ttbar_1_ISRUp = new TH1F("Ttbar_1_ISRUp","",newrec,new_rec);   Ttbar_1_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,1)); Ttbar_1_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,1));
    TH1F *Ttbar_2_ISRUp = new TH1F("Ttbar_2_ISRUp","",newrec,new_rec);   Ttbar_2_ISRUp->SetBinContent(1,Migration_Matrix_ISRUp->GetBinContent(1,2)); Ttbar_2_ISRUp->SetBinContent(2,Migration_Matrix_ISRUp->GetBinContent(2,2));
    TH1F *Ttbar_1_FSRUp = new TH1F("Ttbar_1_FSRUp","",newrec,new_rec);    Ttbar_1_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,1)); Ttbar_1_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,1));
    TH1F *Ttbar_2_FSRUp = new TH1F("Ttbar_2_FSRUp","",newrec,new_rec);    Ttbar_2_FSRUp->SetBinContent(1,Migration_Matrix_FSRUp->GetBinContent(1,2)); Ttbar_2_FSRUp->SetBinContent(2,Migration_Matrix_FSRUp->GetBinContent(2,2));

    TH1F *Ttbar_1_jectimeptetaUp = new TH1F("Ttbar_1_jectimeptetaUp","",newrec,new_rec);    Ttbar_1_jectimeptetaUp->SetBinContent(1,Migration_Matrix_jectimeptetaUp->GetBinContent(1,1)); Ttbar_1_jectimeptetaUp->SetBinContent(2,Migration_Matrix_jectimeptetaUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jectimeptetaUp = new TH1F("Ttbar_2_jectimeptetaUp","",newrec,new_rec);    Ttbar_2_jectimeptetaUp->SetBinContent(1,Migration_Matrix_jectimeptetaUp->GetBinContent(1,2)); Ttbar_2_jectimeptetaUp->SetBinContent(2,Migration_Matrix_jectimeptetaUp->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatHFUp = new TH1F("Ttbar_1_jecRelativeStatHFUp","",newrec,new_rec);    Ttbar_1_jecRelativeStatHFUp->SetBinContent(1,Migration_Matrix_jecRelativeStatHFUp->GetBinContent(1,1)); Ttbar_1_jecRelativeStatHFUp->SetBinContent(2,Migration_Matrix_jecRelativeStatHFUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatHFUp = new TH1F("Ttbar_2_jecRelativeStatHFUp","",newrec,new_rec);    Ttbar_2_jecRelativeStatHFUp->SetBinContent(1,Migration_Matrix_jecRelativeStatHFUp->GetBinContent(1,2)); Ttbar_2_jecRelativeStatHFUp->SetBinContent(2,Migration_Matrix_jecRelativeStatHFUp->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatECUp = new TH1F("Ttbar_1_jecRelativeStatECUp","",newrec,new_rec);    Ttbar_1_jecRelativeStatECUp->SetBinContent(1,Migration_Matrix_jecRelativeStatECUp->GetBinContent(1,1)); Ttbar_1_jecRelativeStatECUp->SetBinContent(2,Migration_Matrix_jecRelativeStatECUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatECUp = new TH1F("Ttbar_2_jecRelativeStatECUp","",newrec,new_rec);    Ttbar_2_jecRelativeStatECUp->SetBinContent(1,Migration_Matrix_jecRelativeStatECUp->GetBinContent(1,2)); Ttbar_2_jecRelativeStatECUp->SetBinContent(2,Migration_Matrix_jecRelativeStatECUp->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatFSRUp = new TH1F("Ttbar_1_jecRelativeStatFSRUp","",newrec,new_rec);    Ttbar_1_jecRelativeStatFSRUp->SetBinContent(1,Migration_Matrix_jecRelativeStatFSRUp->GetBinContent(1,1)); Ttbar_1_jecRelativeStatFSRUp->SetBinContent(2,Migration_Matrix_jecRelativeStatFSRUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatFSRUp = new TH1F("Ttbar_2_jecRelativeStatFSRUp","",newrec,new_rec);    Ttbar_2_jecRelativeStatFSRUp->SetBinContent(1,Migration_Matrix_jecRelativeStatFSRUp->GetBinContent(1,2)); Ttbar_2_jecRelativeStatFSRUp->SetBinContent(2,Migration_Matrix_jecRelativeStatFSRUp->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeSampleUp = new TH1F("Ttbar_1_jecRelativeSampleUp","",newrec,new_rec);    Ttbar_1_jecRelativeSampleUp->SetBinContent(1,Migration_Matrix_jecRelativeSampleUp->GetBinContent(1,1)); Ttbar_1_jecRelativeSampleUp->SetBinContent(2,Migration_Matrix_jecRelativeSampleUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeSampleUp = new TH1F("Ttbar_2_jecRelativeSampleUp","",newrec,new_rec);    Ttbar_2_jecRelativeSampleUp->SetBinContent(1,Migration_Matrix_jecRelativeSampleUp->GetBinContent(1,2)); Ttbar_2_jecRelativeSampleUp->SetBinContent(2,Migration_Matrix_jecRelativeSampleUp->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativePtEC1Up = new TH1F("Ttbar_1_jecRelativePtEC1Up","",newrec,new_rec);    Ttbar_1_jecRelativePtEC1Up->SetBinContent(1,Migration_Matrix_jecRelativePtEC1Up->GetBinContent(1,1)); Ttbar_1_jecRelativePtEC1Up->SetBinContent(2,Migration_Matrix_jecRelativePtEC1Up->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativePtEC1Up = new TH1F("Ttbar_2_jecRelativePtEC1Up","",newrec,new_rec);    Ttbar_2_jecRelativePtEC1Up->SetBinContent(1,Migration_Matrix_jecRelativePtEC1Up->GetBinContent(1,2)); Ttbar_2_jecRelativePtEC1Up->SetBinContent(2,Migration_Matrix_jecRelativePtEC1Up->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativePtEC2Up = new TH1F("Ttbar_1_jecRelativePtEC2Up","",newrec,new_rec);    Ttbar_1_jecRelativePtEC2Up->SetBinContent(1,Migration_Matrix_jecRelativePtEC2Up->GetBinContent(1,1)); Ttbar_1_jecRelativePtEC2Up->SetBinContent(2,Migration_Matrix_jecRelativePtEC2Up->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativePtEC2Up = new TH1F("Ttbar_2_jecRelativePtEC2Up","",newrec,new_rec);    Ttbar_2_jecRelativePtEC2Up->SetBinContent(1,Migration_Matrix_jecRelativePtEC2Up->GetBinContent(1,2)); Ttbar_2_jecRelativePtEC2Up->SetBinContent(2,Migration_Matrix_jecRelativePtEC2Up->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeJEREC1Up = new TH1F("Ttbar_1_jecRelativeJEREC1Up","",newrec,new_rec);    Ttbar_1_jecRelativeJEREC1Up->SetBinContent(1,Migration_Matrix_jecRelativeJEREC1Up->GetBinContent(1,1)); Ttbar_1_jecRelativeJEREC1Up->SetBinContent(2,Migration_Matrix_jecRelativeJEREC1Up->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeJEREC1Up = new TH1F("Ttbar_2_jecRelativeJEREC1Up","",newrec,new_rec);    Ttbar_2_jecRelativeJEREC1Up->SetBinContent(1,Migration_Matrix_jecRelativeJEREC1Up->GetBinContent(1,2)); Ttbar_2_jecRelativeJEREC1Up->SetBinContent(2,Migration_Matrix_jecRelativeJEREC1Up->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeJEREC2Up = new TH1F("Ttbar_1_jecRelativeJEREC2Up","",newrec,new_rec);    Ttbar_1_jecRelativeJEREC2Up->SetBinContent(1,Migration_Matrix_jecRelativeJEREC2Up->GetBinContent(1,1)); Ttbar_1_jecRelativeJEREC2Up->SetBinContent(2,Migration_Matrix_jecRelativeJEREC2Up->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeJEREC2Up = new TH1F("Ttbar_2_jecRelativeJEREC2Up","",newrec,new_rec);    Ttbar_2_jecRelativeJEREC2Up->SetBinContent(1,Migration_Matrix_jecRelativeJEREC2Up->GetBinContent(1,2)); Ttbar_2_jecRelativeJEREC2Up->SetBinContent(2,Migration_Matrix_jecRelativeJEREC2Up->GetBinContent(2,2));
    TH1F *Ttbar_1_jecAbsoluteStatUp = new TH1F("Ttbar_1_jecAbsoluteStatUp","",newrec,new_rec);    Ttbar_1_jecAbsoluteStatUp->SetBinContent(1,Migration_Matrix_jecAbsoluteStatUp->GetBinContent(1,1)); Ttbar_1_jecAbsoluteStatUp->SetBinContent(2,Migration_Matrix_jecAbsoluteStatUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jecAbsoluteStatUp = new TH1F("Ttbar_2_jecAbsoluteStatUp","",newrec,new_rec);    Ttbar_2_jecAbsoluteStatUp->SetBinContent(1,Migration_Matrix_jecAbsoluteStatUp->GetBinContent(1,2)); Ttbar_2_jecAbsoluteStatUp->SetBinContent(2,Migration_Matrix_jecAbsoluteStatUp->GetBinContent(2,2));

    TH1F *Ttbar_1_jerUp = new TH1F("Ttbar_1_jerUp","",newrec,new_rec);   Ttbar_1_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,1)); Ttbar_1_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,1));
    TH1F *Ttbar_2_jerUp = new TH1F("Ttbar_2_jerUp","",newrec,new_rec);   Ttbar_2_jerUp->SetBinContent(1,Migration_Matrix_jerUp->GetBinContent(1,2)); Ttbar_2_jerUp->SetBinContent(2,Migration_Matrix_jerUp->GetBinContent(2,2));
    TH1F *Ttbar_1_hdampUp = new TH1F("Ttbar_1_hdampUp","",newrec,new_rec);   Ttbar_1_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,1)); Ttbar_1_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,1));
    TH1F *Ttbar_2_hdampUp = new TH1F("Ttbar_2_hdampUp","",newrec,new_rec);   Ttbar_2_hdampUp->SetBinContent(1,Migration_Matrix_hdampUp->GetBinContent(1,2)); Ttbar_2_hdampUp->SetBinContent(2,Migration_Matrix_hdampUp->GetBinContent(2,2));

    TH1F *Ttbar_1_btag_HF_corrUp = new TH1F("Ttbar_1_btag_HF_corrUp","",newrec,new_rec);   Ttbar_1_btag_HF_corrUp->SetBinContent(1,Migration_Matrix_btag_HF_corrUp->GetBinContent(1,1)); Ttbar_1_btag_HF_corrUp->SetBinContent(2,Migration_Matrix_btag_HF_corrUp->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_HF_corrUp = new TH1F("Ttbar_2_btag_HF_corrUp","",newrec,new_rec);   Ttbar_2_btag_HF_corrUp->SetBinContent(1,Migration_Matrix_btag_HF_corrUp->GetBinContent(1,2)); Ttbar_2_btag_HF_corrUp->SetBinContent(2,Migration_Matrix_btag_HF_corrUp->GetBinContent(2,2));
    TH1F *Ttbar_1_btag_LF_corrUp = new TH1F("Ttbar_1_btag_LF_corrUp","",newrec,new_rec);   Ttbar_1_btag_LF_corrUp->SetBinContent(1,Migration_Matrix_btag_LF_corrUp->GetBinContent(1,1)); Ttbar_1_btag_LF_corrUp->SetBinContent(2,Migration_Matrix_btag_LF_corrUp->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_LF_corrUp = new TH1F("Ttbar_2_btag_LF_corrUp","",newrec,new_rec);   Ttbar_2_btag_LF_corrUp->SetBinContent(1,Migration_Matrix_btag_LF_corrUp->GetBinContent(1,2)); Ttbar_2_btag_LF_corrUp->SetBinContent(2,Migration_Matrix_btag_LF_corrUp->GetBinContent(2,2));
    TH1F *Ttbar_1_btag_HF_unc18Up = new TH1F("Ttbar_1_btag_HF_unc18Up","",newrec,new_rec);   Ttbar_1_btag_HF_unc18Up->SetBinContent(1,Migration_Matrix_btag_HF_unc18Up->GetBinContent(1,1)); Ttbar_1_btag_HF_unc18Up->SetBinContent(2,Migration_Matrix_btag_HF_unc18Up->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_HF_unc18Up = new TH1F("Ttbar_2_btag_HF_unc18Up","",newrec,new_rec);   Ttbar_2_btag_HF_unc18Up->SetBinContent(1,Migration_Matrix_btag_HF_unc18Up->GetBinContent(1,2)); Ttbar_2_btag_HF_unc18Up->SetBinContent(2,Migration_Matrix_btag_HF_unc18Up->GetBinContent(2,2));
    TH1F *Ttbar_1_btag_LF_unc18Up = new TH1F("Ttbar_1_btag_LF_unc18Up","",newrec,new_rec);   Ttbar_1_btag_LF_unc18Up->SetBinContent(1,Migration_Matrix_btag_LF_unc18Up->GetBinContent(1,1)); Ttbar_1_btag_LF_unc18Up->SetBinContent(2,Migration_Matrix_btag_LF_unc18Up->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_LF_unc18Up = new TH1F("Ttbar_2_btag_LF_unc18Up","",newrec,new_rec);   Ttbar_2_btag_LF_unc18Up->SetBinContent(1,Migration_Matrix_btag_LF_unc18Up->GetBinContent(1,2)); Ttbar_2_btag_LF_unc18Up->SetBinContent(2,Migration_Matrix_btag_LF_unc18Up->GetBinContent(2,2));

    TH1F *Ttbar_1_pileupDown = new TH1F("Ttbar_1_pileupDown","",newrec,new_rec);  Ttbar_1_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,1)); Ttbar_1_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,1));
    TH1F *Ttbar_2_pileupDown = new TH1F("Ttbar_2_pileupDown","",newrec,new_rec);  Ttbar_2_pileupDown->SetBinContent(1,Migration_Matrix_pileupDown->GetBinContent(1,2)); Ttbar_2_pileupDown->SetBinContent(2,Migration_Matrix_pileupDown->GetBinContent(2,2));
    TH1F *Ttbar_1_muIDDown = new TH1F("Ttbar_1_muIDDown","",newrec,new_rec);      Ttbar_1_muIDDown->SetBinContent(1,Migration_Matrix_muIDDown->GetBinContent(1,1)); Ttbar_1_muIDDown->SetBinContent(2,Migration_Matrix_muIDDown->GetBinContent(2,1));
    TH1F *Ttbar_2_muIDDown = new TH1F("Ttbar_2_muIDDown","",newrec,new_rec);      Ttbar_2_muIDDown->SetBinContent(1,Migration_Matrix_muIDDown->GetBinContent(1,2)); Ttbar_2_muIDDown->SetBinContent(2,Migration_Matrix_muIDDown->GetBinContent(2,2));
    TH1F *Ttbar_1_muHLTDown = new TH1F("Ttbar_1_muHLTDown","",newrec,new_rec);    Ttbar_1_muHLTDown->SetBinContent(1,Migration_Matrix_muHLTDown->GetBinContent(1,1)); Ttbar_1_muHLTDown->SetBinContent(2,Migration_Matrix_muHLTDown->GetBinContent(2,1));
    TH1F *Ttbar_2_muHLTDown = new TH1F("Ttbar_2_muHLTDown","",newrec,new_rec);    Ttbar_2_muHLTDown->SetBinContent(1,Migration_Matrix_muHLTDown->GetBinContent(1,2)); Ttbar_2_muHLTDown->SetBinContent(2,Migration_Matrix_muHLTDown->GetBinContent(2,2));
    TH1F *Ttbar_1_Top_pT_rewDown = new TH1F("Ttbar_1_Top_pT_rewDown","",newrec,new_rec);   Ttbar_1_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,1)); Ttbar_1_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,1));
    TH1F *Ttbar_2_Top_pT_rewDown = new TH1F("Ttbar_2_Top_pT_rewDown","",newrec,new_rec);   Ttbar_2_Top_pT_rewDown->SetBinContent(1,Migration_Matrix_Top_pT_rewDown->GetBinContent(1,2)); Ttbar_2_Top_pT_rewDown->SetBinContent(2,Migration_Matrix_Top_pT_rewDown->GetBinContent(2,2));
    TH1F *Ttbar_1_mistagDown = new TH1F("Ttbar_1_mistagDown","",newrec,new_rec);   Ttbar_1_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,1)); Ttbar_1_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,1));
    TH1F *Ttbar_2_mistagDown = new TH1F("Ttbar_2_mistagDown","",newrec,new_rec);   Ttbar_2_mistagDown->SetBinContent(1,Migration_Matrix_mistagDown->GetBinContent(1,2)); Ttbar_2_mistagDown->SetBinContent(2,Migration_Matrix_mistagDown->GetBinContent(2,2));
    TH1F *Ttbar_1_toptagDown = new TH1F("Ttbar_1_toptagDown","",newrec,new_rec);   Ttbar_1_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,1)); Ttbar_1_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,1));
    TH1F *Ttbar_2_toptagDown = new TH1F("Ttbar_2_toptagDown","",newrec,new_rec);    Ttbar_2_toptagDown->SetBinContent(1,Migration_Matrix_toptagDown->GetBinContent(1,2)); Ttbar_2_toptagDown->SetBinContent(2,Migration_Matrix_toptagDown->GetBinContent(2,2));
    TH1F *Ttbar_1_muon_recDown = new TH1F("Ttbar_1_muon_recDown","",newrec,new_rec);    Ttbar_1_muon_recDown->SetBinContent(1,Migration_Matrix_muon_recDown->GetBinContent(1,1)); Ttbar_1_muon_recDown->SetBinContent(2,Migration_Matrix_muon_recDown->GetBinContent(2,1));
    TH1F *Ttbar_2_muon_recDown = new TH1F("Ttbar_2_muon_recDown","",newrec,new_rec);    Ttbar_2_muon_recDown->SetBinContent(1,Migration_Matrix_muon_recDown->GetBinContent(1,2)); Ttbar_2_muon_recDown->SetBinContent(2,Migration_Matrix_muon_recDown->GetBinContent(2,2));
    TH1F *Ttbar_1_ISRDown = new TH1F("Ttbar_1_ISRDown","",newrec,new_rec);   Ttbar_1_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,1)); Ttbar_1_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,1));
    TH1F *Ttbar_2_ISRDown = new TH1F("Ttbar_2_ISRDown","",newrec,new_rec);   Ttbar_2_ISRDown->SetBinContent(1,Migration_Matrix_ISRDown->GetBinContent(1,2)); Ttbar_2_ISRDown->SetBinContent(2,Migration_Matrix_ISRDown->GetBinContent(2,2));
    TH1F *Ttbar_1_FSRDown = new TH1F("Ttbar_1_FSRDown","",newrec,new_rec);    Ttbar_1_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,1)); Ttbar_1_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,1));
    TH1F *Ttbar_2_FSRDown = new TH1F("Ttbar_2_FSRDown","",newrec,new_rec);    Ttbar_2_FSRDown->SetBinContent(1,Migration_Matrix_FSRDown->GetBinContent(1,2)); Ttbar_2_FSRDown->SetBinContent(2,Migration_Matrix_FSRDown->GetBinContent(2,2));

    TH1F *Ttbar_1_jectimeptetaDown = new TH1F("Ttbar_1_jectimeptetaDown","",newrec,new_rec);    Ttbar_1_jectimeptetaDown->SetBinContent(1,Migration_Matrix_jectimeptetaDown->GetBinContent(1,1)); Ttbar_1_jectimeptetaDown->SetBinContent(2,Migration_Matrix_jectimeptetaDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jectimeptetaDown = new TH1F("Ttbar_2_jectimeptetaDown","",newrec,new_rec);    Ttbar_2_jectimeptetaDown->SetBinContent(1,Migration_Matrix_jectimeptetaDown->GetBinContent(1,2)); Ttbar_2_jectimeptetaDown->SetBinContent(2,Migration_Matrix_jectimeptetaDown->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatHFDown = new TH1F("Ttbar_1_jecRelativeStatHFDown","",newrec,new_rec);    Ttbar_1_jecRelativeStatHFDown->SetBinContent(1,Migration_Matrix_jecRelativeStatHFDown->GetBinContent(1,1)); Ttbar_1_jecRelativeStatHFDown->SetBinContent(2,Migration_Matrix_jecRelativeStatHFDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatHFDown = new TH1F("Ttbar_2_jecRelativeStatHFDown","",newrec,new_rec);    Ttbar_2_jecRelativeStatHFDown->SetBinContent(1,Migration_Matrix_jecRelativeStatHFDown->GetBinContent(1,2)); Ttbar_2_jecRelativeStatHFDown->SetBinContent(2,Migration_Matrix_jecRelativeStatHFDown->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatECDown = new TH1F("Ttbar_1_jecRelativeStatECDown","",newrec,new_rec);    Ttbar_1_jecRelativeStatECDown->SetBinContent(1,Migration_Matrix_jecRelativeStatECDown->GetBinContent(1,1)); Ttbar_1_jecRelativeStatECDown->SetBinContent(2,Migration_Matrix_jecRelativeStatECDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatECDown = new TH1F("Ttbar_2_jecRelativeStatECDown","",newrec,new_rec);    Ttbar_2_jecRelativeStatECDown->SetBinContent(1,Migration_Matrix_jecRelativeStatECDown->GetBinContent(1,2)); Ttbar_2_jecRelativeStatECDown->SetBinContent(2,Migration_Matrix_jecRelativeStatECDown->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeStatFSRDown = new TH1F("Ttbar_1_jecRelativeStatFSRDown","",newrec,new_rec);    Ttbar_1_jecRelativeStatFSRDown->SetBinContent(1,Migration_Matrix_jecRelativeStatFSRDown->GetBinContent(1,1)); Ttbar_1_jecRelativeStatFSRDown->SetBinContent(2,Migration_Matrix_jecRelativeStatFSRDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeStatFSRDown = new TH1F("Ttbar_2_jecRelativeStatFSRDown","",newrec,new_rec);    Ttbar_2_jecRelativeStatFSRDown->SetBinContent(1,Migration_Matrix_jecRelativeStatFSRDown->GetBinContent(1,2)); Ttbar_2_jecRelativeStatFSRDown->SetBinContent(2,Migration_Matrix_jecRelativeStatFSRDown->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeSampleDown = new TH1F("Ttbar_1_jecRelativeSampleDown","",newrec,new_rec);    Ttbar_1_jecRelativeSampleDown->SetBinContent(1,Migration_Matrix_jecRelativeSampleDown->GetBinContent(1,1)); Ttbar_1_jecRelativeSampleDown->SetBinContent(2,Migration_Matrix_jecRelativeSampleDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeSampleDown = new TH1F("Ttbar_2_jecRelativeSampleDown","",newrec,new_rec);    Ttbar_2_jecRelativeSampleDown->SetBinContent(1,Migration_Matrix_jecRelativeSampleDown->GetBinContent(1,2)); Ttbar_2_jecRelativeSampleDown->SetBinContent(2,Migration_Matrix_jecRelativeSampleDown->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativePtEC1Down = new TH1F("Ttbar_1_jecRelativePtEC1Down","",newrec,new_rec);    Ttbar_1_jecRelativePtEC1Down->SetBinContent(1,Migration_Matrix_jecRelativePtEC1Down->GetBinContent(1,1)); Ttbar_1_jecRelativePtEC1Down->SetBinContent(2,Migration_Matrix_jecRelativePtEC1Down->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativePtEC1Down = new TH1F("Ttbar_2_jecRelativePtEC1Down","",newrec,new_rec);    Ttbar_2_jecRelativePtEC1Down->SetBinContent(1,Migration_Matrix_jecRelativePtEC1Down->GetBinContent(1,2)); Ttbar_2_jecRelativePtEC1Down->SetBinContent(2,Migration_Matrix_jecRelativePtEC1Down->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativePtEC2Down = new TH1F("Ttbar_1_jecRelativePtEC2Down","",newrec,new_rec);    Ttbar_1_jecRelativePtEC2Down->SetBinContent(1,Migration_Matrix_jecRelativePtEC2Down->GetBinContent(1,1)); Ttbar_1_jecRelativePtEC2Down->SetBinContent(2,Migration_Matrix_jecRelativePtEC2Down->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativePtEC2Down = new TH1F("Ttbar_2_jecRelativePtEC2Down","",newrec,new_rec);    Ttbar_2_jecRelativePtEC2Down->SetBinContent(1,Migration_Matrix_jecRelativePtEC2Down->GetBinContent(1,2)); Ttbar_2_jecRelativePtEC2Down->SetBinContent(2,Migration_Matrix_jecRelativePtEC2Down->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeJEREC1Down = new TH1F("Ttbar_1_jecRelativeJEREC1Down","",newrec,new_rec);    Ttbar_1_jecRelativeJEREC1Down->SetBinContent(1,Migration_Matrix_jecRelativeJEREC1Down->GetBinContent(1,1)); Ttbar_1_jecRelativeJEREC1Down->SetBinContent(2,Migration_Matrix_jecRelativeJEREC1Down->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeJEREC1Down = new TH1F("Ttbar_2_jecRelativeJEREC1Down","",newrec,new_rec);    Ttbar_2_jecRelativeJEREC1Down->SetBinContent(1,Migration_Matrix_jecRelativeJEREC1Down->GetBinContent(1,2)); Ttbar_2_jecRelativeJEREC1Down->SetBinContent(2,Migration_Matrix_jecRelativeJEREC1Down->GetBinContent(2,2));
    TH1F *Ttbar_1_jecRelativeJEREC2Down = new TH1F("Ttbar_1_jecRelativeJEREC2Down","",newrec,new_rec);    Ttbar_1_jecRelativeJEREC2Down->SetBinContent(1,Migration_Matrix_jecRelativeJEREC2Down->GetBinContent(1,1)); Ttbar_1_jecRelativeJEREC2Down->SetBinContent(2,Migration_Matrix_jecRelativeJEREC2Down->GetBinContent(2,1));
    TH1F *Ttbar_2_jecRelativeJEREC2Down = new TH1F("Ttbar_2_jecRelativeJEREC2Down","",newrec,new_rec);    Ttbar_2_jecRelativeJEREC2Down->SetBinContent(1,Migration_Matrix_jecRelativeJEREC2Down->GetBinContent(1,2)); Ttbar_2_jecRelativeJEREC2Down->SetBinContent(2,Migration_Matrix_jecRelativeJEREC2Down->GetBinContent(2,2));
    TH1F *Ttbar_1_jecAbsoluteStatDown = new TH1F("Ttbar_1_jecAbsoluteStatDown","",newrec,new_rec);    Ttbar_1_jecAbsoluteStatDown->SetBinContent(1,Migration_Matrix_jecAbsoluteStatDown->GetBinContent(1,1)); Ttbar_1_jecAbsoluteStatDown->SetBinContent(2,Migration_Matrix_jecAbsoluteStatDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jecAbsoluteStatDown = new TH1F("Ttbar_2_jecAbsoluteStatDown","",newrec,new_rec);    Ttbar_2_jecAbsoluteStatDown->SetBinContent(1,Migration_Matrix_jecAbsoluteStatDown->GetBinContent(1,2)); Ttbar_2_jecAbsoluteStatDown->SetBinContent(2,Migration_Matrix_jecAbsoluteStatDown->GetBinContent(2,2));

    TH1F *Ttbar_1_jerDown = new TH1F("Ttbar_1_jerDown","",newrec,new_rec);   Ttbar_1_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,1)); Ttbar_1_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,1));
    TH1F *Ttbar_2_jerDown = new TH1F("Ttbar_2_jerDown","",newrec,new_rec);   Ttbar_2_jerDown->SetBinContent(1,Migration_Matrix_jerDown->GetBinContent(1,2)); Ttbar_2_jerDown->SetBinContent(2,Migration_Matrix_jerDown->GetBinContent(2,2));
    TH1F *Ttbar_1_hdampDown = new TH1F("Ttbar_1_hdampDown","",newrec,new_rec);   Ttbar_1_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,1)); Ttbar_1_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,1));
    TH1F *Ttbar_2_hdampDown = new TH1F("Ttbar_2_hdampDown","",newrec,new_rec);   Ttbar_2_hdampDown->SetBinContent(1,Migration_Matrix_hdampDown->GetBinContent(1,2)); Ttbar_2_hdampDown->SetBinContent(2,Migration_Matrix_hdampDown->GetBinContent(2,2));

    TH1F *Ttbar_1_btag_HF_corrDown = new TH1F("Ttbar_1_btag_HF_corrDown","",newrec,new_rec);   Ttbar_1_btag_HF_corrDown->SetBinContent(1,Migration_Matrix_btag_HF_corrDown->GetBinContent(1,1)); Ttbar_1_btag_HF_corrDown->SetBinContent(2,Migration_Matrix_btag_HF_corrDown->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_HF_corrDown = new TH1F("Ttbar_2_btag_HF_corrDown","",newrec,new_rec);   Ttbar_2_btag_HF_corrDown->SetBinContent(1,Migration_Matrix_btag_HF_corrDown->GetBinContent(1,2)); Ttbar_2_btag_HF_corrDown->SetBinContent(2,Migration_Matrix_btag_HF_corrDown->GetBinContent(2,2)); 
    TH1F *Ttbar_1_btag_LF_corrDown = new TH1F("Ttbar_1_btag_LF_corrDown","",newrec,new_rec);   Ttbar_1_btag_LF_corrDown->SetBinContent(1,Migration_Matrix_btag_LF_corrDown->GetBinContent(1,1)); Ttbar_1_btag_LF_corrDown->SetBinContent(2,Migration_Matrix_btag_LF_corrDown->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_LF_corrDown = new TH1F("Ttbar_2_btag_LF_corrDown","",newrec,new_rec);   Ttbar_2_btag_LF_corrDown->SetBinContent(1,Migration_Matrix_btag_LF_corrDown->GetBinContent(1,2)); Ttbar_2_btag_LF_corrDown->SetBinContent(2,Migration_Matrix_btag_LF_corrDown->GetBinContent(2,2));
    TH1F *Ttbar_1_btag_HF_unc18Down = new TH1F("Ttbar_1_btag_HF_unc18Down","",newrec,new_rec);   Ttbar_1_btag_HF_unc18Down->SetBinContent(1,Migration_Matrix_btag_HF_unc18Down->GetBinContent(1,1)); Ttbar_1_btag_HF_unc18Down->SetBinContent(2,Migration_Matrix_btag_HF_unc18Down->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_HF_unc18Down = new TH1F("Ttbar_2_btag_HF_unc18Down","",newrec,new_rec);   Ttbar_2_btag_HF_unc18Down->SetBinContent(1,Migration_Matrix_btag_HF_unc18Down->GetBinContent(1,2)); Ttbar_2_btag_HF_unc18Down->SetBinContent(2,Migration_Matrix_btag_HF_unc18Down->GetBinContent(2,2));
    TH1F *Ttbar_1_btag_LF_unc18Down = new TH1F("Ttbar_1_btag_LF_unc18Down","",newrec,new_rec);   Ttbar_1_btag_LF_unc18Down->SetBinContent(1,Migration_Matrix_btag_LF_unc18Down->GetBinContent(1,1)); Ttbar_1_btag_LF_unc18Down->SetBinContent(2,Migration_Matrix_btag_LF_unc18Down->GetBinContent(2,1));
    TH1F *Ttbar_2_btag_LF_unc18Down = new TH1F("Ttbar_2_btag_LF_unc18Down","",newrec,new_rec);   Ttbar_2_btag_LF_unc18Down->SetBinContent(1,Migration_Matrix_btag_LF_unc18Down->GetBinContent(1,2)); Ttbar_2_btag_LF_unc18Down->SetBinContent(2,Migration_Matrix_btag_LF_unc18Down->GetBinContent(2,2));
 


Ttbar_1_jerDown->Scale(Ttbar_1_nominal->Integral()/Ttbar_1_jerDown->Integral());
Ttbar_2_jerDown->Scale(Ttbar_2_nominal->Integral()/Ttbar_2_jerDown->Integral());
Ttbar_1_jerUp->Scale(Ttbar_1_nominal->Integral()/Ttbar_1_jerUp->Integral());
Ttbar_2_jerUp->Scale(Ttbar_2_nominal->Integral()/Ttbar_2_jerUp->Integral());


Ttbar_1_jectimeptetaDown->Scale(Ttbar_1_nominal->Integral()*0.973/Ttbar_1_jectimeptetaDown->Integral());
Ttbar_2_jectimeptetaDown->Scale(Ttbar_2_nominal->Integral()*0.973/Ttbar_2_jectimeptetaDown->Integral());
Ttbar_1_jectimeptetaUp->Scale(Ttbar_1_nominal->Integral()*1.027/Ttbar_1_jectimeptetaUp->Integral());
Ttbar_2_jectimeptetaUp->Scale(Ttbar_2_nominal->Integral()*1.027/Ttbar_2_jectimeptetaUp->Integral());
Ttbar_1_jecRelativeStatHFDown->Scale(Ttbar_1_nominal->Integral()*0.974/Ttbar_1_jecRelativeStatHFDown->Integral());
Ttbar_2_jecRelativeStatHFDown->Scale(Ttbar_2_nominal->Integral()*0.974/Ttbar_2_jecRelativeStatHFDown->Integral());
Ttbar_1_jecRelativeStatHFUp->Scale(Ttbar_1_nominal->Integral()*1.026/Ttbar_1_jecRelativeStatHFUp->Integral());
Ttbar_2_jecRelativeStatHFUp->Scale(Ttbar_2_nominal->Integral()*1.026/Ttbar_2_jecRelativeStatHFUp->Integral());
Ttbar_1_jecRelativeStatECDown->Scale(Ttbar_1_nominal->Integral()*0.972/Ttbar_1_jecRelativeStatECDown->Integral());
Ttbar_2_jecRelativeStatECDown->Scale(Ttbar_2_nominal->Integral()*0.972/Ttbar_2_jecRelativeStatECDown->Integral());
Ttbar_1_jecRelativeStatECUp->Scale(Ttbar_1_nominal->Integral()*1.028/Ttbar_1_jecRelativeStatECUp->Integral());
Ttbar_2_jecRelativeStatECUp->Scale(Ttbar_2_nominal->Integral()*1.028/Ttbar_2_jecRelativeStatECUp->Integral());
Ttbar_1_jecRelativeStatFSRDown->Scale(Ttbar_1_nominal->Integral()*0.971/Ttbar_1_jecRelativeStatFSRDown->Integral());
Ttbar_2_jecRelativeStatFSRDown->Scale(Ttbar_2_nominal->Integral()*0.971/Ttbar_2_jecRelativeStatFSRDown->Integral());
Ttbar_1_jecRelativeStatFSRUp->Scale(Ttbar_1_nominal->Integral()*1.029/Ttbar_1_jecRelativeStatFSRUp->Integral());
Ttbar_2_jecRelativeStatFSRUp->Scale(Ttbar_2_nominal->Integral()*1.029/Ttbar_2_jecRelativeStatFSRUp->Integral());
Ttbar_1_jecRelativeSampleDown->Scale(Ttbar_1_nominal->Integral()*0.975/Ttbar_1_jecRelativeSampleDown->Integral());
Ttbar_2_jecRelativeSampleDown->Scale(Ttbar_2_nominal->Integral()*0.975/Ttbar_2_jecRelativeSampleDown->Integral());
Ttbar_1_jecRelativeSampleUp->Scale(Ttbar_1_nominal->Integral()*1.025/Ttbar_1_jecRelativeSampleUp->Integral());
Ttbar_2_jecRelativeSampleUp->Scale(Ttbar_2_nominal->Integral()*1.025/Ttbar_2_jecRelativeSampleUp->Integral());
Ttbar_1_jecRelativePtEC1Down->Scale(Ttbar_1_nominal->Integral()*0.9745/Ttbar_1_jecRelativePtEC1Down->Integral());
Ttbar_2_jecRelativePtEC1Down->Scale(Ttbar_2_nominal->Integral()*0.9745/Ttbar_2_jecRelativePtEC1Down->Integral());
Ttbar_1_jecRelativePtEC1Up->Scale(Ttbar_1_nominal->Integral()*1.022/Ttbar_1_jecRelativePtEC1Up->Integral());
Ttbar_2_jecRelativePtEC1Up->Scale(Ttbar_2_nominal->Integral()*1.022/Ttbar_2_jecRelativePtEC1Up->Integral());
Ttbar_1_jecRelativePtEC2Down->Scale(Ttbar_1_nominal->Integral()*0.973/Ttbar_1_jecRelativePtEC2Down->Integral());
Ttbar_2_jecRelativePtEC2Down->Scale(Ttbar_2_nominal->Integral()*0.973/Ttbar_2_jecRelativePtEC2Down->Integral());
Ttbar_1_jecRelativePtEC2Up->Scale(Ttbar_1_nominal->Integral()*1.027/Ttbar_1_jecRelativePtEC2Up->Integral());
Ttbar_2_jecRelativePtEC2Up->Scale(Ttbar_2_nominal->Integral()*1.027/Ttbar_2_jecRelativePtEC2Up->Integral());
Ttbar_1_jecRelativeJEREC1Down->Scale(Ttbar_1_nominal->Integral()*0.972/Ttbar_1_jecRelativeJEREC1Down->Integral());
Ttbar_2_jecRelativeJEREC1Down->Scale(Ttbar_2_nominal->Integral()*0.972/Ttbar_2_jecRelativeJEREC1Down->Integral());
Ttbar_1_jecRelativeJEREC1Up->Scale(Ttbar_1_nominal->Integral()*1.028/Ttbar_1_jecRelativeJEREC1Up->Integral());
Ttbar_2_jecRelativeJEREC1Up->Scale(Ttbar_2_nominal->Integral()*1.028/Ttbar_2_jecRelativeJEREC1Up->Integral());
Ttbar_1_jecRelativeJEREC2Down->Scale(Ttbar_1_nominal->Integral()*0.974/Ttbar_1_jecRelativeJEREC2Down->Integral());
Ttbar_2_jecRelativeJEREC2Down->Scale(Ttbar_2_nominal->Integral()*0.974/Ttbar_2_jecRelativeJEREC2Down->Integral());
Ttbar_1_jecRelativeJEREC2Up->Scale(Ttbar_1_nominal->Integral()*1.026/Ttbar_1_jecRelativeJEREC2Up->Integral());
Ttbar_2_jecRelativeJEREC2Up->Scale(Ttbar_2_nominal->Integral()*1.026/Ttbar_2_jecRelativeJEREC2Up->Integral());
Ttbar_1_jecAbsoluteStatDown->Scale(Ttbar_1_nominal->Integral()*0.974/Ttbar_1_jecAbsoluteStatDown->Integral());
Ttbar_2_jecAbsoluteStatDown->Scale(Ttbar_2_nominal->Integral()*0.974/Ttbar_2_jecAbsoluteStatDown->Integral());
Ttbar_1_jecAbsoluteStatUp->Scale(Ttbar_1_nominal->Integral()*1.026/Ttbar_1_jecAbsoluteStatUp->Integral());
Ttbar_2_jecAbsoluteStatUp->Scale(Ttbar_2_nominal->Integral()*1.026/Ttbar_2_jecAbsoluteStatUp->Integral());

TFile out("Input_undfolding_data_.root","recreate");


Ttbar_1_nominal->Write();
Ttbar_2_nominal->Write();

Ttbar_1_pileupUp->Write();
Ttbar_2_pileupUp->Write();
Ttbar_1_muIDUp->Write();
Ttbar_2_muIDUp->Write();
Ttbar_1_muHLTUp->Write();
Ttbar_2_muHLTUp->Write();
Ttbar_1_Top_pT_rewUp->Write();
Ttbar_2_Top_pT_rewUp->Write();
Ttbar_1_mistagUp->Write();
Ttbar_2_mistagUp->Write();
Ttbar_1_toptagUp->Write();
Ttbar_2_toptagUp->Write();
Ttbar_1_muon_recUp->Write();
Ttbar_2_muon_recUp->Write();
Ttbar_1_ISRUp->Write();
Ttbar_2_ISRUp->Write();
Ttbar_1_FSRUp->Write();
Ttbar_2_FSRUp->Write();

Ttbar_1_jectimeptetaUp->Write();
Ttbar_2_jectimeptetaUp->Write();
Ttbar_1_jecRelativeStatHFUp->Write();
Ttbar_2_jecRelativeStatHFUp->Write();
Ttbar_1_jecRelativeStatECUp->Write();
Ttbar_2_jecRelativeStatECUp->Write();
Ttbar_1_jecRelativeStatFSRUp->Write();
Ttbar_2_jecRelativeStatFSRUp->Write();
Ttbar_1_jecRelativeSampleUp->Write();
Ttbar_2_jecRelativeSampleUp->Write();
Ttbar_1_jecRelativePtEC1Up->Write();
Ttbar_2_jecRelativePtEC1Up->Write();
Ttbar_1_jecRelativePtEC2Up->Write();
Ttbar_2_jecRelativePtEC2Up->Write();
Ttbar_1_jecRelativeJEREC2Up->Write();
Ttbar_2_jecRelativeJEREC2Up->Write();
Ttbar_1_jecRelativeJEREC1Up->Write();
Ttbar_2_jecRelativeJEREC1Up->Write();
Ttbar_1_jecAbsoluteStatUp->Write();
Ttbar_2_jecAbsoluteStatUp->Write();

Ttbar_1_jerUp->Write();
Ttbar_2_jerUp->Write();
Ttbar_1_hdampUp->Write();
Ttbar_2_hdampUp->Write();

Ttbar_1_btag_HF_corrUp->Write();
Ttbar_2_btag_HF_corrUp->Write();
Ttbar_1_btag_LF_corrUp->Write();
Ttbar_2_btag_LF_corrUp->Write();
Ttbar_1_btag_HF_unc18Up->Write();
Ttbar_2_btag_HF_unc18Up->Write();
Ttbar_1_btag_LF_unc18Up->Write();
Ttbar_2_btag_LF_unc18Up->Write();

Ttbar_1_pileupDown->Write();
Ttbar_2_pileupDown->Write();
Ttbar_1_muIDDown->Write();
Ttbar_2_muIDDown->Write();
Ttbar_1_muHLTDown->Write();
Ttbar_2_muHLTDown->Write();
Ttbar_1_Top_pT_rewDown->Write();
Ttbar_2_Top_pT_rewDown->Write();
Ttbar_1_mistagDown->Write();
Ttbar_2_mistagDown->Write();
Ttbar_1_toptagDown->Write();
Ttbar_2_toptagDown->Write();
Ttbar_1_muon_recDown->Write();
Ttbar_2_muon_recDown->Write();
Ttbar_1_ISRDown->Write();
Ttbar_2_ISRDown->Write();
Ttbar_1_FSRDown->Write();
Ttbar_2_FSRDown->Write();

Ttbar_1_jectimeptetaDown->Write();
Ttbar_2_jectimeptetaDown->Write();
Ttbar_1_jecRelativeStatHFDown->Write();
Ttbar_2_jecRelativeStatHFDown->Write();
Ttbar_1_jecRelativeStatFSRDown->Write();
Ttbar_2_jecRelativeStatFSRDown->Write();
Ttbar_1_jecRelativeStatECDown->Write();
Ttbar_2_jecRelativeStatECDown->Write();
Ttbar_1_jecRelativeSampleDown->Write();
Ttbar_2_jecRelativeSampleDown->Write();
Ttbar_1_jecRelativePtEC1Down->Write();
Ttbar_2_jecRelativePtEC1Down->Write();
Ttbar_1_jecRelativePtEC2Down->Write();
Ttbar_2_jecRelativePtEC2Down->Write();
Ttbar_1_jecRelativeJEREC2Down->Write();
Ttbar_2_jecRelativeJEREC2Down->Write();
Ttbar_1_jecRelativeJEREC1Down->Write();
Ttbar_2_jecRelativeJEREC1Down->Write();
Ttbar_1_jecAbsoluteStatDown->Write();
Ttbar_2_jecAbsoluteStatDown->Write();

Ttbar_1_jerDown->Write();
Ttbar_2_jerDown->Write();
Ttbar_1_hdampDown->Write();
Ttbar_2_hdampDown->Write();

Ttbar_1_btag_HF_corrDown->Write();
Ttbar_2_btag_HF_corrDown->Write();
Ttbar_1_btag_LF_corrDown->Write();
Ttbar_2_btag_LF_corrDown->Write();
Ttbar_1_btag_HF_unc18Down->Write();
Ttbar_2_btag_HF_unc18Down->Write();
Ttbar_1_btag_LF_unc18Down->Write();
Ttbar_2_btag_LF_unc18Down->Write();

auto c1    = new TCanvas("c1","c1",600,400);
c1->cd();
Migration_Matrix->GetYaxis()->SetTitle("#Delta #cbar y_{gen} #cbar");   
Migration_Matrix->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
Migration_Matrix->Draw("COLZ");

TLatex latex;
latex.SetTextSize(0.045);
latex.SetTextAlign(11);  //align at top
latex.DrawLatex(-1.9,2.05,"CMS preliminary");

TLatex latex2;
latex2.SetTextSize(0.045);
latex2.SetTextAlign(11);  //align at top
latex2.DrawLatex(0.9,2.05,"58.8 fb^{-1} (13 TeV)");

c1->Print("Migration_Matrix.pdf");

/*
    TH2F *Stability_Matrix = new TH2F("Stability_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);
    TH2F *Purity_Matrix = new TH2F("Purity_Matrix","",binnum_gen,bins_gen,binnum_gen,bins_gen);

   for(int a=1;a<=binnum_gen;a++){
       for(Int_t b=1;b<=binnum_gen;b++){
            Stability_Matrix->SetBinContent(a,b,Migration_Matrix->GetBinContent(a,b)/Migration_Matrix->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinContent(a,b,Migration_Matrix->GetBinContent(a,b)/Migration_Matrix->Integral(a,a,1,binnum_gen));
            Stability_Matrix->SetBinError(a,b,Migration_Matrix->GetBinError(a,b)/Migration_Matrix->Integral(1,binnum_gen,b,b));
            Purity_Matrix->SetBinError(a,b,Migration_Matrix->GetBinError(a,b)/Migration_Matrix->Integral(a,a,1,binnum_gen));
       }
   }

// Purity && Stability

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
   Stability->GetXaxis()->SetTitle("#Delta #cbar y_{rec} #cbar");
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

   TLegend leg(.55, .55, .75, .75, "");
   leg.SetFillColor(0);
   leg.AddEntry(Purity, "Purity");
   leg.AddEntry(Stability, "Stability");
   leg.SetBorderSize(0);
   leg.Draw("Same");

   TLatex latex3;
   latex3.SetTextSize(0.045);
   latex3.SetTextAlign(11);
   latex3.DrawLatex(-1.9,1.02,"CMS preliminary");

   TLatex latex4;
   latex4.SetTextSize(0.045);
   latex4.SetTextAlign(11);
   latex4.DrawLatex(1.1,1.02,"36.77 fb^{-1} (13 TeV)");

   cc->Print("PS.pdf");

   TMatrix H(8,8);
   for (Int_t irow = 0; irow < 2; irow++){
   for (Int_t icol = 0; icol < 2; icol++){
      H[icol][irow] = Migration_Matrix->GetBinContent(irow+1,icol+1);
   }
   }
   cout << H.Determinant() << endl;

   TVectorD rowsum(2);
   TVectorD fSig(2);
   for (Int_t irow = 0; irow < 2; irow++){
   for (Int_t icol = 0; icol < 2; icol++){
   rowsum(irow-1) += H(irow,icol);
   }
   }
   TDecompSVD lu(H);
   TVectorD sig = lu.GetSig();
   for (Int_t irow = 0; irow < 2; irow++){
    cout << sig[irow] << endl;
   }

*/ 
}


