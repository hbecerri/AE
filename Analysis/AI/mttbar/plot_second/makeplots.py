from ROOT import *
import os
import sys
from sys import *
from optparse import OptionParser

from numpy import log10
from array import array
import math


stackList = {"TTToSemiLeptonic_4":[kRed], "TTToSemiLeptonic_3":[kRed],"TTToSemiLeptonic_1":[kRed], "TTToSemiLeptonic_2":[kRed], "wjetstolnu":[kGreen], "dyjetstoll_m-50_ht":[kYellow], "st":[kBlue], "qcd_ht":[kOrange], "diboson":[kTeal], "zgammatojjgamma":[kCyan+2], "wgtolnug":[kViolet], "gjets_int":[kRed-2]}

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
legendStart = 0.55
legendEnd = 0.95-(R/W)
legendR = TLegend(2*legendStart - legendEnd , 1.06 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.97-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(2)

legendR.SetBorderSize(0)
legendR.SetFillColor(0)


stack = THStack("hs","stack; ; Events")

histName=argv[1]
histograms = {
              "Delta_E": ["#Delta E", "Events", 2, [-2000, 2000]],
}

sample_names = ["wjetstolnu", "st", "dyjetstoll_m-50_ht", "qcd_ht","TTToSemiLeptonic_1","TTToSemiLeptonic_2","TTToSemiLeptonic_3","TTToSemiLeptonic_4"]

legend_index = 0
_file = {}
_file2 = {}
_file3 = {}
hist1_={}
hist2_={}
hist3_={}

for sample in sample_names:

    print(sample)

    _file[sample] = TFile("shapes.root","read")
    _file2[sample] = TFile("shapes.root","read")
    _file3[sample] = TFile("shapes.root","read")

    hist1_[sample] = _file[sample].Get("muon_2016postVFP_500_700_postfit/%s"%sample)
    hist2_[sample] = _file2[sample].Get("muon_2016postVFP_700_900_postfit/%s"%sample)
    hist3_[sample] = _file3[sample].Get("muon_2016postVFP_900_Inf_postfit/%s"%sample)
    total_n_bins = hist1_[sample].GetXaxis().GetNbins() + hist2_[sample].GetXaxis().GetNbins() + hist3_[sample].GetXaxis().GetNbins()
    h1 = TH1F("h1","test1",total_n_bins,0,total_n_bins)
    for i in range(1,total_n_bins+1):
        if(i < 5):              h1.SetBinContent(i,hist1_[sample].GetBinContent(i))
        if(i >=5 and i < 8):   h1.SetBinContent(i,hist2_[sample].GetBinContent(i - 4))
        if(i==8):              h1.SetBinContent(i,hist2_[sample].GetBinContent(4))
        if(i > 8 and i < 12):  h1.SetBinContent(i,hist3_[sample].GetBinContent(i - 8))
        if(i==12):              h1.SetBinContent(i,hist3_[sample].GetBinContent(4))
    h1.SetFillColor(stackList[sample][0])
    h1.SetLineColor(stackList[sample][0])

    if(sample == 'TTToSemiLeptonic_1') : legendR.AddEntry(h1,'t#bar{t}','f')
    if(sample == 'wjetstolnu') : legendR.AddEntry(h1,'W(l\nu) + j','f')
    if(sample == 'st') : legendR.AddEntry(h1,'Single t','f')
    if(sample == 'qcd_ht') : legendR.AddEntry(h1,'QCD','f')  
    if(sample == 'dyjetstoll_m-50_ht') : legendR.AddEntry(h1,'Drell-Yan','f')   
  
    stack.Add(h1)
    del h1


data1 = TFile("shapes.root","read")
dataHist1=data1.Get("muon_2016postVFP_500_700_postfit/data_obs")
data2 = TFile("shapes.root","read")
dataHist2=data2.Get("muon_2016postVFP_700_900_postfit/data_obs")
data3 = TFile("shapes.root","read")
dataHist3=data3.Get("muon_2016postVFP_900_Inf_postfit/data_obs")
total_n_bins = dataHist1.GetXaxis().GetNbins() + dataHist2.GetXaxis().GetNbins() + dataHist3.GetXaxis().GetNbins()
data = TH1F("data","data",total_n_bins,0,total_n_bins)

for i in range(1,total_n_bins+1):
    if(i < 5):              data.SetBinContent(i,dataHist1.GetBinContent(i))
    if(i >=5 and i < 8):   data.SetBinContent(i,dataHist2.GetBinContent(i - 4))
    if(i==8):              data.SetBinContent(i,dataHist2.GetBinContent(4))
    if(i > 8 and i < 12):  data.SetBinContent(i,dataHist3.GetBinContent(i - 8))
    if(i==12):              data.SetBinContent(i,dataHist3.GetBinContent(4))


legendR.AddEntry(data, "Data", 'pe')
maxVal =stack.GetMaximum()
minVal = 1
minVal = max(stack.GetStack()[0].GetMinimum(),1)
log=1
if log:
    stack.SetMaximum(20**(1.5*log10(maxVal) - 0.5*log10(minVal)))
else:
    stack.SetMaximum(1.85*maxVal)
stack.SetMinimum(minVal)

data.SetMarkerColor(kBlack)

stack.SetTitle()

c1 = TCanvas("c1","multipads",1200,700)
c1.cd()
c1.SetLogy(log)

pad1 = TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
pad1.SetBottomMargin(0)
pad1.SetLogy(log)
pad1.Draw()
pad1.cd()

stack.Draw("HIST")
data.Draw("same pe, x0")
legendR.Draw("SAME")

gPad.Update()
stack.GetYaxis().SetTitle("Events")

l1 = TLine(4.0,0,4.0,20000)
l1.Draw("same")

l2 = TLine(8,0,8,20000)
l2.Draw("same")

latex = TLatex();
latex.SetTextSize(0.05);
latex.SetTextAlign(13);
latex.DrawLatex(0.02,17.5**(1.66*log10(maxVal) - 0.5*log10(minVal)),"CMS #font[12]{preliminary}");
latex.DrawLatex(9.00,17.5**(1.67*log10(maxVal) - 0.5*log10(minVal)),"138 fb^{-1} (13 TeV)");

latex.SetTextSize(0.03)
latex.DrawLatex(1.5,30000,"p_{T} (#gamma) #in [200,250]");
latex.DrawLatex(5.5,30000,"p_{T} (#gamma) #in [250,350]");
latex.DrawLatex(9.5,30000,"p_{T} (#gamma) #in [350,Inf]");

c1.cd();
pad2 = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
pad2.SetTopMargin(0);
pad2.SetBottomMargin(0.2);
pad2.SetGridx();
pad2.Draw();
pad2.cd();

#h3 = stack.GetStack().Last().Clone("h3")
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

data_bin1=shapes.Get("muon_2016postVFP_500_700_postfit/data_obs")
data_bin2=shapes.Get("muon_2016postVFP_700_900_postfit/data_obs")
data_bin3=shapes.Get("muon_2016postVFP_900_Inf_postfit/data_obs")

bkg_bin1=shapes.Get("muon_2016postVFP_500_700_postfit/TotalSig")
bkg_bin2=shapes.Get("muon_2016postVFP_700_900_postfit/TotalSig")
bkg_bin3=shapes.Get("muon_2016postVFP_900_Inf_postfit/TotalSig")

for i in range(1,total_n_bins+1):

    if(i < 5):              errorband.SetBinError(i,data_bin1.GetBinError(i)/bkg_bin1.GetBinContent(i))
    if(i >=5 and i < 8):   errorband.SetBinError(i,data_bin2.GetBinError(i - 4)/bkg_bin2.GetBinContent(i-4))
    if(i==8):              errorband.SetBinError(i,data_bin2.GetBinError(4)/bkg_bin2.GetBinContent(4))
    if(i > 8 and i < 12):  errorband.SetBinError(i,data_bin3.GetBinError(i - 8)/bkg_bin3.GetBinContent(i-8))
    if(i==12):              errorband.SetBinError(i,data_bin3.GetBinError(4)/bkg_bin3.GetBinContent(4))


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

for i in range(1,total_n_bins+1):
    if(i < 5):              errorband2.SetBinError(i,4*math.sqrt(data_bin1.GetBinError(i)**2 + bkg_bin1.GetBinError(i)**2) /bkg_bin1.GetBinContent(i))
    if(i >=5 and i < 8):   errorband2.SetBinError(i,4*math.sqrt(data_bin2.GetBinError(i-4)**2+bkg_bin2.GetBinError(i-4)**2)/bkg_bin2.GetBinContent(i-4))
    if(i==8):              errorband2.SetBinError(i,4*math.sqrt(data_bin2.GetBinError(4)**2+bkg_bin2.GetBinError(4)**2)/bkg_bin2.GetBinContent(4))
    if(i > 8 and i < 12):  errorband2.SetBinError(i,4*math.sqrt(data_bin3.GetBinError(i-8)**2+bkg_bin3.GetBinError(i-8)**2)/bkg_bin3.GetBinContent(i-8))
    if(i==12):              errorband2.SetBinError(i,4*math.sqrt(data_bin3.GetBinError(4)**2+bkg_bin3.GetBinError(4)**2)/bkg_bin3.GetBinContent(4))
 
errorband2.Draw('e2,same')
errorband.Draw('e2,same')
h3.Draw("ep same");
c1.SaveAs("new_log.pdf")

