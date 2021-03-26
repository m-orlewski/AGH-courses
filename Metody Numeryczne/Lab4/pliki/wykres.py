import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

liczby = [ [], [], [], [], [], [], [] ]
with open("../wyniki/alfa.txt", "r") as f:
    for line in f:
        podzielone = line.strip().split(' ')
        for counter, liczba in enumerate(podzielone):
            liczby[counter].append( float(liczba) )


alfa = np.array(liczby[0])
w1 = np.array(liczby[1])
w2 = np.array(liczby[2])
w3 = np.array(liczby[3])
w4 = np.array(liczby[4])
w5 = np.array(liczby[5])
w6 = np.array(liczby[6])

red_patch = mpatches.Patch(color='red', label='\u03C9 0')
green_patch = mpatches.Patch(color='green', label='\u03C9 1')
blue_patch = mpatches.Patch(color='blue', label='\u03C9 2')
cyan_patch = mpatches.Patch(color='cyan', label='\u03C9 3')
magenta_patch = mpatches.Patch(color='magenta', label='\u03C9 4')
black_patch = mpatches.Patch(color='black', label='\u03C9 5')

plt.legend(handles=[red_patch, green_patch, blue_patch, cyan_patch, magenta_patch, black_patch])

plt.title("Wartości własne w funkcji parametru \u03B1")
plt.xlabel("\u03B1")
plt.ylabel("wartości własne")


plt.plot(alfa, w1, 'r')
plt.plot(alfa, w2, 'g')
plt.plot(alfa, w3, 'b')
plt.plot(alfa, w4, 'c')
plt.plot(alfa, w5, 'm')
plt.plot(alfa, w6, 'k')

plt.ylim(ymin=0, ymax=0.25)
plt.xlim(left=0, right=100)


plt.show()
