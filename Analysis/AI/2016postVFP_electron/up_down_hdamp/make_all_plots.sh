#!/bin/bash

declare -a StringArray=("hdamp")

for var in ${StringArray[@]}; do

python up_down.py ${var}


done













