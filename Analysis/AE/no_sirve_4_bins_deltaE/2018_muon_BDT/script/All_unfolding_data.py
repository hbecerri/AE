import ROOT
from ROOT import TFile, TChain, TH1F, gStyle

def all_unfolding_data(var_name="", var_gen="", region="", year="2018"):
    # Open a new ROOT file for output
    out = TFile("Input_unfolding_data_all.root", "recreate")
    
    # Define the datasets
    texts = ["data", "Ttbar_in", "ttbar_out", "wjets", "st", "dy", "qcd", "diboson", "ttbar_ll", "ttbar_had"]
    
    # Array used in the unfolding (based on the structure of your macro)
    new_rec = [0, 0.2, 0.4, 0.6, 0.8, 1.0]
    newrec = len(new_rec) - 1  # Number of bins

    # Define systematic variations
    systs = ["1","weight_pu_up/weight_pu","weight_pu_down/weight_pu", "weight_sfmu_id_up/weight_sfmu_id", "weight_sfmu_id_down/weight_sfmu_id", "weight_sfmu_iso_up/weight_sfmu_iso", "weight_sfmu_iso_down/weight_sfmu_iso","weight_sfmu_trigger_up/weight_sfmu_trigger","weight_sfmu_trigger_down/weight_sfmu_trigger","weight_toptagsf_corr_up/weight_toptagsf","weight_toptagsf_corr_down/weight_toptagsf", "weight_toptagsf_uncorr_up/weight_toptagsf","weight_toptagsf_uncorr_down/weight_toptagsf", "weight_fsr_sqrt2_down", "weight_fsr_sqrt2_up", "weight_isr_sqrt2_up", "weight_isr_sqrt2_down", "weight_murmuf_downdown", "weight_murmuf_downnone", "weight_murmuf_nonedown", "weight_murmuf_noneup", "weight_murmuf_upnone", "weight_murmuf_upup", "weight_btag_bc_up/weight_btag", "weight_btag_bc_down/weight_btag", "weight_btag_udsg_up/weight_btag", "weight_btag_udsg_down/weight_btag", "weight_btag_bc_up_un/weight_btag", "weight_btag_bc_down_un/weight_btag", "weight_btag_udsg_up_un/weight_btag", "weight_btag_udsg_down_un/weight_btag", "weight_toppt_a_up/weight_toppt_nominal", "weight_toppt_a_down/weight_toppt_nominal", "prefiringWeightUp/prefiringWeight", "prefiringWeightDown/prefiringWeight", "hdamp_up", "hdamp_down"]

    for text in texts:
        print "value of text: %s" % text
        gStyle.SetOptStat(0)

        chreco_ttbar_semi = TChain("Events", "")
        chreco_ttbar_semi.Add("/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2018_muon/%s.root/Events" % text)
        treereco_ttbar_semi = chreco_ttbar_semi

        # Handling data
        if text == "data":
            chreco_data = TChain("Events", "")
            chreco_data.Add("/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2018_muon/data.root/Events")
            treereco_data = chreco_data

            # Create histograms
            Back_1 = TH1F("Back_1", "", newrec, new_rec)
            Back_2 = TH1F("Back_2", "", newrec, new_rec)

            # Selection cuts
            selcuts_boosted_central_1 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) < 0)"
            selcuts_boosted_central_2 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) > 0)"

            # Project data into histograms
            treereco_data.Project("Back_1", "BDT", selcuts_boosted_central_1)
            treereco_data.Project("Back_2", "BDT", selcuts_boosted_central_2)

            # Merge histograms
            Back = TH1F("Back", "Merged histogram", newrec * 2, 0, 10)
            for i in range(1, 6):
                Back.SetBinContent(i, Back_1.GetBinContent(i))
                Back.SetBinError(i, Back_1.GetBinError(i))
                Back.SetBinContent(i + 5, Back_2.GetBinContent(i))
                Back.SetBinError(i + 5, Back_2.GetBinError(i))

            # Write merged histogram
            Back.Write("data_obs")

            # Clean up
            del Back_1, Back_2, Back
