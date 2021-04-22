import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import math

liczby = [ [], [], []]
with open("../wyniki/xi1_15.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )

green_patch = mpatches.Patch(color='green', label='f(x)=x/(1+x^2)')
blue_patch = mpatches.Patch(color='blue', label='f(x) (węzły optymalne)')
orange_patch = mpatches.Patch(color='orange', label='f(x) (zera w. Czebyszewa)')

plt.legend(handles=[green_patch, blue_patch, orange_patch])

x = np.array(liczby[0])
y1 = np.array(liczby[1])
y2 = np.array(liczby[2])


plt.title("Interpolacja Lagrange'a dla 15 węzłów")
plt.xlabel('x')
plt.ylabel('f(x)')
plt.xlim(left=-3, right=8)

plt.plot(x, y1, 'b')
plt.plot(x, y2, 'orange')
plt.plot(x, x/(1+x**2), 'g')


plt.show()
