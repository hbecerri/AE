import ROOT as R
from ROOT import *
import sys
from sys import argv
import numpy as np


syst=['JEC','JER','hdamp','L1Prefiring17','top_pt_rew','pileup','eleID','eleHLT','toptag_corr','toptag_uncorr','FSR', 'ISR', 'MuR', 'MuF','MuR_MuF','btag_HF_corr','btag_LF_corr','btag_HF_unc16','btag_LF_unc16','BBEC1_2016preVFP','EC2_2016preVFP','RelativeSample_2016preVFP','Absolute_2016preVFP','HF','EC2','Absolute','RelativeBal','LHEPdfWeight_1','LHEPdfWeight_2','LHEPdfWeight_3','LHEPdfWeight_4','LHEPdfWeight_5','LHEPdfWeight_6','LHEPdfWeight_7','LHEPdfWeight_8','LHEPdfWeight_9','LHEPdfWeight_10','LHEPdfWeight_11','LHEPdfWeight_12','LHEPdfWeight_13','LHEPdfWeight_14','LHEPdfWeight_15','LHEPdfWeight_16','LHEPdfWeight_17','LHEPdfWeight_18','LHEPdfWeight_19','LHEPdfWeight_20','LHEPdfWeight_21','LHEPdfWeight_22','LHEPdfWeight_23','LHEPdfWeight_24','LHEPdfWeight_25','LHEPdfWeight_26','LHEPdfWeight_27','LHEPdfWeight_28','LHEPdfWeight_29','LHEPdfWeight_30','LHEPdfWeight_31','LHEPdfWeight_32','LHEPdfWeight_33','LHEPdfWeight_34','LHEPdfWeight_35','LHEPdfWeight_36','LHEPdfWeight_37','LHEPdfWeight_38','LHEPdfWeight_39','LHEPdfWeight_40','LHEPdfWeight_41','LHEPdfWeight_42','LHEPdfWeight_43','LHEPdfWeight_44','LHEPdfWeight_45','LHEPdfWeight_46','LHEPdfWeight_47','LHEPdfWeight_48','LHEPdfWeight_49','LHEPdfWeight_50','LHEPdfWeight_51','LHEPdfWeight_52','LHEPdfWeight_53','LHEPdfWeight_54','LHEPdfWeight_55','LHEPdfWeight_56','LHEPdfWeight_57','LHEPdfWeight_58','LHEPdfWeight_59','LHEPdfWeight_60','LHEPdfWeight_61','LHEPdfWeight_62','LHEPdfWeight_63','LHEPdfWeight_64','LHEPdfWeight_65','LHEPdfWeight_66','LHEPdfWeight_67','LHEPdfWeight_68','LHEPdfWeight_69','LHEPdfWeight_70','LHEPdfWeight_71','LHEPdfWeight_72','LHEPdfWeight_73','LHEPdfWeight_74','LHEPdfWeight_75','LHEPdfWeight_76','LHEPdfWeight_77','LHEPdfWeight_78','LHEPdfWeight_79','LHEPdfWeight_80','LHEPdfWeight_81','LHEPdfWeight_82','LHEPdfWeight_83','LHEPdfWeight_84','LHEPdfWeight_85','LHEPdfWeight_86','LHEPdfWeight_87','LHEPdfWeight_88','LHEPdfWeight_89','LHEPdfWeight_90','LHEPdfWeight_91','LHEPdfWeight_92','LHEPdfWeight_93','LHEPdfWeight_94','LHEPdfWeight_95','LHEPdfWeight_96','LHEPdfWeight_97','LHEPdfWeight_98','LHEPdfWeight_99']
 
proc=["Ttbar_in_1","Ttbar_in_2","wjets", "st",  "dy", "qcd", "diboson", "ttbar_out","ttbar_ll","ttbar_had"]

proc.sort()
proc = list(dict.fromkeys(proc))
proc.sort()

fin = R.TFile('Input_undfolding_data.root')
N_reco_bins = 0
datacard=open("electron_2016preVFP_750_900.txt","w")
datacard.write("1 imax\n")
datacard.write("* jmax\n")
datacard.write("* kmax\n")

datacard.write("----------------\n")

datacard.write("shapes data_obs  *  /nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AE/2016preVFP_electron_BDT/script/Input_undfolding_data.root $PROCESS\n")
datacard.write("shapes *         *  /nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AE/2016preVFP_electron_BDT/script/Input_undfolding_data.root $PROCESS_nominal $PROCESS_$SYSTEMATIC\n")

datacard.write("----------------\n")

datacard.write("bin electron_2016preVFP_750_900")
datacard.write("\n")
datacard.write("observation -1")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write("bin ")
for ireco in range(1,len(proc)+1):
    datacard.write("electron_2016preVFP_750_900 ")
datacard.write("\n")
datacard.write("process ")
datacard.write("Ttbar_in_1 ")
datacard.write("Ttbar_in_2 ")
datacard.write("diboson ")
datacard.write("dy ")
datacard.write("qcd ")
datacard.write("st ")
datacard.write("ttbar_ll ")
datacard.write("ttbar_had ")
datacard.write("ttbar_out ")
datacard.write("wjets ")

datacard.write("\n")
datacard.write("process ")
for ireco in range(-1,len(proc)-1):
    datacard.write("%d "%ireco) 
datacard.write("\n")
datacard.write("rate ")
for ireco in range(-1,len(proc)-1):
    datacard.write("-1 ")
datacard.write("\n")
datacard.write("----------------\n")

datacard.write('luminosity_2016 lnN ')
for xx in range(len(proc)):
    datacard.write('1.01 ')
datacard.write("\n")
datacard.write('luminosity_161718 lnN ')
for xx in range(len(proc)):
    datacard.write('1.006 ')


datacard.write("\n")
for name in proc:
    if('Ttbar_in' in name):
        continue
    datacard.write('xsec_%s lnN '%name)
    for name2 in proc:
        if(name2 == name != -1):
            if(name2.find('ttbar') != -1):
                datacard.write('1.05 ')
            else:
                datacard.write('1.30 ')
        else:
            datacard.write('- ')
    datacard.write("\n")

datacard.write("xsec_ttbar lnN 1.05 1.05 - - - - - - - - -")
datacard.write("\n")

datacard.write("---------------------------------------------------\n")



for name in syst:
    datacard.write('%s shape '%name)
    for name2 in proc:
        fin.cd('')
        dir2 = R.gDirectory.GetListOfKeys()
        existe = '- '
        for element in dir2:
            el = element.GetName() 
            if(el.find(name2+'_'+name+'Up') != -1):
                existe = '1 '
        if('TTToSemiLeptonic' not in name2 and 'PDF' in name): existe = '- '
        datacard.write(existe)      
    datacard.write("\n")
datacard.write('* autoMCStats 1 1')
datacard.write("\n")





