#!/bin/bash

#rm -f -r pdf.root
#rm -f -r q2.root

var_gen='(TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[2] + GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2]))/(GenParticles.m_energy[2] - GenParticles.m_pt[2]*TMath::SinH(GenParticles.m_eta[2])))) - TMath::Abs(0.5*TMath::Log((GenParticles.m_energy[3] + GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3]))/(GenParticles.m_energy[3] - GenParticles.m_pt[3]*TMath::SinH(GenParticles.m_eta[3])))))'

####Q2#######

python createq2templates_SR1T.py 1 1
mv mu_Test_4cat_q2_SR1T.root q2.root

python createq2templates_ttbar1.py 1 1 "${var_gen}"
mv mu_Test_4cat_q2_SR1T.root q2_ttbar1.root

python createq2templates_ttbar2.py 1 1 "${var_gen}"
mv mu_Test_4cat_q2_SR1T.root q2_ttbar2.root

###PDF#######

python createpdftemplates_SR1T.py 1 1 -b
mv mu_Test_4cat_PDF_SR1T.root pdf.root 

python createpdftemplates_ttbar1.py 1 1 "${var_gen}" -b
mv mu_Test_4cat_PDF_SR1T.root pdf_ttbar1.root 

python createpdftemplates_ttbar2.py 1 1 "${var_gen}" -b
mv mu_Test_4cat_PDF_SR1T.root pdf_ttbar2.root

