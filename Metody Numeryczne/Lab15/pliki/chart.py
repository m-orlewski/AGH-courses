import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

I = 0.2557840245

file_input1 = [[], [], []]
with open("../wyniki/kwadratura_mc.dat", "r") as f:
    for line in f:
        line = line.strip().split(' ')
        for c, x in enumerate(line):
            file_input1[c].append( float(x) )

file_input2 = [[], [], []]
with open("../wyniki/roz_exp.dat", "r") as f:
    for line in f:
        line = line.strip().split(' ')
        for c, x in enumerate(line):
            file_input2[c].append( float(x) )


x = np.array(file_input1[0])
y1 = np.array(file_input1[1])
y2 = np.array(file_input2[1])
sig1 = np.array(file_input1[2])
sig2 = np.array(file_input2[2])

#plot 1
'''
plt.xlabel('N')
plt.ylabel('I_num')
plt.xlim(left = 10, right = 100000)
plt.xscale('log')

black_patch = mpatches.Patch(color='black', label='sposob-1')
red_patch = mpatches.Patch(color='red', label='sposob-2')

plt.legend(handles=[black_patch, red_patch])
plt.plot(x, y1, 'black')
plt.plot(x, y2, 'red')
'''

#plot2

plt.xlabel('N')
plt.ylabel('error')
plt.xlim(left = 10, right = 100000)
plt.ylim(ymin = 1e-5, ymax = 1e-1)
plt.xscale('log')
plt.yscale('log')

black_patch = mpatches.Patch(color='black', label='sigma-1')
red_patch = mpatches.Patch(color='red', label='|Idok - Inum|1')
blue_patch = mpatches.Patch(color='blue', label='sigma-2')
green_patch = mpatches.Patch(color='green', label='|Idok - Inum|2')

plt.legend(handles=[black_patch, red_patch, blue_patch, green_patch])

plt.plot(x, sig1, 'black')
plt.plot(x, sig2, 'blue')

for i in range(len(x)):
	y1[i] = abs(y1[i] - I)
	y2[i] = abs(y2[i] - I)

plt.plot(x, y1, 'red')
plt.plot(x, y2, 'green')

plt.show()
