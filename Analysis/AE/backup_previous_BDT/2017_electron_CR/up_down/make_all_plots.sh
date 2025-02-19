#!/bin/bash

declare -a StringArray=("hdamp" "pileup" "eleID" "eleHLT" "eleISO" "toptag_corr" "toptag_uncorr" "FSR" "ISR" "MuR_MuF" "MuR" "MuF" "btag_HF_corr" "btag_LF_corr" "btag_HF_unc17" "btag_LF_unc17" "top_pt_rew" "L1Prefiring17" 
)

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













