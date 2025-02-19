#from ROOT import TFile, TLegend, TCanvas, TPad, THStack, TF1, TPaveText, TGaxis, SetOwnership, TObject, gStyle,TH1F
from ROOT import *
import os

import sys
from sys import argv
from optparse import OptionParser

from numpy import log10
from array import array
import math


padRatio = 0.25
padOverlap = 0.15

padGap = 0.01

plotDirectory = "data_pre_plots"

_fileDir ="/nfs/dust/cms/user/hugobg/analysis/electron"

gROOT.SetBatch(True)

YesLog = True
NoLog=False


# Histogram Information:
# [X-axis title, 
#  Y-axis title,
#  Rebinning factor,
#  [x-min,x-max], -1 means keep as is
#  Extra text about region
#  log plot]
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

#stackList = { "TTbar":[kRed], "DYJets":[kGreen], "QCD":[kYellow],"WJets":[kBlue], "ST":[kOrange], "Diboson":[kTeal]}
#stackList = { "TTToSemiLeptonic_2016postVFP_2":[kRed]} 
#stackList = {"TTToHadronic_2016postVFP":[kRed-3], "TTToOthers":[kRed+2], "TTToSemiLeptonic_2016postVFP":[kRed],"DYJetsToLL_M-50_HT_2016postVFP":[kBlue], "QCD_HT_2016postVFP":[kTeal], "WJetsToLNu_2016postVFP":[kGreen], "ST_2016postVFP":[kYellow], "WW_WZ_ZZ_2016postVFPv3":[kOrange]}
stackList = { "TTToOthers":[kRed+2],"TTToSemiLeptonic_2016postVFP":[kRed], "Others":[kBlue], "WJetsToLNu_2016postVFP":[kGreen]}

print stackList
#print stackList[2]



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



legendHeightPer = 0.04
legList = stackList.keys() 
#legList.reverse()

legendStart = 0.79
legendEnd = 0.97-(R/W)

#legend = TLegend(2*legendStart - legendEnd, 1-T/H-0.01 - legendHeightPer*(len(legList)+1), legendEnd, 0.99-(T/H)-0.01)
legend = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.), legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))
legend.SetNColumns(2)


legendR = TLegend(2*legendStart - legendEnd , 0.99 - (T/H)/(1.-padRatio+padOverlap) - 0.60*legendHeightPer/(1.-padRatio+padOverlap)*round((len(legList)+1)/2.)-0.1, legendEnd, 0.99-(T/H)/(1.-padRatio+padOverlap))

legendR.SetNColumns(1)

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


pad1 = TPad("zxc_p1","zxc_p1",0,padRatio-padOverlap,1,1)
pad2 = TPad("qwe_p2","qwe_p2",0,0,1,padRatio+padOverlap)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetTopMargin( T/H/(1-padRatio+padOverlap) )
pad1.SetBottomMargin( (padOverlap+padGap)/(1-padRatio+padOverlap) )
pad2.SetLeftMargin( L/W )
pad2.SetRightMargin( R/W )
pad2.SetTopMargin( (padOverlap)/(padRatio+padOverlap) )
pad2.SetBottomMargin( B/H/(padRatio+padOverlap) )
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
stack_up = THStack("hs","stack_up")
#SetOwnership(stack,True)
histName=argv[1]
sum_=0
tree_MC={}
tree_MC_up={}
hist={}
hist1_={}
hist1_up={} 
histo={}

histograms = {
              "M_tt": ["M_tt", "Events", 20, [0, 2000]], 
              "Boost_top_E": ["Boost_top_E", "Events", 25, [0,1200]],
              "Boost_top_eta": ["Boost_top_eta", "Events", 25, [-3,3]],
              "Boost_top_phi": ["Boost_top_phi", "Events", 25, [-3,3]],
              "Boost_top_pt": ["Boost_top_pt", "Events", 25, [0,1200]],
              "Boost_antitop_E": ["Boost_antitop_E", "Events", 25, [0,1200]],
              "Boost_antitop_eta": ["Boost_antitop_eta", "Events", 25, [-3,3]],
              "Boost_antitop_phi": ["Boost_antitop_phi", "Events", 25, [-3,3]],
              "Gen_Boost_antitop_pt": ["Gen_Boost_antitop_pt", "Events", 2, [0,2]],
              "Boost_Ak4_add_E": ["Boost_Ak4_add_E", "Events", 25, [0,1200]],
              "Boost_Ak4_add_eta": ["Boost_Ak4_add_eta", "Events", 25, [-3,3]],
              "Boost_Ak4_add_phi": ["Boost_Ak4_add_phi", "Events", 25, [-3,3]],
              "Boost_Ak4_add_pt": ["Boost_Ak4_add_pt", "Events", 25, [0,1200]],
} 

sample_names = ["DYJetsToLL_M-50_HT_2016postVFP"]

for sample in sample_names:
        	print sample, histName
		_file[sample] = TFile("/nfs/dust/cms/user/hugobg/analysis/electron///workdir_Analysis_UL16postVFP_electron_match/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL16postVFP_11.root","read")
		tree_MC[sample]=_file[sample].Get("AnalysisTree")
                tree_MC_up[sample]=_file[sample].Get("AnalysisTree")   
 	        tree_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Ele_pt > 80 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100)")
#                tree_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100)")
                hist1_[sample] = tree_MC[sample].GetHistogram()
                print(hist1_[sample].GetBinContent(1))
                print(hist1_[sample].GetBinContent(2))




