import matplotlib.pyplot as plt
import numpy as np
import matplotlib.patches as mpatches

file_input1 = []
with open("../wyniki/hist_p_dok.dat", "r") as f:
    for line in f:
        line = line.strip()
        file_input1.append( float(line) )

file_input2 = []
with open("../wyniki/hist_p_num.dat", "r") as f:
    for line in f:
        line = line.strip()
        file_input2.append( float(line) )

y1 = np.array(file_input2)
y2 = np.array(file_input1)
x1 = np.array([(0.1 * i) + 0.025 for i in range(10)])
x2 = np.array([x + 0.05 for x in x1])


plt.xticks(np.arange(0, 1, step=0.1))
plt.bar(x1,y1,width=0.040,label='num', color='blue', align='center')
plt.bar(x2,y2,width=0.040,label='dok', color='red', align='center')
plt.legend(framealpha=1,frameon=True)
plt.xlabel('x')
plt.ylabel('pi')


plt.show()

