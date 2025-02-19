#!/bin/bash

rm -f *.root
rm -f *.json
#rm -f *.txt

cp 2018_muon/script/muon_2018_750_900.txt .
cp 2018_muon_CR/script/muon_CR_2018_750_900.txt .

combineCards.py muon_2018_750_900=muon_2018_750_900.txt muon_CR_2018_750_900=muon_CR_2018_750_900.txt > AE_750.txt



text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:rneg[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_pos=expr;;r_pos("9650.5479/9594.2556*@0*(100+@1)/(100-@1)",rneg,AE[-0.29,-20,20])' --PO verbose 

#: <<'END_COMMENT'

#text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:r_1[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_2[1,0,20]' --PO verbose
 
#declare -a POIS=(
#
#  "r_1"
#  "r_2"
#)

declare -a POIS=(
  "rneg"
  "AE"
)

export WORKSPACE=AE_750.root
export VERBOSITY=0

export SetParameters="rgx{r.+}=1,AE=-0.29"
export SetParametersExplicit="rneg=1,AE=-0.229"
export SetParameterRanges="rgx{r.+}=0.,3:AE=-20,20"
export redefineSignalPOIs="AE,rneg"

#export SetParametersExplicit="r_1=1,r_2=1"
#export SetParameterRanges="r_1=0.5,2:r_2=0.5,2"
#export redefineSignalPOIs="r_1,r_2"

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


#END_COMMENT

#echo
echo
echo "Breakdown"
echo
echo

combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .snapshot $ASIMOV
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .nominal $ASIMOV --snapshotName MultiDimFit
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .freezeall $ASIMOV --snapshotName MultiDimFit --freezeParameters allConstrainedNuisances


mv *.* results
mv results/*.txt .
mv results/*.sh .

 







