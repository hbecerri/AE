import array
import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np

proc = ['Ttbar', 'data_obs', 'singletop', 'wjets', 'dy', 'qcd', 'ttbar_others']
fout = R.TFile(argv[1]+'.root', 'recreate')
#fout.mkdir(argv[5])
fout.mkdir(argv[1])

fin = R.TFile('DeltaY.root')
fin.cd(argv[5])
dir = R.gDirectory.GetListOfKeys()            
for key_dir in dir:
    dir_name = key_dir.GetName()
    if (dir_name[0:9] == 'Migration'):
        continue
    fin.cd(argv[5]+'/'+dir_name)
    dir2 = R.gDirectory.GetListOfKeys()
    for variable in dir2:
        tempdata = TH1F("tempdata","tempdata",1,int(argv[2]),int(argv[3])) 
        name = variable.GetName()
#        print(name)
        temp = fin.Get(argv[5]+'/'+dir_name+'/'+name).Clone()
        tempdata.SetBinContent(1,temp.GetBinContent(int(argv[4])))
        fout.cd(argv[1])
        R.gDirectory.WriteObject(tempdata,dir_name+'_'+name)
        del temp
        del tempdata

