#!/bin/bash

rm -f *.root
rm -f *.json
rm -f *.txt

cp 2018_muon/2018_muon_500_700/script/muon_2018_500_700.txt .
cp 2018_muon/2018_muon_700_900/script/muon_2018_700_900.txt . 
cp 2018_muon/2018_muon_900_Inf/script/muon_2018_900_Inf.txt .
 
cp 2017_muon/2017_muon_500_700/script/muon_2017_500_700.txt .
cp 2017_muon/2017_muon_700_900/script/muon_2017_700_900.txt .
cp 2017_muon/2017_muon_900_Inf/script/muon_2017_900_Inf.txt .
 
cp 2016preVFP_muon/2016preVFP_muon_500_700/script/muon_2016_500_700.txt .
cp 2016preVFP_muon/2016preVFP_muon_700_900/script/muon_2016_700_900.txt .
cp 2016preVFP_muon/2016preVFP_muon_900_Inf/script/muon_2016_900_Inf.txt . 
 
cp 2016postVFP_muon/2016postVFP_muon_500_700/script/muon_2016postVFP_500_700.txt .
cp 2016postVFP_muon/2016postVFP_muon_700_900/script/muon_2016postVFP_700_900.txt .
cp 2016postVFP_muon/2016postVFP_muon_900_Inf/script/muon_2016postVFP_900_Inf.txt .
  
cp 2018_electron/2018_electron_500_700/script/electron_2018_500_700.txt .
cp 2018_electron/2018_electron_700_900/script/electron_2018_700_900.txt . 
cp 2018_electron/2018_electron_900_Inf/script/electron_2018_900_Inf.txt .
 
cp 2017_electron/2017_electron_500_700/script/electron_2017_500_700.txt .
cp 2017_electron/2017_electron_700_900/script/electron_2017_700_900.txt .
cp 2017_electron/2017_electron_900_Inf/script/electron_2017_900_Inf.txt . 
 
cp 2016preVFP_electron/2016preVFP_electron_500_700/script/electron_2016_500_700.txt .
cp 2016preVFP_electron/2016preVFP_electron_700_900/script/electron_2016_700_900.txt .
cp 2016preVFP_electron/2016preVFP_electron_900_Inf/script/electron_2016_900_Inf.txt .

cp 2016postVFP_electron/2016postVFP_electron_500_700/script/electron_2016postVFP_500_700.txt .
cp 2016postVFP_electron/2016postVFP_electron_700_900/script/electron_2016postVFP_700_900.txt .
cp 2016postVFP_electron/2016postVFP_electron_900_Inf/script/electron_2016postVFP_900_Inf.txt .
 
combineCards.py muon_2018_500_700=muon_2018_500_700.txt muon_2018_700_900=muon_2018_700_900.txt muon_2018_900_Inf=muon_2018_900_Inf.txt muon_2017_500_700=muon_2017_500_700.txt muon_2017_700_900=muon_2017_700_900.txt muon_2017_900_Inf=muon_2017_900_Inf.txt muon_2016postVFP_500_700=muon_2016postVFP_500_700.txt muon_2016postVFP_700_900=muon_2016postVFP_700_900.txt muon_2016postVFP_900_Inf=muon_2016postVFP_900_Inf.txt muon_2016_500_700=muon_2016_500_700.txt muon_2016_700_900=muon_2016_700_900.txt muon_2016_900_Inf=muon_2016_900_Inf.txt electron_2018_500_700=electron_2018_500_700.txt electron_2018_700_900=electron_2018_700_900.txt electron_2018_900_Inf=electron_2018_900_Inf.txt electron_2017_500_700=electron_2017_500_700.txt electron_2017_700_900=electron_2017_700_900.txt electron_2017_900_Inf=electron_2017_900_Inf.txt electron_2016postVFP_500_700=electron_2016postVFP_500_700.txt electron_2016postVFP_700_900=electron_2016postVFP_700_900.txt electron_2016postVFP_900_Inf=electron_2016postVFP_900_Inf.txt electron_2016_500_700=electron_2016_500_700.txt electron_2016_700_900=electron_2016_700_900.txt electron_2016_900_Inf=electron_2016_900_Inf.txt > AE_inclusive.txt 


#text2workspace.py AE_750.txt -o AE_750.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:rneg[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_pos=expr;;r_pos("114961/115076*@0*(100+@1)/(100-@1)",rneg,AE[0.05,-3,3])' --PO verbose 

text2workspace.py AE_inclusive.txt -o AE_inclusive.root  -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel -m 125 --PO map='.*/TTToSemiLeptonic_1:r_1[1,0,20]' --PO map='.*/TTToSemiLeptonic_2:r_2[1,0,20]' --PO verbose
 
declare -a POIS=(
  "r_1"
  "r_2"
)

#declare -a POIS=(
#  "rneg"
#  "AE"
#)

export WORKSPACE=AE_inclusive.root
export VERBOSITY=0

#export SetParameters="rgx{r.+}=1,AE=0.05"
#export SetParametersExplicit="rneg=1,AE=0.05"
#export SetParameterRanges="rgx{r.+}=0.5,2:AE=-10,5"
#export redefineSignalPOIs="AE,rneg"

export SetParametersExplicit="r_1=1,r_2=1"
export SetParameterRanges="r_1=0.5,2:r_2=0.5,2"
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


mv *.* results
mv results/AE_mttbar.sh .


 







