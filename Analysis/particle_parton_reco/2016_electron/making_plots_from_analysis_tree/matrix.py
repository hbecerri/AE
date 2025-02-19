import ROOT

# Open the ROOT file
file_name = "/nfs/dust/cms/user/hugobg/analysis/electron/workdir_Analysis_UL16preVFP_electron/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL16preVFP_0.root"
file = ROOT.TFile(file_name, "READ")

# Access the TTree
tree = file.Get("AnalysisTree")

# Create a 2D histogram with 2 bins
hist_name = "h2d_diff_energy"
hist_title = "2D Histogram; Ak4_add_E; addnewgenjet_E"
nbins_x = 2
x_min = -100
x_max = 100
nbins_y = 2
y_min = -100
y_max = 100
hist = ROOT.TH2F(hist_name, hist_title, nbins_x, x_min, x_max, nbins_y, y_min, y_max)


# Define the expression for the x and y axes
expr_x = "(Boost_top_E - Boost_antitop_E)"
expr_y = "(Gen_Boost_top_E - Gen_Boost_antitop_E)"
 
#expr_x = '(top_l_m)'
#expr_y = '(h_tl_newgen_m)'
  
# Draw the 2D histogram
tree.Draw(expr_y + ":" + expr_x + ">>" + hist_name, "eventweight*(Ele_pt > 80.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2)", "COLZ")

# Calculate purity and stability
purity = [0] * nbins_x
stability = [0] * nbins_y
for i in range(1, nbins_x + 1):
    generated_in_bin = hist.ProjectionY("", i, i).Integral()
    reconstructed_in_bin = hist.ProjectionX("", i, i).Integral()
    purity[i - 1] = hist.GetBinContent(i, i) / reconstructed_in_bin if reconstructed_in_bin > 0 else 0
    stability[i - 1] = hist.GetBinContent(i, i) / generated_in_bin if generated_in_bin > 0 else 0

# Create a canvas
canvas = ROOT.TCanvas("canvas", "Canvas", 800, 800)

# Divide the canvas to create a main plot and a bottom plot
canvas.Divide(1, 2)
pad1 = canvas.cd(1)
pad1.SetPad(0.0, 0.4, 1.0, 1.0)  # top plot
pad2 = canvas.cd(2)
pad2.SetPad(0.0, 0.0, 1.0, 0.3)  # bottom plot

# Draw the 2D histogram in the top pad
pad1.cd()
hist.Draw("COLZ")

# Create TH1F histograms for purity and stability
pad2.cd()
purity_hist = ROOT.TH1F("purity", "Purity; Bin; Value", nbins_x, 0.5, nbins_x + 0.5)
stability_hist = ROOT.TH1F("stability", "Stability; Bin; Value", nbins_x, 0.5, nbins_x + 0.5)

for i in range(nbins_x):
    purity_hist.SetBinContent(i + 1, purity[i])
    stability_hist.SetBinContent(i + 1, stability[i])

purity_hist.SetLineColor(ROOT.kBlue)
purity_hist.SetLineWidth(2)
stability_hist.SetLineColor(ROOT.kRed)
stability_hist.SetLineWidth(2)

# Draw the histograms
purity_hist.Draw("HIST")
stability_hist.Draw("HIST SAME")

# Customize the axes
purity_hist.GetXaxis().SetTitle("Bin")
purity_hist.GetYaxis().SetTitle("Value")
purity_hist.GetYaxis().SetRangeUser(0, 1)

# Add a legend
legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)
legend.AddEntry(purity_hist, "Purity", "l")
legend.AddEntry(stability_hist, "Stability", "l")
legend.Draw()

# Save the canvas as a PNG file
canvas.SaveAs("AE.png")

# Close the ROOT file
file.Close()
