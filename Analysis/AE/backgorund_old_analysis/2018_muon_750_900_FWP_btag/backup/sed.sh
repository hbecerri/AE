#!/bin/bash

sed -i 's/Top_pT_rew_boosted/Top p_{t} (boosted)/g' *.json
sed -i 's/Top_pT_rew_semiresolved/Top p_{t} (semiresolved)/g' *.json
sed -i 's/Top_pT_rew_resolved/Top p_{t} (resolved)/g' *.json

sed -i 's/q2/#mu_{R} and #mu_{F}/g' *.json
sed -i 's/muonHLT/Lepton HLT/g' *.json
sed -i 's/HT/H_{T}\/nJets (btag)/g' *.json

sed -i 's/ttbar_rate/TTbar rate/g' *.json
sed -i 's/hdamp/H_{damp}/g' *.json
sed -i 's/lumi/Lumi/g' *.json
sed -i 's/wjets_rate/Bkg rate/g' *.json
sed -i 's/hf/hf (btag)/g' *.json
sed -i 's/misttag/MisTopTag/g' *.json
sed -i 's/muonID/Lepton ID/g' *.json


sed -i 's/lfstats2/lfstats2 (btag)/g' *.json
sed -i 's/lfstats1/lfstats1 (btag)/g' *.json
sed -i 's/toptag/TopTag/g' *.json
sed -i 's/muon_rec/Lepton Reco/g' *.json
sed -i 's/pdf/PDF/g' *.json
sed -i 's/hfstats2/hfstats2 (btag)/g' *.json
sed -i 's/hfstats1/hfstats1 (btag)/g' *.json
sed -i 's/cferr2/cferr2 (btag)/g' *.json
sed -i 's/cferr1/cferr1 (batg)/g' *.json
sed -i 's/pileup/Pileup/g' *.json

sed -i 's/jes (btag) (btag)/jes/g' *.json
sed -i 's/jes/jes (btag)/g' *.json

