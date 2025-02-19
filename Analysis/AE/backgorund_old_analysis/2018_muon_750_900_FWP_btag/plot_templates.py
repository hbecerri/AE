#! /usr/bin/env python
from ROOT import *
import sys
import numpy

#'nominal'
#systematic_direction={'__pileup','__toptag','__mistoptag','__muID','__muTRK','__muHLT'}
#systematic_direction={'__csv_cferr1','__csv_cferr2','__csv_hf','__csv_hfstats1','__csv_hfstats2','__csv_jes','__csv_lf','__csv_lfstats1','__csv_lfstats2'}
#systematic_direction={'toppt_reweight','q2ttbar','muID','csv_jes','pileup','toptag','PDF','csv_lf','jer','jec','csv_hf','muHLT','csv_cferr1','mistoptag','csv_hfstats2','csv_hfstats1','csv_cferr2','csv_lfstats1','q2wjets','csv_lfstats2','muTKR'}
systematic_direction={'hdamp'}

#samplelist = {'singletop','Ttbar','qcd','wjets','dy'}
samplelist = {'Ttbar_1', 'Ttbar_2'}
fin = TFile('DeltaY.root', 'open')
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
                nominalhist[samp+syst] = fin.Get(samp+'_nominal')
                print 'systematc: ', syst
                canvas_Bkg[samp+syst] = TCanvas("SystVariation_"+samp+syst,"SystVariation_"+samp+syst,800,600)
                #            legend = TLegend(.54,.70,.99,.95)
                #                legend = TLegend(.34,.70,.99,.99)
                legend = TLegend(.70,.80,.9,.9)
                gStyle.SetOptStat(0)
                gStyle.SetOptTitle(0)
                
                #Upper plot will be in pad1
                pad1[samp+syst] = TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
                #            pad1.SetBottomMargin(0); # Upper and lower plot are joined
                pad1[samp+syst].SetBottomMargin(5); # Upper and lower plot are not joined
                pad1[samp+syst].SetGridx();         # Vertical grid
                pad1[samp+syst].Draw();             # Draw the upper pad: pad1
                pad1[samp+syst].cd();               # pad1 becomes the current pad
                
                
                systvarhist[samp+syst+'Up'] = fin.Get(samp+'_'+syst+'Up')
                print(systvarhist[samp+syst+'Up'])
                systvarhist[samp+syst+'Up'].Print()
                systvarhist[samp+syst+'Down'] = fin.Get(samp+'_'+syst+'Down')
                systvarhist[samp+syst+'Down'].Print()
                if systvarhist[samp+syst+'Up'] == None or systvarhist[samp+syst+'Down'] == None:
                    continue
                systvarhistDraw[samp+syst+'Up'] = systvarhist[samp+syst+'Up'].DrawClone('ep')
                systvarhistDraw[samp+syst+'Up'].GetXaxis().SetTitle("#Delta|y|")
#                systvarhistDraw[samp+syst+'Up'].GetXaxis().SetRangeUser(0,3000)
                
                systvarhistDraw[samp+syst+'Up'].SetMarkerColor(kRed)
#                systvarhistDraw[samp+syst+'Up'].SetMarkerStyle(21)
                systvarhistDraw[samp+syst+'Up'].SetLineColor(kRed)
                
                systvarhistDraw[samp+syst+'Down'] = systvarhist[samp+syst+'Down'].DrawClone('same')
                systvarhistDraw[samp+syst+'Down'].SetMarkerColor(kBlue)
#                systvarhistDraw[samp+syst+'Down'].SetMarkerStyle(21)
                systvarhistDraw[samp+syst+'Down'].SetLineColor(kBlue)
                
                nominalhistDraw[samp+syst] = nominalhist[samp+syst].DrawClone('same')
                nominalhistDraw[samp+syst].GetXaxis().SetTitle("#Delta|y|")
                nominalhistDraw[samp+syst].GetYaxis().SetRangeUser(0,10000)
                systvarhistDraw[samp+syst+'Up'].GetYaxis().SetRangeUser(0,10000)
                systvarhistDraw[samp+syst+'Down'].GetYaxis().SetRangeUser(0,10000)
                nominalhistDraw[samp+syst].SetMarkerStyle(20)
                nominalhistDraw[samp+syst].SetMarkerSize(1.5)
                nominalhistDraw[samp+syst].SetMarkerColor(kBlack)
                nominalhistDraw[samp+syst].SetLineColor(kBlack)
                
#                legend.AddEntry(nominalhistDraw[samp+sys],'nominal',"lp")
                legend.AddEntry(systvarhistDraw[samp+syst+'Up'],'Up','lp')
                legend.AddEntry(systvarhistDraw[samp+syst+'Down'],'Down','lp')
                legend.Draw()
                #lower plot will be in pad
                
                
                
                canvas_Bkg[samp+syst].cd();          # Go back to the main canvas before defining pad2
                pad2[samp+syst] = TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
                pad2[samp+syst].SetTopMargin(5);
                pad2[samp+syst].SetBottomMargin(5);
                pad2[samp+syst].SetGridx(); # vertical grid
                pad2[samp+syst].Draw();
                pad2[samp+syst].cd();      # pad2 becomes the current pad
                systvarhistRatio[samp+syst+'__plus__ratio']  = systvarhistDraw[samp+syst+'Up'].Clone(samp+syst+'Up_Ratio')
                systvarhistRatio[samp+syst+'__plus__ratio'].Divide(nominalhistDraw[samp+syst])
                systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.6,1.4)
                #                systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0.9,1.1)
                systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetNdivisions(5,5,0)
                systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetLabelSize(0.12)
                systvarhistRatio[samp+syst+'__plus__ratio'].GetXaxis().SetLabelSize(0.12)
                systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetTitle("Variation/Nominal")
                systvarhistRatio[samp+syst+'__plus__ratio'].GetXaxis().SetTitle("#Delta|y|")
                #systvarhistRatio[samp+syst+'__plus__ratio'].GetYaxis().SetRangeUser(0,10000)
                systvarhistRatio[samp+syst+'__plus__ratio'].SetMarkerStyle(1)
                systvarhistRatio[samp+syst+'__plus__ratio'].Draw('')
                #     systvarhistRatioDraw['Draw'+samp+syst+'__minus__ratio'] = systvarhistRatio[samp+syst+'__minus__ratio'].DrawClone('same')
                #     systvarhistRatioDraw['Draw'+samp+syst+'__minus__ratio'].SetMarkerStyle(1)
                
                
                systvarhistRatio[samp+syst+'__minus__ratio']  = systvarhistDraw[samp+syst+'Down'].Clone(samp+syst+'Down_Ratio')
                systvarhistRatio[samp+syst+'__minus__ratio'].Divide(nominalhistDraw[samp+syst])
                systvarhistRatio[samp+syst+'__minus__ratio'].SetMarkerStyle(1)
                systvarhistRatio[samp+syst+'__minus__ratio'].Draw('same')
                canvas_Bkg[samp+syst].SaveAs("SystVariation_"+samp+syst+'.pdf')
