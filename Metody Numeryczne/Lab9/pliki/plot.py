import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import math

liczby = [ [], [] ]
with open("g_aprox2_N101.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )

liczby2 = [ [], [] ]
with open("node_values_N101.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby2[counter].append( float(liczba) )

#green_patch = mpatches.Patch(color='green', label='G(x)')
#orange_patch = mpatches.Patch(color='orange', label='g(x)')

#plt.legend(handles=[green_patch, orange_patch])

x = np.array(liczby[0])
y1 = np.array(liczby[1])
x2 = np.array(liczby2[0])
y2 = np.array(liczby2[1])


plt.title("Wykres G(x) i wartości g(x) w węzłach (N=101)")
plt.xlabel('x')
plt.ylabel('g(x)')
plt.xlim(left=-10, right=14)

plt.scatter(x2, y2, s=5)
plt.plot(x, y1, 'red')



plt.show()
