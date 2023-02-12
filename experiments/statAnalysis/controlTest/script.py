#!/usr/bin/python

# -*- coding: utf-8 -*-
"""
============================================================================
Authors:
    Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
    *Department of Informatics 
    Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
"""
# Python: 3.8
"""
Script for execute Friedman and Holm test (Adapted from StatAnalysis_CEC2017_Lucas)
"""
import sys
sys.path.append('../../')

import subprocess
import numpy as np
from utils import dataset

print("******* START *******")

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND", "SSO"]
initial_number_generation = 0       # change {0, 1, 2, 3, 4, 5} list of initial number generations
number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations
type_data = "metric"   # change {"metric", "runtime"}

# execute a command with Call
def execute_call(command):
    print(command)
    subprocess.call(command, shell=True)

input_folder        = "../CSV_files/{}/".format(type_data)
output_folder       = "Latex/{}/".format(type_data)

for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:   # change [0, ..., 29]
    print(dataset[index_dataset][0], initial_number_generation, number_generation)

    input = "{}output_{}_{}_{}.csv".format(input_folder, dataset[index_dataset][0], initial_number_generation, number_generation)
    output = "{}output_{}_{}_{}.tex".format(output_folder, dataset[index_dataset][0], initial_number_generation, number_generation)
    command = "java Friedman {} > {}".format(input, output)     # change {Friedman, Holm}
    execute_call(command)
print("******* END *******")

# Run:
# python script.py