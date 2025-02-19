from ROOT import *
import sys
import numpy
from array import array
import string

array_rec = [-2,0,2]
len_rec = len(array_rec) - 1

ct_top = 'weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew_nolimit*weight_btag*muonrecSF_nominal*0.9'

Mttbar_gen_energia = 'TMath::Power(GenParticles.m_energy[2] + GenParticles.m_energy[3],2)'
Mttbar_gen_p1 = 'TMath::Power(GenParticles.m_pt[2]*TMath::Cos(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Cos(GenParticles.m_phi[3]),2)'
Mttbar_gen_p2 = 'TMath::Power(GenParticles.m_pt[2]*TMath::Sin(GenParticles.m_phi[2]) + GenParticles.m_pt[3]*TMath::Sin(GenParticles.m_phi[3]),2)'
Mttbar_gen_p3 = 'TMath::Power(GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]) + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]),2)'

Mttbar_gen = 'TMath::Sqrt({e} - {p1} - {p2} - {p3})'.format(e=Mttbar_gen_energia,p1=Mttbar_gen_p1,p2=Mttbar_gen_p2,p3=Mttbar_gen_p3)

systematic_direction_ttbar={}

for i in range(1,100):
    pdfstring  = '*(wgtMC__PDF['+str(i)+'])'
    systematic_direction_ttbar['PDF_'+str(i)+'Up'] = ct_top+pdfstring
    systematic_direction_ttbar['PDF_'+str(i)+'Down'] = ct_top

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/"
samplelist = {
'ttbar_semi':'uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root',
}

categories=['T1']
fout = TFile('mu_Test_4cat_PDF_SR1T.root', 'recreate')

gROOT.SetBatch(kTRUE)
                               
for cat in categories:
    cut_string_GL='(Mttbar>750 & Mttbar<900 &'
    if cat == 'T1':
        cut_string = cut_string_GL+' rec_chi2<30  '
        a=0
        for key_sample in samplelist:
            if key_sample == 'QCD':
                continue
            myfile = TFile(inputdir+samplelist[key_sample])
            mytree = myfile.Get("AnalysisTree")
            mytree.SetAlias("invmass","DeltaY")
            if key_sample == 'DATA':
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat_PDF_SR1T.root:/SR1T/data_obs')
                cut = str(cut_string+' & ttagN<=%d & btagN>=1 & wtagN<=%d)'%(argv[1],argv[2]))
                print("--------------------------------------")
                print "Processing: ",key_sample
                print "Applying cut:",cut
                tempdata = TH1F("tempdata","tempdata",len_rec,array('d',array_rec))
                mytree.Draw("invmass>>tempdata",cut)
                tempdata.SetName(key_sample)
                tempdata.SetBinContent(1,tempdata.GetBinContent(0)+tempdata.GetBinContent(1))
                tempdata.SetBinContent(14,tempdata.GetBinContent(15)+tempdata.GetBinContent(14))
                gDirectory.WriteObject(tempdata,'nominal')
                del tempdata
#            elif 'ttbar' in key_sample:
            else:
                for syst in systematic_direction_ttbar:
                    cut = str(cut_string+' & ttagN<=%s & btagN>=1 & wtagN<=%s & %s > 0)*1.00*'%(sys.argv[1],sys.argv[2],sys.argv[3])+systematic_direction_ttbar[syst])
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    if syst == 'nominal':
                        temp = TH1F("temp","temp",len_rec,array('d',array_rec))
                        mytree.Draw("invmass>>temp",cut)
                        temp.SetName(syst)
                        temp.SetBinContent(1,temp.GetBinContent(0)+temp.GetBinContent(1))
                        temp.SetBinContent(2,temp.GetBinContent(2)+temp.GetBinContent(3))
                        print "Rebinning T1 nom:", str(temp.GetNbinsX())
                        gDirectory.WriteObject(temp,syst)
                        del temp
                    elif 'nominal' not in syst:
                        temp2sys = TH1F("temp2sys","temp2sys",len_rec,array('d',array_rec))
                        mytree.Draw("invmass>>temp2sys",cut)
                        temp2sys.SetName(syst)
                        temp2sys.SetBinContent(1,temp2sys.GetBinContent(0)+temp2sys.GetBinContent(1))
                        temp2sys.SetBinContent(2,temp2sys.GetBinContent(2)+temp2sys.GetBinContent(3))
                        gDirectory.cd('mu_Test_4cat_PDF_SR1T.root:/')
                        gDirectory.WriteObject(temp2sys,'Ttbar_2_'+syst)
                        del temp2sys


