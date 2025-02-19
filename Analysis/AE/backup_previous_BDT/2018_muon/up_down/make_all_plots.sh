#!/bin/bash

#declare -a StringArray=("hdamp" "pileup" "muID" "muHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc18" "btag_LF_unc18" "top_pt_rew" 
#)

#declare -a StringArray=( "RelativeSample" "RelativeStatEC" "RelativeStatFSR" "JEREC1" "PtEC2" "JEREC2" "TimePtEta" "PtEC1" "MuR_MuF")

declare -a StringArray=("hdamp" "pileup" "muISO" "muID" "muHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR" "MuF" "MuR_MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc18" "btag_LF_unc18" "BBEC1_2018" "EC2_2018" "RelativeSample_2018" "Absolute_2018" "HF" "EC2" "Absolute" "RelativeBal" "JER")

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













