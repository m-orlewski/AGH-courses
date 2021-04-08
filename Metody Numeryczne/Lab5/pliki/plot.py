import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

iteracje = [i for i in range(1, 13)]
liczby = [ [], [], [], [], [], [], [] ]
with open("../wyniki/lambdas.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split(' ')
        if podzielone[0] != '':
            liczby[int(podzielone[0])].append(float(podzielone[2]))

l1 = np.array(liczby[0])
l2 = np.array(liczby[1])
l3 = np.array(liczby[2])
l4 = np.array(liczby[3])
l5 = np.array(liczby[4])
l6 = np.array(liczby[5])

print(liczby[0])

red_patch = mpatches.Patch(color='red', label='k=0')
green_patch = mpatches.Patch(color='green', label='k=1')
blue_patch = mpatches.Patch(color='blue', label='k=2')
cyan_patch = mpatches.Patch(color='cyan', label='k=3')
magenta_patch = mpatches.Patch(color='magenta', label='k=4')
black_patch = mpatches.Patch(color='black', label='k=5')

plt.legend(handles=[red_patch, green_patch, blue_patch, cyan_patch, magenta_patch, black_patch])

plt.title("Przybliżenia wartości własnych w kolejnych iteracjach")
plt.xlabel("Numer iteracji")
plt.ylabel("Wartość własna")

plt.plot(iteracje, l1, 'r')
plt.plot(iteracje, l2, 'g')
plt.plot(iteracje, l3, 'b')
plt.plot(iteracje, l4, 'c')
plt.plot(iteracje, l5, 'm')
plt.plot(iteracje, l6, 'k')

plt.show()

plt.ylim(ymin=0, ymax=3.7)
plt.xlim(left=0, right=12)
