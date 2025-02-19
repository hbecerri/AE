#!/bin/bash


declare -a StringArray=(

#"TTTo2L2Nu_UL17_0"
#"TTTo2L2Nu_UL17_10"
#"TTTo2L2Nu_UL17_12"
#"TTTo2L2Nu_UL17_13"
#"TTTo2L2Nu_UL17_14"
#"TTTo2L2Nu_UL17_15"
#"TTTo2L2Nu_UL17_16"
#"TTTo2L2Nu_UL17_17"
#"TTTo2L2Nu_UL17_4"
#"TTTo2L2Nu_UL17_5"
#"TTTo2L2Nu_UL17_6"
#"TTTo2L2Nu_UL17_7"
#"TTTo2L2Nu_UL17_8"
#"TTTo2L2Nu_UL17_9"
#"TTToHadronic_UL17_12"
#"TTToHadronic_UL17_13"
#"TTToHadronic_UL17_16"
#"TTToHadronic_UL17_17"
#"TTToHadronic_UL17_18"
#"TTToHadronic_UL17_1"
#"TTToHadronic_UL17_20"
#"TTToHadronic_UL17_21"
#"TTToHadronic_UL17_22"
#"TTToHadronic_UL17_23"
#"TTToHadronic_UL17_25"
#"TTToHadronic_UL17_26"
#"TTToHadronic_UL17_3"
#"TTToHadronic_UL17_4"
#"TTToHadronic_UL17_5"
#"TTToHadronic_UL17_6"
#"TTToHadronic_UL17_7"
#"TTToHadronic_UL17_8"
#"TTToHadronic_UL17_9"
"TTToSemiLeptonic_UL17_0"
"TTToSemiLeptonic_UL17_10"
"TTToSemiLeptonic_UL17_11"
"TTToSemiLeptonic_UL17_12"
"TTToSemiLeptonic_UL17_13"
"TTToSemiLeptonic_UL17_14"
"TTToSemiLeptonic_UL17_15"
"TTToSemiLeptonic_UL17_16"
"TTToSemiLeptonic_UL17_17"
"TTToSemiLeptonic_UL17_18"
"TTToSemiLeptonic_UL17_19"
"TTToSemiLeptonic_UL17_1"
"TTToSemiLeptonic_UL17_20"
"TTToSemiLeptonic_UL17_21"
"TTToSemiLeptonic_UL17_22"
"TTToSemiLeptonic_UL17_23"
"TTToSemiLeptonic_UL17_24"
"TTToSemiLeptonic_UL17_25"
"TTToSemiLeptonic_UL17_26"
"TTToSemiLeptonic_UL17_27"
"TTToSemiLeptonic_UL17_2"
"TTToSemiLeptonic_UL17_3"
"TTToSemiLeptonic_UL17_4"
"TTToSemiLeptonic_UL17_5"
"TTToSemiLeptonic_UL17_6"
"TTToSemiLeptonic_UL17_7"
"TTToSemiLeptonic_UL17_8"
"TTToSemiLeptonic_UL17_9"

)

for var in ${StringArray[@]}; do
        root -l -b -q "add_hdamp.C(\"${var}\")"
done
