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
import math

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND", "SSO"]
number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations
number_experiments = 10      # change {1, ..., 50}
initial_number_generation = 0	# change {0, 1, 2, 3, 4, 5} list of initial number generations
index_dataset_ = [21, 23, 24, 27]	# change [20, 21, 22, 23, 24, 25] or [26, 27, 28, 29]

columns = 1
rows = int(math.ceil(len(index_dataset_) / columns))
plt.figure(0)

for count, index_dataset in enumerate(index_dataset_):
	print(dataset[index_dataset][0], initial_number_generation)
	limit_count_fitness = 0
	with open("output/fitness/{}_{}.count".format(dataset[index_dataset][0], number_generation), "r") as file:
		for line in file:
			limit_count_fitness = int(line)
		file.close()
	limit_count_fitness *= 24
	# print(limit_count_fitness)

	# configuration for plot
	# print(number_subplot)
	# plt.subplot("521")
	# number_subplot += 0  # (int(len(index_dataset_) / 2) + * 100 + 20) + (count + 1)

	plt.subplot2grid((rows, columns), (int((count - (count % columns))/ columns), count % columns))

	topology_best = {}
	topology_bad = {}

	y_min = 10000000
	y_max = 0
	for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]:  # change [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
		# print(topology[index_topology])
		# open file of SSO and P-SSO (convergence)
		if index_topology == 9:
			experiment_name = "output/sso/conv/{}_{}_{}.out".format(
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation*3) 	# only because convergence data is for 300 generations
		else:
			experiment_name = "output/psso/conv/{}_{}_{}_{}.out".format(
				topology[index_topology],	
				dataset[index_dataset][0],
				initial_number_generation,
				number_generation*3)
		# print(experiment_name)

		# get min length of array (call fitness)
		file_out_experiment = open(experiment_name, "r") 
		
		index_min = 10000000
		index_last = 0

		for line in file_out_experiment:
			aux = line.split(",")
			# print(aux)
			if len(aux) == 3:
				if float(aux[2]) >= limit_count_fitness:
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

		# add initial metric (bad) to dict
		topology_bad[topology[index_topology]] = np.max(y)

		# draw mectric vs call fitness
		plt.plot(x, y, linestyle="-", label=topology[index_topology], linewidth=2, marker="")

	# order dict for get best topology under metric
	bad_metric = 0
	for item in sorted (topology_best.items(), key = lambda x : x[1]):
		print("{}:\t{}".format(item[0], item[1]))
		bad_metric = item[1]
	# plt.text(10, 62150, initial_number_generation)
	# print(topology_best)

	# order dict for get bad topology under metric
	# sort_topology_bad = sorted(topology_bad.items(), key=lambda x: x[1], reverse=True)
	# print(sort_topology_bad)

	# graphic vertical line for number call fitness by generation
	plt.axvline(x=limit_count_fitness, label="N° gen: {}".format(number_generation), color="k")

	# limit range for metric for each generation initial
	# limit_y = [y_min - ((y_max - y_min) * 0.2 / 100), ((y_max - y_min) * 10 / 100) + y_min]
	# limit_y = [y_min - 0.2, y_min + 5]
	# limit_y = [y_min - 0.2, y_min + 10]
	# limit_y = [y_min - ((y_max - y_min) * 0.2 / 100), y_min + 5]
	limit_y = [y_min - ((bad_metric - y_min) * 1 / 100), bad_metric + ((bad_metric - y_min) * 100 / 100)]
	# limit_y = [y_min - ((topology_bad["SSO"] - y_min) * 1 / 100), y_min + ((topology_bad["SSO"] - y_min) * 100 / 100)]
	# limit_y = [y_min - ((topology_bad["SSO"] - y_min) * 2 / 100), y_min + ((topology_bad["SSO"] - y_min) * 100 / 100)]
	print(limit_y)
	# plt.ylim(limit_y)

	# naming the x axis 
	plt.xlabel("Fitness function evaluation number", fontsize=12)
	# naming the y axis 
	plt.ylabel("Metric", fontsize=12) 
	# giving a title to my graph 
	plt.title("Dataset: {}".format(dataset[index_dataset][0]), fontsize=14)
	# add grid
	plt.grid()

	# show a legend on the plot 
	# plt.legend(loc="upper right", ncol=3, borderaxespad=0.2, prop={"size":8})
	plt.legend(loc="upper right", ncol=3, borderaxespad=0.2, prop={"size":12})

# show a legend on the plot 
# plt.legend(loc=0)
# plt.legend(loc="upper right", ncol=2, borderaxespad=0.2, prop={"size":8})
# plt.legend(bbox_to_anchor=(1.01, 1), loc='upper left', borderaxespad=0., prop={"size":10})
# plt.legend(bbox_to_anchor=(0., 1.02, 1., .102), loc='lower left', ncol=2, mode="expand", borderaxespad=0.)

# plt.subplots_adjust(top=0.96, bottom=0.045, left=0.06, right=0.985, hspace=0.280, wspace=0.150)
plt.subplots_adjust(top=0.96, bottom=0.065, left=0.06, right=0.985, hspace=0.280, wspace=0.150)

# function to show the plot 
plt.show()
# plt.ion() 

# Run:
# python graphic_convergence_paper.py