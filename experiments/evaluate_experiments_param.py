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
Script for normalization metric of experiments for configuration 1 and 2
"""

import os
import numpy as np
from utils import topology, dataset

print("******* START *******")

configuration = (("config1", 18), ("config2", 30))
index_configuration = 1		# change {0 = config1, 1 = config2}
normalization_name = ["min-max", "z-score"]

for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8]:   # change [0, 1, 2, 3, 4, 5, 6, 7, 8]
	print(topology[index_topology])

	result = [0] * configuration[index_configuration][1]
	count_dataset = 0
	for index_dataset in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]:   # change [0, ..., 29]
		print("{} ({})".format(dataset[index_dataset][0], index_dataset))
		
		metric = []
		metric_normalization = [0] * configuration[index_configuration][1]
		with open("output/param/{}/{}_{}.out".format(configuration[index_configuration][0], topology[index_topology], dataset[index_dataset][0]), 'r') as file:
			for line in file:
				aux = line.split(",")
				print(float(aux[0]))
				metric.append(float(aux[0]))
			file.close()

		# normalization min-max for initial data
		index_normalization = 0
		min_ = np.min(metric)
		max_ = np.max(metric)
		# print("max - min: {}".format(max_ - min_))
		if max_ - min_ != 0:
			for k, item in enumerate(metric):
				min_max = ((item - min_) / (max_ - min_)) * (1 - 0) + 0
				# print(min_max)
				metric_normalization[k] = min_max			

		# calculate media of metric normalizate for dataset (using normalization min-max)
		index_normalization = 0
		min_ = np.min(metric_normalization)
		max_ = np.max(metric_normalization)
		print("max - min: {}".format(max_ - min_))

		std_ = np.std(metric_normalization)
		print("std: {}".format(std_))
		if std_ >= 0.2 and std_ <= 0.4: # for final experiments used: std_ >= 0.2
			count_dataset += 1
			for k, item in enumerate(metric_normalization):
				min_max = ((item - min_) / (max_ - min_)) * (1 - 0) + 0
				# print(min_max)
				result[k] += min_max
		else:
			print("No: {} ({})".format(dataset[index_dataset][0], index_dataset))			

	# print(result)
	print("Mean {} normalization:".format(normalization_name[index_normalization]))
	for k, item in enumerate(result):
		result[k] = item / count_dataset
		print(result[k])

	print("Config{}-{}: {}".format((index_configuration + 1), topology[index_topology], result.index(min(result)) + 1))
print("******* END *******")

# Run:
# for index_configuration = 0
# python evaluate_experiments_param.py > output/param/evaluate_config1.out
# for index_configuration = 1
# python evaluate_experiments_param.py > output/param/evaluate_config2.out


# normalization min-max
""" index_normalization = 0
min_ = np.min(metric_normalization)
max_ = np.max(metric_normalization)
print("max - min: {}".format(max_ - min_))
if max_ - min_ <= 0.01:
	count_dataset -= 1
	print("No: {} ({})".format(dataset[index_dataset][0], index_dataset))
else:
	for k, item in enumerate(metric_normalization):
		min_max = ((item - min_) / (max_ - min_)) * (1 - 0) + 0
		# print(min_max)
		result[k] += min_max """

# normalization z-score
""" min_ = np.min(metric_normalization)
max_ = np.max(metric_normalization)
print("max - min: {}".format(max_ - min_))

index_normalization = 1
mean_ = np.mean(metric_normalization)
std_ = np.std(metric_normalization)
print("std: {}".format(std_))
if (std_ == 0):
	count_dataset -= 1
	print("No: {} ({})".format(dataset[index_dataset][0], index_dataset))
else:
	for k, item in enumerate(metric_normalization):
		z_score = (item - mean_) / std_
		# print(z_score)
		result[k] += z_score """