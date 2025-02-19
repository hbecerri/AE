#!/bin/bash
# run_unfolding.sh

# Load ROOT environment (if necessary)
# source /path/to/root/bin/thisroot.sh  # Uncomment and adjust if needed.
source /cvmfs/cms.cern.ch/cmsset_default.sh
source /afs/desy.de/user/h/hugobg/uhh2_ul.sh
# Run the ROOT script
root -l -b -q /nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AE/2018_muon_BDT/script/all_unfolding_data.C

