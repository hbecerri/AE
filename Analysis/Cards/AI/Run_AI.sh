#!/bin/bash

rm -f *.root
rm -f *.json
#rm -f *.txt


text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:r_1[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_2[1,0,20]'  --PO map='.*/TTToSemiLeptonic_3:r_3[1,0,20]' --PO map='.*/TTToSemiLeptonic_4:r_4=expr;;r_4("24847/25590*@1*(100+@3)/(100-@3) + 25478.6284/25590*@2*(100+@3)/(100-@3) - 24847/25590*@0",r_1,r_2,r_3,IA[0.11,-5,5])' --PO verbose



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





 







