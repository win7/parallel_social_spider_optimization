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
Script for calculate fitness for 100, 150, 200, 300 of population size
"""

import os
from utils import dataset, seed, GetDateTime

print("******* START *******")
print(GetDateTime())

for index_dataset in [20, 21, 22, 23, 24, 25, 26, 27, 28, 29]:   # change
	for number_generation in [100, 150, 200, 300]:   # change [100, 150, 200, 300] for select fitness under number generations
		print(dataset[index_dataset][0], number_generation)
		os.system("./main_fitness dataset/{}.cols {} {} dataset/{}.data {} {} > output/fitness/{}_{}.count"
		.format(dataset[index_dataset][0],
				dataset[index_dataset][1],
				dataset[index_dataset][2],
				dataset[index_dataset][0],
				seed[0],
				number_generation,
				dataset[index_dataset][0],
				number_generation))
print(GetDateTime())
print("******* END *******")
# Run:
# python count_fitness.py

# Output:
# files with name: (dataset name)_(number generation).count