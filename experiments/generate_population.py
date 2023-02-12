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
Script for generate population for 0, 1, 2, 3, 4, 5 number generation
"""

import os
from utils import dataset, seed, GetDateTime

print("******* START *******")
print(GetDateTime())
number_experiments = 50         # change {1, ..., 50}

for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:       # change [0, ..., 29]
	for initial_number_generation in [0, 1, 2, 3]:      # change [0, 1, 2, 3, 4, 5] list of generations
		for index_seed in range(number_experiments):
			os.system("./main_population dataset/{}.cols {} {} dataset/{}.data {} {} > output/population/{}_{}_{}.data"
			.format(dataset[index_dataset][0],
					dataset[index_dataset][1],
					dataset[index_dataset][2],
					dataset[index_dataset][0],
					seed[index_seed],
					initial_number_generation,
					dataset[index_dataset][0],
					index_seed,
					initial_number_generation))
			print(dataset[index_dataset][0], index_seed, initial_number_generation)
print(GetDateTime())
print("******* END *******")

# Run
# python generate_population.py

# Output:
# files with name: (dataset name)_(index seed)_(number generation).data