#!/bin/bash


#rm -f -r *.root 
#rm -f -r *"
#rm -f -r *.pdf
#rm -f -r *.json


declare -a StringArray=(

#"TTTo2L2Nu_UL16preVFP_0"
#"TTTo2L2Nu_UL16preVFP_1"
#"TTTo2L2Nu_UL16preVFP_2"
#"TTTo2L2Nu_UL16preVFP_3"
#"TTTo2L2Nu_UL16preVFP_4"
#"TTTo2L2Nu_UL16preVFP_5"
#"TTTo2L2Nu_UL16preVFP_6"
#"TTToHadronic_UL16preVFP_0"
#"TTToHadronic_UL16preVFP_10"
#"TTToHadronic_UL16preVFP_11"
#"TTToHadronic_UL16preVFP_1"
#"TTToHadronic_UL16preVFP_2"
#"TTToHadronic_UL16preVFP_3"
#"TTToHadronic_UL16preVFP_4"
#"TTToHadronic_UL16preVFP_5"
#"TTToHadronic_UL16preVFP_6"
#"TTToHadronic_UL16preVFP_7"
#"TTToHadronic_UL16preVFP_8"
#"TTToHadronic_UL16preVFP_9"
"TTToSemiLeptonic_UL16preVFP_0"
"TTToSemiLeptonic_UL16preVFP_10"
"TTToSemiLeptonic_UL16preVFP_1"
"TTToSemiLeptonic_UL16preVFP_2"
"TTToSemiLeptonic_UL16preVFP_3"
"TTToSemiLeptonic_UL16preVFP_4"
"TTToSemiLeptonic_UL16preVFP_5"
"TTToSemiLeptonic_UL16preVFP_6"
"TTToSemiLeptonic_UL16preVFP_7"
"TTToSemiLeptonic_UL16preVFP_8"
"TTToSemiLeptonic_UL16preVFP_9"


)

for var in ${StringArray[@]}; do
        root -l -b -q "add_hdamp.C(\"${var}\")"
done
