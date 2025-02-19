#!/usr/bin/env bash
date

text2workspace.py electron_2018_750_900.txt -o electron_2018_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:r_1[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_2[1,0,20]' --PO verbose

#text2workspace.py electron_2018_750_900.txt -o electron_2018_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:rneg[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:rpos=expr;;rpos("18710/18178*@0*(100+@1)/(100-@1)",rneg,AE[-1.4,-5,5])' --PO verbose
 

declare -a POIS=(
  "r_1"
  "r_2"
)

#declare -a POIS=(
#  "rneg"
#  "AE"
#)

export WORKSPACE=electron_2018_750_900.root
export VERBOSITY=0

#export SetParameters="rgx{r.+}=1,AE=-1.4"
#export SetParametersExplicit="rneg=1,AE=-1.4"
#export SetParameterRanges="rgx{r.+}=0.5,2:AE=-20,20"
#export redefineSignalPOIs="AE,rneg"

export SetParametersExplicit="r_1=1,r_2=1"
export SetParameterRanges="r_1=0.0,3:r_2=0.0,3"
export redefineSignalPOIs="r_1,r_2"

#export ASIMOV="-t -1"
#export ASIMOV="-t 100 --saveToys"
export ASIMOV=""


###IMPACTS
echo
echo
echo "DO INITIAL FIT"
echo
echo
combine -M MultiDimFit --algo singles -d $WORKSPACE -n .part3E.snapshot -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace $ASIMOV
mv higgsCombine.part3E.snapshot.MultiDimFit.mH125.root higgsCombine_initialFit_Test.MultiDimFit.mH125.root


echo
echo
echo "DO FITS"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE --robustFit 1 --doFits -m 125 --redefineSignalPOIs $redefineSignalPOIs  --setParameters $SetParametersExplicit --setParameterRanges $SetParameterRanges --cminDefaultMinimizerStrategy 0 $ASIMOV --parallel 20


echo
echo
echo "CREATE IMPACTS JSON"
echo
echo
combineTool.py -M Impacts -d $WORKSPACE -o impacts.json -m 125 --redefineSignalPOIs $redefineSignalPOIs



echo
echo
echo "CREATE PLOTS"
echo
echo
for POI in ${POIS[@]}; do
  plotImpacts.py -i impacts.json -o $POI --POI $POI
done
echo
echo


mv higg*.root higgs_root
