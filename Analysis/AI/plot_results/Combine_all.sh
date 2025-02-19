#!/bin/bash

cp ../AE_750.txt .

text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:r_1[1,0,20]' --PO map='.*/Ttbar_in_2:r_2[1,0,20]'  --PO map='.*/Ttbar_in_3:r_3[1,0,20]' --PO map='.*/Ttbar_in_4:r_4=expr;;r_4("24847/25590*@1*(100+@3)/(100-@3) + 25478.6284/25590*@2*(100+@3)/(100-@3) - 24847/25590*@0",r_1,r_2,r_3,IA[0.11,-5,5])' --PO verbose



declare -a POIS=(
  "r_1"
  "r_2"
  "r_3"
  "IA"
)

export WORKSPACE=AE_750.root
export VERBOSITY=0

export SetParameters="rgx{r.+}=1,IA=0.11"
export SetParametersExplicit="r_1=1,r_2=1,r_3=1,IA=0.11"
export SetParameterRanges="rgx{r.+}=0.5,2:IA=-10,5"
export redefineSignalPOIs="IA,r_1,r_2,r_3"

#export SetParametersExplicit="r_1=1,r_2=1,r_3=1,r_4=1"
#export SetParameterRanges="r_1=0.5,2:r_2=0.5,2:r_3=0.5,2:r_4=0.5,2"
#export redefineSignalPOIs="r_1,r_2,r_3,r_4"

#export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
export ASIMOV=""



rm -f multidimfit.root

combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 1 -m 125 --saveFitResult  $ASIMOV 

PostFitShapesFromWorkspace -d AE_750.txt -w AE_750.root --output shapes.root -m 125 -f multidimfit.root:fit_mdf --postfit --sampling --print



