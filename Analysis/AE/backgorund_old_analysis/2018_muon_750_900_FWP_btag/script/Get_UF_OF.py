from array import array
from ROOT import *
import ROOT as R
import sys
from sys import *
import numpy

samplelist = {
'other':argv[1]+'_muon_3cat.root',
}

fout = R.TFile(argv[1]+'_muon.root', 'recreate')

for key_sample in samplelist:
    fin = R.TFile(samplelist[key_sample])
    dir = R.gDirectory.GetListOfKeys()
    for key_dir in dir:
        name = key_dir.GetName()
        temp = fin.Get(name)
        nb = temp.GetNbinsX()
        temp.SetBinContent(1,temp.GetBinContent(0)+temp.GetBinContent(1)) 		
        temp.SetBinContent(nb,temp.GetBinContent(nb)+temp.GetBinContent(nb+1))                        
        fout.cd('')
        R.gDirectory.WriteObject(temp,name)
        del temp








