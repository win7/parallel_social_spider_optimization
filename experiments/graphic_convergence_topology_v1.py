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
Script for evaluate best topology (static and dinamic) about convergence
"""

import matplotlib.pyplot as plt
from matplotlib.ticker import NullFormatter  # useful for `logit` scale
import numpy as np
from utils import topology, dataset

print("******* START *******")

dataset_topology = [
	[9, 5, 2, 3, 7, 8, 4, 1, 6],	# d 20
	[],								# d 21
	[5, 7, 2, 6, 8, 9, 3, 1, 4],	# d 22
	[9, 5, 1, 2, 8, 3, 4, 6, 7],	# d 23
	[8, 7, 1, 5, 2, 4, 3, 6, 9],	# d 24
	[7, 8, 1, 5, 6, 4, 2, 3, 9],	# d 25
	[9, 8, 4, 5, 1, 2, 6, 7, 3],	# d 26
	[7, 4, 1, 2, 8, 9, 3, 5, 6],	# d 27
	[8, 6, 3, 4, 5, 7, 1, 2, 9],	# d 28
	[]								# d 29
]

number_subplot = 111
plt.subplot(number_subplot)

for index, index_topology in enumerate([0, 1, 2, 3, 4, 5, 6, 7, 8]):   # change [0, 1, 2, 3, 4, 5, 6, 7, 8]
	x = []	# dataset size
	y = []	# rankig by metric
	# load data for plot
	for index_dataset in [20, 22, 23, 24, 25, 26, 27, 28]:   # change [0, ..., 29]
		y.append(dataset_topology[index_dataset - 20][index])
		x.append(dataset[index_dataset][2])

	# draw mectric vs call fitness
	plt.plot(x, y, linestyle="-", label=topology[index_topology], linewidth=2, marker="")

plt.axvline(x=2000, label="Limit", color="k")

# naming the x axis 
plt.xlabel("Dataset size") 
# naming the y axis 
plt.ylabel("Rankig metric") 
# giving a title to my graph 
plt.title("Best Topology")
# add grid
plt.grid()

# show a legend on the plot 
plt.legend(loc="upper right", ncol=3, borderaxespad=0.2, prop={"size":9})


plt.subplots_adjust(top=0.96, bottom=0.065, left=0.06, right=0.985, hspace=0.260, wspace=0.150)

# function to show the plot 
plt.show()
print("******* END *******")

# Run:
# python graphic_convergence_topology_v1.py