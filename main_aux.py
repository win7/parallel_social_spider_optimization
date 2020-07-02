import numpy as np
import matplotlib.pyplot as plt

columns = 2
rows = 5
for i in range(rows):
    for j in range(columns):
        print(i, j)

print()
for count in range(10):
	print(int((count - (count % columns))/ columns), count % columns)

def make_plot(axs):
    box = dict(facecolor='yellow', pad=5, alpha=0.2)

    # Fixing random state for reproducibility
    np.random.seed(19680801)
    ax1 = axs[0, 0]
    ax1.plot(2000*np.random.rand(10))
    ax1.set_title('ylabels not aligned')
    ax1.set_ylabel('misaligned 1', bbox=box)
    ax1.set_ylim(0, 2000)

    ax3 = axs[1, 0]
    ax3.set_ylabel('misaligned 2', bbox=box)
    ax3.plot(np.random.rand(10))

    ax2 = axs[0, 1]
    ax2.set_title('ylabels aligned')
    ax2.plot(2000*np.random.rand(10))
    ax2.set_ylabel('aligned 1', bbox=box)
    ax2.set_ylim(0, 2000)

    ax4 = axs[1, 1]
    ax4.plot(np.random.rand(10))
    ax4.set_ylabel('aligned 2', bbox=box)


# Plot 1:
fig, axs = plt.subplots(2, 2)
fig.subplots_adjust(left=0.2, wspace=0.6)
make_plot(axs)

# just align the last column of axes:
fig.align_ylabels(axs[:, 1])
plt.show()

# Example for generate ranking calification for islandssss
""" import numpy as np

def insertSort(list_):
	for k in range(1, len(list_)):
		key = list(list_[k].keys())[0]
		value = list(list_[k].values())[0]
		index = k - 1;

		while index >= 0 and list(list_[index].values())[0] > value:
			list_[index + 1] = list_[index]
			index -= 1
		list_[index + 1] = {key: value}
	return list_

def printList(list_):
	for item in list_:
		print(item)
	print()

np.random.seed(19680801)
world_size = 24
p = []
s = []
for k in range(24):
	population = np.random.rand(1, 10) + 97
	mean_ = np.mean(population)
	std_ = np.std(population)
	p.append({k: round(mean_, 3)})
	s.append({k: round(std_, 3)})

p_ = insertSort(p)
printList(p_)

s_ = insertSort(s)
printList(s_)

ranking = [{0:0}]*world_size
for k in range(world_size):
	key = list(p_[k].keys())[0]
	value = list(ranking[key].values())[0] + k + 1
	ranking[key] = {key: value}

	key = list(s_[k].keys())[0]
	value = list(ranking[key].values())[0] + world_size - k
	ranking[key] = {key: value}

printList(ranking)
ranking_ = insertSort(ranking)
printList(ranking_) """

"""
MEAN
{4: 97.279}
{3: 97.353}
{21: 97.369}
{20: 97.399}
{23: 97.399}
{5: 97.411}
{13: 97.423}
{8: 97.433}
{17: 97.442}
{11: 97.454}
{16: 97.485}
{0: 97.49}
{19: 97.499}
{12: 97.513}
{6: 97.521}
{1: 97.529}
{10: 97.531}
{2: 97.544}
{7: 97.566}
{15: 97.608}
{14: 97.621}
{22: 97.696}
{9: 97.745}
{18: 97.748}
STD
{4: 0.186}
{19: 0.186}
{23: 0.201}
{15: 0.207}
{18: 0.217}
{11: 0.242}
{17: 0.243}
{9: 0.25}
{10: 0.25}
{6: 0.252}
{12: 0.252}
{1: 0.258}
{22: 0.27}
{7: 0.273}
{2: 0.282}
{3: 0.293}
{0: 0.295}
{8: 0.296}
{5: 0.301}
{13: 0.302}
{16: 0.308}
{21: 0.315}
{20: 0.321}
{14: 0.33}
RANKING
{0: 20}
{1: 29}
{2: 28}
{3: 11}
{4: 25}
{5: 12}
{6: 30}
{7: 30}
{8: 15}
{9: 40}
{10: 33}
{11: 29}
{12: 28}
{13: 12}
{14: 22}
{15: 41}
{16: 15}
{17: 27}
{18: 44}
{19: 36}
{20: 6}
{21: 6}
{22: 34}
{23: 27}
ORDER RANKING
{20: 6}
{21: 6}
{3: 11}
{5: 12}
{13: 12}
{8: 15}
{16: 15}
{0: 20}
{14: 22}
{4: 25}
{17: 27}
{23: 27}
{2: 28}
{12: 28}
{1: 29}
{11: 29}
{6: 30}
{7: 30}
{10: 33}
{22: 34}
{19: 36}
{9: 40}
{15: 41}
{18: 44}
"""

