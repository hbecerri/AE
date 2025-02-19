#!/bin/bash

#declare -a StringArray=("hdamp" "pileup" "eleID" "eleHLT" "eleISO" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc16" "btag_LF_unc16" "top_pt_rew" "L1Prefiring16")

declare -a StringArray=("hdamp" "L1Prefiring16" "top_pt_rew" "pileup" "eleID" "eleHLT" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR" "MuF" "MuR_MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc16" "btag_LF_unc16" "PDF1" "PDF2" "BBEC1_2016" "EC2_2016" "RelativeSample_2016" "Absolute_2016" "HF" "EC2" "Absolute" "RelativeBal" "JER")



for var in ${StringArray[@]}; do

python up_down.py ${var}


done













