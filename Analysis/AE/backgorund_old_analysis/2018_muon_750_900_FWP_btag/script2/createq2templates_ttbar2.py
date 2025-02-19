from ROOT import *
import sys
import numpy
from array import array
import string

array_rec = [-2,0,2]
len_rec = len(array_rec) - 1

#ct_top = '(weight)*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)'
#ct_top = 'weight*(weight_sfmu_HighPtID)*(weight_pu)*(weight_sfmu_Trigger)*(weight_toptagSF_)*(weight_pt_rew_nolimit)*(weight_btagdisc_central)*(muonrecSF_nominal)*(weight_HT_HT)'
ct_top = 'weight*weight_sfmu_HighPtID*weight_sfmu_Trigger*weight_pu*weight_toptagSF_*weight_pt_rew*weight_btagdisc_central*muonrecSF_nominal*(weight_HT_HT)'
 
systematic_direction_ttbar={'nominal':ct_top,
                            'q2ttbarMuRdnMuFdn__plus':ct_top+'*(weight_murmuf_downdown)',
                            'q2ttbarMuRupMuFup__plus':ct_top+'*(weight_murmuf_upup)',
                            'q2ttbarMuRdnMuFct__plus':ct_top+'*(weight_murmuf_downnone)',
                            'q2ttbarMuRupMuFct__plus':ct_top+'*(weight_murmuf_upnone)',
                            'q2ttbarMuRctMuFdn__plus':ct_top+'*(weight_murmuf_nonedown)',
                            'q2ttbarMuRctMuFup__plus':ct_top+'*(weight_murmuf_noneup)'
                           }

inputdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/"
samplelist = {
'ttbar_semi':'uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_2018.root',
}

categories=['T1']
fout = TFile('mu_Test_4cat_q2_SR1T.root', 'recreate')

fout.mkdir("SR1T/ttbar_semi")

gROOT.SetBatch(kTRUE)
                               
for cat in categories:
    cut_string_GL='(Mttbar>900 &'
    if cat == 'T1':
        cut_string = cut_string_GL+' rec_chi2<30  '
        a=0
        for key_sample in samplelist:
            if key_sample == 'QCD':
                continue
            myfile = TFile(inputdir+samplelist[key_sample])
            mytree = myfile.Get("AnalysisTree")
            mytree.SetAlias("invmass","DeltaY")
            gDirectory.cd('mu_Test_4cat_q2_SR1T.root:/SR1T/'+key_sample)
            if key_sample == 'DATA':
                gDirectory.cd('/afs/desy.de/user/h/hugobg/public/theta/CMSSW_8_0_24/src/Combine_Limits/muon_mle/mu_Test_4cat_q2_SR1T.root:/SR1T/data_obs')
                cut = str(cut_string+' & ttagN==1 & btagN>=0)')
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
            else:
#            elif 'ttbar' in key_sample:
                for syst in systematic_direction_ttbar:
                    cut = str(cut_string+' & ttagN<=%s & btagN>=1 & wtagN<=%s & %s >= 0)*1.00*'%(sys.argv[1],sys.argv[2],sys.argv[3])+systematic_direction_ttbar[syst])
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
                        gDirectory.WriteObject(temp2sys,syst)
                        del temp2sys
