import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches
import math

file_input = [[], []]
with open("../wyniki/f3(x)p(x).dat", "r") as f:
    for line in f:
        args = line.strip().split(' ')
        for c, x in enumerate(args):
            file_input[c].append(float(x))


#plt.title('(x−10)^2 * sin(4x) * e^(−x)')
plt.title('x^7 * 2^(−x2+x+4) * e^(−x2)')
plt.plot(file_input[0], file_input[1])
plt.show()
