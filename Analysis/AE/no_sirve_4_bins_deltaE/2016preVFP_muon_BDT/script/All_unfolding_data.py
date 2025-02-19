from array import array
from ROOT import *
import sys
from sys import *
import numpy

systematic_direction_ttbar_in={
            'nominal':'eventweight',
            'pileupUp':'eventweight*weight_pu_up/weight_pu', 'pileupDown':'eventweight*weight_pu_down/weight_pu',
            'muIDUp':'eventweight*weight_sfmu_id_up/weight_sfmu_id'                   ,  'muIDDown':'eventweight*weight_sfmu_id_down/weight_sfmu_id',
            'muHLTUp':'eventweight*weight_sfmu_iso_up/weight_sfmu_iso'                ,  'muISODown':'eventweight*weight_sfmu_iso_down/weight_sfmu_iso',
            'muHLTU':'eventweight*weight_sfmu_trigger_up/weight_sfmu_trigger'         ,  'muHLTDown':'eventweight*weight_sfmu_trigger_down/weight_sfmu_trigger',
            'toptag_corrUp':'eventweight*weight_toptagsf_corr_up/weight_toptagsf'     ,  'toptag_corrDown':'eventweight*weight_toptagsf_corr_down/weight_toptagsf',
            'toptag_uncorrUp':'eventweight*weight_toptagsf_uncorr_up/weight_toptagsf' ,  'toptag_uncorrDown':'eventweight*weight_toptagsf_uncorr_down/weight_toptagsf',
            'FSRDown':'eventweight*weight_fsr_sqrt2_up'                          , 'FSRDown':'eventweight*weight_fsr_sqrt2_down',
            'ISRDown':'eventweight*weight_isr_sqrt2_up'                          , 'ISRDown':'eventweight*weight_isr_sqrt2_down',
            'MuR_MuFDown':'eventweight*weight_murmuf_downdown'                   , 'MuR_MuFUp':'eventweight*weight_murmuf_upup',
            'MuRDown':'eventweight*weight_murmuf_downnone'                       , 'MuRUp':'eventweight*weight_murmuf_upnone',
            'MuFDown':'eventweight*weight_murmuf_nonedown'                       , 'MuFUp':'eventweight*weight_murmuf_noneup',
            'btag_HF_corrUp':'eventweight*weight_btag_bc_up/weight_btag'         , 'btag_HF_corrDown':'eventweight*weight_btag_bc_down/weight_btag'   ,
            'btag_LF_corrUp':'eventweight*weight_btag_udsg_up/weight_btag'       , 'btag_LF_corrDown':'eventweight*weight_btag_udsg_down/weight_btag'   ,
            'btag_HF_unc16Up':'eventweight*weight_btag_bc_up_un/weight_btag'     , 'btag_HF_unc16Down':'eventweight*weight_btag_bc_down_un/weight_btag'  ,
            'btag_LF_unc16Up':'eventweight*weight_btag_udsg_up_un/weight_btag'   , 'btag_LF_unc16Down':'eventweight*weight_btag_udsg_down_un/weight_btag'  ,
            'L1Prefiring16Up':'eventweight*prefiringWeightUp/prefiringWeight'    , 'L1Prefiring16Down':'eventweight*prefiringWeightDown/prefiringWeight"'  ,
            'top_pt_rewUp':'eventweight*weight_toppt_a_up/weight_toppt_nominal'  , 'top_pt_rewDown':'eventweight*weight_toppt_a_down/weight_toppt_nominal'  ,
            'hdampUp':'eventweight*hdamp_up") '"hdampUp"                         , 'hdampDown':'eventweight*hdamp_down',
}

for i in range(1,101):
    pdfstring  = 'eventweight*LHEPdfWeight_'+str(i)
    systematic_direction_ttbar_in['LHEPdfWeight_'+str(i)+'Up'] = pdfstring
    systematic_direction_ttbar_in['LHEPdfWeight_'+str(i)+'Down'] = 'eventweight'

inputdir = '/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2016preVFP_muon/'

samplelist = {
'data':'data.root', 
'Ttbar_in':'Ttbar_in.root', 
'ttbar_out':'ttbar_out.root', 
'wjets':'wjets.root', 
'st':'st.root', 
'dy':'dy.root', 
'qcd':'qcd.root', 
'diboson':'diboson.root', 
'ttbar_ll':'ttbar_ll.root', 
'ttbar_had':'ttbar_had.root' 
} 

