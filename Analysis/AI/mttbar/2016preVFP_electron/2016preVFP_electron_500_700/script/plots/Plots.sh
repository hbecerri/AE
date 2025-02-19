#!/bin/bash

declare -a StringArray=("Delta_E")

for var in ${StringArray[@]}; do

python makeplots.py ${var}


done


