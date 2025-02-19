from ROOT import *
import os
import sys
from sys import *
from optparse import OptionParser

from numpy import log10
from array import array
import math

gStyle.SetOptStat(0)

_file  = TFile("shapes.root","read")
 
h1 = _file.Get("gamma_all_SR_2018_SR_bin1_2018_prefit/EWK_ajj_1")
h2 = _file.Get("gamma_all_SR_2017_SR_bin1_2017_prefit/EWK_ajj_1") 
h3 = _file.Get("gamma_all_SR_2016_SR_bin1_2016_prefit/EWK_ajj_1")
h4 = _file.Get("gamma_all_SR_2016pre_SR_bin1_2016pre_prefit/EWK_ajj_1") 

h5 = _file.Get("gamma_all_SR_2018_SR_bin2_2018_prefit/EWK_ajj_1")
h6 = _file.Get("gamma_all_SR_2017_SR_bin2_2017_prefit/EWK_ajj_1") 
h7 = _file.Get("gamma_all_SR_2016_SR_bin2_2016_prefit/EWK_ajj_1")
h8 = _file.Get("gamma_all_SR_2016pre_SR_bin2_2016pre_prefit/EWK_ajj_1")

h9 = _file.Get("gamma_all_SR_2018_SR_bin3_2018_prefit/EWK_ajj_1")
h10 = _file.Get("gamma_all_SR_2017_SR_bin3_2017_prefit/EWK_ajj_1") 
h11 = _file.Get("gamma_all_SR_2016_SR_bin3_2016_prefit/EWK_ajj_1")
h12 = _file.Get("gamma_all_SR_2016pre_SR_bin3_2016pre_prefit/EWK_ajj_1")

h13 = _file.Get("gamma_all_SR_2018_SR_bin4_2018_prefit/EWK_ajj_1")
h14 = _file.Get("gamma_all_SR_2017_SR_bin4_2017_prefit/EWK_ajj_1")
h15 = _file.Get("gamma_all_SR_2016_SR_bin4_2016_prefit/EWK_ajj_1")
h16 = _file.Get("gamma_all_SR_2016pre_SR_bin4_2016pre_prefit/EWK_ajj_1")
 
###############

h17 = _file.Get("gamma_all_SR_2018_SR_bin1_2018_prefit/EWK_ajj_2")
h18 = _file.Get("gamma_all_SR_2017_SR_bin1_2017_prefit/EWK_ajj_2")
h19 = _file.Get("gamma_all_SR_2016_SR_bin1_2016_prefit/EWK_ajj_2")
h20 = _file.Get("gamma_all_SR_2016pre_SR_bin1_2016pre_prefit/EWK_ajj_2")

h21 = _file.Get("gamma_all_SR_2018_SR_bin2_2018_prefit/EWK_ajj_2")
h22 = _file.Get("gamma_all_SR_2017_SR_bin2_2017_prefit/EWK_ajj_2")
h23 = _file.Get("gamma_all_SR_2016_SR_bin2_2016_prefit/EWK_ajj_2")
h24 = _file.Get("gamma_all_SR_2016pre_SR_bin2_2016pre_prefit/EWK_ajj_2")

h25 = _file.Get("gamma_all_SR_2018_SR_bin3_2018_prefit/EWK_ajj_2")
h26 = _file.Get("gamma_all_SR_2017_SR_bin3_2017_prefit/EWK_ajj_2")
h27 = _file.Get("gamma_all_SR_2016_SR_bin3_2016_prefit/EWK_ajj_2")
h28 = _file.Get("gamma_all_SR_2016pre_SR_bin3_2016pre_prefit/EWK_ajj_2")

h29 = _file.Get("gamma_all_SR_2018_SR_bin4_2018_prefit/EWK_ajj_2")
h30 = _file.Get("gamma_all_SR_2017_SR_bin4_2017_prefit/EWK_ajj_2")
h31 = _file.Get("gamma_all_SR_2016_SR_bin4_2016_prefit/EWK_ajj_2")
h32 = _file.Get("gamma_all_SR_2016pre_SR_bin4_2016pre_prefit/EWK_ajj_2")

 
##############

h41 = _file.Get("gamma_all_SR_2018_SR_bin1_2018_prefit/EWK_ajj_3")
h42 = _file.Get("gamma_all_SR_2017_SR_bin1_2017_prefit/EWK_ajj_3")
h43 = _file.Get("gamma_all_SR_2016_SR_bin1_2016_prefit/EWK_ajj_3")
h44 = _file.Get("gamma_all_SR_2016pre_SR_bin1_2016pre_prefit/EWK_ajj_3")

h45 = _file.Get("gamma_all_SR_2018_SR_bin2_2018_prefit/EWK_ajj_3")
h46 = _file.Get("gamma_all_SR_2017_SR_bin2_2017_prefit/EWK_ajj_3")
h47 = _file.Get("gamma_all_SR_2016_SR_bin2_2016_prefit/EWK_ajj_3")
h48 = _file.Get("gamma_all_SR_2016pre_SR_bin2_2016pre_prefit/EWK_ajj_3")

