#!/usr/bin/env bash
date

text2workspace.py  muon_2016postVFP_750_900.txt -o muon_2016postVFP_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:r_1[1,0,20]' --PO map='.*/Ttbar_in_2:r_2[1,0,20]' --PO verbose

#text2workspace.py muon_2016postVFP_750_900.txt -o muon_2016postVFP_750_900.root -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:rneg[1,0,20]' --PO map='.*/Ttbar_in_1:r_pos=expr;;r_pos("2770.3799/2754.7318*@0*(100+@1)/(100-@1)",rneg,AE[-0.28,-100,100])' --PO verbose
 

declare -a POIS=(
  "r_1"
  "r_2"
)

#declare -a POIS=(
#  "rneg"
#  "AE"
#)

export WORKSPACE=muon_2016postVFP_750_900.root
export VERBOSITY=0

#export SetParameters="rgx{r.+}=1,AE=-0.28"
#export SetParametersExplicit="rneg=1,AE=-0.28"
#export SetParameterRanges="rgx{r.+}=0.0,20:AE=-100,100"
#export redefineSignalPOIs="AE,rneg"

export SetParametersExplicit="r_1=1,r_2=1"
export SetParameterRanges="r_1=0.0,3:r_2=0.0,3"
export redefineSignalPOIs="r_1,r_2"

export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
#export ASIMOV=""


###IMPACTS
echo
echo
echo "DO INITIAL FIT"
echo
echo
combine -M MultiDimFit --algo singles -d $WORKSPACE -n .part3E.snapshot -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace $ASIMOV
mv higgsCombine.part3E.snapshot.MultiDimFit.mH125.root higgsCombine_initialFit_Test.MultiDimFit.mH125.root

combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .snapshot $ASIMOV
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .nominal $ASIMOV --snapshotName MultiDimFit
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .freezeall $ASIMOV --snapshotName MultiDimFit --freezeParameters allConstrainedNuisances

