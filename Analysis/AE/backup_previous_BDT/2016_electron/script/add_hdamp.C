#include <fstream>
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
#include <vector>

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2016")
{

vector<Float_t> g1;
Float_t w;

std::ifstream ifs("/nfs/dust/cms/user/hugobg/hdamp/CMSSW_11_2_5_patch2/src/hdamp_down_joke_muon/TTToSemiLeptonic_UL17_15.txt");

std::string line;

while(std::getline(ifs, line))
{
     w = std::stof(line); 
    g1.push_back(w); 
}


//system("python3 myscript.py");

TFile *fin=TFile::Open("/nfs/dust/cms/user/hugobg/analysis/muon_good_with_new_variables/hdamp/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL17_15.root","UPDATE"); 
TTree *t = (TTree*)fin->Get("AnalysisTree");
Float_t new_var_down;
TBranch * _new_var_down = t->Branch("new_var_down",&new_var_down,"grid/F");

cout << g1.size() << endl;
cout << t->GetEntries() << endl;


for(int ev=0; ev < t->GetEntries() ; ++ev) {

         if(ev < g1.size()) new_var_down = g1.at(ev);
         else new_var_down = g1.at(ev%g1.size());
	_new_var_down->Fill();
} 
 

t->Write("", TObject::kOverwrite);




 
//TFile fout("exit_file.root","UPDATE");
//t->Write();
//
//
//
//fout.Close();

//=========
/*  
TFile out("Input_undfolding_data_.root","recreate");
string texts[]={"DATA","TTToSemiLeptonic","WJetsToLNu","ST","DYJetsToLL_M-50_HT","QCD_HT","Diboson"};
//string texts[]={"WJetsToLNu"}; 
//string texts[]={"TTToSemiLeptonic"};
 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("AnalysisTree","");
    chreco_ttbar_semi->Add(Form("/nfs/dust/cms/user/hugobg/analysis/electron/uhh2.AnalysisModuleRunner.MC.%s_2016preVFP.root/AnalysisTree",text.c_str()));
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t bins_gen[] = {-20000,0,20000};
    Float_t new_rec[]  = {-20000,0,20000};

//    int len = 10, len_rec = 10;
//    Float_t bins_gen[] = {0,100,200,300,400,750,600,750,800,900,750};
//    Float_t new_rec[]  = {0,100,200,300,400,750,600,750,800,900,750};
  
    
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;
    Int_t   binnum_gen = sizeof(bins_gen)/sizeof(Float_t) - 1;

//--------Unfold----------??

       if(text == "DATA"){
 
       TChain *chreco_data = new TChain("AnalysisTree","");
       chreco_data->Add("/nfs/dust/cms/user/hugobg/analysis/electron/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016preVFP.root/AnalysisTree");
       TTree *treereco_data = (TTree*) chreco_data;
 
       TH1F *Back_1 = new TH1F("Back_1","",2,-2000,2000);
       string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
       treereco_data->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s",selcuts_boosted_central_1.c_str()));
       Back_1->Write("data_obs");
       delete Back_1;


       }else if(text == "TTToSemiLeptonic"){

       string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfelec_id_up/weight_sfelec_id", "weight_sfelec_id_down/weight_sfelec_id","weight_sfelec_trigger_up/weight_sfelec_trigger","weight_sfelec_trigger_down/weight_sfelec_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

//        string systs[] = {"1"};
   
        for(const string &syst : systs){
 
            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen); 
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";

           treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
//           treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_Ak4_add_pt:Boost_Ak4_add_pt",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
 

            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);

            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";
            if(syst == "weight_sfelec_id_up/weight_sfelec_id") sys = "eleIDUp";  if(syst == "weight_sfelec_id_down/weight_sfelec_id") sys = "eleIDDown";
            if(syst == "weight_sfelec_iso_up/weight_sfelec_iso") sys = "eleISOUp";  if(syst == "weight_sfelec_iso_down/weight_sfelec_iso") sys = "eleISODown";
            if(syst == "weight_sfelec_trigger_up/weight_sfelec_trigger") sys = "eleHLTUp";  if(syst == "weight_sfelec_trigger_down/weight_sfelec_trigger") sys = "eleHLTDown";
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
   
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str())); 
            
            if(syst == "1"){
                auto c1    = new TCanvas("c1","c1",600,400);
                c1->cd();
                Migration_Matrix_1->Draw("COLZ");
                TLatex latex;
                latex.SetTextSize(0.045);
                latex.SetTextAlign(11);  //align at top
                latex.DrawLatex(-2000,2005.5,"CMS preliminary");
                TLatex latex2;
                latex2.SetTextSize(0.045);
                latex2.SetTextAlign(11);  //align at top
                latex2.DrawLatex(1200,2005.5,"58.8 fb^{-1} (13 TeV)");
                c1->Print("Migration_Matrix_Mapp.pdf");
             }

             delete Ttbar_1_nominal; delete Ttbar_2_nominal;
             delete Migration_Matrix_1;
            
         }

         for(int k=1;k<=11;k++){

            string syst="wgtMC__PDF["+std::to_string(k)+"]";
            cout << syst << endl;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);
            string sys = "PDF"+std::to_string(k)+"Up";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Ttbar_2_nominal;
            delete Migration_Matrix_1;
         } 

         for(int k=1;k<=11;k++){

            string syst="1";
            cout << syst << endl;

            TH2F *Migration_Matrix_1 = new TH2F("Migration_Matrix_1","",newrec,new_rec,binnum_gen,bins_gen);
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
            treereco_ttbar_semi->Project("Migration_Matrix_1","Gen_Boost_top_E - Gen_Boost_antitop_E:Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            TH1D* Ttbar_1_nominal = Migration_Matrix_1->ProjectionX("Ttbar_1_nominal", 1,1);
            TH1D* Ttbar_2_nominal = Migration_Matrix_1->ProjectionX("Ttbar_2_nominal", 2,2);
            string sys = "PDF"+std::to_string(k)+"Down";
            Ttbar_1_nominal->Write(Form("%s_1_%s",text.c_str(),sys.c_str()));
            Ttbar_2_nominal->Write(Form("%s_2_%s",text.c_str(),sys.c_str()));
            delete Ttbar_1_nominal; delete Ttbar_2_nominal;
            delete Migration_Matrix_1;
         }

 
       } else{


        string systs[] = {"1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfelec_id_up/weight_sfelec_id", "weight_sfelec_id_down/weight_sfelec_id","weight_sfelec_trigger_up/weight_sfelec_trigger","weight_sfelec_trigger_down/weight_sfelec_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight"};

        for(const string &syst : systs){

            TH1F *Back_1 = new TH1F("Back_1","",2,-2000,2000);
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
  
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys;
            if(syst == "1") sys = "nominal";
            if(syst == "weight_pu_up/weight_pu") sys = "pileupUp";  if(syst == "weight_pu_down/weight_pu") sys = "pileupDown";  
            if(syst == "weight_sfelec_id_up/weight_sfelec_id") sys = "eleIDUp";  if(syst == "weight_sfelec_id_down/weight_sfelec_id") sys = "eleIDDown"; 
            if(syst == "weight_sfelec_iso_up/weight_sfelec_iso") sys = "eleISOUp";  if(syst == "weight_sfelec_iso_down/weight_sfelec_iso") sys = "eleISODown";  
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
            if(syst == "weight_btag_bc_up_un/weight_btag")   sys = "btag_HF_unc16Up"       ; if(syst == "weight_btag_bc_down_un/weight_btag")   sys = "btag_HF_unc16Down"  ;
            if(syst == "weight_btag_udsg_up_un/weight_btag") sys = "btag_LF_unc16Up"       ; if(syst == "weight_btag_udsg_down_un/weight_btag") sys = "btag_LF_unc16Down"  ;
            if(syst == "prefiringWeightUp/prefiringWeight") sys = "L1Prefiring16Up"       ; if(syst == "prefiringWeightDown/prefiringWeight") sys = "L1Prefiring16Down"  ;
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }

        for(int k=1;k<=11;k++){       
     
            string syst="wgtMC__PDF["+std::to_string(k)+"]"+"/"+"wgtMC__PDF[1]";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",2,-2000,2000);
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Up";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;
   
        } 
        for(int k=1;k<=11;k++){

            string syst="1";
            cout << syst << endl;

            TH1F *Back_1 = new TH1F("Back_1","",2,-2000,2000);
            string selcuts_boosted_central_1 = "(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 750 && chi2 < 30 && Boost_Ak4_add_pt > 100)";
            treereco_ttbar_semi->Project("Back_1","Boost_top_E - Boost_antitop_E",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            string tt=text;  transform(tt.begin(), tt.end(), tt.begin(), ::tolower);
            string sys = "PDF"+std::to_string(k)+"Down";
            Back_1->Write(Form("%s_%s",tt.c_str(),sys.c_str()));
            delete Back_1;

        }


    }  
     
}
*/ 
}


