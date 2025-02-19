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

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2016")
{

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/%s_CHS/muon/uhh2.AnalysisModuleRunner.MC.TTToS*.root/AnalysisTree",year.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

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

//    TH2F *Migration_Matrix_ = new TH2F("Migration_Matrix_resolved","",newrec,new_rec,binnum_gen,bins_gen);
//    TH2F *Migration_Matrix_semiresolved = new TH2F("Migration_Matrix_semiresolved","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_pileupUp = new TH2F("Migration_Matrix_pileupUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muIDUp = new TH2F("Migration_Matrix_muIDUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTUp = new TH2F("Migration_Matrix_muHLTUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewUp = new TH2F("Migration_Matrix_Top_pT_rewUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagUp = new TH2F("Migration_Matrix_mistagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagUp = new TH2F("Migration_Matrix_toptagUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recUp = new TH2F("Migration_Matrix_muon_recUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRUp = new TH2F("Migration_Matrix_ISRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRUp = new TH2F("Migration_Matrix_FSRUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecUp = new TH2F("Migration_Matrix_jecUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jerUp = new TH2F("Migration_Matrix_jerUp","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampUp = new TH2F("Migration_Matrix_hdampUp","",newrec,new_rec,binnum_gen,bins_gen);

    TH2F *Migration_Matrix_pileupDown = new TH2F("Migration_Matrix_pileupDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muIDDown = new TH2F("Migration_Matrix_muIDDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muHLTDown = new TH2F("Migration_Matrix_muHLTDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_Top_pT_rewDown = new TH2F("Migration_Matrix_Top_pT_rewDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_mistagDown = new TH2F("Migration_Matrix_mistagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_toptagDown = new TH2F("Migration_Matrix_toptagDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_muon_recDown = new TH2F("Migration_Matrix_muon_recDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_ISRDown = new TH2F("Migration_Matrix_ISRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_FSRDown = new TH2F("Migration_Matrix_FSRDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jecDown = new TH2F("Migration_Matrix_jecDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_jerDown = new TH2F("Migration_Matrix_jerDown","",newrec,new_rec,binnum_gen,bins_gen);
    TH2F *Migration_Matrix_hdampDown = new TH2F("Migration_Matrix_hdampDown","",newrec,new_rec,binnum_gen,bins_gen);


    string  pileupUp = "(weight_sfmu_HighPtID)*(weight_pu_up)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  pileupDown = "(weight_sfmu_HighPtID)*(weight_pu_down)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  muIDUp = "(weight_sfmu_HighPtID_up)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  muIDDown = "(weight_sfmu_HighPtID_down)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  muHLTUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger_up)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  muHLTDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger_down)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  cferr1Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1up)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  cferr1Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr1down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  cferr2Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2up)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  cferr2Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_cferr2down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfup)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfdown)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfstats1Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfstats1Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats1down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfstats2Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hfstats2Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_hfstats2down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  jesUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesup)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  jesDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_jesdown)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfup)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfdown)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfstats1Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1up)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfstats1Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats1down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfstats2Up = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2up)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  lfstats2Down = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_lfstats2down)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  Top_pT_rewUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(1)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  Top_pT_rewDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_down_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  mistagUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*1.02*(weight_HT_HT)";
    string  mistagDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*0.98*(weight_HT_HT)";
    string  toptagUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_up_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  toptagDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_down_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  muon_recUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_up)*(weight_HT_HT)";
    string  muon_recDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_down)*(weight_HT_HT)";
    string  HTUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT_up)";
    string  HTDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT_down)";
    string  ISRUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*ISRup";
    string  ISRDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*ISRdown";
    string  FSRUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*FSRup";
    string  FSRDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*FSRdown";
    string  jecUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  jecDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  jerUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  jerDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)";
    string  hdampUp = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*0.84";
    string  hdampDown = "(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_MuonTrigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)*0.84";

    Float_t mistag_nominal = 1.;

    string selcuts_boosted_central = Form("(ttagN <= 1 && btagN >= 1 && wtagN <= 1 && rec_chi2 < 30 && Mttbar > 900)*%f",mistag_nominal);

//Matrices
    treereco_ttbar_semi->Project("Migration_Matrix",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_MuonTrigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)",selcuts_boosted_central.c_str()));

    treereco_ttbar_semi->Project("Migration_Matrix_pileupUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muIDUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jecUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jerUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerUp.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hdampUp",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampUp.c_str(),selcuts_boosted_central.c_str()));


    treereco_ttbar_semi->Project("Migration_Matrix_pileupDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",pileupDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muIDDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muIDDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muHLTDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muHLTDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_Top_pT_rewDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",Top_pT_rewDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_mistagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",mistagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_toptagDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",toptagDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_muon_recDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",muon_recDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_ISRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",ISRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_FSRDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",FSRDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jecDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jecDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_jerDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",jerDown.c_str(),selcuts_boosted_central.c_str()));
    treereco_ttbar_semi->Project("Migration_Matrix_hdampDown",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("weight*%s*%s",hdampDown.c_str(),selcuts_boosted_central.c_str()));


//----------Making_input_root_file_for_unfolding-----------?

    TFile out("Input_undfolding_data_.root","recreate");
    out.mkdir("SR1T");

    out.cd("SR1T");
    Migration_Matrix->Write();    
    Migration_Matrix_pileupUp->Write();
    Migration_Matrix_muIDUp->Write();
    Migration_Matrix_muHLTUp->Write();
    Migration_Matrix_Top_pT_rewUp->Write();
    Migration_Matrix_mistagUp->Write();
    Migration_Matrix_toptagUp->Write();
    Migration_Matrix_muon_recUp->Write();
    Migration_Matrix_ISRUp->Write();
    Migration_Matrix_FSRUp->Write();
    Migration_Matrix_jecUp->Write();
    Migration_Matrix_jerUp->Write();
    Migration_Matrix_hdampUp->Write();

    Migration_Matrix_pileupDown->Write();
    Migration_Matrix_muIDDown->Write();
    Migration_Matrix_muHLTDown->Write();
    Migration_Matrix_Top_pT_rewDown->Write();
    Migration_Matrix_mistagDown->Write();
    Migration_Matrix_toptagDown->Write();
    Migration_Matrix_muon_recDown->Write();
    Migration_Matrix_ISRDown->Write();
    Migration_Matrix_FSRDown->Write();
    Migration_Matrix_jecDown->Write();
    Migration_Matrix_jerDown->Write();
    Migration_Matrix_hdampDown->Write();
  
}


/*
 /semiresolved
    treereco_ttbar_semi->Project("Migration_Matrix_semiresolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_MuonTrigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)",selcuts_semiresolved_central.c_str()));

//resolved
//    treereco_ttbar_semi->Project("Migration_Matrix_resolved",Form("%s < %f ? %f : (%s > %f ? %f : %s) : %s < %f ? %f : (%s > %f ? %f : %s)",var_gen.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_gen.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_gen.c_str(),var_name.c_str(),bins_gen[0]+0.01,bins_gen[0]+0.01,var_name.c_str(),bins_gen[binnum_gen]-0.01,bins_gen[binnum_gen]-0.01,var_name.c_str()),Form("%s*weight*weight_sfmu_HighPtID*weight_sfmu_MuonTrigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)",selcuts_resolved_central.c_str()));
//    */


