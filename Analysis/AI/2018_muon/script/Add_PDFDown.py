from array import array
from ROOT import *
import ROOT as R
import sys
from sys import *
import numpy

samplelist = {
'other':'.root',
}

fout = R.TFile('vjj_combine_2018.root', 'recreate')
fin = R.TFile('vjj_2018.root')

for key_sample in samplelist:
    fin = R.TFile(samplelist[key_sample])
    dir = R.gDirectory.GetListOfKeys()
    for key_dir in dir:
        name = key_dir.GetName()
        if('G1' in name): continue
        if('fake' in name): continue
        temp = fin.Get(name)
        fout.cd('')
        R.gDirectory.WriteObject(temp,name)
        del temp


