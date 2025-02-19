#!/bin/bash


#rm -f -r *.root 
#rm -f -r *"
#rm -f -r *.pdf
#rm -f -r *.json


declare -a StringArray=(
#"TTTo2L2Nu_UL16postVFP_0"
#"TTTo2L2Nu_UL16postVFP_1"
#"TTTo2L2Nu_UL16postVFP_2"
#"TTTo2L2Nu_UL16postVFP_3"
#"TTTo2L2Nu_UL16postVFP_4"
#"TTTo2L2Nu_UL16postVFP_5"
#"TTTo2L2Nu_UL16postVFP_6"
#"TTTo2L2Nu_UL16postVFP_7"
#"TTToHadronic_UL16postVFP_0"
#"TTToHadronic_UL16postVFP_10"
#"TTToHadronic_UL16postVFP_11"
#"TTToHadronic_UL16postVFP_12"
#"TTToHadronic_UL16postVFP_1"
#"TTToHadronic_UL16postVFP_2"
#"TTToHadronic_UL16postVFP_3"
#"TTToHadronic_UL16postVFP_4"
#"TTToHadronic_UL16postVFP_5"
#"TTToHadronic_UL16postVFP_6"
#"TTToHadronic_UL16postVFP_7"
#"TTToHadronic_UL16postVFP_8"
#"TTToHadronic_UL16postVFP_9"
"TTToSemiLeptonic_UL16postVFP_0"
"TTToSemiLeptonic_UL16postVFP_10"
"TTToSemiLeptonic_UL16postVFP_11"
"TTToSemiLeptonic_UL16postVFP_1"
"TTToSemiLeptonic_UL16postVFP_2"
"TTToSemiLeptonic_UL16postVFP_3"
"TTToSemiLeptonic_UL16postVFP_4"
"TTToSemiLeptonic_UL16postVFP_5"
"TTToSemiLeptonic_UL16postVFP_6"
"TTToSemiLeptonic_UL16postVFP_7"
"TTToSemiLeptonic_UL16postVFP_8"
"TTToSemiLeptonic_UL16postVFP_9"
)

for var in ${StringArray[@]}; do
        root -l -b -q "add_hdamp.C(\"${var}\")"
done
