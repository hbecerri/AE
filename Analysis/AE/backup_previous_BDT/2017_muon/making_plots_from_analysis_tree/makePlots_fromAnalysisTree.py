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

_fileDir ="/data/dust/user/hugobg/analysis/muon"

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
#stackList = { "TTToSemiLeptonic_2017_2":[kRed]} 
#stackList = {"TTToHadronic_2017":[kRed-3], "TTToOthers":[kRed+2], "TTToSemiLeptonic_2017":[kRed],"DYJetsToLL_M-50_HT_2017":[kBlue], "QCD_HT_2017":[kTeal], "WJetsToLNu_2017":[kGreen], "ST_2017":[kYellow], "WW_WZ_ZZ_2017v3":[kOrange]}
stackList = { "TTToOthers":[kRed+2],"TTToSemiLeptonic_2017":[kRed], "Others":[kBlue], "WJetsToLNu_2017":[kGreen]}

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
              "Mu_eta": ["#eta (#mu)", "Events", 25, [-2.4,2.4]],
              "Mu_phi": ["#phi (#mu)", "Events", 25, [-3,3]],
              "Mu_pt": ["p_{T} (#mu)", "Events", 25, [55,500]],
              "N_Ak4": ["N_{jets}", "Events", 7, [3,10]],
              "antitop_m": ["m(#bar{t})", "Events", 24, [50, 300]],
              "top_m": ["m(t)", "Events", 24, [50, 300]],
              "chi2": ["#chi^2", "Events", 15, [0, 30]],
              "Ak4_j1_pt": ["j_{1}^{p_{T}}", "Events", 20, [150, 600]],
              "Ak4_j2_pt": ["j_{2}^{p_{T}}", "Events", 25, [50, 400]],
              "Ak4_j1_eta": ["j_{1}^{#eta}", "Events", 10, [-2.4, 2.4]],
              "Ak4_j2_eta": ["j_{2}^{#eta}", "Events", 10, [-2.4, 2.4]],
              "btagN": ["N_{jets}^{b}", "Events", 2, [1,5]],
} 

sample_names = ["TTTo2L2Nu_2017","TTToHadronic_2017","Diboson_2017","QCD_HT_2017","DYJetsToLL_M-50_HT_2017","ST_2017","WJetsToLNu_2017","TTToSemiLeptonic_2017"]