fout = TFile('all_unfolding_data.root', 'recreate')
Bin = [0.,0.33,0.66,1.0]; nb = len(Bin)-1
gROOT.SetBatch(kTRUE)

for key_sample in samplelist:
	myfile = TFile(inputdir+samplelist[key_sample])
	mytree = myfile.Get("Events")
        mytree.SetAlias("invmass","BDT")
        gDirectory.cd('all_unfolding_data.root:/')
        if key_sample == 'data':
            gDirectory.cd('all_unfolding_data.root:/')
            selcuts_boosted_central_1 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) < 0)"
            selcuts_boosted_central_2 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) > 0)"
            tempdata1 = TH1F("tempdata1","tempdata1",nb,array('d',Bin))
            tempdata2 = TH1F("tempdata2","tempdata2",nb,array('d',Bin))
            mytree.Draw("invmass>>tempdata1",selcuts_boosted_central_1)
            mytree.Draw("invmass>>tempdata2",selcuts_boosted_central_2)
            Back = TH1F("Back", "Back", nb*2, 0, nb*2)
            for i in range(1, nb+1):
                Back.SetBinContent(i, tempdata1.GetBinContent(i))
                Back.SetBinError(i, tempdata1.GetBinError(i))
                Back.SetBinContent(i + nb, tempdata2.GetBinContent(i))
                Back.SetBinError(i + nb, tempdata2.GetBinError(i))
            gDirectory.WriteObject(Back,'data_obs')
            del tempdata1; del tempdata2; del Back
        elif 'Ttbar_in' in key_sample: 
            for syst in systematic_direction_ttbar_in:   
                gDirectory.cd('all_unfolding_data.root:/')  
                selcuts_boosted_central_1 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)*("+str(systematic_direction_ttbar_in[syst])+")"
                selcuts_boosted_central_2 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)*("+str(systematic_direction_ttbar_in[syst])+")"
                selcuts_boosted_central_3 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)*("+str(systematic_direction_ttbar_in[syst])+")"
                selcuts_boosted_central_4 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)*("+str(systematic_direction_ttbar_in[syst])+")"
                tempdata1 = TH1F("tempdata1","tempdata1",nb,array('d',Bin))
                tempdata2 = TH1F("tempdata2","tempdata2",nb,array('d',Bin))
                tempdata3 = TH1F("tempdata3","tempdata3",nb,array('d',Bin))
                tempdata4 = TH1F("tempdata4","tempdata4",nb,array('d',Bin))
                mytree.Draw("invmass>>tempdata1",selcuts_boosted_central_1)
                mytree.Draw("invmass>>tempdata2",selcuts_boosted_central_2) 
                mytree.Draw("invmass>>tempdata3",selcuts_boosted_central_3)
                mytree.Draw("invmass>>tempdata4",selcuts_boosted_central_4)
                print("--------------------------------------")
                print "Processing: ",key_sample
                print "Syst:",syst
                Back_pos = TH1F("Back_pos", "Back_pos", nb*2, 0, nb*2); Back_neg = TH1F("Back_neg", "Back_neg", nb*2, 0, nb*2)
                for i in range(1, nb+1):
                    Back_pos.SetBinContent(i, tempdata1.GetBinContent(i))
                    Back_pos.SetBinError(i, tempdata1.GetBinError(i))
                    Back_pos.SetBinContent(i + nb, tempdata2.GetBinContent(i))
                    Back_pos.SetBinError(i + nb, tempdata2.GetBinError(i))
                    Back_neg.SetBinContent(i, tempdata3.GetBinContent(i))
                    Back_neg.SetBinError(i, tempdata3.GetBinError(i))
                    Back_neg.SetBinContent(i + nb, tempdata4.GetBinContent(i))
                    Back_neg.SetBinError(i + nb, tempdata4.GetBinError(i)) 
                gDirectory.WriteObject(Back_pos,key_sample+'_2_'+syst); gDirectory.WriteObject(Back_neg,key_sample+'_1_'+syst);
                del tempdata1; del tempdata2; del tempdata3; del tempdata4; del Back_pos; del Back_neg;
 


