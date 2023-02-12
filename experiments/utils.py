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

import os
from datetime import datetime
import numpy as np

topology = ["RING", "TREE", "NETA", "NETB", "TORUS", "GRAPH", "SAME", "GOODBAD", "RAND"]
emigration = ["CLONE", "REMOVE"]
choiceEmi = ["BEST", "WORST", "RANDOM"]
choiceImm = ["BEST", "WORST", "RANDOM"]
numberEmiImm = [1, 2, 3, 4, 5]
intervalEmiImm = [1, 2, 4, 6, 8, 10]

dataset = [
	["crude_oil", 3, 56],                   # 0
	["caesarian", 2, 80],                   # 1
	["breast_tissue", 6, 106],              # 2
	["hayes_roth", 3, 132],                 # 3
	["iris", 3, 150],                       # 4
	["tae", 3, 151],                        # 5
	["wine", 3, 178],                       # 6
	["glass", 7, 214],                      # 7
	["statlog_heart", 2, 270],              # 8
	["haberman", 2, 306],                   # 9
	["column_2c", 2, 310],                  # 10
	["column_3c", 3, 310],                  # 11
	["ecoli", 8, 336],                      # 12
	["ilpd", 2, 583],                       # 13
	["balance_scale", 3, 625],              # 14
	["australian_credit", 2, 690],          # 15
	["breast_cancer_wisconsin", 2, 699],    # 16
	["healthy_older_people", 4, 724],       # 17
	["transfusion", 2, 748],                # 18
	["vehicle_silhouettes", 4, 946],        # 19
	["messidor_features", 2, 1151],         # 20
	["website_phishing", 3, 1353],          # 21
	["banknote_authentication", 2, 1372],   # 22
	["cmc", 3, 1473],                       # 23
	["yeast", 10, 1484],                    # 24
	["wifi_localization", 4, 2000],         # 25
	["electrical_grind", 2, 10000],         # 26
	["avila_tr", 12, 10430],                # 27
	["firm_teacher", 4, 10800],             # 28
	["eeg_eye", 2, 14980]                   # 29
]

seed = [
	169735477,
	160028434,
	160897947,
	157407246,
	153881302,
	172694171,
	171070236,
	154302761,
	165786948,
	159504387,
	172007822,
	171759537,
	167673018,
	161471032,
	153969729,
	162772019,
	162871815,
	164484920,
	165299547,
	172039163,
	154936578,
	168577700,
	153992657,
	172048626,
	158530753,
	160026451,
	164317733,
	170918034,
	169403955,
	162541554,
	160937381,
	170219188,
	157430629,
	154508394,
	162819603,
	168764208,
	168557415,
	166309796,
	154966946,
	155241744,
	171859107,
	173430800,
	156284381,
	157136719,
	160813250,
	170995803,
	169041299,
	166136032,
	162228293,
	168958481
]

def EvaluteResult(file_out_result, aux_name, number_experiments):   # no used
	file_out_aux = open(aux_name, "r") 
	# get min length of array (call fitness)
	index_min = 1000000
	index_last = 0
	for line in file_out_aux:
		aux = line.split(",")
		index = int(aux[0])
		if index == 0:
			if index_last < index_min:
				index_min = index_last
		index_last = index
	file_out_aux.close()

	metric_call_fitness = []
	for k in range(index_min):
		metric_call_fitness.append([0, 0])

	metric_runtime = []
	# read line to get metric, num_call_fitness and runtime
	file_out_aux = open(aux_name, "r") 
	for line in file_out_aux:
		aux = line.split(",")
		index = int(aux[0])
		if index == 0:
			metric_ = float(aux[1])
			runtime_ = float(aux[2])
			metric_runtime.append([metric_, runtime_])
		else:
			if index <= index_min:
				metric_ = float(aux[1])
				call_fitness = float(aux[2])
				metric_call_fitness[index - 1][0] += metric_
				metric_call_fitness[index - 1][1] += call_fitness

	# calculate and print average: metric, call fitness
	for item in metric_call_fitness:
		item[0] /= number_experiments
		item[1] /= number_experiments
		file_out_result.write("{},{}\n".format(item[0], item[1]))
	file_out_result.write("\n")

	metric = []
	runtime = []

	# calculate and print: metric, runtime for number experiments
	for item in metric_runtime:
		file_out_result.write("{},{}\n".format(item[0], item[1]))
		metric.append(item[0])
		runtime.append(item[1])

	file_out_result.write("\n")

	# metric.sort()
	# runtime.sort()

	file_out_result.write("\"\"\"\n")
	file_out_result.write("Metric\n")
	mean_ = np.mean(metric)
	file_out_result.write("{}\n".format(mean_))
	median_ = np.median(metric)
	file_out_result.write("{}\n".format(median_))
	max_ = np.max(metric)
	file_out_result.write("{}\n".format(max_))
	min_ = np.min(metric)
	file_out_result.write("{}\n".format(min_))
	file_out_result.write("Runtime\n")
	mean_ = np.mean(runtime)
	file_out_result.write("{}\n".format(mean_))
	median_ = np.median(runtime)
	file_out_result.write("{}\n".format(median_))
	max_ = np.max(runtime)
	file_out_result.write("{}\n".format(max_))
	min_ = np.min(runtime)
	file_out_result.write("{}\n".format(min_))
	file_out_result.write("\"\"\"\n")

	file_out_aux.close()
	os.system("rm {}".format(aux_name))
	file_out_result.close()

def GetDateTime():
	now = datetime.now()
	# dd/mm/YY H:M:S
	dt_string = now.strftime("%d/%m/%Y %H:%M:%S")
	return dt_string