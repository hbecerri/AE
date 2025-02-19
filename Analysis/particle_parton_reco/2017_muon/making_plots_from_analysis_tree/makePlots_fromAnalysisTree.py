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

_fileDir ="/nfs/dust/cms/user/hugobg/analysis/muon///workdir_Analysis_UL17_muon/"

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

stackList = { "TTToOthers":[kRed+2],"TToSemiLeptonic_UL16postVFP_11":[kRed], "Others1":[kBlue], "Others2":[kRed],"WJetsToLNu_2016postVFP":[kGreen]}

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
#pad2 = TPad("qwe_p2","qwe_p2",0,0,1,padRatio+padOverlap)
pad1.SetLeftMargin( L/W )
pad1.SetRightMargin( R/W )
pad1.SetTopMargin( T/H/(1-padRatio+padOverlap) )
pad1.SetBottomMargin( (padOverlap+padGap)/(1-padRatio+padOverlap) )
#pad2.SetLeftMargin( L/W )
#pad2.SetRightMargin( R/W )
#pad2.SetTopMargin( (padOverlap)/(padRatio+padOverlap) )
#pad2.SetBottomMargin( B/H/(padRatio+padOverlap) )
pad1.SetFillColor(0)
pad1.SetBorderMode(0)
pad1.SetFrameFillStyle(0)
pad1.SetFrameBorderMode(0)
pad1.SetTickx(0)
pad1.SetTicky(0)

#pad2.SetFillColor(0)
#pad2.SetFillStyle(4000)
#pad2.SetBorderMode(0)
#pad2.SetFrameFillStyle(0)
#pad2.SetFrameBorderMode(0)
#pad2.SetTickx(0)
#pad2.SetTicky(0)


canvasRatio.cd()
pad1.Draw()
#pad2.Draw()


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
              "M_tt": ["M_tt", "Events", 20, [500, 2000]], 
              "Boost_top_E": ["Boost_top_E", "Events", 25, [0,1200]],
              "Boost_top_eta": ["Boost_top_eta", "Events", 25, [-3,3]],
              "Boost_top_phi": ["Boost_top_phi", "Events", 25, [-3,3]],
              "Boost_top_pt": ["Boost_top_pt", "Events", 25, [0,1200]],
              "Boost_antitop_E": ["Boost_antitop_E", "Events", 25, [0,1200]],
              "Boost_antitop_eta": ["Boost_antitop_eta", "Events", 25, [-3,3]],
              "Boost_antitop_phi": ["Boost_antitop_phi", "Events", 25, [-3,3]],
              "Boost_antitop_pt": ["Boost_antitop_pt", "Events", 25, [0,1200]],
              "Boost_Ak4_add_E": ["Boost_Ak4_add_E", "Events", 25, [0,1200]],
              "Boost_Ak4_add_eta": ["Boost_Ak4_add_eta", "Events", 25, [-3,3]],
              "Boost_Ak4_add_phi": ["Boost_Ak4_add_phi", "Events", 25, [-3,3]],
              "Boost_Ak4_add_pt": ["Boost_Ak4_add_pt", "Events", 25, [0,1200]],
              "top_pt": ["p_{T}(t)", "Events", 25, [0,1000]],
              "antitop_pt": ["p_{T}(#bar{t})", "Events", 25, [0,1000]],
              "MET_pt": ["MET", "Events", 25, [50,500]],
              "Ele_E": ["E (e)", "Events", 25, [0,1200]],
              "Ele_eta": ["#eta (e)", "Events", 25, [-3,3]],
              "Ele_phi": ["#phi (e)", "Events", 25, [-3,3]],
              "Ele_pt": ["p_{T} (e)", "Events", 25, [80,800]],
              "Mu_E": ["E (#mu)", "Events", 25, [0,1200]],
              "Mu_eta": ["#eta (#mu)", "Events", 25, [-3,3]],
              "Mu_phi": ["#phi (#mu)", "Events", 25, [-3,3]],
              "h_th_newgen_m": ["p_{T} (#mu)", "Events", 25, [50,500]],
              "h_tl_newgen_m": ["p_{T} (#mu)", "Events", 25, [50,500]],
              "newgentop_m": ["p_{T} (#mu)", "Events", 25, [0,1000]],
              "newgenantitop_m": ["p_{T} (#mu)", "Events", 25, [0,1000]],
              "N_Ak4": ["N_{jets}", "Events", 7, [3,10]],
              "antitop_m": ["M_tt", "Events", 40, [100, 500]],
              "top_m": ["M_tt", "Events", 40, [100, 500]],
              
} 

