#!/bin/bash


declare -a StringArray=("M_tophad_dr_ak4" "M_tophad_dr_ttag" "M_toplep_dr_ak4" "M_toplep_dr_ttag")

for var in ${StringArray[@]}; do
    root -l -q -b "FitGaussianToTH1.C(\"${var}\")"
done
 







