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
Script for create CSV files for test Friedman and Holm (Adapted from StatAnalysis_CEC2017_Lucas)
"""
import sys
sys.path.append('../')

import numpy as np
from utils import dataset

print("******* START *******")

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND", "SSO"]
initial_number_generation = 0       # change {0, 1, 2, 3, 4, 5} list of initial number generations
number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations
topologies_index = [0, 1, 2, 3, 4, 5, 6, 7, 8]   # change [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
type_data = "metric"	# change {"metric", "runtime"}

for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:   # change [0, ..., 29]
	print(dataset[index_dataset][0], initial_number_generation, number_generation)
	out_file_name = "CSV_files/{}/output_{}_{}_{}.csv".format(
		type_data,
		dataset[index_dataset][0],
		initial_number_generation,
		number_generation
	)

	file = open(out_file_name, "w" )

	text = "rep"
	for index_topology in topologies_index:
		text += ", {}".format(topology[index_topology])
	text += "\n"
	file.write(text)

	list_data = []
	for index_topology in topologies_index:
		print(topology[index_topology])
	
		if index_topology == 9: # SSO secuencial
			experiment_out_name = "../output/sso/{}/{}_{}_{}.out".format(
				type_data,
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)
		else:
			experiment_out_name = "../output/psso/{}/{}_{}_{}_{}.out".format(
				type_data,
				topology[index_topology],
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)

		data = np.loadtxt(experiment_out_name, dtype=np.float)
		list_data.append(data)

	# generate CSV file
	for i in range(len(list_data[0])):
		text = "{}".format(i + 1)
		for j in range(len(topologies_index)):
			text += ", {}".format(1.0 / list_data[j][i])
		text += "\n"
		file.write(text)

	file.close()
print("******* END *******")

# Run:
# python scriptForCSV_files.py