""" prices = {'Apple': 1.99, 'Banana': 1.99, 'Orange': 1.49, 'Cantaloupe': 3.99, 'Grapes': 0.39}

for i in sorted (prices.items(), key = lambda x : x[1]):
	print(i) """

""" key_list = list(topology_best.keys())
	values_list = list(topology_best.values())
	print(key_list)
	print(values_list)
	for i in sorted (values_list):
		print(i, key_list[values_list.index(i)]) """

""" topology = {}
   
" topology[2.278282] = "a"
topology[2.372282] = "o"
topology[2.518282] = "e"
topology[2.478211] = "u"
topology[2.478211] = "i" ""

topology["i"] = 2.278282
topology["e"] = 2.372282
topology["a"] = 2.518282
topology["u"] = 2.478211
topology["o"] = 2.478211

key_list = list(topology.keys()) 
val_list = list(topology.values()) 

for i in sorted (val_list) :  
	print(i, key_list[val_list.index(i)]) """


""" a = [1, 2, 3, 4, 5]
b = [1, 2, 3, 4, 5, 6]
c = a + b
print(c) """

"""
L = [
[92157640.884068,2.278282],
[92154390.458411,2.327390],
[92154390.458411,2.366919],
[92154390.458411,2.394073],
[92154390.458411,2.340547],
[92177192.731755,2.539666],
[92154390.458411,2.193075],
[92154390.458411,2.494308],
[92157640.884068,2.840769],
[92167878.023127,2.727679]
]
sum_ = 0
for item in L:
	sum_ += item[0]
print(sum_/10)
"""
"""
A = [
[1, 17718.551714, 343.607878],
[7, 17739.405028, 244.319429],
[23, 17724.298986, 204.813338],
[23, 17718.865249, 358.892953],
[13, 17714.889719, 240.617752],
[2, 17710.252194, 813.696202],
[18, 17711.015264, 268.167102],
[23, 17757.554079, 566.323329],
[1, 17719.347366, 1883.430679],
[6, 17722.897049, 404.535372],
[8, 17722.936796, 1261.940644],
[23, 17732.904773, 1584.724337],
[8, 17715.746987, 273.114712],
[1, 17720.540877, 382.975152],
[7, 17725.062465, 1121.647296],
[17, 17726.983519, 717.745858],
[13, 17711.424994, 724.489592],
[21, 17722.600993, 695.437479],
[9, 17749.361905, 1103.004653],
[17, 17715.303039, 862.942001],
[9, 17707.021485, 606.213904],
[8, 17748.652042, 1776.959402],
[5, 17713.865156, 2174.713316],
[20, 17726.445881, 312.006843],
[1, 17731.956775, 562.830586],
[19, 17720.789571, 1147.453452],
[7, 17725.222703, 1433.624017],
[20, 17730.157038, 377.060862],
[19, 17718.114015, 1257.130706]
]
sum_ = 0
for item in A:
	sum_ += item[2]
average = sum_/len(A)

hr = int(sum_ / 3600)
aux1 = sum_ % 3600
min_ = int(aux1 / 60)
seg = int(aux1 % 60)
print("{} {}".format(int(average / 60), len(A)))
print("{}:{}:{}".format(hr, min_, seg)) """

""" n = 12
l = []
for k in range(1, 13):
	l = []
	while True:
		l.append(k)
		if sum(l) == 26 and len(l) == 4:
			print(l)
			break
		else:
			if sum(l) < 26 and len(l) == 4:
				l.pop()
			else:
				if sum(l) > 26:
					break
			k += 1
			if k == 13:
				k = l.pop() + 1 """
 
""" import math
A = [5, 15, 12, 18, 28]
average = sum(A) / len(A)
sum_ = 0
for x in A:
	sum_ += math.pow(x - average, 2)
S = math.sqrt(sum_ / (len(A)))
print(S) """

""" for i in range(3):
	for j in range(4):
		print(i * 4 + j) """

""" list_ = [
18977.822610799998,
18971.543938500003,
18977.319591700005,
18990.7368599,
18979.1061216,
18974.972229700004,
18975.0548728,
18975.400300200003,
18978.0378756,
18988.5755202,
18989.217478900002,
18984.294685,
18977.398903400004,
18969.622389300002,
18970.801222900005,
18975.2219213,
18976.6059233,
18976.7279814
]
print(min(list_))
print(list_.index(min(list_)) + 1)
print("\a") """

