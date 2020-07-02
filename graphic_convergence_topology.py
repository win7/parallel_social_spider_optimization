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

rankig_low = []		# ranking metric for low dataset
rankig_high = []	# ranking metric for high dataset
rankig_all = []		# ranking metric low and high dataset

for index, index_topology in enumerate([0, 1, 2, 3, 4, 5, 6, 7, 8]):   # change [0, 1, 2, 3, 4, 5, 6, 7, 8]
	
	# load data for plot
	rankig_l = []
	rankig_h = []
	rankig_a = []
	for index_dataset in [20, 22, 23, 24, 25, 26, 27, 28]:   # change [0, ..., 29]
		if index_dataset >= 26:
			rankig_h.append(dataset_topology[index_dataset - 20][index])
		else:
			rankig_l.append(dataset_topology[index_dataset - 20][index])
		rankig_a.append(dataset_topology[index_dataset - 20][index])

	rankig_low.append(np.sum(rankig_l))
	rankig_high.append(np.sum(rankig_h))
	rankig_all.append(np.sum(rankig_a))

labels = topology
# rankig_low = [20, 34, 30, 35, 27]
# rankig_high = [25, 32, 34, 20, 25]

x = np.arange(len(labels))  # the label locations
width = 0.25  # the width of the bars

fig, ax = plt.subplots()
rects1 = ax.bar(x - width / 2, rankig_low, width, label='Low size')
rects2 = ax.bar(x + width / 2, rankig_high, width, label='High size')

"""rects1 = ax.bar(x - width, rankig_low, width, label='Low size')
rects2 = ax.bar(x, rankig_high, width, label='High size')
rects3 = ax.bar(x + width, rankig_all, width, label='All') """

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel("Scores")
ax.set_xlabel("Topology")
ax.set_title("Best Topology")
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

def autolabel(rects):
    """Attach a text label above each bar in *rects*, displaying its height."""
    for rect in rects:
        height = rect.get_height()
        ax.annotate('{}'.format(height),
                    xy=(rect.get_x() + rect.get_width() / 2, height),
                    xytext=(0, 3),  # 3 points vertical offset
                    textcoords="offset points",
                    ha='center', va='bottom')

autolabel(rects1)
autolabel(rects2)
# autolabel(rects3)

fig.tight_layout()

plt.grid()
plt.show()

print("******* END *******")

# Run:
# python graphic_convergence_topology.py