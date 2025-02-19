from ROOT import *
import os
import sys
from sys import *
from optparse import OptionParser

from numpy import log10
from array import array
import math

#Bin = [0.,0.3,0.6,0.7,0.8,0.9,1.0]
Bin=[-1,0,1]
nb = len(Bin)-1

stackList = {"TTToSemiLeptonic_1":[kRed], "TTToSemiLeptonic_2":[kRed],"diboson":[kBlue], "dyjetstoll_m-50_ht":[kBlue], "qcd_ht":[kBlue], "st":[kBlue], "wjetstolnu":[kGreen], "fake":[kOrange], "wgammatojjgamma":[kTeal], "zgammatojjgamma":[kCyan+2], "wgtolnug":[kViolet], "gjets_int":[kRed-2], "tttosemileptonic_outfiducial":[kRed-2], "ttto2l2nu":[kViolet],"tttohadronic":[kViolet]}

legList = stackList.keys()
padRatio = 0.25
padOverlap = 0.15
padGap = 0.01

H = 600;
W = 1000;

T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W


legendHeightPer = 0.04
legendStart = 0.7
legendEnd = 0.95-(R/W)
legendR = TLegend(2*legendStart - legendEnd , 1.06 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.97-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(2)

legendR.SetBorderSize(0)
legendR.SetFillColor(0)


stack = THStack("hs","stack; ; Events")

histName=argv[1]
histograms = {
              "score_NLO": ["BDT score", "Events", 8, [-2,2]],
}

sample_names = ["diboson", "dyjetstoll_m-50_ht", "qcd_ht", "st", "wjetstolnu","ttto2l2nu","tttohadronic","tttosemileptonic_outfiducial","TTToSemiLeptonic_1","TTToSemiLeptonic_2"]

legend_index = 0

_file = {}
_file2 = {}
_file3 = {}
hist1_={}
hist2_={}
hist3_={}

_file_2017 = {}
_file2_2017 = {}
_file3_2017 = {}
hist1_2017={}
hist2_2017={}
hist3_2017={}

_file_2016 = {}
_file2_2016 = {}
_file3_2016 = {}
hist1_2016={}
hist2_2016={}
hist3_2016={}

_file_2016pre = {}
_file2_2016pre = {}
_file3_2016pre = {}
hist1_2016pre={}
hist2_2016pre={}
hist3_2016pre={}

for sample in sample_names:

    print(sample)

    _file_2016[sample]  = TFile("shapes.root","read")

    hist1_2016[sample] = _file_2016[sample].Get("muon_2016_750_900_prefit/%s"%sample)

    total_n_bins = hist1_2016[sample].GetXaxis().GetNbins()

    h3 = TH1F("h3","test3",nb,array('d',Bin))
    for i in range(1,total_n_bins+1):
        if(i < 100):              h3.SetBinContent(i,hist1_2016[sample].GetBinContent(i))
    h3.SetFillColor(stackList[sample][0])
    h3.SetLineColor(stackList[sample][0])

    if(sample == 'TTToSemiLeptonic_1') : legendR.AddEntry(h3,'t#bar{t} (l+jets)','f')
    if(sample == 'diboson') : legendR.AddEntry(h3,'Others','f')
    if(sample == 'wjetstolnu') : legendR.AddEntry(h3,'W + jets','f')
    if(sample == 'ttgjets') : legendR.AddEntry(h3,'t#bar{t} #gamma','f')
    if(sample == 'diphoton') : legendR.AddEntry(h3,'#gamma#gamma','f')
    if(sample == 'fake') : legendR.AddEntry(h3,'fake #gamma','f')
    if(sample == 'wgammatojjgamma') : legendR.AddEntry(h3,'W(jj) #gamma','f')
    if(sample == 'zgammatojjgamma') : legendR.AddEntry(h3,'Z(jj) #gamma','f')
    if(sample == 'wgtolnug') : legendR.AddEntry(h3,'W(l#nu) #gamma','f')
    if(sample == 'tttosemileptonic_outfiducial') : legendR.AddEntry(h3,'t#bar{t} (out)','f')
    if(sample == 'ttto2l2nu') : legendR.AddEntry(h3,'t#bar{t} (others)','f')

    stack.Add(h3)
    del h3


data3 = TFile("shapes.root","read")

dataHist1_2016=data3.Get("muon_2016_750_900_prefit/data_obs")

total_n_bins = dataHist1_2016.GetXaxis().GetNbins()
data = TH1F("data","data",nb,array('d',Bin))

for i in range(1,total_n_bins+1):
    if(i < 100):              data.SetBinContent(i,dataHist1_2016.GetBinContent(i))

legendR.AddEntry(data, "Data", 'pe')
maxVal =stack.GetMaximum()
minVal = 1
minVal = max(stack.GetStack()[0].GetMinimum(),1)
log=0
if log:
    stack.SetMaximum(15**(1.5*log10(maxVal) - 0.5*log10(minVal)))
else:
    stack.SetMaximum(1.85*maxVal)
stack.SetMinimum(minVal)

data.SetMarkerStyle(20)
data.SetMarkerSize(1)
data.SetMarkerColor(kBlack)

stack.SetTitle()

print(total_n_bins)

c1 = TCanvas("c1","multipads",1200,700)
c1.cd()
c1.SetLogy(log)

pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
pad1.SetBottomMargin(0)
pad1.SetLogy(log)
pad1.Draw()
pad1.cd()

stack.Draw("HIST")
#data.Draw("same pe, x0")
data.Draw("same hist p")
legendR.Draw("SAME")
gPad.Update()
stack.GetYaxis().SetTitle("Events")

l1 = TLine(8.0,0,8.0,20000)
#l1.Draw("same")

l2 = TLine(16,0,16,20000)
#l2.Draw("same")

latex = TLatex();
latex.SetTextSize(0.05);
latex.SetTextAlign(13);
latex.DrawLatex(-1,12**(1.66*log10(maxVal) - 0.5*log10(minVal)),"CMS #font[12]{preliminary}");
latex.DrawLatex(0.5,12**(1.67*log10(maxVal) - 0.5*log10(minVal)),"138 fb^{-1} (13 TeV)");

latex.SetTextSize(0.03)

c1.cd();
pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
pad2.SetTopMargin(0);
pad2.SetBottomMargin(0.2);
pad2.SetGridx();
pad2.Draw();
pad2.cd();

h3 = data.Clone("h3")
h3.SetLineColor(kBlack);
h3.SetMinimum(0.8);
h3.SetMaximum(1.2);
h3.Sumw2();
h3.SetStats(0);
h3.Divide(stack.GetStack().Last())
h3.SetMarkerStyle(21);
h3.Draw("ep");

h3.SetTitle("");

h3.GetYaxis().SetTitle("Data/MC ");
h3.GetYaxis().SetNdivisions(505);
h3.GetYaxis().SetTitleSize(20);
h3.GetYaxis().SetTitleFont(43);
h3.GetYaxis().SetTitleOffset(1.55);
h3.GetYaxis().SetLabelFont(43);
h3.GetYaxis().SetLabelSize(15);

h3.GetXaxis().SetTitleSize(20);
h3.GetXaxis().SetTitleFont(43);
h3.GetXaxis().SetTitleOffset(1);
h3.GetXaxis().SetLabelFont(43);
h3.GetXaxis().SetLabelSize(15);


errorband=stack.GetStack().Last().Clone("errorband")
temp1    =stack.GetStack().Last().Clone("temp1")
errorband.Sumw2()
errorband.SetLineColor(kRed-9)
errorband.SetFillColor(kRed-9)
errorband.SetFillStyle(1001)
errorband.SetMarkerSize(0)
errorband.Divide(temp1)

shapes = TFile("shapes.root","read")

bkg_bin1=shapes.Get("muon_2018_750_900_prefit/TotalProcs")
bkg_bin1_2017=shapes.Get("muon_2017_750_900_prefit/TotalProcs")
bkg_bin1_2016=shapes.Get("muon_2016postVFP_750_900_prefit/TotalProcs")
bkg_bin1_2016pre=shapes.Get("muon_2016postVFP_750_900_prefit/TotalProcs")




errorband.Draw('e2,same')

oneLine = TF1("oneline","1",-9e9,9e9)
oneLine.SetLineColor(kBlack)
oneLine.SetLineWidth(1)
oneLine.SetLineStyle(2)
oneLine.Draw("same")


errorband2= stack.GetStack().Last().Clone("errorband2")
temp3     = stack.GetStack().Last().Clone("temp3")
errorband2.Sumw2()
errorband2.SetLineColor(kBlack)
errorband2.SetFillColor(kBlack)
errorband2.SetFillStyle(3001)
errorband2.SetMarkerSize(0)
errorband2.Divide(temp3)


h3.Draw("hist p same");

c1.SaveAs("final_muon_AE.pdf")


