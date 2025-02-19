#!/bin/bash

#declare -a StringArray=("N_Ak4" "MET_pt" "Ele_E" "Ele_eta" "Ele_phi" "Ele_pt" "Mu_E" "Mu_eta" "Mu_phi" "Mu_pt" "Boost_Ak4_add_E" "Boost_Ak4_add_eta" "Boost_Ak4_add_pt" "Boost_Ak4_add_phi" "Boost_antitop_E" "Boost_antitop_pt" "Boost_antitop_eta" "Boost_antitop_phi" "M_tt" "Boost_top_E" "Boost_top_eta" "Boost_top_phi" "Boost_top_pt")

#declare -a StringArray=("M_tt") 

declare -a StringArray=("M_tt" "top_pt" "antitop_pt" "Mu_pt" "MET_pt" "N_Ak4")

for var in ${StringArray[@]}; do

python makePlots_fromAnalysisTree.py ${var} 


done