integral1 = 1
integral2 = 1
sample_names = ["TTToSemiLeptonic_UL17_11","TTToSemiLeptonic_UL17_13","TTToSemiLeptonic_UL17_14","TTToSemiLeptonic_UL17_15","TTToSemiLeptonic_UL17_12"]
 
for sample in sample_names:
        	print sample, histName
		_file[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
        	print "%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample)
		tree_MC[sample]=_file[sample].Get("AnalysisTree")
                tree_MC_up[sample]=_file[sample].Get("AnalysisTree")   
 
                if("12" in sample):
                    tree_MC[sample].Draw("top_m>>h2_%s(%i,%i,%f)"%(sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2 && h_parton_rec == -1)")
                if("13" in sample):
                    tree_MC[sample].Draw("top_m>>h2_%s(%i,%i,%f)"%(sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2 && h_parton_rec == 2)")
                if("14" in sample):
                    tree_MC[sample].Draw("top_m>>h2_%s(%i,%i,%f)"%(sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2 && h_parton_rec == 3)")
                if("15" in sample):
                    tree_MC[sample].Draw("top_m>>h2_%s(%i,%i,%f)"%(sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2 && h_parton_rec == 4)")           
                if("11" in sample):
                    tree_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2 && h_parton_rec == 1)") 
 
                hist1_[sample] = tree_MC[sample].GetHistogram()

                if(sample == "DYJetsToLL_M-50_HT_2016postVFP" or sample == "QCD_HT_2016postVFP" or sample == "ST_2016postVFP"):
                    hist1_[sample].SetFillColor(stackList["Others"][0])
                    hist1_[sample].SetLineColor(stackList["Others"][0])
                    if(sample == "ST_2016postVFP"):
                        legendR.AddEntry(hist1_[sample],"Others",'f')

                else:
                    if("11" in sample):
                        hist1_[sample].SetFillColor(stackList["Others2"][0])
                    if("13" in sample):
                        hist1_[sample].SetFillColor(kGreen)
                    if("14" in sample):
                        hist1_[sample].SetFillColor(kYellow)
                    if("15" in sample):
                        hist1_[sample].SetFillColor(kGreen)
                    if("12" in sample):
                        hist1_[sample].SetLineColor(stackList["Others1"][0])
#                    if(sample == "TTToSemiLeptonic_UL16postVFP_11"):
#                        legendR.AddEntry(hist1_[sample],"Parton-level reco",'f')
#                    if(sample == "TTToSemiLeptonic_UL16postVFP_12"):
#                        legendR.AddEntry(hist1_[sample],"Particle-level reco",'f')
#                    if(sample == "WJetsToLNu_2016postVFP"):
#                        legendR.AddEntry(hist1_[sample],"W+jets",'f')
#                    if(sample == "TTToOthers"):
#                        legendR.AddEntry(hist1_[sample],"t#bar{t} (others)",'f')



                    hist1_[sample].SetYTitle(histograms[histName][1])
                stack.Add(hist1_[sample])

                tree_MC_up[sample].Draw("%s>>h3_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight")
                hist1_up[sample] = tree_MC_up[sample].GetHistogram()
                stack_up.Add(hist1_up[sample])



#_file["Data"] = TFile("%s/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016postVFP.root"%(_fileDir),"read")
#print "%s/uhh2.AnalysisModuleRunner.DATA.DATA.root"%(_fileDir)

#tree = _file["Data"].Get("AnalysisTree")
#tree.Draw("%s>>dat_hist(%i,%i,%f)"%(histName,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"1*(Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 500 && chi2 < 30 && Ak4_add_pt > 100 && N_Ak4 > 2)")
#dataHist=tree.GetHistogram()
#print "total:",dataHist.Integral()
#print "bins:",dataHist.GetNbinsX()
#data=dataHist.GetBinContent(1)
#print data
#dataHist.SetMarkerColor(kBlack)
#dataHist.SetYTitle(histograms[histName][1])     
#dataHist.Draw("pe,x0")
total_integral = 0 
for hist in stack.GetHists():
    total_integral += hist.Integral()
normalized_stack = ROOT.THStack("normalized_stack", "Normalized Stacked Histograms")
intt = 0
for hist in stack.GetHists():
    normalized_hist = hist.Clone()
    integral = normalized_hist.Integral()
    if integral != 0:
        normalized_hist.Scale(1.0 /total_integral)
        if (intt==4): legendR.AddEntry(normalized_hist,"Particle-level reco",'f')
        if (intt==0):  legendR.AddEntry(normalized_hist,"Parton-level reco (no-lepton)",'f')
        if (intt==2):  legendR.AddEntry(normalized_hist,"Parton-level reco (no-b_jets)",'f')
        if (intt==3):  legendR.AddEntry(normalized_hist,"Parton-level reco (no-Ak4_jets)",'f')
    normalized_stack.Add(normalized_hist) 
    print(normalized_hist.Integral())
    intt+=1 
 
normalized_stack.Draw("HIST,SAME")
canvas.Clear()
canvasRatio.cd()
canvasRatio.ResetDrawn()
canvasRatio.Draw()
canvasRatio.cd()
pad1.Draw()
normalized_stack.Draw("HIST")
legendR.Draw("SAME")
canvasRatio.SaveAs("%s_new.pdf"%(histName))


'''
syst_up=stack_up.GetStack().Last().Clone("syst_up")
errorban=stack.GetStack().Last().Clone("errorban")
errorban.Sumw2()
errorban.SetLineColor(kGray+2)
errorban.SetFillColor(kGray+2)
errorban.SetFillStyle(3245)
errorban.SetMarkerSize(0)

#for jj in range(1,errorban.GetNbinsX() + 1):
#	errorban.SetBinError(jj, math.sqrt(errorban.GetBinError(jj)*errorban.GetBinError(jj) + (syst_up.GetBinContent(jj) - errorban.GetBinContent(jj))*(syst_up.GetBinContent(jj) - errorban.GetBinContent(jj))))
#        print((syst_up.GetBinContent(jj) - errorban.GetBinContent(jj)))
errorban.Draw("E2,SAME")

oneLine = TF1("oneline","1",-9e9,9e9)
oneLine.SetLineColor(kBlack)
oneLine.SetLineWidth(1)
oneLine.SetLineStyle(2)
	

maxVal =stack.GetMaximum()
minVal = 1
minVal = max(stack.GetStack()[0].GetMinimum(),1)
print minVal, maxVal

#print "data, top:",dataHist.GetBinContent(1)

print "max stack:",1.5*maxVal
log=0
if log:
	stack.SetMaximum(10**(1.5*log10(maxVal) - 0.5*log10(minVal)))
else:
	stack.SetMaximum(1.7*maxVal)
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
#pad2.Draw()

pad1.cd()

pad1.SetLogy(log)

y2 = pad1.GetY2()

stack.Draw("HIST")


stack.GetXaxis().SetTitle('')
#stack.GetYaxis().SetTitle(dataHist.GetYaxis().GetTitle())

stack.SetTitle('')
stack.GetXaxis().SetLabelSize(0)
stack.GetYaxis().SetLabelSize(0.9*gStyle.GetLabelSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleSize(0.9*gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitle("Events")

#dataHist.Draw("E,X0,SAME")

errorban.Draw("E2,SAME")

#legendR.AddEntry(dataHist, "Data", 'pe')

##ratio = dataHist.Clone("temp")
#temp = stack.GetStack().Last().Clone("temp")

#for i_bin in range(1,temp.GetNbinsX()+1):
#       	temp.SetBinError(i_bin,0.)

#ratio = dataHist.Clone("temp")
#ratio.Divide(temp)
#print ratio.GetNbinsX()
#print ratio
#print ratio.GetNbinsX()
#ratio.SetTitle('')
histName=argv[1]
#ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
#ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
#ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
#ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
#ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
#ratio.GetYaxis().SetRangeUser(0.8,1.2)
#ratio.GetYaxis().SetNdivisions(504)
#ratio.GetXaxis().SetTitle(histograms[histName][0])
#ratio.GetYaxis().SetTitle("Data/MC")
CMS_lumi.CMS_lumi(pad1, 4, 11)
legendR.Draw()
#pad2.cd()
#ratio.SetMarkerStyle(dataHist.GetMarkerStyle())
#ratio.SetMarkerSize(dataHist.GetMarkerSize())
#ratio.SetLineColor(dataHist.GetLineColor())
#ratio.SetLineWidth(dataHist.GetLineWidth())
#ratio.Draw('e,x0')
#errorband.Divide(temp)



#for i in range(1, errorband.GetNbinsX() + 1):
#    if(errorban.GetBinContent(i) == 0):
#        errorband.SetBinError(i,0)
#    else:
#        errorband.SetBinError(i, errorban.GetBinError(i)/errorban.GetBinContent(i))

#errorband.Draw('e2,same')


oneLine.Draw("same")
	
canvasRatio.Update()
canvasRatio.RedrawAxis()

histName=argv[1]

if log:
	canvasRatio.SaveAs("%s_new_log.pdf"%(histName))
else:
	canvasRatio.SaveAs("%s_new.pdf"%(histName))


'''
