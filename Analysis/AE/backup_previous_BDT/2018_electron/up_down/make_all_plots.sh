#!/bin/bash

#declare -a StringArray=("hdamp" "pileup" "eleID" "eleHLT" "eleISO" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc18" "btag_LF_unc18" "top_pt_rew" )

declare -a StringArray=("hdamp" "top_pt_rew" "pileup" "eleID" "eleHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR" "MuF" "MuR_MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc18" "btag_LF_unc18" "BBEC1_2018" "EC2_2018" "RelativeSample_2018" "Absolute_2018" "HF" "EC2" "Absolute" "RelativeBal" "PDF1" "PDF2")

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













