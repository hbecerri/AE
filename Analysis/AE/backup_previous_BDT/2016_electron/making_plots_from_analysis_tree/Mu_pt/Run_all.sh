#!/bin/bash

#"Ele_pt" "Ele_eta" "Ak4_j1_pt" "Ak4_j2_pt" "Ak4_j1_eta" "Ak4_j2_eta" "M_tt" "N_Ak4" "btagN" "chi2" "MET_pt"
 
#root -l -b -q 'all_unfolding_data.C(25,55,550,"Ele_pt")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ele_pt.root

#root -l -b -q 'all_unfolding_data.C(25,-2.4,2.4,"Ele_eta")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ele_eta.root

#root -l -b -q 'all_unfolding_data.C(20,150,600,"Ak4_j1_pt")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ak4_j1_pt.root

#root -l -b -q 'all_unfolding_data.C(25,50,400,"Ak4_j2_pt")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ak4_j2_pt.root

#root -l -b -q 'all_unfolding_data.C(10,-2.4,2.4,"Ak4_j1_eta")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ak4_j1_eta.root

#root -l -b -q 'all_unfolding_data.C(10,-2.4,2.4,"Ak4_j2_eta")'
#mv Input_undfolding_data_all.root Input_undfolding_data_Ak4_j2_eta.root

#root -l -b -q 'all_unfolding_data.C(40,100,500,"M_tt")'
#mv Input_undfolding_data_all.root Input_undfolding_data_M_tt.root

#root -l -b -q 'all_unfolding_data.C(7,3,10,"N_Ak4")'
#mv Input_undfolding_data_all.root Input_undfolding_data_N_Ak4.root

#root -l -b -q 'all_unfolding_data.C(15,0, 30,"chi2")'
#mv Input_undfolding_data_all.root Input_undfolding_data_chi2.root

#root -l -b -q 'all_unfolding_data.C(25,50,500,"MET_pt")'
#mv Input_undfolding_data_all.root Input_undfolding_data_MET_pt.root

root -l -b -q 'all_unfolding_data.C(24,50,300,"top_m")'
mv Input_undfolding_data_all.root Input_undfolding_data_top_m.root

root -l -b -q 'all_unfolding_data.C(24,50,300,"antitop_m")'
mv Input_undfolding_data_all.root Input_undfolding_data_antitop_m.root


