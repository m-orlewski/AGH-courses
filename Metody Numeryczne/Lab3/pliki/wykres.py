import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

liczby = [ [], [], [], [] ]
with open("../wyniki/double_0.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )

liczby2 = [ [], [], [], [] ]
with open("../wyniki/double_1.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split('\t')
        for counter, liczba in enumerate(podzielone):
            liczby2[counter].append( float(liczba) )


x = np.array(liczby[0])
y = np.array(liczby[3])

x1 = np.array(liczby2[0])
y1 = np.array(liczby2[3])

green_patch = mpatches.Patch(color='green', label='x_pocz=1')
blue_patch = mpatches.Patch(color='red', label='x_pocz=0')

plt.legend(handles=[green_patch, blue_patch])

plt.title("Metoda największego spadku(porównanie dla innych warunków początkowych)")
plt.xlabel("numer iteracji")
plt.ylabel(f"||x||\N{SUBSCRIPT TWO}")

plt.yscale(value="log")

plt.plot(x, y, 'r')
plt.plot(x1, y1, 'g')


plt.show()
