import pyswarms as ps
from pyswarms.utils.functions import single_obj as fx
from pyswarms.utils.plotters import plot_contour, plot_surface
from pyswarms.utils.plotters.formatters import Mesher, Designer
import matplotlib.pyplot as plt
from matplotlib.animation import Animation
import numpy as np


pop = 20
it = 50
c1 = 0.5
c2 = 0.3


def f(x):
    x_ = x[:, 0]
    y_ = x[:, 1]

    j = x_**2 + y_**2 - 20 * (np.cos(np.pi*x_) + np.cos(np.pi*y_) - 2)

    return j


if __name__ == '__main__':

    max_bound = 10.0 * np.ones(2)
    min_bound = -max_bound
    bounds = (min_bound, max_bound)

    options = {'c1': c1, 'c2': c2, 'w': 0.9}
    optimizer = ps.single.GlobalBestPSO(n_particles=pop, dimensions=2, options=options, bounds=bounds)

    avg_pos = [0, 0]
    avg_cost = 0

    first_optimizer = None
    for i in range(10):
        cost, pos = optimizer.optimize(f, iters=it)
        avg_pos[0] += pos[0]
        avg_pos[1] += pos[1]
        avg_cost += cost

        if not first_optimizer:
            first_optimizer = optimizer

    avg_pos[0] /= 10
    avg_pos[1] /= 10
    avg_cost /= 10

    print(f'Best average pos: {avg_pos} with best average cost: {avg_cost}')

    m = Mesher(func=f)
    
    animation = plot_contour(pos_history=first_optimizer.pos_history,
                             mesher=m, mark=(0, 0))

    plt.show()
    '''

    pos_history_3d = m.compute_history_3d(first_optimizer.pos_history)
    d = Designer(limits=[(-10, 10), (-10, 10), (-10, 10)], label=['x_axis', 'y_axis', 'z_axis'])
    animation3d = plot_surface(pos_history=pos_history_3d, mesher=m, designer=d, mark=(0,0,0))

    plt.show()
    '''

    