import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

m = [0, 1, 5]
k = [1, 1, 5]


for i in range(3):
    simpson = [ [], [] ]
    end = "_m" + str(m[i]) + "_k" + str(k[i]) + ".dat"
    with open("simpson" + end, "r") as f:
        for line in f:
            podzielone = line.strip().split('\t')
            for counter, liczba in enumerate(podzielone):
                simpson[counter].append( float(liczba) if counter == 1 else int(liczba))

    analityczne = [[]]
    with open("sumy" + end, "r") as f:
        for line in f:
            podzielone = line.strip().split('\t')
            for counter, liczba in enumerate(podzielone):
                analityczne[counter].append( float(liczba))

    x1 = np.array(simpson[0])
    y2 = analityczne[0][len(analityczne[0])-1]
    y1 = np.array([abs(simpson[1][i]-y2) for i in range(len(simpson[1]))])

    blue_patch = mpatches.Patch(color='blue', label='|C-I|')
    orange_patch = mpatches.Patch(color='orange', label='0.0')

    plt.legend(handles=[blue_patch, orange_patch])

    plt.title("Wykres zależności |C-I| od liczby węzłów dla m = " + str(m[i]) + " k = " + str(k[i]))
    plt.plot(x1, y1, 'o')
    plt.plot([0, 210], [0, 0])
    plt.show()
