import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np

syst=['hdamp','top_pt_rew','pileup','eleID','eleHLT','toptag_corr','toptag_uncorr','FSR', 'ISR', 'MuR', 'MuF','btag_HF_corr','btag_LF_corr','btag_HF_unc18','btag_LF_unc18','PDF1','PDF2']#,'PDF3','PDF4','PDF5','PDF6','PDF7','PDF8','PDF9','PDF10','PDF11','PDF12','PDF13','PDF14','PDF15','PDF16','PDF17','PDF18','PDF19','PDF20','PDF21','PDF22','PDF23','PDF24','PDF25','PDF26','PDF27','PDF28','PDF29','PDF30','PDF31','PDF32','PDF33','PDF34','PDF35','PDF36','PDF37','PDF38','PDF39','PDF40','PDF41','PDF42','PDF43','PDF44','PDF45','PDF46','PDF47','PDF48','PDF49','PDF50','PDF51','PDF52','PDF53','PDF54','PDF55','PDF56','PDF57','PDF58','PDF59','PDF60','PDF61','PDF62','PDF63','PDF64','PDF65','PDF66','PDF67','PDF68','PDF69','PDF70','PDF71','PDF72','PDF73','PDF74','PDF75','PDF76','PDF77','PDF78','PDF79','PDF80','PDF81','PDF82','PDF83','PDF84','PDF85','PDF86','PDF87','PDF88','PDF89','PDF90','PDF91','PDF92','PDF93','PDF94','PDF95','PDF96','PDF97','PDF98','PDF99']
 
proc=["TTToSemiLeptonic_1","TTToSemiLeptonic_2","TTToSemiLeptonic_3","TTToSemiLeptonic_4","diboson", "dyjetstoll_m-50_ht", "qcd_ht", "st","wjetstolnu"]

proc.sort()
proc = list(dict.fromkeys(proc))
proc.sort()

fin = R.TFile('Input_undfolding_data_.root')
N_reco_bins = 0
datacard=open("electron_2018_500_700.txt","w")
datacard.write("1 imax\n")
datacard.write("* jmax\n")
datacard.write("* kmax\n")

datacard.write("----------------\n")

datacard.write("shapes data_obs  *  /nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AI/theta/2018_electron/2018_electron_500_700/script/Input_undfolding_data_.root $PROCESS\n")
datacard.write("shapes *         *  /nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AI/theta/2018_electron/2018_electron_500_700/script/Input_undfolding_data_.root $PROCESS_nominal $PROCESS_$SYSTEMATIC\n")

datacard.write("----------------\n")

datacard.write("bin electron_2018_500_700")
datacard.write("\n")
datacard.write("observation -1")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write("bin ")
for ireco in range(1,len(proc)+1):
    datacard.write("electron_2018_500_700 ")
datacard.write("\n")
datacard.write("process ")
datacard.write("TTToSemiLeptonic_1 ")
datacard.write("TTToSemiLeptonic_2 ")
datacard.write("TTToSemiLeptonic_3 ")
datacard.write("TTToSemiLeptonic_4 ")
datacard.write("diboson ")
datacard.write("dyjetstoll_m-50_ht ")
datacard.write("qcd_ht ")
datacard.write("st ")
datacard.write("wjetstolnu ")

datacard.write("\n")
datacard.write("process ")
for ireco in range(-3,6):
    datacard.write("%d "%ireco) 
datacard.write("\n")
datacard.write("rate ")
for ireco in range(-3,6):
    datacard.write("-1 ")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write('luminosity_2018 lnN ')
for xx in range(len(proc)):
    datacard.write('1.015 ')
datacard.write("\n")
datacard.write('luminosity_1718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.002 ')
datacard.write("\n")
datacard.write('luminosity_161718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.02 ')

datacard.write("\n")
datacard.write('dR_electron_18 lnN ')
for xx in range(len(proc)):
    datacard.write('1.05 ')

datacard.write("\n")
for name in proc:
    if('TTToSemiLeptonic' in name):
        continue
    datacard.write('xsec_%s lnN '%name)
    for name2 in proc:
        if(name2 == name != -1):
            if(name2.find('Ttbar') != -1):
                datacard.write('1.05 ')
            else:
                datacard.write('1.30 ')
        else:
            datacard.write('- ')
    datacard.write("\n")
datacard.write("---------------------------------------------------\n")
datacard.write("xsec_ttbar lnN 1.05 1.05 1.05 1.05 - - - - -")
datacard.write("\n")


for name in syst:
    datacard.write('%s shape '%name)
    for name2 in proc:
        fin.cd('')
        dir2 = R.gDirectory.GetListOfKeys()
        existe = '- '
        for element in dir2:
            el = element.GetName() 
            if("iboso" in name2 and "PDF" in name): continue
            if(el.find(name2+'_'+name+'Up') != -1):
                existe = '1 '
        if('TTToSemiLeptonic' not in name2 and 'PDF' in name): existe = '- '
        datacard.write(existe)      
    datacard.write("\n")
datacard.write('* autoMCStats 1 1')
datacard.write("\n")





