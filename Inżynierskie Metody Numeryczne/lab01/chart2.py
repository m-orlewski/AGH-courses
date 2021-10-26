import numpy as np
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def plot_rlc(filenames, figure_name):
    t = []
    i = []
    q = []

    for filename in filenames:
        t.append([])
        i.append([])
        q.append([])
        with open(filename, 'r') as f:
            for line in f:
                line = line.strip().split('\t')
                t[-1].append(float(line[0]))
                i[-1].append(float(line[1]))
                q[-1].append(float(line[2]))

    black_patch = mpatches.Patch(color='black', label='I(t)')
    red_patch = mpatches.Patch(color='red', label='Q(t)')


    plt.legend(handles=[black_patch, red_patch])
    plt.title('Metoda jawna RK4 - rozwiązanie RLC (wv = 0.5w0)')
    plt.xlabel('t')
    plt.ylabel('y(t)')

    plt.plot(t[0], i[0], color='black')
    plt.plot(t[0], q[0], color='red')

    plt.savefig(figure_name + '_1.png')
    plt.close()

    plt.title('Metoda jawna RK4 - rozwiązanie RLC (wv = 0.8w0)')
    plt.plot(t[1], i[1], color='black')
    plt.plot(t[1], q[1], color='red')

    plt.savefig(figure_name + '_2.png')
    plt.close()

    plt.title('Metoda jawna RK4 - rozwiązanie RLC (wv = 1.0w0)')
    plt.plot(t[2], i[2], color='black')
    plt.plot(t[2], q[2], color='red')

    plt.savefig(figure_name + '_3.png')
    plt.close()

    plt.title('Metoda jawna RK4 - rozwiązanie RLC (wv = 1.2w0)')
    plt.plot(t[3], i[3], color='black')
    plt.plot(t[3], q[3], color='red')

    plt.savefig(figure_name + '_4.png')
    plt.close()




