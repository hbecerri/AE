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
 
            TH1F *Back_2 = new TH1F("Back_2","",60,-600,600);

            TH2F *Back1 = new TH2F("Back1","",2,-600,600,2,-600,600);
 
            string selcuts_boosted_central_1 = "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && TMath::Abs(Boost_top_E - Boost_antitop_E) > 50 && TMath::Abs(Gen_Boost_top_E - Gen_Boost_antitop_E) > 50)";

            treereco_ttbar_semi->Project("Back_2","(Boost_top_E - Boost_antitop_E)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
            treereco_ttbar_semi->Project("Back1" ,"(Boost_top_E - Boost_antitop_E):(Gen_Boost_top_E - Gen_Boost_antitop_E)",Form("%s*eventweight*%s",selcuts_boosted_central_1.c_str(),syst.c_str()));
 
            string sys;
            if(syst == "1") sys = "nominal";

            Back_2->Write("DeltaE");
            Back1->Write("Matrix");
            
       }

} 
}
}

