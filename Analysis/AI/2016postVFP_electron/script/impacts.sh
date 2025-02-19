#!/usr/bin/env bash
date

#text2workspace.py electron_2016postVFP_750_900.txt -o electron_2016postVFP_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:r_1[1,0,20]' --PO map='.*/Ttbar_in_2:r_2[1,0,20]'  --PO map='.*/Ttbar_in_3:r_3[1,0,20]' --PO map='.*/Ttbar_in_4:r_4[1,0,20]' --PO verbose

text2workspace.py electron_2016postVFP_750_900.txt -o electron_2016postVFP_750_900.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/Ttbar_in_1:r_1[1,0,20]' --PO map='.*/Ttbar_in_2:r_2[1,0,20]'  --PO map='.*/Ttbar_in_3:r_3[1,0,20]' --PO map='.*/Ttbar_in_4:r_4=expr;;r_4("-5541/5893*@0 + 6770/5893*@1*(100+@3)/(100-@3) + 5894/5893*@2*(100+@3)/(100-@3)",r_1,r_2,r_3,IA[-.1,-20,20])'    --PO verbose


#declare -a POIS=(
#  "r_1"
#  "r_2"
#  "r_3"
#  "r_4"
#) 

declare -a POIS=(
  "r_1"
  "r_2"
  "r_3"
  "IA"
) 

export WORKSPACE=electron_2016postVFP_750_900.root
export VERBOSITY=0

export SetParameters="rgx{r.+}=1,IA=-5.1"
export SetParametersExplicit="r_1=1,r_2=1,r_3=1,IA=-.1"
export SetParameterRanges="rgx{r.+}=0.5,2:IA=-20,20"
export redefineSignalPOIs="IA,r_1,r_2,r_3"
 
#export SetParametersExplicit="r_1=1,r_2=1,r_3=1,r_4=1"
#export SetParameterRanges="r_1=0.,5:r_2=0.,5:r_3=0.,5:r_4=0.,5"
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



#echo
#echo
#echo "STAT ONLY UNCERTAINTY (ALL NUISANCES FROZEN)"
#echo
#echo
#combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n _paramFit_Test_allConstrainedNuisancesFrozen --freezeParameters allConstrainedNuisances $ASIMOV



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

combine -M MultiDimFit --algo singles -d $WORKSPACE -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .snapshot $ASIMOV
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .nominal $ASIMOV --snapshotName MultiDimFit
combine -M MultiDimFit higgsCombine.snapshot.MultiDimFit.mH125.root --algo singles -v $VERBOSITY --redefineSignalPOIs $redefineSignalPOIs --setParameterRanges $SetParameterRanges --setParameters $SetParametersExplicit --robustFit 1 --cminDefaultMinimizerStrategy 0 -m 125 --saveWorkspace -n .freezeall $ASIMOV --snapshotName MultiDimFit --freezeParameters allConstrainedNuisances
