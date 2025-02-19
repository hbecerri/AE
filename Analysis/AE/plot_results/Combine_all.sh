#!/bin/bash

cp ../AE_750.txt .

text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:r_1[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_2[1,0,20]' --PO verbose

declare -a POIS=(

  "r_1"
  "r_2"
)

export WORKSPACE=AE_750.root
export VERBOSITY=0

export SetParametersExplicit="r_1=1,r_2=1"
export SetParameterRanges="r_1=0.5,2:r_2=0.5,2"
export redefineSignalPOIs="r_1,r_2"

#export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
export ASIMOV=""

rm -f multidimfit.root

combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 1 -m 125 --saveFitResult  $ASIMOV 

PostFitShapesFromWorkspace -d AE_750.txt -w AE_750.root --output shapes.root -m 125 -f multidimfit.root:fit_mdf --postfit --sampling --print



