#include <vector>
#include <string>
#include <iostream>
#include "TFile.h"
#include "TChain.h"
#include "TH1F.h"
#include "TMath.h"

void jes_ttbar_2(string var_name = "", string var_gen = "", string region = "", string year = "2018") {
    TFile out("Input_unfolding_data_jes.root", "recreate");
    std::vector<std::string> texts = {"Ttbar_in", "Ttbar_in_JECdown", "Ttbar_in_JERdown"};
    const int nBins = 10;
    float nominal[2][nBins] = {0}, variation[2][nBins] = {0}, difference[2][nBins] = {0};

    for (const auto& text : texts) {
        std::cout << "Processing: " << text << std::endl;

        TChain chain("AnalysisTree");
        chain.Add(("/nfs/dust/cms/user/hugobg/analysis/muon/BDT/2018_muon/" + text + ".root/Events").c_str());

        TH1F* histograms[4];
        for (int i = 0; i < 4; ++i) {
            histograms[i] = new TH1F(Form("Back_%d", i + 1), "", nBins, 0, 1);
        }

        std::vector<std::string> selcuts = {
            "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)",
            "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) < 0)",
            "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) < 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)",
            "(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.6*3.1459 && leadgenjet_pt > 150 && subleadgenjet_pt > 50  && dressed_lep_pt > 55 && Gen_M_tt > 450 && h_parton_rec < 0 && (Boost_top_E - Boost_antitop_E) > 0 && (Gen_Boost_top_E - Gen_Boost_antitop_E) > 0)"
        };

        for (size_t i = 0; i < selcuts.size(); ++i) {
            chain.Project(histograms[i]->GetName(), "BDT", (selcuts[i] + "*eventweight").c_str());
        }

        TH1F* Back_neg = new TH1F("Back_neg", "Merged histogram", nBins * 2, 0, 2);
        TH1F* Back_pos = new TH1F("Back_pos", "Merged histogram", nBins * 2, 0, 2);

        for (int bin = 1; bin <= nBins; ++bin) {
            Back_neg->SetBinContent(bin, histograms[0]->GetBinContent(bin));
            Back_neg->SetBinContent(bin + nBins, histograms[1]->GetBinContent(bin));
            Back_pos->SetBinContent(bin, histograms[2]->GetBinContent(bin));
            Back_pos->SetBinContent(bin + nBins, histograms[3]->GetBinContent(bin));
        }

        for (int bin = 0; bin < nBins; ++bin) {
            nominal[0][bin] = Back_neg->GetBinContent(bin + 1);
            nominal[1][bin] = Back_pos->GetBinContent(bin + 1);
            variation[0][bin] = Back_neg->GetBinContent(bin + 1);
            variation[1][bin] = Back_pos->GetBinContent(bin + 1);
            difference[0][bin] = TMath::Abs(nominal[0][bin] - variation[0][bin]);
            difference[1][bin] = TMath::Abs(nominal[1][bin] - variation[1][bin]);
        }

        TH1F* Ttbar_down[2] = {
            new TH1F("Ttbar_1_down", "Down", nBins, 0, 1),
            new TH1F("Ttbar_2_down", "Down", nBins, 0, 1)
        };
        TH1F* Ttbar_up[2] = {
            new TH1F("Ttbar_1_up", "Up", nBins, 0, 1),
            new TH1F("Ttbar_2_up", "Up", nBins, 0, 1)
        };

        for (int bin = 0; bin < nBins; ++bin) {
            for (int i = 0; i < 2; ++i) {
                Ttbar_down[i]->SetBinContent(bin + 1, nominal[i][bin] - difference[i][bin]);
                Ttbar_up[i]->SetBinContent(bin + 1, nominal[i][bin] + difference[i][bin]);
            }
        }

        for (int i = 0; i < 2; ++i) {
            Ttbar_down[i]->Write();
            Ttbar_up[i]->Write();
        }

        for (auto* hist : histograms) delete hist;
        delete Back_neg;
        delete Back_pos;
        for (int i = 0; i < 2; ++i) {
            delete Ttbar_down[i];
            delete Ttbar_up[i];
        }
    }
}

