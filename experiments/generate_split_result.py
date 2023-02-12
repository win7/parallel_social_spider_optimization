# -*- coding: utf-8 -*-
"""
============================================================================
Authors:
	Edwin Alvarez-Mamani and Jose Luis Soncco-Alvarez*
	*Department of Informatics 
	Universidad Nacional de San Antonio Abad del Cusco (UNSAAC) - Perú
============================================================================
"""
# Python: 3.8.x
"""
Script for split metric and runtime of experiments
"""

import numpy as np
from utils import dataset

print("******* START *******")

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND", "SSO"]
initial_number_generation = 0       # change {0, 1, 2, 3, 4, 5} list of initial number generations
number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations

for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:   # change [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
	print(topology[index_topology])
	for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:   # change [0, ..., 29]
		print(dataset[index_dataset][0], initial_number_generation, number_generation)

		if index_topology == 9:	# SSO secuencial
			experiment_out_name = "output/sso/{}_{}_{}.out".format(
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)

			experiment_metric_resul_name = "output/sso/metric/{}_{}_{}.out".format(
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)
		else:
			experiment_out_name = "output/psso/{}_{}_{}_{}.out".format(
				topology[index_topology],
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)

			experiment_metric_resul_name = "output/psso/metric/{}_{}_{}_{}.out".format(
				topology[index_topology],
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)

		file_out_experiment = open(experiment_out_name, "r") 

		file_result_metric = open(experiment_metric_resul_name, "w")
		file_result_runtime = open(experiment_metric_resul_name.replace("metric", "runtime"), "w")
		
		for line in file_out_experiment:
			aux = line.split(",")
			metric_ = "{}\n".format(aux[0])
			time_ = aux[1]
			file_result_metric.write(metric_)
			file_result_runtime.write(time_)

		file_out_experiment.close()
		file_result_metric.close()
		file_result_runtime.close()
print("******* END *******")

# Run:
# python generate_split_result.py