h49 = _file.Get("gamma_all_SR_2018_SR_bin3_2018_prefit/EWK_ajj_3")
h50 = _file.Get("gamma_all_SR_2017_SR_bin3_2017_prefit/EWK_ajj_3")
h51 = _file.Get("gamma_all_SR_2016_SR_bin3_2016_prefit/EWK_ajj_3")
h52 = _file.Get("gamma_all_SR_2016pre_SR_bin3_2016pre_prefit/EWK_ajj_3")

h53 = _file.Get("gamma_all_SR_2018_SR_bin4_2018_prefit/EWK_ajj_3")
h54 = _file.Get("gamma_all_SR_2017_SR_bin4_2017_prefit/EWK_ajj_3")
h55 = _file.Get("gamma_all_SR_2016_SR_bin4_2016_prefit/EWK_ajj_3")
h56 = _file.Get("gamma_all_SR_2016pre_SR_bin4_2016pre_prefit/EWK_ajj_3")

#############

h57 = _file.Get("gamma_all_SR_2018_SR_bin1_2018_prefit/EWK_ajj_4")
h58 = _file.Get("gamma_all_SR_2017_SR_bin1_2017_prefit/EWK_ajj_4")
h59 = _file.Get("gamma_all_SR_2016_SR_bin1_2016_prefit/EWK_ajj_4")
h60 = _file.Get("gamma_all_SR_2016pre_SR_bin1_2016pre_prefit/EWK_ajj_4")

h61 = _file.Get("gamma_all_SR_2018_SR_bin2_2018_prefit/EWK_ajj_4")
h62 = _file.Get("gamma_all_SR_2017_SR_bin2_2017_prefit/EWK_ajj_4")
h63 = _file.Get("gamma_all_SR_2016_SR_bin2_2016_prefit/EWK_ajj_4")
h64 = _file.Get("gamma_all_SR_2016pre_SR_bin2_2016pre_prefit/EWK_ajj_4")

h65 = _file.Get("gamma_all_SR_2018_SR_bin3_2018_prefit/EWK_ajj_4")
h66 = _file.Get("gamma_all_SR_2017_SR_bin3_2017_prefit/EWK_ajj_4")
h67 = _file.Get("gamma_all_SR_2016_SR_bin3_2016_prefit/EWK_ajj_4")
h68 = _file.Get("gamma_all_SR_2016pre_SR_bin3_2016pre_prefit/EWK_ajj_4")

h69 = _file.Get("gamma_all_SR_2018_SR_bin4_2018_prefit/EWK_ajj_4")
h70 = _file.Get("gamma_all_SR_2017_SR_bin4_2017_prefit/EWK_ajj_4")
h71 = _file.Get("gamma_all_SR_2016_SR_bin4_2016_prefit/EWK_ajj_4")
h72 = _file.Get("gamma_all_SR_2016pre_SR_bin4_2016pre_prefit/EWK_ajj_4")

  
h1.Add(h2); h1.Add(h3); h1.Add(h4); h1.Add(h17); h1.Add(h18); h1.Add(h19); h1.Add(h20); h1.Add(h41); h1.Add(h42); h1.Add(h43); h1.Add(h44); h1.Add(h57); h1.Add(h58); h1.Add(h59); h1.Add(h60);
h5.Add(h6); h5.Add(h7); h5.Add(h8); h5.Add(h21); h5.Add(h22); h5.Add(h23); h5.Add(h24); h5.Add(h45); h5.Add(h46); h5.Add(h47); h5.Add(h48); h5.Add(h61); h5.Add(h62) ; h5.Add(h63) ; h5.Add(h64);
h9.Add(h10); h9.Add(h11); h9.Add(h12); h9.Add(h25); h9.Add(h26); h9.Add(h27); h9.Add(h28); h9.Add(h49); h9.Add(h50); h9.Add(h51); h9.Add(h52);  h9.Add(h65);  h9.Add(h66);  h9.Add(h67);  h9.Add(h68);  
h13.Add(h14); h13.Add(h15); h13.Add(h16); h13.Add(h29); h13.Add(h30); h13.Add(h31); h13.Add(h32); h13.Add(h53); h13.Add(h54); h13.Add(h55); h13.Add(h56);  h13.Add(h69);  h13.Add(h70);  h13.Add(h71);  h13.Add(h72); 
     
binLowE = [-3.2,-2.0,0,2.0,3.2] 
uniformTau = TH1D("uniformTau","",4,array('d',binLowE)) 

uniformTau.SetBinContent(1,h1.Integral())
uniformTau.SetBinContent(2,h5.Integral())
uniformTau.SetBinContent(3,h9.Integral())
uniformTau.SetBinContent(4,h13.Integral())

uniformTau.Scale(1/uniformTau.Integral())

uniformTau.GetYaxis().SetRangeUser(0,1)


uniformTau.GetYaxis().SetTitle("#frac{1}{#sigma_{fid}} #frac{d#sigma}{dp_{T}}")
uniformTau.GetXaxis().SetTitle("gen #Delta #phi_{jj}")

c1 = TCanvas("c1","multipads",1200,700)
c1.cd()
uniformTau.Draw()

latex = TLatex();
latex.SetTextSize(0.05);
latex.SetTextAlign(13);
latex.DrawLatex(-3.1,1.06,"CMS #font[12]{preliminary}");
latex.DrawLatex(1.75,1.06,"138 fb^{-1} (13 TeV)");

c1.SaveAs("diff.pdf")
 


