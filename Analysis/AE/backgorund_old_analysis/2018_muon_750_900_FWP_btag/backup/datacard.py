import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np

fin = R.TFile('bin1_boosted.root')
N_reco_bins = 0
datacard=open("bin1_boosted.txt","w")
datacard.write("1 imax\n")
datacard.write("* jmax\n")
datacard.write("* kmax\n")
datacard.write("----------------\n")
datacard.write("bin ")
dir = R.gDirectory.GetListOfKeys()
dir_name = ""
for key_dir in dir:
    dir_name = key_dir.GetName()
    datacard.write("%s "%dir_name)
datacard.write("\n")
datacard.write("observation ")
temp = fin.Get('bin1_boosted/data_obs_nominal').Clone()
datacard.write("%d "%(temp.GetBinContent(1)))
datacard.write("\n")
datacard.write("----------------\n")
datacard.write("bin ")
for ireco in range(1,8):
    datacard.write("%s "%dir_name)
datacard.write("\n")
datacard.write("process ")
datacard.write("Gen_1 ")
datacard.write("Gen_2 ")
datacard.write("qcd ")
datacard.write("singletop ")
datacard.write("wjets ")
datacard.write("dy ")
datacard.write("ttbar_others ")
datacard.write("\n")
datacard.write("process ")
for ireco in range(-1,6):
    datacard.write("%d "%ireco) 
datacard.write("\n")
datacard.write("rate ")
for ireco in range(-1,6):
    datacard.write("-1 ")
datacard.write("\n")
datacard.write("----------------\n")


'''
datacard.write("\n")
datacard.write("process ")
for ireco in range(1,hReco.GetNbinsX()+1):
for igen in range(1,hGen.GetNbinsX()+1):
if cleanup and hResp.GetBinContent(ireco,igen)<0.01: continue
datacard.write("Gen_%d "%igen) ##sig igen, in reco ireco
datacard.write("Bkg ")## bkg
datacard.write("\n")
'''
