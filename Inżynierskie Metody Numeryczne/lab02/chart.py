import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

data = [[[], []], [[], []], [[], []]]
filenames = ['wyniki/picard.dat', 'wyniki/newton.dat', 'wyniki/rk2.dat']

for i, filename in enumerate(filenames):
    with open(filename, 'r') as f:
        for line in f:
            line = line.strip().split('\t')
            data[i][0].append(float(line[0]))
            data[i][1].append(float(line[1]))

plt.plot(data[0][0], data[0][1])
z = [500 - u for u in data[0][1]]
plt.plot(data[0][0], z)
plt.legend(['u(t)', 'z(t)'])

plt.savefig('wykresy/picard.png')
plt.close()

plt.plot(data[1][0], data[1][1])
z = [500 - u for u in data[1][1]]
plt.plot(data[1][0], z)
plt.legend(['u(t)', 'z(t)'])

plt.savefig('wykresy/newton.png')
plt.close()

plt.plot(data[2][0], data[2][1])
z = [500 - u for u in data[2][1]]
plt.plot(data[2][0], z)
plt.legend(['u(t)', 'z(t)'])

plt.savefig('wykresy/rk2.png')
plt.close()
