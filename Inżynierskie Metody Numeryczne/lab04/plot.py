import matplotlib.pyplot as plt

filenames = ['wyniki/global_0_6.dat', 'wyniki/global_1_0.dat', 'wyniki/local_1_0.dat', 'wyniki/local_1_4.dat', 'wyniki/local_1_8.dat', 'wyniki/local_1_9.dat']

data = []

for i, filename in enumerate(filenames):
    data.append([[], []])
    with open(filename, "r") as f:
        for line in f:
            line = line.strip().split()
            data[i][0].append(float(line[0]))
            data[i][1].append(float(line[1]))


plt.plot(data[0][0], data[0][1], label='wg = 0.6')
plt.plot(data[1][0], data[1][1], label='wg = 1.0')
plt.xscale('log')
plt.title('S(it) - relaksacja globalna')
plt.xlabel('it')
plt.ylabel('S(it)')
plt.legend()
plt.savefig('wykresy/global_s_it.png')

plt.close()
plt.plot(data[2][0], data[2][1], label='wg = 1.0')
plt.plot(data[3][0], data[3][1], label='wg = 1.4')
plt.plot(data[4][0], data[4][1], label='wg = 1.8')
plt.plot(data[5][0], data[5][1], label='wg = 1.9')
plt.xscale('log')
plt.title('S(it) - relaksacja lokalna')
plt.xlabel('it')
plt.ylabel('S(it)')
plt.legend()
plt.savefig('wykresy/local_s_it.png')