""" import numpy as np
import matplotlib.pyplot as plt

x = np.random_.randn(10)
y = np.random_.randn(10)
z = np.random_.randn(10)
print(x)
print(y)
Cluster = np.array([0, 1, 1, 1, 3, 2, 2, 3, 0, 2])    # Labels of cluster 0 to 3
print(Cluster)
centers = np.random_.randn(4, 2) 
print(centers)

fig = plt.figure()
ax = fig.add_subplot(111)
scatter = ax.scatter(x,y,c=Cluster,s=50)
for i,j in centers:
	ax.scatter(i,j,s=50,c='red',marker='+')
ax.set_xlabel('x')
ax.set_ylabel('y')
plt.colorbar(scatter)
#3fig.show()
plt.savefig("plot_cluster.png") """

"""" numberEmiImm = 5
numberCluster = 3
pointDimension = 4
orderNode = 2 # ayuda a ver que porcion del arreglo de fitness (ordenado) se empaquetara para enviar, segun en numberEmiImm
lengthSpider = 100
for k in range(numberEmiImm):
	print((orderNode - 1) * numberEmiImm + k)
	print(lengthSpider -1 - ((orderNode - 1) * numberEmiImm + k))
	for i in range(numberCluster):
		for j in range(pointDimension):
			print(((k * numberCluster + i) * pointDimension + j), i, j) """

####### Topology #######
""" print("ring")
np = 24
for k in range(np):
	print k,
	print(((k + 1) % np), ((k + np - 1) % np)) """

""" print("tree")
np = 24
for k in range(24):
	if k == 0:
		a = 2 * k + 1
		b = 2 * k + 2
		print k,
		print(a, b)
	elif k >= 1 and k <= 6:
		a = (k - 1) / 2
		b = 2 * k + 1
		c = 2 * k + 2
		print k,
		print(a, b, c)
	elif k >= 7 and k <= 15:
		a = (k - 1) / 2
		b = k + 8
		print k,
		print(a, b)
	else:
		a = k - 8
		print k,
		print(a) """

""" print("red A 6x4")
np = 24
A = [5, 6, 9 ,10, 13, 14, 17, 18]
B = [0, 4, 8, 12, 16, 20]
C = [3, 7, 11, 15, 19, 23]
D = [1, 2]
E = [21, 22]

for k in A:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 1) % 24
	d = (k + 4) % 24
	print "A ", k,
	print(a, b, c, d)

for k in B:
	a = (k - 4 + 24) % 24
	b = (k + 1) % 24
	c = (k + 4) % 24
	print "B ", k,
	print(a, b, c)

for k in C:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 4) % 24
	print "C ", k,
	print(a, b, c)

for k in D:
	a = (k - 1 + 24) % 24
	b = (k + 1) % 24
	c = (k + 4) % 24
	print "D ", k,
	print(a, b, c)

for k in E:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 1) % 24
	print "E ", k,
	print(a, b, c) """

""" print("red B 6x4")
np = 24
A = [9 ,10, 13,14]
B = [0, 4, 6, 8, 12, 16, 18, 20]
C = [3, 5, 7, 11, 15, 17, 19, 23]
D = [1, 2]
E = [21, 22]

for k in A:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 1) % 24
	d = (k + 4) % 24
	print "A ", k,
	print(a, b, c, d)

for k in B:
	a = (k - 4 + 24) % 24
	b = (k + 1) % 24
	c = (k + 4) % 24
	print "B ", k,
	print(a, b, c)

for k in C:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 4) % 24
	print "C ", k,
	print(a, b, c)

for k in D:
	a = (k - 1 + 24) % 24
	b = (k + 1) % 24
	c = (k + 4) % 24
	print "D ", k,
	print(a, b, c)

for k in E:
	a = (k - 4 + 24) % 24
	b = (k - 1 + 24) % 24
	c = (k + 1) % 24
	print "E ", k,
	print(a, b, c) """

""" print("torus 6x4")
np = 24
A = [1, 2, 5, 6, 9, 10, 13, 14, 17, 18, 21, 22]     # i i+1, (i+4) (i+4) +1
B = [0, 4, 8, 12, 16, 20]                           # if id mod 4 = 0
C = [3, 7, 11, 15, 19, 23]                          #if id mod 4 = 3

for k in range(24):
	if k % 4 == 0:
		a = (k - 4 + 24) % 24
		b = (k + 1) % 24
		c = (k + 3) % 24
		d = (k + 4) % 24
		print k,
		print(a, b, c, d)
	elif k % 4 == 3:
		a = (k - 4 + 24) % 24
		b = (k - 3 + 24) % 24
		c = (k - 1 + 24) % 24
		d = (k + 4) % 24
		print k,
		print(a, b, c, d)
	else:
		a = (k - 4 + 24) % 24
		b = (k - 1 + 24) % 24
		c = (k + 1) % 24
		d = (k + 4) % 24
		print k,
		print(a, b, c, d) """

""" print("graph")
np = 24
for k in range(np):
	print k,
	for i in range(np):
		if i != k:
			print i,
	print """