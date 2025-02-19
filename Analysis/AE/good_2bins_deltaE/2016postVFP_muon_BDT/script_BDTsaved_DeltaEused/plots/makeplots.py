#from ROOT import TFile, TLegend, TCanvas, TPad, THStack, TF1, TPaveText, TGaxis, SetOwnership, TObject, gStyle,TH1F
from ROOT import *
import os

import sys
from sys import *
from optparse import OptionParser

from numpy import log10
from array import array


padRatio = 0.25
padOverlap = 0.15

padGap = 0.01

plotDirectory = "data_pre_plots"

_fileDir ="/nfs/dust/cms/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AE/2016postVFP_muon/script/"

gROOT.SetBatch(True)

YesLog = True
NoLog=False


regionText ="loose selection"


import CMS_lumi

from Style import *
thestyle = Style()

HasCMSStyle = False
style = None
if os.path.isfile('tdrstyle.C'):
    ROOT.gROOT.ProcessLine('.L tdrstyle.C')
    ROOT.setTDRStyle()
    print "Found tdrstyle.C file, using this style."
    HasCMSStyle = True
    if os.path.isfile('CMSTopStyle.cc'):
        gROOT.ProcessLine('.L CMSTopStyle.cc+')
        style = CMSTopStyle()
        style.setupICHEPv1()
        print "Found CMSTopStyle.cc file, use TOP style if requested in xml file."
if not HasCMSStyle:
    print "Using default style defined in cuy package."
    thestyle.SetStyle()

ROOT.gROOT.ForceStyle()

stackList = {"TTToSemiLeptonic_1_nominal":[kRed], "TTToSemiLeptonic_2_nominal":[kRed], "wjetstolnu_nominal":[kGreen], "dyjetstoll_m-50_ht_nominal":[kYellow], "st_nominal":[kBlue], "qcd_ht_nominal":[kOrange], "diboson_nominal":[kTeal], "zgammatojjgamma_nominal":[kCyan+2], "wgtolnug_nominal":[kViolet], "gjets_int_nominal":[kRed-2]}
 
print stackList

_channelText = "#mu+jets"

CMS_lumi.channelText = _channelText
CMS_lumi.writeChannelText = True
CMS_lumi.writeExtraText = True


H = 600;
W = 800;


# references for T, B, L, R                                                                                                             
T = 0.08*H
B = 0.12*H
L = 0.12*W
R = 0.1*W


# SetOwnership(canvas, False)
# SetOwnership(canvasRatio, False)
# SetOwnership(pad1, False)
# SetOwnership(pad2, False)



legendHeightPer = 0.02
legList = stackList.keys()
#legList.reverse()

legendStart = 0.65
legendEnd = 0.97-(R/W)

legend = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.), legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))
legend.SetNColumns(2)


legendR = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(2)

legendR.SetBorderSize(0)
legendR.SetFillColor(0)



legend.SetBorderSize(0)
legend.SetFillColor(0)

_file = {}




canvas = TCanvas('c1','c1',W,H)
canvas.SetFillColor(0)
canvas.SetBorderMode(0)
canvas.SetFrameFillStyle(0)
canvas.SetFrameBorderMode(0)
canvas.SetLeftMargin( L/W )
canvas.SetRightMargin( R/W )
canvas.SetTopMargin( T/H )
canvas.SetBottomMargin( B/H )
canvas.SetTickx(0)

canvasRatio = TCanvas('c1Ratio','c1Ratio',W,H)
canvasRatio.SetFillColor(0)
canvasRatio.SetBorderMode(0)
canvasRatio.SetFrameFillStyle(0)
canvasRatio.SetFrameBorderMode(0)
canvasRatio.SetLeftMargin( L/W )
canvasRatio.SetRightMargin( R/W )
canvasRatio.SetTopMargin( T/H )
canvasRatio.SetBottomMargin( B/H )
canvasRatio.SetTickx(0)
canvasRatio.SetTicky(0)
canvasRatio.Draw()
canvasRatio.cd()


pad1 = TPad("zxc_p1","zxc_p1",0.035,padRatio-padOverlap,1,1)
#pad2 = TPad("qwe_p2","qwe_p2",0,0,1,padRatio+padOverlap)
pad2 = TPad("qwe_p2","qwe_p2",0,0.005,0.945,0.23)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetFrameFillStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetTickx(0)
pad1.SetTicky(0)

pad2.SetFillColor(0)
pad2.SetFillStyle(4000)
pad2.SetBorderMode(0)
pad2.SetFrameFillStyle(0)
pad2.SetFrameBorderMode(0)
pad2.SetTickx(0)
pad2.SetTicky(0)


canvasRatio.cd()
pad1.Draw()
pad2.Draw()


canvas.cd()


canvas.ResetDrawn()

stack = THStack("hs","stack")
#SetOwnership(stack,True)

histName=argv[1]


