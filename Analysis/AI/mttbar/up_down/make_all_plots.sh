#!/bin/bash

declare -a StringArray=("2018_muon/2018_muon_500_700" "2018_muon/2018_muon_700_900" "2018_muon/2018_muon_900_Inf"
"2018_electron/2018_electron_500_700" "2018_electron/2018_electron_700_900" "2018_electron/2018_electron_900_Inf"
"2017_muon/2017_muon_500_700" "2017_muon/2017_muon_700_900" "2017_muon/2017_muon_900_Inf"
"2017_electron/2017_electron_500_700" "2017_electron/2017_electron_700_900" "2017_electron/2017_electron_900_Inf"
"2016preVFP_muon/2016preVFP_muon_500_700" "2016preVFP_muon/2016preVFP_muon_700_900" "2016preVFP_muon/2016preVFP_muon_900_Inf"
"2016preVFP_electron/2016preVFP_electron_500_700" "2016preVFP_electron/2016preVFP_electron_700_900" "2016preVFP_electron/2016preVFP_electron_900_Inf"
"2016postVFP_muon/2016postVFP_muon_500_700" "2016postVFP_muon/2016postVFP_muon_700_900" "2016postVFP_muon/2016postVFP_muon_900_Inf"
"2016postVFP_electron/2016postVFP_electron_500_700" "2016postVFP_electron/2016postVFP_electron_700_900" "2016postVFP_electron/2016postVFP_electron_900_Inf"
)

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













