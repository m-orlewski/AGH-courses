import matplotlib.pyplot as plt
import numpy as np


ks = [16, 8, 4, 2, 1]

x = []
y = []
for i, k in enumerate(ks):
    filename1 = "wyniki/S_k_" + str(k) + ".dat"
    filename2 = "wyniki/V_k_" + str(k) + ".dat"

    x.append([])
    y.append([])
    with open(filename1, "r") as f:
        for line in f:
            line = line.strip().split('\t')
            x[i].append(float(line[0]))
            y[i].append(float(line[1]))

for i,k in enumerate(ks):
    plt.plot(x[i], y[i], label=f'k = {k}')
    

plt.xscale('log')
plt.title('S(it)')
plt.xlabel('it')
plt.ylabel('S(it)')
plt.legend()
plt.savefig('wykresy/S_it.png')

