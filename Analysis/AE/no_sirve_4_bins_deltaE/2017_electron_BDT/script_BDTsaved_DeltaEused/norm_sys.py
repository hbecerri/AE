from array import array
from ROOT import *
import ROOT as R
import sys
from sys import *
import numpy

samplelist = {
'other':'Input_undfolding_data_all.root',
}

fout = R.TFile('Input_undfolding_data_all_2.root', 'recreate')

for key_sample in samplelist:
    fin = R.TFile(samplelist[key_sample])
    dir = R.gDirectory.GetListOfKeys()
    for key_dir in dir:
        name = key_dir.GetName()
        temp = fin.Get(name)
        if(temp.Integral() <=0): continue
        if('Up' in name or 'Down' in name):
            if('MuR' in name or 'MuF' in name or 'ISR' in name or 'FSR' in name or 'PDF' in name or 'hdamp' in name): 
                if('TTToSemiLeptonic_1' in name): temp2 = fin.Get('TTToSemiLeptonic_1_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('TTToSemiLeptonic_2' in name): temp2 = fin.Get('TTToSemiLeptonic_2_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('tttosemileptonic_outfiducial' in name): temp2 = fin.Get('tttosemileptonic_outfiducial_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('wjetstolnu' in name): temp2 = fin.Get('wjetstolnu_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('st' in name): temp2 = fin.Get('st_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('dyjetstoll_m-50_ht' in name): temp2 = fin.Get('dyjetstoll_m-50_ht_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('qcd_ht' in name): temp2 = fin.Get('qcd_ht_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
           	if('diboson' in name): temp2 = fin.Get('diboson_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
           	if('ttto2l2nu' in name): temp2 = fin.Get('ttto2l2nu_nominal'); temp.Scale(temp2.Integral()/temp.Integral())
            	if('tttohadronic' in name): temp2 = fin.Get('tttohadronic_nominal'); temp.Scale(temp2.Integral()/temp.Integral()) 
        fout.cd('') 
        R.gDirectory.WriteObject(temp,name)
        del temp




