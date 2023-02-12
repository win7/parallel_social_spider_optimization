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
Script for execute algorithm P-SSO
"""

import os
from utils import seed, topology, emigration, choiceEmi, choiceImm, numberEmiImm, intervalEmiImm, dataset, GetDateTime

print("******* START *******")
print(GetDateTime())

params = [
	[0, 0, 1, 4, 1], # RING
	[0, 0, 2, 4, 0], # TREE
	[0, 0, 2, 1, 0], # NETA
	[0, 0, 2, 2, 0], # NETB
	[0, 0, 2, 0, 0], # TORUS
	[0, 0, 2, 0, 1], # GRAPH
	[0, 0, 2, 1, 0], # SAME
	[0, 0, 2, 3, 1], # GOODBAD
	[0, 0, 1, 1, 0]  # RAND
]   # change under best params for congig1 and config2

policy_name = "policy/policy.in"

number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations
number_experiments = 50      # change {1, ..., 50}

for index_topology in [0, 1, 2, 3, 4, 5, 6, 7, 8]:      # change [0, 1, 2, 3, 4, 5, 6, 7, 8]
	print(topology[index_topology])

	index_emigration = params[index_topology][0]
	index_choiceEmi = params[index_topology][1]
	index_choiceImm = params[index_topology][2]
	index_numberEmiImm = params[index_topology][3]
	index_intervalEmiImm = params[index_topology][4]

	for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:    # change [0, ..., 29]
		for initial_number_generation in [0]:       # change [0, 1, 2, 3, 4, 5] list of initial number generations
			print(dataset[index_dataset][0], initial_number_generation)

			limit_count_fitness = 0
			with open("output/fitness/{}_{}.count".format(dataset[index_dataset][0], number_generation), "r") as file:
				for line in file:
					limit_count_fitness = int(line)
				file.close()

			output_name = "output/psso/{}_{}_{}_{}.out".format(topology[index_topology], dataset[index_dataset][0], initial_number_generation, number_generation)
			if os.path.exists(output_name):
				os.remove(output_name)
			
			file_in_policy = open(policy_name, "w") 
			file_in_policy.write("topology:" + topology[index_topology] + "\n") 
			file_in_policy.write("emigration:" + emigration[index_emigration] + "\n") 
			file_in_policy.write("choiceEmi:" + choiceEmi[index_choiceEmi] + "\n") 
			file_in_policy.write("choiceImm:" + choiceImm[index_choiceImm] + "\n") 
			file_in_policy.write("numberEmiImm:" + str(numberEmiImm[index_numberEmiImm]) + "\n") 
			file_in_policy.write("intervalEmiImm:" + str(intervalEmiImm[index_intervalEmiImm]) + "\n") 
			file_in_policy.close()

			for index_seed in range(number_experiments):
				os.system("mpirun -n 24 --oversubscribe ./main_psso_exp dataset/{}.cols {} {} dataset/{}.data {} output/population/{}_{}_{}.data {} {} {}"
				# os.system("mpirun -n 24 ./main_psso_exp dataset/{}.cols {} {} dataset/{}.data {} output/population/{}_{}_{}.data {} {} {}"
				.format(dataset[index_dataset][0],
						dataset[index_dataset][1],
						dataset[index_dataset][2],
						dataset[index_dataset][0],
						policy_name,
						dataset[index_dataset][0],
						index_seed,
						initial_number_generation,
						24 * limit_count_fitness,
						seed[index_seed],
						output_name))
print(GetDateTime())
print("******* END *******")

# Run:
# python experiments_psso.py

# Output:
# files with name: (topology)_(dataset name)_(initial number generation)_(number generation for count fitness).out