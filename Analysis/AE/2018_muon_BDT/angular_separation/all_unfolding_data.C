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
#include <iostream>

void all_unfolding_data(string var_name = "", string var_gen = "", string region = "", string year = "2018")
{
  
TFile out("Input_undfolding_data_all.root","recreate");
string texts[]={"Ttbar_in"};

 
for(const string &text : texts){
    cout << "value of text: " << text << endl;

    gStyle->SetOptStat(0);

//----obetener_toda_la_informacion_de_entrada--------??

    TChain *chreco_ttbar_semi = new TChain("Events","");
    chreco_ttbar_semi->Add("/nfs/dust/cms/user/hugobg/analysis/muon/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root/AnalysisTree");
    TTree *treereco_ttbar_semi = (TTree*) chreco_ttbar_semi;

//array for variable 

    int len = 3, len_rec = 3;
    Float_t new_rec[]  = {0,0.2,0.4,0.6,0.8,1};
    Int_t   newrec     = sizeof(new_rec)/sizeof(Float_t) - 1;

//--------Unfold----------??

    if(text == "Ttbar_in"){

         string systs[] = {"1"};
         for(const string &syst : systs){
 
            TH1F *Back_1 = new TH1F("Back_1","",12,1.2,6);
            TH1F *Back_2 = new TH1F("Back_2","",12,1.2,6);
            TH1F *Back_3 = new TH1F("Back_3","",12,1.2,6);
            TH1F *Back_4 = new TH1F("Back_4","",12,1.2,6); 

            TH2F *Back1 = new TH2F("Back1","",12,1.2,6,12,1.2,6);
            TH2F *Back2 = new TH2F("Back2","",12,1.2,6,12,1.2,6);   
 
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0)";

            treereco_ttbar_semi->Project("Back_1","sqrt(pow(Ak4_add_eta - top_eta, 2) + pow(fmod(Ak4_add_phi - top_phi + 3.1415, 2 * 3.1415) - 3.1415, 2))",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back_2","sqrt(pow(Ak4_add_eta - antitop_eta, 2) + pow(fmod(Ak4_add_phi - antitop_phi + 3.1415, 2 * 3.1415) - 3.1415, 2))",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));

string deltaR_gentop = "sqrt(pow(0.5 * log((sqrt(pow(newgentop_px, 2) + pow(newgentop_py, 2) + pow(newgentop_pz, 2)) + newgentop_pz) / "
                       "(sqrt(pow(newgentop_px, 2) + pow(newgentop_py, 2) + pow(newgentop_pz, 2)) - newgentop_pz)) - "
                       "0.5 * log((sqrt(pow(addnewgenjet_px, 2) + pow(addnewgenjet_py, 2) + pow(addnewgenjet_pz, 2)) + addnewgenjet_pz) / "
                       "(sqrt(pow(addnewgenjet_px, 2) + pow(addnewgenjet_py, 2) + pow(addnewgenjet_pz, 2)) - addnewgenjet_pz)), 2) + "
                       "pow(TMath::ATan2(newgentop_py, newgentop_px) - TMath::ATan2(addnewgenjet_py, addnewgenjet_px), 2))";

string deltaR_genantitop = "sqrt(pow(0.5 * log((sqrt(pow(newgenantitop_px, 2) + pow(newgenantitop_py, 2) + pow(newgenantitop_pz, 2)) + newgenantitop_pz) / "
                          "(sqrt(pow(newgenantitop_px, 2) + pow(newgenantitop_py, 2) + pow(newgenantitop_pz, 2)) - newgenantitop_pz)) - "
                          "0.5 * log((sqrt(pow(addnewgenjet_px, 2) + pow(addnewgenjet_py, 2) + pow(addnewgenjet_pz, 2)) + addnewgenjet_pz) / "
                          "(sqrt(pow(addnewgenjet_px, 2) + pow(addnewgenjet_py, 2) + pow(addnewgenjet_pz, 2)) - addnewgenjet_pz)), 2) + "
                          "pow(TMath::ATan2(newgenantitop_py, newgenantitop_px) - TMath::ATan2(addnewgenjet_py, addnewgenjet_px), 2))";

treereco_ttbar_semi->Project("Back_3", deltaR_gentop.c_str(), Form("%s*eventweight*%s", selcuts_boosted_central_1.c_str(), syst.c_str()));
treereco_ttbar_semi->Project("Back_4", deltaR_genantitop.c_str(), Form("%s*eventweight*%s", selcuts_boosted_central_1.c_str(), syst.c_str()));

treereco_ttbar_semi->Project("Back1", Form("%s:sqrt(pow(Ak4_add_eta - top_eta, 2) + pow(fmod(Ak4_add_phi - top_phi + 3.1415, 2 * 3.1415) - 3.1415, 2))",deltaR_gentop.c_str()), Form("%s*eventweight*%s", selcuts_boosted_central_1.c_str(), syst.c_str()));
treereco_ttbar_semi->Project("Back2", Form("%s:sqrt(pow(Ak4_add_eta - antitop_eta, 2) + pow(fmod(Ak4_add_phi - antitop_phi + 3.1415, 2 * 3.1415) - 3.1415, 2))",deltaR_genantitop.c_str()), Form("%s*eventweight*%s", selcuts_boosted_central_1.c_str(), syst.c_str())); 
  
            string sys;
            if(syst == "1") sys = "nominal";

            Back_1->Write("top_add_jet_reco");
            Back_2->Write("antitop_add_jet_reco");
            Back_3->Write("gentop_add_jet_reco");
            Back_4->Write("genantitop_add_jet_reco");
            Back1->Write("Matrix_top");  
            Back2->Write("Matrix_antitop");  
       }

} 
}
}

