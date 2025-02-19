from array import array
from ROOT import *
import sys
from sys import *
import numpy

Bin = [-1000.,0.,1000.]
nb = len(Bin)-1
ct = 'eventweight'
systematic_direction_otherbkgs={
                            'nominal':'eventweight',
                            'pileupUp':'eventweight*weight_pu_up/weight_pu',
                            'pileupDown':'eventweight*weight_pu_down/weight_pu',
                            'muIDUp':'eventweight*weight_sfmu_id_up/weight_sfmu_id',
                            'muIDDown':'eventweight*weight_sfmu_id_down/weight_sfmu_id',
                            'muHLTUp':'eventweight*weight_sfmu_trigger_up/weight_sfmu_trigger',
                            'muHLTDown':'eventweight*weight_sfmu_trigger_up/weight_sfmu_trigger',
                            'toptag_corrUp':'eventweight*weight_toptagsf_corr_up/weight_toptagsf',
                            'toptag_corrDown':'eventweight*weight_toptagsf_corr_down/weight_toptagsf',
                            'muon_recUp':'eventweight*weight_sfmu_reco_up/weight_sfmu_reco',
                            'muon_recDown':'eventweight*weight_sfmu_reco_down/weight_sfmu_reco',
                            'btag_cferr1Up':'eventweight*weight_btagdisc__cferr1_up/weight_btagdisc__central',
                            'btag_cferr1Down':'eventweight*weight_btagdisc__cferr1_down/weight_btagdisc__central',
                            'btag_cferr2Up':'eventweight*weight_btagdisc__cferr2_up/weight_btagdisc__central',
                            'btag_cferr2Down':'eventweight*weight_btagdisc__cferr2_down/weight_btagdisc__central',
                            'btag_hfUp':'eventweight*weight_btagdisc__hf_up/weight_btagdisc__central',
                            'btag_hfDown':'eventweight*weight_btagdisc__hf_down/weight_btagdisc__central',
                            'btag_hfstats1Up':'eventweight*weight_btagdisc__hfstats1_up/weight_btagdisc__central',
                            'btag_hfstats1Down':'eventweight*weight_btagdisc__hfstats1_down/weight_btagdisc__central',
                            'btag_hfstats2Up':'eventweight*weight_btagdisc__hfstats1_up/weight_btagdisc__central',
                            'btag_hfstats2Down':'eventweight*weight_btagdisc__hfstats1_down/weight_btagdisc__central',
                            'btag_lfUp':'eventweight*weight_btagdisc__lf_up/weight_btagdisc__central',
                            'btag_lfDown':'eventweight*weight_btagdisc__lf_down/weight_btagdisc__central',
                            'btag_lfstats1Up':'eventweight*weight_btagdisc__lfstats1_up/weight_btagdisc__central',
                            'btag_lfstats1Down':'eventweight*weight_btagdisc__lfstats1_down/weight_btagdisc__central',
                            'btag_lfstats2Up':'eventweight*weight_btagdisc__lfstats2_up/weight_btagdisc__central',
                            'btag_lfstats2Down':'eventweight*weight_btagdisc__lfstats2_down/weight_btagdisc__central',
                            'ISRUp':'eventweight*weight_isr_2_up',
                            'ISRDown':'eventweight*weight_isr_2_down',
                            'FSRUp':'eventweight*weight_fsr_2_up',
                            'FSRDown':'eventweight*weight_fsr_2_down',
}


jecdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_JECdown/"
jecupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_JECup/"
jerupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_JERup/"
jerdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/workdir_Zprime_Analysis_2018_muon_CHS_JERdown/"
hdampupdir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/hdamp_up/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampup_2018v3.root"
hdampdowndir = "/nfs/dust/cms/user/hugobg/ZPrime_102X/analysis_output/2018_CHS/muon/hdamp_down/uhh2.AnalysisModuleRunner.MC.TTToSemileptonic_hdampdown_2018v3.root"
 

inputdir = "/nfs/dust/cms/user/hugobg/analysis/muon/"
samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2018.root',
'singletop':'uhh2.AnalysisModuleRunner.MC.ST_2018.root',
'qcd':'uhh2.AnalysisModuleRunner.MC.QCD_HT_2018.root',
'dy':'uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT_2018.root',
'wjets':'uhh2.AnalysisModuleRunner.MC.WJetsToLNu_2018.root',
}

categories=['T1']
fout = TFile(argv[1]+'_muon.root', 'recreate')

gROOT.SetBatch(kTRUE)

for cat in categories:
    if cat == 'T1':
            a=0
            for key_sample in samplelist:
                myfile = TFile(inputdir+samplelist[key_sample])
                mytree = myfile.Get("AnalysisTree")
                mytree.SetAlias("invmass",argv[1])
                gDirectory.cd(argv[1]+'_muon.root:/')
                if key_sample == 'DATA':
                    gDirectory.cd(argv[1]+'_muon.root:/')
                    cut = str('(DeepttagN<=1 & btagN>=1 & M_tt>500 & chi2 < 30)')
                    print("--------------------------------------")
                    print "Processing: ",key_sample
                    print "Applying cut:",cut
                    tempdata = TH1F("tempdata","tempdata",nb,array('d',Bin))
                    mytree.Draw("invmass>>tempdata",cut)
                    tempdata.SetName(key_sample)
                    gDirectory.WriteObject(tempdata,'data_obs')
                    del tempdata
                elif 'singletop' in key_sample or 'wjets' in key_sample or 'dy' in key_sample or 'qcd' in key_sample:
                    for syst in systematic_direction_otherbkgs:
                        cut = str('(DeepttagN<=1 & btagN>=1 & M_tt>500 & chi2 < 30)*'+systematic_direction_otherbkgs[syst])
                        print("--------------------------------------")
                        print "Processing: ",key_sample
                        print "Applying cut:",cut
                        if syst=='jecUp' or syst=='jecDown' or syst=='jerUp' or syst=='jerDown':
                            if syst=='jecUp':
                                je_file = TFile(jecupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jecDown':
                                je_file = TFile(jecdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerUp':
                                je_file = TFile(jerupdir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            if syst=='jerDown':
                                je_file = TFile(jerdowndir+samplelist[key_sample])
                                je_tree = je_file.Get("AnalysisTree")
                            gDirectory.cd('_muon.root:/')
                            je_tree.SetAlias("invmass",argv[1])
                            tempsys = TH1F("tempsys","tempsys",nb,array('d',Bin))
                            je_tree.Draw("invmass>>tempsys",cut)
                            tempsys.SetName(syst)
                            gDirectory.WriteObject(tempsys,key_sample+'_'+syst)
                            del tempsys
                        else:
                            temp2sys = TH1F("temp2sys","temp2sys",nb,array('d',Bin))
                            mytree.Draw("invmass>>temp2sys",cut)
                            temp2sys.SetName(syst)
                            gDirectory.WriteObject(temp2sys,key_sample+'_'+syst)
                            del temp2sys
