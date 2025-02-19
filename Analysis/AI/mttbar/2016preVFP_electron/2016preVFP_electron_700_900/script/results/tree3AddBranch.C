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
 

void tree3AddBranch() {
    TFile *f("/nfs/dust/cms/user/hugobg/analysis/muon_good_with_new_variables/workdir_Analysis_UL17_muon/uhh2.AnalysisModuleRunner.MC.WZ_UL17_1.root", "update");
 
    Float_t new_v;
    auto t3 = f->Get<TTree>("AnalysisTree");
    auto newBranch = t3->Branch("new_v", &new_v, "new_v/F");
 
    Long64_t nentries = t3->GetEntries(); // read the number of entries in the t3
 
    for (Long64_t i = 0; i < nentries; i++) {
        new_v = gRandom->Gaus(0, 1);
        newBranch->Fill();
    }
 
    t3->Write("", TObject::kOverwrite); // save only the new version of the tree
}
