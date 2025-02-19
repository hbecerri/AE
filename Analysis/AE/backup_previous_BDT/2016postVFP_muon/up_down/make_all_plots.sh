#!/bin/bash

declare -a StringArray=("hdamp" "pileup" "muID" "muHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc16" "btag_LF_unc16" "top_pt_rew" "L1Prefiring16")

#declare -a StringArray=( "RelativeSample" "RelativeStatEC" "RelativeStatFSR" "JEREC1" "PtEC2" "JEREC2" "TimePtEta" "PtEC1" "MuR_MuF")

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













