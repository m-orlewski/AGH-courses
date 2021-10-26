import matplotlib.pyplot as plt
import matplotlib.patches as mpatches

def plot(plot_title, err_plot_title, filenames, figure_name):
    x = []
    y = []
    y_dok = []
    y_err = []

    for filename in filenames:
        x.append([])
        y.append([])
        y_dok.append([])
        y_err.append([])
        with open(filename, 'r') as f:
            for line in f:
                line = line.strip().split('\t')
                x[-1].append(float(line[0]))
                y[-1].append(float(line[1]))
                y_dok[-1].append(float(line[2]))
                y_err[-1].append(float(line[3]))

    black_patch = mpatches.Patch(color='black', label='dt=0.01')
    red_patch = mpatches.Patch(color='red', label='dt=0.10')
    blue_patch = mpatches.Patch(color='blue', label='dt=1.00')
    green_patch = mpatches.Patch(color='green', label='wart. dokł')

    plt.legend(handles=[black_patch, red_patch, blue_patch, green_patch])
    plt.title(plot_title)
    plt.xlabel('t')
    plt.ylabel('y(t)')

    plt.plot(x[0], y[0], color='black')
    plt.plot(x[1], y[1], color='red')
    plt.plot(x[2], y[2], color='blue')
    plt.plot(x[0], y_dok[0], color='green')

    plt.savefig(figure_name + '.png')
    plt.close()

    black_patch = mpatches.Patch(color='black', label='dt=0.01')
    red_patch = mpatches.Patch(color='red', label='dt=0.10')
    blue_patch = mpatches.Patch(color='blue', label='dt=1.00')

    plt.legend(handles=[black_patch, red_patch, blue_patch])
    plt.title(err_plot_title)
    plt.xlabel('t')
    plt.ylabel('y(t)-y_dok(t)')

    plt.plot(x[0], y_err[0], color='black')
    plt.plot(x[1], y_err[1], color='red')
    plt.plot(x[2], y_err[2], color='blue')

    plt.savefig(figure_name + '_err.png')
    plt.close()



