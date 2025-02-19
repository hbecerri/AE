#!/bin/bash

#declare -a StringArray=("hdamp" "pileup" "eleID" "eleHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc18" "btag_LF_unc18" "top_pt_rew")
#declare -a StringArray=( "RelativeSample" "RelativeStatEC" "RelativeStatFSR" "JEREC1" "PtEC2" "JEREC2" "TimePtEta" "PtEC1")

declare -a StringArray=("MuR_MuF")

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













