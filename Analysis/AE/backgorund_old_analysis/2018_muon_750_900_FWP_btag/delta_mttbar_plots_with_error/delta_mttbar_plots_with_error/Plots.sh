#!/bin/bash

#python makePlots_fromAnalysisTree.py Mttbar 0 0
#mv Mttbar_new.pdf Mttbar_btag_2016_ele.pdf

#python makePlots_fromAnalysisTree.py Mttbar 1 0
#mv Mttbar_new.pdf Mttbar_ttag_2016_ele.pdf

#python makePlots_fromAnalysisTree.py Mttbar 0 1
#mv Mttbar_new.pdf Mttbar_wtag_2016_ele.pdf 

#python makePlots_fromAnalysisTree.py rec_chi2 1 1
#mv Mttbar_new.pdf Mttbar_wtag_2016_ele.pdf 

mkdir ttag
mkdir btag
mkdir wtag

declare -a StringArray=("TH_M" "TL_M" "MET_pt" "lep1_pt" "N_Ak8" "N_Ak4" "pT_ttbar" "rec_chi2" "Mttbar")

for var in ${StringArray[@]}; do

rm *.pdf 
python makePlots_fromAnalysisTree.py ${var} 0 0
mv *.pdf btag/

rm *.pdf
python makePlots_fromAnalysisTree.py ${var} 1 0
mv *.pdf ttag/

rm *.pdf
python makePlots_fromAnalysisTree.py ${var} 0 1
mv *.pdf wtag/

done

