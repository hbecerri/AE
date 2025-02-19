#!/bin/bash

#declare -a StringArray=("Boost_Ak4_add_E" "Boost_Ak4_add_eta" "Boost_Ak4_add_pt" "Boost_Ak4_add_phi" "Boost_antitop_E" "Boost_antitop_pt" "Boost_antitop_eta" "Boost_antitop_phi" "M_tt" "Boost_top_E" "Boost_top_eta" "Boost_top_phi" "Boost_top_pt" "N_Ak4" "N_Ak8")

declare -a StringArray=("M_tt" "top_pt" "antitop_pt" "Mu_pt" "MET_pt" "N_Ak4" "chi2")
 
for var in ${StringArray[@]}; do

python makePlots_fromAnalysisTree.py ${var} 


done

