import multiprocessing as mp
from ROOT import TFile, TH1F, gDirectory, gROOT
from array import array

def process_sample(key_sample, samplelist, inputdir, fout_name, systematic_direction_ttbar_in, nb, Bin):
    # Open the input ROOT file
    myfile = TFile(inputdir + samplelist[key_sample])
    mytree = myfile.Get("Events")
    mytree.SetAlias("invmass","BDT")
    gDirectory.cd('all_unfolding_data.root:/')
 
    # Set up histogram bins
    Bin_array = array('d', Bin)

    # Apply some selection cuts (as an example)
    gROOT.SetBatch(True)  # Ensure ROOT doesn't open windows

    if key_sample == 'data':
        selcuts_boosted_central_1 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) < 0)"
        selcuts_boosted_central_2 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && (Boost_top_E - Boost_antitop_E) > 0)"

        # Create histograms
        tempdata1 = TH1F("tempdata1", "tempdata1", nb, Bin_array)
        tempdata2 = TH1F("tempdata2", "tempdata2", nb, Bin_array)

        # Fill histograms with selected data
        mytree.Draw("invmass>>tempdata1", selcuts_boosted_central_1)
        mytree.Draw("invmass>>tempdata2", selcuts_boosted_central_2)

        # Create combined histogram
        Back = TH1F("Back", "Back", nb * 2, 0, nb * 2)
        for i in range(1, nb + 1):
            Back.SetBinContent(i, tempdata1.GetBinContent(i))
            Back.SetBinError(i, tempdata1.GetBinError(i))
            Back.SetBinContent(i + nb, tempdata2.GetBinContent(i))
            Back.SetBinError(i + nb, tempdata2.GetBinError(i))
 
        # Save histogram to ROOT file
        print(Back.Integral())
        gDirectory.cd('all_unfolding_data.root:/')
        gDirectory.WriteObject(Back, 'data_obs')
        Back.Write('data_obs')
  
        # Clean up
        del tempdata1
        del tempdata2
        del Back

    elif 'Ttbar_in' in key_sample:
        for syst in systematic_direction_ttbar_in:
            gDirectory.cd('all_unfolding_data.root:/')
            selcuts_boosted_central_1 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)*(" + str(systematic_direction_ttbar_in[syst]) + ")"
            selcuts_boosted_central_2 = "(N_Ak4 >= 3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 && chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.14159 && angle_theta_opt < 0.55*3.14159 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)*(" + str(systematic_direction_ttbar_in[syst]) + ")"

            # Create and fill histograms for Ttbar_in
            tempdata1 = TH1F("tempdata1", "tempdata1", nb, Bin_array)
            tempdata2 = TH1F("tempdata2", "tempdata2", nb, Bin_array)

            mytree.Draw("invmass>>tempdata1", selcuts_boosted_central_1)
            mytree.Draw("invmass>>tempdata2", selcuts_boosted_central_2)

            Back = TH1F("Back_" + syst, "Back_" + syst, nb * 2, 0, nb * 2)
            for i in range(1, nb + 1):
                Back.SetBinContent(i, tempdata1.GetBinContent(i))
                Back.SetBinError(i, tempdata1.GetBinError(i))
                Back.SetBinContent(i + nb, tempdata2.GetBinContent(i))
                Back.SetBinError(i + nb, tempdata2.GetBinError(i))

            gDirectory.cd('all_unfolding_data.root:/')
            gDirectory.WriteObject(Back, 'Back_' + syst)
 
            # Clean up
            del tempdata1
            del tempdata2
            del Back

    myfile.Close()

def parallel_processing():
    inputdir = '/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2016preVFP_muon/'
    samplelist = {
        'data': 'data.root',
        'Ttbar_in': 'Ttbar_in.root',
        'ttbar_out': 'ttbar_out.root',
        'wjets': 'wjets.root',
        'st': 'st.root',
        'dy': 'dy.root',
        'qcd': 'qcd.root',
        'diboson': 'diboson.root',
        'ttbar_ll': 'ttbar_ll.root',
        'ttbar_had': 'ttbar_had.root'
    }

    # Systematic variations
    systematic_direction_ttbar_in = {
        'nominal': 'eventweight',
        # Add the rest of the systematics as in your original code
    }

    fout_name = 'all_unfolding_data.root'
    fout = TFile(fout_name, 'recreate')

    # Define bins and number of bins (replace with your actual bin values)
    Bin = [0., 0.33, 0.66, 1.0]
    nb = len(Bin) - 1

    # Create a pool of processes
    pool = mp.Pool(mp.cpu_count())

    # Distribute sample processing across the pool
    for key_sample in samplelist:
        pool.apply_async(process_sample, args=(key_sample, samplelist, inputdir, fout_name, systematic_direction_ttbar_in, nb, Bin))

    # Close the pool and wait for all tasks to complete
    pool.close()
    pool.join()

    fout.Close()

if __name__ == '__main__':
    parallel_processing()


