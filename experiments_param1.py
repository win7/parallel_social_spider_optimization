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
Script for find best param for configuration 1
"""

import os
from utils import seed, topology, emigration, choiceEmi, choiceImm, numberEmiImm, intervalEmiImm, dataset, GetDateTime

iteration_foreach_configuration = 10

policy_name = "policy/policy.in"
aux_name = "output/aux_psso.out"

print("******* START *******")
print(GetDateTime())

for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8]:   # change [0, 1, 2, 3, 4, 5, 6, 7, 8]
	print(topology[index_topology])
	for index_dataset in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]:   # change [0, ..., 29]
		print(dataset[index_dataset][0])
		result_name = "output/param/config1/{}_{}.out".format(topology[index_topology], dataset[index_dataset][0])
		file_out_result = open(result_name, "w") 
		for k in range(len(emigration)):
			for i in range(len(choiceEmi)):
				for j in range(len(choiceImm)):
					file_in_policy = open(policy_name, "w") 
					file_in_policy.write("topology:" + topology[index_topology] + "\n") 
					file_in_policy.write("emigration:" + emigration[k] + "\n") 
					file_in_policy.write("choiceEmi:" + choiceEmi[i] + "\n") 
					file_in_policy.write("choiceImm:" + choiceImm[j] + "\n") 
					if index_topology == 5:
						file_in_policy.write("numberEmiImm:" + str(numberEmiImm[3]) + "\n")
					else:
						file_in_policy.write("numberEmiImm:" + str(numberEmiImm[4]) + "\n")
					file_in_policy.write("intervalEmiImm:" + str(intervalEmiImm[2]) + "\n")
					file_in_policy.close()

					for index_seed in range(iteration_foreach_configuration):
						# os.system("mpirun -n 24 --oversubscribe ./main_psso dataset/{}.cols {} {} dataset/{}.data {} {}"
						os.system("mpirun -n 24 ./main_psso dataset/{}.cols {} {} dataset/{}.data {} {}"
						.format(dataset[index_dataset][0],
								dataset[index_dataset][1],
								dataset[index_dataset][2],
								dataset[index_dataset][0],
								policy_name,
								seed[index_seed]))

					# show complete
					""" file_out_result.write("# " + str((k * len(choiceEmi) + i) * len(choiceImm) + j + 1) + ":\n")

					file_out_aux = open(aux_name, "r") 
					average_metric = 0
					average_time = 0
					for line in file_out_aux:
						aux = line.split(",")
						average_metric += float(aux[0])
						average_time += float(aux[1])
						file_out_result.write("\t" + line)

					file_out_result.write("Average metric:\t" + str(average_metric / iteration_foreach_configuration) + "\n")
					file_out_result.write("Average time:\t" + str(average_time / iteration_foreach_configuration) + "\n\n") """


					# show only average metric and time
					file_out_aux = open(aux_name, "r") 
					average_metric = 0
					average_time = 0
					for line in file_out_aux:
						aux = line.split(",")
						average_metric += float(aux[0])
						average_time += float(aux[1])

					file_out_result.write(str(average_metric / iteration_foreach_configuration) + "," + str(average_time / iteration_foreach_configuration) + "\n")

					file_out_aux.close()
					os.system("rm " + aux_name)
		file_out_result.close()
print(GetDateTime())
print("******* END *******")

# Run:
# python experiments_param1.py