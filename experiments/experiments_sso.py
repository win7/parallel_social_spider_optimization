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
Script for execute algorithm SSO
"""

import os
from utils import seed, dataset, GetDateTime

print("******* START *******")
print(GetDateTime())

number_generation = 100      # change {100, 150, 200, 300} for select fitness under number generations
number_experiments = 50      # change {1, ..., 50}

for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:   # change [0, ..., 29]
	for initial_number_generation in [0]:       # change [0, 1, 2, 3, 4, 5] list of initial number generations
		print(dataset[index_dataset][0], initial_number_generation)

		limit_count_fitness = 0
		with open("output/fitness/{}_{}.count".format(dataset[index_dataset][0], number_generation), "r") as file:
			for line in file:
				limit_count_fitness = int(line)
			file.close()

		output_name = "output/sso/{}_{}_{}.out".format(dataset[index_dataset][0], initial_number_generation, number_generation)
		if os.path.exists(output_name):
			os.remove(output_name)

		for index_seed in range(number_experiments):
			os.system("./main_sso_exp dataset/{}.cols {} {} dataset/{}.data output/population/{}_{}_{}.data {} {} {}"
			.format(dataset[index_dataset][0],
					dataset[index_dataset][1],
					dataset[index_dataset][2],
					dataset[index_dataset][0],
					dataset[index_dataset][0],
					index_seed,
					initial_number_generation,
					24 * limit_count_fitness,
					seed[index_seed],
					output_name))
print(GetDateTime())
print("******* END *******")

# Run:
# python experiments_sso.py

# Output:
# files with name: (dataset name)_(initial number generation)_(number generation for count fitness).out