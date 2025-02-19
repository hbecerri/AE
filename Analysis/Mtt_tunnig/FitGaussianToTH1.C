#include <iostream>
#include <TFile.h>
#include <TH1.h>
#include <TF1.h>
#include <TCanvas.h>
#include <TStyle.h>

void FitGaussianToTH1(string plot = "") {
 
    // Open ROOT file containing the TH1 histogram
    TFile *file = new TFile("/nfs/dust/cms/user/hugobg/analysis/muon///workdir_Analysis_UL18_muon_Matched/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL18_44.root");
    TH1F *histogram = (TH1F*)file->Get(Form("CorrectMatchDiscriminator_General/%s",plot.c_str()));
    histogram->Scale(1/histogram->Integral());
 

    // Create a Gaussian function
    TF1 *gaussian = new TF1("gaussian","gaus",140,220);

    // Fit the Gaussian to the histogram
    histogram->Fit("gaussian", "Q","",140,220);

    // Get the parameters of the fit
    double mean = gaussian->GetParameter(1);
    double sigma = gaussian->GetParameter(2);

    // Display the fit parameters
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Sigma: " << sigma << std::endl;

    histogram->SetMarkerStyle(4);
    histogram->SetTitle("");

    // Create a canvas to display the histogram and fit
    TCanvas *c1 = new TCanvas("c1", "Gaussian Fit", 800, 600);
    histogram->Draw("hist p");

    histogram->SetStats(0);
    gStyle->SetOptFit(0);

    TF1 *fitFunction = histogram->GetFunction("gaussian");
    fitFunction->SetLineColor(kRed);
    fitFunction->Draw("SAME");

    if(plot == "M_toplep_dr_ttag") plot="M_tophad_dr_wtag";

    TLatex latex;
    latex.SetTextSize(0.025);
    latex.SetTextAlign(13);  //align at top

    latex.DrawLatex(500,histogram->GetMaximum()*0.80,plot.c_str());
    latex.DrawLatex(500,histogram->GetMaximum()*0.75,Form("Mean: %f",mean));
    latex.DrawLatex(500,histogram->GetMaximum()*0.70,Form("Sigma: %f",sigma));
 

    c1->Update();
    c1->SaveAs(Form("%s.pdf",plot.c_str()));




}