for sample in sample_names:
        	print sample, histName
		_file[sample] = TFile("%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample),"read")
        	print "%s/uhh2.AnalysisModuleRunner.MC.%s.root"%(_fileDir,sample)
		tree_MC[sample]=_file[sample].Get("AnalysisTree")
                tree_MC_up[sample]=_file[sample].Get("AnalysisTree")   
 	        tree_MC[sample].Draw("%s>>h2_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight*(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459)")
                hist1_[sample] = tree_MC[sample].GetHistogram()
 
                if(sample == "DYJetsToLL_M-50_HT_2017" or sample == "QCD_HT_2017" or sample == "ST_2017" or sample == "Diboson_2017"):
                    hist1_[sample].SetFillColor(stackList["Others"][0])
                    hist1_[sample].SetLineColor(stackList["Others"][0])
                    if(sample == "ST_2017"):
                        legendR.AddEntry(hist1_[sample],"Others",'f')

                else:
                    if(sample == "TTToSemiLeptonic_2017"):
                        legendR.AddEntry(hist1_[sample],"t#bar{t} (l+jets)",'f')
                        hist1_[sample].SetFillColor(stackList[sample][0])
                        hist1_[sample].SetLineColor(stackList[sample][0])
                    if(sample == "WJetsToLNu_2017"):
                        legendR.AddEntry(hist1_[sample],"W+jets",'f')
                        hist1_[sample].SetFillColor(stackList[sample][0])
                        hist1_[sample].SetLineColor(stackList[sample][0])
                    if("TTTo2" in sample):
                        legendR.AddEntry(hist1_[sample],"t#bar{t} (others)",'f')
                        hist1_[sample].SetFillColor(stackList["TTToOthers"][0])
                        hist1_[sample].SetLineColor(stackList["TTToOthers"][0])


                    hist1_[sample].SetYTitle(histograms[histName][1])
                stack.Add(hist1_[sample])

                tree_MC_up[sample].Draw("%s>>h3_%s(%i,%i,%f)"%(histName,sample,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"eventweight")
                hist1_up[sample] = tree_MC_up[sample].GetHistogram()
                stack_up.Add(hist1_up[sample])



_file["Data"] = TFile("%s/uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2017.root"%(_fileDir),"read")
print "%s/uhh2.AnalysisModuleRunner.DATA.DATA.root"%(_fileDir)

tree = _file["Data"].Get("AnalysisTree")
tree.Draw("%s>>dat_hist(%i,%i,%f)"%(histName,histograms[histName][2],histograms[histName][3][0],histograms[histName][3][1]),"1*(N_Ak4 >=3 && Mu_pt > 55.0 && DeepttagN <= 1 && btagN >= 1 && M_tt > 450 &&chi2 < 30 && Ak4_add_pt > 100 && angle_theta_opt > 0.25*3.1459 && angle_theta_opt < 0.55*3.1459)")
dataHist=tree.GetHistogram()
print "total:",dataHist.Integral()
print "bins:",dataHist.GetNbinsX()
data=dataHist.GetBinContent(1)
print data
dataHist.SetMarkerColor(kBlack)
dataHist.SetYTitle(histograms[histName][1])     
dataHist.Draw("pe,x0")
stack.Draw("HIST,SAME")

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

print "data, top:",dataHist.GetBinContent(1)

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
pad2.Draw()

pad1.cd()

pad1.SetLogy(log)

y2 = pad1.GetY2()

stack.Draw("HIST")


stack.GetXaxis().SetTitle('')
stack.GetYaxis().SetTitle(dataHist.GetYaxis().GetTitle())

stack.SetTitle('')
stack.GetXaxis().SetLabelSize(0)
stack.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(1.-padRatio+padOverlap))
stack.GetYaxis().SetTitle("Events")

dataHist.Draw("E,X0,SAME")

errorban.Draw("E2,SAME")

legendR.AddEntry(dataHist, "Data", 'pe')

ratio = dataHist.Clone("temp")
temp = stack.GetStack().Last().Clone("temp")

for i_bin in range(1,temp.GetNbinsX()+1):
       	temp.SetBinError(i_bin,0.)

ratio = dataHist.Clone("temp")
ratio.Divide(temp)
print ratio.GetNbinsX()
print ratio
print ratio.GetNbinsX()
ratio.SetTitle('')
histName=argv[1]
ratio.GetXaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetLabelSize(gStyle.GetLabelSize()/(padRatio+padOverlap))
ratio.GetXaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleSize(gStyle.GetTitleSize()/(padRatio+padOverlap))
ratio.GetYaxis().SetTitleOffset(gStyle.GetTitleYOffset()*(padRatio+padOverlap-padGap))
ratio.GetYaxis().SetRangeUser(0.5,1.5)
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



for i in range(1, errorband.GetNbinsX() + 1):
    if(errorban.GetBinContent(i) == 0):
        errorband.SetBinError(i,0)
    else:
        errorband.SetBinError(i, errorban.GetBinError(i)/errorban.GetBinContent(i))

errorband.Draw('e2,same')

#####

errorband2= stack.GetStack().Last().Clone("errorband2")
temp3     = stack.GetStack().Last().Clone("temp3")
errorband2.Sumw2()
errorband2.SetLineColor(kOrange)
errorband2.SetFillColor(kOrange)
errorband2.SetFillStyle(3001)
errorband2.SetMarkerSize(0)
errorband2.Divide(temp3)

syst_list=['JEC','JER','hdamp','top_pt_rew','pileup','muISO','muID','muHLT','toptag_corr','toptag_uncorr','FSR', 'ISR', 'MuR', 'MuF','MuR_MuF','btag_HF_corr','btag_LF_corr','btag_HF_unc17','btag_LF_unc17','BBEC1_2017','EC2_2017','RelativeSample_2017','Absolute_2017','HF','EC2','Absolute','RelativeBal','LHEPdfWeight_1','LHEPdfWeight_2','LHEPdfWeight_3','LHEPdfWeight_4','LHEPdfWeight_5','LHEPdfWeight_6','LHEPdfWeight_7','LHEPdfWeight_8','LHEPdfWeight_9','LHEPdfWeight_10','LHEPdfWeight_11','LHEPdfWeight_12','LHEPdfWeight_13','LHEPdfWeight_14','LHEPdfWeight_15','LHEPdfWeight_16','LHEPdfWeight_17','LHEPdfWeight_17','LHEPdfWeight_19','LHEPdfWeight_20','LHEPdfWeight_21','LHEPdfWeight_22','LHEPdfWeight_23','LHEPdfWeight_24','LHEPdfWeight_25','LHEPdfWeight_26','LHEPdfWeight_27','LHEPdfWeight_28','LHEPdfWeight_29','LHEPdfWeight_30','LHEPdfWeight_31','LHEPdfWeight_32','LHEPdfWeight_33','LHEPdfWeight_34','LHEPdfWeight_35','LHEPdfWeight_36','LHEPdfWeight_37','LHEPdfWeight_38','LHEPdfWeight_39','LHEPdfWeight_40','LHEPdfWeight_41','LHEPdfWeight_42','LHEPdfWeight_43','LHEPdfWeight_44','LHEPdfWeight_45','LHEPdfWeight_46','LHEPdfWeight_47','LHEPdfWeight_48','LHEPdfWeight_49','LHEPdfWeight_50','LHEPdfWeight_51','LHEPdfWeight_52','LHEPdfWeight_53','LHEPdfWeight_54','LHEPdfWeight_55','LHEPdfWeight_56','LHEPdfWeight_57','LHEPdfWeight_58','LHEPdfWeight_59','LHEPdfWeight_60','LHEPdfWeight_61','LHEPdfWeight_62','LHEPdfWeight_63','LHEPdfWeight_64','LHEPdfWeight_65','LHEPdfWeight_66','LHEPdfWeight_67','LHEPdfWeight_68','LHEPdfWeight_69','LHEPdfWeight_70','LHEPdfWeight_71','LHEPdfWeight_72','LHEPdfWeight_73','LHEPdfWeight_74','LHEPdfWeight_75','LHEPdfWeight_76','LHEPdfWeight_77','LHEPdfWeight_78','LHEPdfWeight_79','LHEPdfWeight_80','LHEPdfWeight_81','LHEPdfWeight_82','LHEPdfWeight_83','LHEPdfWeight_84','LHEPdfWeight_85','LHEPdfWeight_86','LHEPdfWeight_87','LHEPdfWeight_88','LHEPdfWeight_89','LHEPdfWeight_90','LHEPdfWeight_91','LHEPdfWeight_92','LHEPdfWeight_93','LHEPdfWeight_94','LHEPdfWeight_95','LHEPdfWeight_96','LHEPdfWeight_97','LHEPdfWeight_98','LHEPdfWeight_99']

b=[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
_file_syst = TFile("/data/dust/user/hugobg/UHH2_UL/CMSSW_10_6_28/src/UHH2/Analysis/AE/backup_previous_BDT/2017_muon/making_plots_from_analysis_tree/Mu_pt/Input_undfolding_data_%s.root"%(argv[1]),"read")
for name in syst_list:
    hi1 = _file_syst.Get('tttosemileptonic_'+name+'Up')
    if hi1:
        hi2 = _file_syst.Get('tttosemileptonic_nominal')
        a = []
        for i in range(1,hi2.GetNbinsX()+1):
            if(hi2.GetBinContent(i)==0): continue
            a.append(abs((hi2.GetBinContent(i) - hi1.GetBinContent(i)))/hi2.GetBinContent(i))
        for j in range(0,len(a)):
            b[j]=math.sqrt(b[j]*b[j] + a[j]*a[j])
    else:
        continue

print(b)

for i in range(1, errorband.GetNbinsX()+1):
        errorband2.SetBinError(i, math.sqrt(errorband.GetBinError(i)*errorband.GetBinError(i) + b[i-1]*b[i-1]))


errorband2.Draw('e2,same')
errorband.Draw('e2,same')


####

oneLine.Draw("same")
	
canvasRatio.Update()
canvasRatio.RedrawAxis()

histName=argv[1]

if log:
	canvasRatio.SaveAs("%s_new_log.pdf"%(histName))
else:
	canvasRatio.SaveAs("%s_new.pdf"%(histName))



