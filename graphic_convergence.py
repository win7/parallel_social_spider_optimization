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
Script for graphic convergence for dataset, topology and count call fitness function
"""

import matplotlib.pyplot as plt
from matplotlib.ticker import NullFormatter  # useful for `logit` scale
import numpy as np
from utils import dataset

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND", "SSO"]
index_dataset = 22   # change {0, ..., 29}
number_generations = [100, 150, 200, 300]   # change [100, 150, 200, 300]
number_generation = 300      # change {100, 150, 200, 300} for select fitness under number generations
number_experiments = 10      # change {1, ..., 50}
initial_number_generations = [0]	# change [0, 1, 2, 3, 4, 5] list of initial number generations

y_min = 10000000
y_max = 0
for count, initial_number_generation in enumerate(initial_number_generations):
	print("Initial generation: {}".format(initial_number_generation))

	if len(initial_number_generations) == 1:
		number_subplot = 110 + (count + 1)
	else:
		number_subplot = 220 + (count + 1)
	# print(number_subplot)
	plt.subplot(number_subplot)

	topology_best = {}

	for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:  # change [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
		# open file of SSO and P-SSO (convergence)
		if index_topology == 9:
			experiment_name = "output/sso/conv/{}_{}_{}.out".format(
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)
		else:
			experiment_name = "output/psso/conv/{}_{}_{}_{}.out".format(
				topology[index_topology],
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation)
		# print(experiment_name)

		# get min length of array (call fitness)
		file_out_experiment = open(experiment_name, "r") 
		
		index_min = 1000000
		index_last = 0

		for line in file_out_experiment:
			aux = line.split(",")
			# print(aux)
			if len(aux) == 2:
				if index_last < index_min:
					index_min = index_last
			else:
				index = int(aux[0])
			index_last = index
		file_out_experiment.close()
		# print("min index", index_min)

		# create array for save metric and call fitness
		metric_call_fitness = []
		for k in range(index_min):
			metric_call_fitness.append([0, 0])

		# read line to get metric and call fitness
		file_out_experiment = open(experiment_name, "r")
		for line in file_out_experiment:
			aux = line.split(",")
			# print(aux)
			if len(aux) == 3:
				index = int(aux[0])
				if index <= index_min:
					metric = float(aux[1])
					call_fitness = float(aux[2])
					metric_call_fitness[index - 1][0] += metric
					metric_call_fitness[index - 1][1] += call_fitness
		file_out_experiment.close()

		# calculate mean: metric, call fitness
		for item in metric_call_fitness:
			item[0] /= number_experiments
			item[1] /= number_experiments

		x = []	# call fitness
		y = []	# metric

		# load data for plot
		for item in metric_call_fitness:
			metric = float(item[0])
			call_fitness = float(item[1])
			x.append(call_fitness)
			y.append(metric)

		# get min and max metric
		if np.min(y) < y_min:
			y_min = np.min(y)
		if np.max(y) > y_max:
			y_max = np.max(y)

		# add min metric to dict
		topology_best[topology[index_topology]] = np.min(y)
		# print(topology[index_topology], y_min)

		# draw mectric vs call fitness
		plt.plot(x, y, linestyle="-", label=topology[index_topology], linewidth=2, marker="")

	# order dict for get best topology under metric
	for item in sorted (topology_best.items(), key = lambda x : x[1]):
		print("{}:\t{}".format(item[0], item[1]))
	# plt.text(10, 62150, initial_number_generation)

	# graphic vertical line for number call fitness by generation
	for number_generation_ in number_generations:
		with open("output/fitness/{}_{}.count".format(dataset[index_dataset][0], number_generation_), 'r') as file:
			for line in file:
				limit_count_fitness = int(line)
				print("Generation {}: {}".format(number_generation_, limit_count_fitness * 24))
				plt.axvline(x=limit_count_fitness * 24, label="N° gen: {}".format(number_generation_), color="k")
			file.close()
	print()

	# limit range for metric for each generation initial
	""" limit_y = [y_min - 0.01, y_min + 0.5]    # y_max
	plt.ylim(limit_y) """

	# naming the x axis 
	plt.xlabel("# Evaluation fitness") 
	# naming the y axis 
	plt.ylabel("Metric") 
	# giving a title to my graph 
	plt.title("Dataset: {}_{}".format(dataset[index_dataset][0], initial_number_generation))
	# add grid
	plt.grid()

	# show a legend on the plot 
	plt.legend(loc="upper right", ncol=3, borderaxespad=0.2, prop={"size":9})

# show a legend on the plot 
# plt.legend(loc=0)
# plt.legend(loc="upper right", ncol=2, borderaxespad=0.2, prop={"size":8})
# plt.legend(bbox_to_anchor=(1.01, 1), loc='upper left', borderaxespad=0., prop={"size":10})
# plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)

plt.subplots_adjust(top=0.96, bottom=0.065, left=0.06, right=0.985, hspace=0.260, wspace=0.150)

# function to show the plot 
plt.show()
# plt.ion() 

# Run:
# python graphic_convergence.py