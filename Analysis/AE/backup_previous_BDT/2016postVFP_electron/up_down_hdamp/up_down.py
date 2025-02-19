#! /usr/bin/env python
from ROOT import *
import ROOT
import sys
import numpy
from sys import argv
import re

systematic_direction={argv[1]}
samplelist = {'TTToSemiLeptonic_1','TTToSemiLeptonic_2'}
fin = TFile('../script/Input_undfolding_data_all.root', 'open')
fin2 = TFile('../script/Input_undfolding_data_jes.root', 'open')
nominalhist = {}
nominalhistDraw = {}
systvarhist = {}
systvarhistDraw = {}
systvarhistRatio = {}
systvarhistRatioDraw = {}
canvas_Bkg = {}
pad1 = {}
pad2 = {}
gROOT.SetBatch(kTRUE)

for samp in samplelist:
    for syst in systematic_direction:
        print syst
        if((syst == 'FSR' or syst == 'ISR' or syst == 'jec' or syst == 'jer' or syst == 'q2' or syst == 'pdf') and ('TTToSemiLeptonic' not in samp)):
            continue 
        nominalhist[samp+syst] = fin.Get(samp+'_nominal')
        canvas_Bkg[samp+syst] = TCanvas("SystVariation_"+samp+syst,"SystVariation_"+samp+syst,800,600)
        legend = TLegend(.7,.70,.9,.9)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
                
        #Upper plot will be in pad1
        pad1[samp+syst] = TPad("pad1", "pad1", 0., 0.25, 1., 1.);
        #pad1.SetBottomMargin(0) # Upper and lower plot are joined
        pad1[samp+syst].SetBottomMargin(5); # Upper and lower plot are not joined
        pad1[samp+syst].SetGridx();         # Vertical grid
        pad1[samp+syst].Draw();             # Draw the upper pad: pad1
        pad1[samp+syst].cd();               # pad1 becomes the current pad
                
        systvarhist[samp+syst+'Up'] = fin.Get(samp+'_'+syst+'Up')
        print(systvarhist[samp+syst+'Up'])
        systvarhist[samp+syst+'Up'].Print()
        systvarhist[samp+syst+'Down'] = fin.Get(samp+'_'+syst+'Down')
        systvarhist[samp+syst+'Down'].Print()
        systvarhist[samp+syst+'Up2'] = fin2.Get(samp+'_'+syst+'Up')
        systvarhist[samp+syst+'Down2'] = fin2.Get(samp+'_'+syst+'Down')

        for i in range(1, systvarhist[samp+syst+'Up2'].GetNbinsX() + 1):
            systvarhist[samp+syst+'Up2'].SetBinError(i,systvarhist[samp+syst+'Up2'].GetBinError(i)*3)
            systvarhist[samp+syst+'Down2'].SetBinError(i,systvarhist[samp+syst+'Down2'].GetBinError(i)*3)
            print(systvarhist[samp+syst+'Up2'].GetBinError(i))
            print(systvarhist[samp+syst+'Down2'].GetBinError(i))

        systvarhistDraw[samp+syst+'Up'] = systvarhist[samp+syst+'Up'].DrawClone('ep')
        a = systvarhist[samp+syst+'Up'].GetMaximum()
        systvarhistDraw[samp+syst+'Up'].GetYaxis().SetRangeUser(0,a*1.5)
        systvarhistDraw[samp+syst+'Up'].GetXaxis().SetLabelSize(0);
        systvarhistDraw[samp+syst+'Up'].SetMarkerColor(kRed)
        systvarhistDraw[samp+syst+'Up'].SetMarkerStyle(21)
        systvarhistDraw[samp+syst+'Up'].SetLineColor(kRed)

        systvarhistDraw[samp+syst+'Up2'] = systvarhist[samp+syst+'Up2'].DrawClone('e same')
        systvarhistDraw[samp+syst+'Up2'].SetMarkerColor(kRed-5)
        systvarhistDraw[samp+syst+'Up2'].SetMarkerStyle(22)
        systvarhistDraw[samp+syst+'Up2'].SetLineColor(kRed-5)

        systvarhistDraw[samp+syst+'Down2'] = systvarhist[samp+syst+'Down2'].DrawClone('e same')
        systvarhistDraw[samp+syst+'Down2'].SetMarkerColor(kBlue-5)
        systvarhistDraw[samp+syst+'Down2'].SetMarkerStyle(22)
        systvarhistDraw[samp+syst+'Down2'].SetLineColor(kBlue-5)
                
        systvarhistDraw[samp+syst+'Down'] = systvarhist[samp+syst+'Down'].DrawClone('same')
        systvarhistDraw[samp+syst+'Down'].SetMarkerColor(kBlue)
        systvarhistDraw[samp+syst+'Down'].SetMarkerStyle(21)
        systvarhistDraw[samp+syst+'Down'].SetLineColor(kBlue)
                
        legend.AddEntry(systvarhistDraw[samp+syst+'Up'],syst+'Up','lp')
        legend.AddEntry(systvarhistDraw[samp+syst+'Down'],syst+'Down','lp')
        legend.AddEntry(systvarhistDraw[samp+syst+'Up2'],'MC Up','lp')
        legend.AddEntry(systvarhistDraw[samp+syst+'Down2'],'MC Down','lp')
        legend.Draw()

        latex = ROOT.TLatex()
        latex.SetTextSize(0.045)
        latex.SetTextAlign(11)
        latex.DrawLatex(-1950,a*1.52,"Work in progress")

        latex2 = ROOT.TLatex()
        latex2.SetTextSize(0.045)
        latex2.SetTextAlign(11)
        #if('2017' in argv[1]):  latex2.DrawLatex(1000,a*1.52,"41.51 fb^{-1} (13 TeV)")
        #if('pre' in argv[1]):   latex2.DrawLatex(1000,a*1.52,"19.52 fb^{-1} (13 TeV)")
        latex2.DrawLatex(1000,a*1.52,"16.81 fb^{-1} (13 TeV)")

                
        canvas_Bkg[samp+syst].cd();          # Go back to the main canvas before defining pad2
        pad2[samp+syst] = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
        pad2[samp+syst].SetTopMargin(5);
        pad2[samp+syst].SetBottomMargin(5);
        pad2[samp+syst].SetGridx(); # vertical grid
        pad2[samp+syst].Draw();
        pad2[samp+syst].cd();      # pad2 becomes the current pad
        systvarhistRatio[samp+syst+'__plus__ratio']  = systvarhistDraw[samp+syst+'Up'].Clone(samp+syst+'Up_Ratio')
        systvarhistRatio[samp+syst+'__plus__ratio'].Divide(systvarhistDraw[samp+syst+'Up2'])
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.75,1.25)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetTitleSize(0.6)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetNdivisions(5,5,0)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetLabelSize(0.12)
        systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetTitle("Variation/Nominal")
        systvarhistRatio[samp+syst+'__plus__ratio'].GetXaxis().SetTitle("")
        systvarhistRatio[samp+syst+'__plus__ratio'].SetMarkerStyle(1)
        systvarhistRatio[samp+syst+'__plus__ratio'].Draw('l')
        systvarhistRatio[samp+syst+'__minus__ratio']  = systvarhistDraw[samp+syst+'Down'].Clone(samp+syst+'Down_Ratio')
        systvarhistRatio[samp+syst+'__minus__ratio'].Divide(systvarhistDraw[samp+syst+'Down2'])
        systvarhistRatio[samp+syst+'__minus__ratio'].SetMarkerStyle(1)
        systvarhistRatio[samp+syst+'__minus__ratio'].Draw('same')

        oneLine = TF1("oneline","1",-9e9,9e9)
        oneLine.SetLineColor(kBlack)
        oneLine.SetLineWidth(1)
        oneLine.SetLineStyle(2)
        oneLine.Draw("same")
 
        #argv[1] = s = re.sub(r"[-()\"#/@;:<>{}`+=~|.!?,]", "", argv[1])
   
        canvas_Bkg[samp+syst].SaveAs(samp+syst+'_2016postelectron.pdf')
