#!/bin/bash


text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:r_1[1,0,20]' --PO map='.*/Ttbar_in_2:r_2[1,0,20]'  --PO map='.*/Ttbar_in_3:r_3[1,0,20]' --PO map='.*/Ttbar_in_4:r_4[1,0,20]'  --PO verbose



declare -a POIS=(
  "r_1"
  "r_2"
  "r_3"
  "r_4"
)

export WORKSPACE=AE_750.root
export VERBOSITY=0

export SetParametersExplicit="r_1=1,r_2=1,r_3=1,r_4=1"
export SetParameterRanges="r_1=0.5,2:r_2=0.5,2:r_3=0.5,2:r_4=0.5,2"
export redefineSignalPOIs="r_1,r_2,r_3,r_4"

export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
#export ASIMOV=""

combine -M GenerateOnly AE_750.root -m 125 --freezeParameters MH -t 1000 -n .generate_exp --expectSignal 1 --saveToys --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --cminDefaultMinimizerStrategy 0 -v $VERBOSITY

combine -M MultiDimFit AE_750.root -m 125 --freezeParameters MH -t 1000 -n .bias_truth_exp_fit_poly --expectSignal 1 --toysFile higgsCombine.generate_exp.GenerateOnly.mH125.123456.root --algo singles --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --cminDefaultMinimizerStrategy 0 --robustFit 1
 
