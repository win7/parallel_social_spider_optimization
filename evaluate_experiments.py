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
Script for get mean, median, max and min for metric and runtime
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

		metric = []
		runtime = []
		if index_topology == 9:
			experiment_name = "output/sso/{}_{}_{}.out".format(
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)
		else:
			experiment_name = "output/psso/{}_{}_{}_{}.out".format(
				topology[index_topology],
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)

		file_out_experiment = open(experiment_name, "r") 
		average_metric = 0
		average_time = 0
		for line in file_out_experiment:
			aux = line.split(",")
			# print(aux)
			metric_ = float(aux[0])
			time_ = float(aux[1])
			metric.append(metric_)
			runtime.append(time_)
		file_out_experiment.close()
		
		metric.sort()
		runtime.sort()

		print("Metric")
		mean_ = np.mean(metric)
		print("{}".format(mean_))
		median_ = np.median(metric)
		print("{}".format(median_))
		max_ = np.max(metric)
		print("{}".format(max_))
		min_ = np.min(metric)
		print("{}".format(min_))
		print("Runtime")
		mean_ = np.mean(runtime)
		print("{}".format(mean_))
		median_ = np.median(runtime)
		print("{}".format(median_))
		max_ = np.max(runtime)
		print("{}".format(max_))
		min_ = np.min(runtime)
		print("{}".format(min_))
print("******* END *******")

# Run:
# python evaluate_experiments.py > output/sso_psso/evaluate_experiments.out