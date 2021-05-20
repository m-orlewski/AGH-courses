import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

liczby = [ [], [], []]
with open("k12_niezab.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split(' ')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )


red_patch = mpatches.Patch(color='blue', label='niezaburzone')
black_patch = mpatches.Patch(color='black', label='splot')

plt.legend(handles=[red_patch, black_patch])

x = np.array(liczby[0])
y1 = np.array(liczby[1])
y2 = np.array(liczby[2])

plt.xlim(left=0, right=x[len(x)-1])
plt.plot(x, y1, "black")
plt.scatter(x, y2, s=5)

plt.show()
