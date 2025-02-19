#! /usr/bin/env python
from ROOT import *
import sys
import numpy

#'nominal'
#systematic_direction={'__pileup','__toptag','__mistoptag','__muID','__muTRK','__muHLT'}
#systematic_direction={'__csv_cferr1','__csv_cferr2','__csv_hf','__csv_hfstats1','__csv_hfstats2','__csv_jes','__csv_lf','__csv_lfstats1','__csv_lfstats2'}
#systematic_direction={'toppt_reweight','q2ttbar','muID','csv_jes','pileup','toptag','PDF','csv_lf','jer','jec','csv_hf','muHLT','csv_cferr1','mistoptag','csv_hfstats2','csv_hfstats1','csv_cferr2','csv_lfstats1','q2wjets','csv_lfstats2','muTKR'}
systematic_direction={'muID','hfstats2','hfstats1'}

#samplelist = {'singletop','Ttbar','qcd','wjets','dy'}
samplelist = {'Ttbar'}
categories=['SR1T','SR0T','CR1']
fin = TFile('DeltaY_muon_3cat.root', 'open')
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

for cat in categories:
    for samp in samplelist:
        #        nominalhist[cat+samp] = fin.Get(cat+'/'+samp+'/nominal')
            #print "Number of events ", nominalhist[cat+samp].GetEntries()
            #        if(nominalhist[cat+samp].GetEntries()>0):
            for syst in systematic_direction:
                nominalhist[cat+samp+syst] = fin.Get(cat+'/'+samp+'/nominal')
                print 'systematc: ', syst
                canvas_Bkg[cat+samp+syst] = TCanvas("SystVariation_"+cat+samp+syst,"SystVariation_"+cat+samp+syst,800,600)
                #            legend = TLegend(.54,.70,.99,.95)
                #                legend = TLegend(.34,.70,.99,.99)
                legend = TLegend(.50,.70,.99,.99)
                gStyle.SetOptStat(0)
                gStyle.SetOptTitle(0)
                
                #Upper plot will be in pad1
                pad1[cat+samp+syst] = TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
                #            pad1.SetBottomMargin(0); # Upper and lower plot are joined
                pad1[cat+samp+syst].SetBottomMargin(5); # Upper and lower plot are not joined
                pad1[cat+samp+syst].SetGridx();         # Vertical grid
                pad1[cat+samp+syst].Draw();             # Draw the upper pad: pad1
                pad1[cat+samp+syst].cd();               # pad1 becomes the current pad
                
                
                systvarhist[cat+samp+syst+'Up'] = fin.Get(cat+'/'+samp+'/'+syst+'Up')
                print(systvarhist[cat+samp+syst+'Up'])
                systvarhist[cat+samp+syst+'Up'].Print()
                systvarhist[cat+samp+syst+'Down'] = fin.Get(cat+'/'+samp+'/'+syst+'Down')
                systvarhist[cat+samp+syst+'Down'].Print()
                if systvarhist[cat+samp+syst+'Up'] == None or systvarhist[cat+samp+syst+'Down'] == None:
                    continue
                systvarhistDraw[cat+samp+syst+'Up'] = systvarhist[cat+samp+syst+'Up'].DrawClone('ep')
                systvarhistDraw[cat+samp+syst+'Up'].GetXaxis().SetTitle("M_{ttbar}, GeV")
#                systvarhistDraw[cat+samp+syst+'Up'].GetXaxis().SetRangeUser(0,3000)
                
                systvarhistDraw[cat+samp+syst+'Up'].SetMarkerColor(kRed)
                systvarhistDraw[cat+samp+syst+'Up'].SetMarkerStyle(21)
                systvarhistDraw[cat+samp+syst+'Up'].SetLineColor(kRed)
                
                systvarhistDraw[cat+samp+syst+'Down'] = systvarhist[cat+samp+syst+'Down'].DrawClone('same')
                systvarhistDraw[cat+samp+syst+'Down'].SetMarkerColor(kBlue)
                systvarhistDraw[cat+samp+syst+'Down'].SetMarkerStyle(21)
                systvarhistDraw[cat+samp+syst+'Down'].SetLineColor(kBlue)
                
                nominalhistDraw[cat+samp+syst] = nominalhist[cat+samp+syst].DrawClone('same')
                nominalhistDraw[cat+samp+syst].GetXaxis().SetTitle("M_{ttbar}, GeV")
                nominalhistDraw[cat+samp+syst].SetMarkerStyle(20)
                nominalhistDraw[cat+samp+syst].SetMarkerSize(1.5)
                nominalhistDraw[cat+samp+syst].SetMarkerColor(kBlack)
                nominalhistDraw[cat+samp+syst].SetLineColor(kBlack)
                
                #legend.AddEntry(nominalhistDraw[cat+samp+sys],cat+samp+'nominal',"lp")
                #legend.AddEntry(systvarhistDraw[cat+samp+syst+'Up'],syst+'Up','lp')
                #legend.AddEntry(systvarhistDraw[cat+samp+syst+'Down'],syst+'Down','lp')
                #legend.Draw()
                #lower plot will be in pad
                
                
                
                canvas_Bkg[cat+samp+syst].cd();          # Go back to the main canvas before defining pad2
                pad2[cat+samp+syst] = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
                pad2[cat+samp+syst].SetTopMargin(5);
                pad2[cat+samp+syst].SetBottomMargin(5);
                pad2[cat+samp+syst].SetGridx(); # vertical grid
                pad2[cat+samp+syst].Draw();
                pad2[cat+samp+syst].cd();      # pad2 becomes the current pad
                systvarhistRatio[cat+samp+syst+'__plus__ratio']  = systvarhistDraw[cat+samp+syst+'Up'].Clone(cat+samp+syst+'Up_Ratio')
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].Divide(nominalhistDraw[cat+samp+syst])
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.6,1.4)
                #                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.9,1.1)
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetYaxis().SetNdivisions(5,5,0)
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetYaxis().SetLabelSize(0.12)
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetXaxis().SetLabelSize(0.12)
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetYaxis().SetTitle("Variation/Nominal")
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].GetXaxis().SetTitle("M$_{ttbar}$, GeV")
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].SetMarkerStyle(1)
                systvarhistRatio[cat+samp+syst+'__plus__ratio'].Draw('l')
                #     systvarhistRatioDraw['Draw'+cat+samp+syst+'__minus__ratio'] = systvarhistRatio[cat+samp+syst+'__minus__ratio'].DrawClone('same')
                #     systvarhistRatioDraw['Draw'+cat+samp+syst+'__minus__ratio'].SetMarkerStyle(1)
                
                
                systvarhistRatio[cat+samp+syst+'__minus__ratio']  = systvarhistDraw[cat+samp+syst+'Down'].Clone(cat+samp+syst+'Down_Ratio')
                systvarhistRatio[cat+samp+syst+'__minus__ratio'].Divide(nominalhistDraw[cat+samp+syst])
                systvarhistRatio[cat+samp+syst+'__minus__ratio'].SetMarkerStyle(1)
                systvarhistRatio[cat+samp+syst+'__minus__ratio'].Draw('same')
                canvas_Bkg[cat+samp+syst].SaveAs("SystVariation_"+cat+samp+syst+'.pdf')
