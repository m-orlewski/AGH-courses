import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

liczby = [ [], [], [] ]
with open("results500.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )

green_patch = mpatches.Patch(color='green', label='V(x)-teoretyczne')
blue_patch = mpatches.Patch(color='blue', label='V(x)-numeryczne')

plt.legend(handles=[green_patch, blue_patch])

x = np.array(liczby[0])
y1 = np.array(liczby[1])
y2 = np.array(liczby[2])

plt.title("Wykres zależności V(x) dla N=500")

print(x)
print(y1)
print(y2)

plt.plot(x, y1, 'b')

plt.plot(x, y2, 'g')

plt.show()