histograms = {
              "Delta_E": ["#Delta E", "Events", 2, [-2000, 2000]],
#              "Boost_top_E": ["Boost_top_E", "Events", 25, [0,1200]],
#              "Boost_top_eta": ["Boost_top_eta", "Events", 25, [-3,3]],
#              "Boost_top_phi": ["Boost_top_phi", "Events", 25, [-3,3]],
#              "Boost_top_pt": ["Boost_top_pt", "Events", 25, [0,1200]],
#              "Boost_antitop_E": ["Boost_antitop_E", "Events", 25, [0,1200]],
#              "Boost_antitop_eta": ["Boost_antitop_eta", "Events", 25, [-3,3]],
#              "Boost_antitop_phi": ["Boost_antitop_phi", "Events", 25, [-3,3]],
#              "Boost_antitop_pt": ["Boost_antitop_pt", "Events", 25, [0,1200]],
#              "Boost_Ak4_add_E": ["Boost_Ak4_add_E", "Events", 25, [0,1200]],
#              "Boost_Ak4_add_eta": ["Boost_Ak4_add_eta", "Events", 25, [-3,3]],
#              "Boost_Ak4_add_phi": ["Boost_Ak4_add_phi", "Events", 25, [-3,3]],
#              "Boost_Ak4_add_pt": ["Boost_Ak4_add_pt", "Events", 25, [0,1200]],
}


sample_names = ["wjetstolnu_nominal", "st_nominal",  "dyjetstoll_m-50_ht_nominal", "qcd_ht_nominal","TTToSemiLeptonic_1_nominal","TTToSemiLeptonic_2_nominal"]
#sample_names = ["wjetstolnu_nominal","st_nominal"]
legend_index = 0
_file = {}
sum_=0
tree_MC={}
tree2_MC={}
hist={}
hist1_={}
histo={}
for sample in sample_names:
    _file[sample] = TFile("../Input_undfolding_data_.root","read")
    hist1_[sample] = _file[sample].Get(sample)
    hist1_[sample].SetFillColor(stackList[sample][0])
    hist1_[sample].SetLineColor(stackList[sample][0])
    if(legend_index == 0): 
        if(sample == 'TTToSemiLeptonic_1_nominal') : legendR.AddEntry(hist1_[sample],'TTbar','f')
        if(sample == 'wjetstolnu_nominal') : legendR.AddEntry(hist1_[sample],'W + jets','f')
        if(sample == 'st_nominal') : legendR.AddEntry(hist1_[sample],'Single top','f')
        if(sample == 'dyjetstoll_m-50_ht_nominal') : legendR.AddEntry(hist1_[sample],'Drell-Yan','f')
        if(sample == 'qcd_ht_nominal') : legendR.AddEntry(hist1_[sample],'QCD','f')
        if(sample == 'diboson_nominal') : legendR.AddEntry(hist1_[sample],'Diboson','f')
    hist1_[sample].SetYTitle(histograms[histName][1])
    stack.Add(hist1_[sample])
_file["Data"] = TFile("../Input_undfolding_data_.root","read")
dataHist=_file["Data"].Get("data_obs")
data=dataHist.GetBinContent(1)
dataHist.SetMarkerColor(kBlack)
dataHist.SetYTitle(histograms[histName][1])

oneLine = TF1("oneline","1",-9e9,9e9)
oneLine.SetLineColor(kBlack)
oneLine.SetLineWidth(1)
oneLine.SetLineStyle(2)


maxVal =stack.GetMaximum()
minVal = 1
minVal = max(stack.GetStack()[0].GetMinimum(),1)

log=0
if log:
    stack.SetMaximum(10**(1.5*log10(maxVal) - 0.5*log10(minVal)))
else:
    stack.SetMaximum(1.85*maxVal)
stack.SetMinimum(minVal)

errorband=stack.GetStack().Last().Clone("error")
errorband.Sumw2()
errorband.SetLineColor(kBlack)
errorband.SetFillColor(kBlack)
errorband.SetFillStyle(3245)
errorband.SetMarkerSize(0)

canvas.Clear()
canvasRatio.cd()
canvasRatio.ResetDrawn()
canvasRatio.Draw()
canvasRatio.cd()

pad1.Draw()
pad2.Draw()

pad1.cd()
pad1.SetLogy(log)

y2 = pad1.GetY2()

stack.Draw("HIST")

stack.GetXaxis().SetTitle('')
stack.GetYaxis().SetTitle(dataHist.GetYaxis().GetTitle())
stack.SetMinimum(0.1)

stack.SetTitle('')
stack.GetXaxis().SetLabelSize(0.)
stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.-padRatio+padOverlap)/2)
stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap)/2)
stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap)*1.26)
stack.GetYaxis().SetTitle("Events")
stack.GetYaxis().SetMaxDigits(2);

dataHist.Draw("E,X0,SAME")
if(legend_index == 0):
    legendR.AddEntry(dataHist, "Data", 'pe')
ratio = dataHist.Clone("temp")
temp = stack.GetStack().Last().Clone("temp")
ratio.Divide(temp)
ratio.SetTitle('')
ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap)/2)
ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap)/2)
ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap)/2)
ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap)/2)
ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
ratio.GetYaxis().SetRangeUser(0.7,1.3)
ratio.GetYaxis().SetNdivisions(504)
ratio.GetXaxis().SetTitle(histograms[histName][0])
ratio.GetYaxis().SetTitle("Data/MC")
CMS_lumi.CMS_lumi(pad1, 4, 11)
legendR.Draw()
pad2.cd()
ratio.SetMarkerStyle(dataHist.GetMarkerStyle())
ratio.SetMarkerSize(dataHist.GetMarkerSize())
ratio.SetLineColor(dataHist.GetLineColor())
ratio.SetLineWidth(dataHist.GetLineWidth())
ratio.Draw('e,x0')
errorband.Divide(temp)
errorband.Draw('e2,same')
oneLine.Draw("same")

canvasRatio.Update()
canvasRatio.RedrawAxis()
if log:
    canvasRatio.SaveAs("%s_new_log.pdf"%(histName))
else:
    canvasRatio.SaveAs(argv[1]+'.pdf')
legend_index = legend_index + 1

