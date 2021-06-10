import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

file_input = [[], [], []]
with open("../wyniki/gauleg_2.dat", "r") as f:
	for line in f:
		args = line.strip().split(' ')
		for c, x in enumerate(args):
			file_input[c].append(float(x))

with open("../wyniki/gaulag_2.dat", "r") as f:
	for line in f:
		args = line.strip().split(' ')
		file_input[2].append(float(args[1]))

blue_patch = mpatches.Patch(color='blue', label='y2-Legendre')
black_patch = mpatches.Patch(color='black', label='y2-Laguerre')
plt.legend(handles=[blue_patch, black_patch])
plt.yscale("log")

x = np.array(file_input[0])
y1 = np.array(file_input[1])
y2 = np.array(file_input[2])

plt.ylim(ymin = 10e-9, ymax = 10e02)

plt.ylabel('|C_dok - C_num|')
plt.xlabel('n')
plt.plot(x, y1, "blue")
plt.plot(x, y2, "black")
plt.show()
