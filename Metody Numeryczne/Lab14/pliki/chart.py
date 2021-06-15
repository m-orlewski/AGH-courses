import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

file_input = [[], []]
with open("../wyniki/gen_miesz_1.dat", "r") as f:
    for line in f:
        line = line.strip().split(' ')
        for c, x in enumerate(line):
            file_input[c].append( float(x) )

x = np.array(file_input[0])
y = np.array(file_input[1])

plt.xlabel('X[i]')
plt.ylabel('X[i+1] = f(X[i])')
plt.title('Generator mieszany o rozkładzie jednorodnym (a = 123, c = 1, m=2^15)')

plt.plot(x, y, '.', markersize=1)
plt.show()