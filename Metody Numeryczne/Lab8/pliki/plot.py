import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import math

liczby = [ [], [], []]
with open("f2n5.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split(' ')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )

green_patch = mpatches.Patch(color='green', label='s(x)')
orange_patch = mpatches.Patch(color='orange', label='f(x)=cos(2x)')

plt.legend(handles=[green_patch, orange_patch])

x = np.array(liczby[0])
y1 = np.array(liczby[1])
y2 = np.array(liczby[2])


plt.title("Funkcja interpolowana f(x) i interpolująca s(x) (n=5)")
plt.xlabel('x')
plt.ylabel('f(x)')
plt.xlim(left=-5, right=5)

plt.plot(x, y1, 'g')
plt.plot(x, y2, 'orange')


plt.show()
