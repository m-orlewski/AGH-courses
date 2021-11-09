import matplotlib.pyplot as plt

def f(x, v):
    return v

def g(x, v, alfa):
    return alfa * (1 - x * x)*v - x

def rk2(x, v, dt, alfa):
    k1x = f(x, v)
    k1v = g(x, v, alfa)

    k2x = f(x + dt*k1x, v + dt*k1v)
    k2v = g(x + dt*k1x, v + dt*k1v, alfa)

    x_n1 = x + dt/2 * (k1x + k2x)
    v_n1 = v + dt/2 * (k1v + k2v)

    return (x_n1, v_n1)

def trapez(x, v, dt, alfa):
    x_n1 = x
    v_n1 = v
    while True:
        a11 = 1
        a12 = -dt/2
        a21 = -dt/2 * (-2*alfa*x_n1*v_n1 - 1)
        a22 = 1 - dt/2*alfa*(1 - x_n1*x_n1)

        F = x_n1 - x - dt/2 * (f(x, v) + f(x_n1, v_n1))
        G = v_n1 - v - dt/2 * (g(x, v, alfa) + g(x_n1, v_n1, alfa))

        

        dx = (-F * a22 + G * a12) / (a11*a22 - a12*a21)
        dv = (-G * a11 + F * a21) / (a11*a22 - a12*a21)

        x_n1 += dx
        v_n1 += dv

        if abs(dx) < 1e-10 and abs(dv) < 1e-10:
            break
    return x_n1, v_n1


def time_step(schemat, TOL, filename):
    alfa = 5
    t_max = 40
    xn = 0.01
    vn = 0
    dt = 1
    p = 2
    t = 0
    S = 0.75

    result = [[], [], [], []]
    f = open(filename, "w")

    while True:
        x_n1, v_n1 = schemat(xn, vn, dt, alfa)
        x_n2_2, v_n2_2 = schemat(x_n1, v_n1, dt, alfa)
        x_n2_1, v_n2_1 = schemat(xn, vn, 2*dt, alfa)

        E_x = (x_n2_2 - x_n2_1) / (2**p - 1)
        E_v = (v_n2_2 - v_n2_1) / (2**p - 1)
        print(max(abs(E_x), abs(E_v)))

        if max(abs(E_x), abs(E_v)) < TOL:
            t += 2 * dt
            xn = x_n2_2
            vn = v_n2_2
            f.write(f'{t},{dt},{xn},{vn}\n')
            result[0].append(t)
            result[1].append(dt)
            result[2].append(xn)
            result[3].append(vn)

        dt = ((S * TOL) / (max(abs(E_x), abs(E_v)))) ** (1 / (p+1)) * dt

        if t > t_max:
            break

    f.close()
    return result

def plot_results(x1, y1, x2, y2, title, filename):
    plt.close()
    plt.title(title)
    plt.plot(x1, y1, label='TOL=1e-2')
    plt.plot(x2, y2, label='TOL=1e-5')
    plt.legend()

    plt.savefig(filename)


if __name__ == '__main__':
    tr_1 = time_step(trapez, 1e-2, 'wyniki/trapez_1.csv')
'''    tr_2 = time_step(trapez, 1e-5, 'wyniki/trapez_2.csv')
    
    rk2_1 = time_step(rk2, 1e-2, 'wyniki/rk2_1.csv')
    rk2_2 = time_step(rk2, 1e-5, 'wyniki/rk2_2.csv') 

    plot_results(rk2_1[0], rk2_1[2], rk2_2[0], rk2_2[2], 'x(t) - rk2', 'wykresy/x_rk2.png')
    plot_results(rk2_1[0], rk2_1[3], rk2_2[0], rk2_2[3], 'v(t) - rk2', 'wykresy/v_rk2.png')
    plot_results(rk2_1[0], rk2_1[1], rk2_2[0], rk2_2[1], 'dt(t) - rk2', 'wykresy/dt_rk2.png')
    plot_results(rk2_1[2], rk2_1[3], rk2_2[2], rk2_2[3], 'v(x) - rk2', 'wykresy/vx_rk2.png')

    plot_results(tr_1[0], tr_1[2], tr_2[0], tr_2[2], 'x(t) - trapez', 'wykresy/x_trapez.png')
    plot_results(tr_1[0], tr_1[3], tr_2[0], tr_2[3], 'v(t) - trapez', 'wykresy/v_trapez.png')
    plot_results(tr_1[0], tr_1[1], tr_2[0], tr_2[1], 'dt(t) - trapez', 'wykresy/dt_trapez.png')
    plot_results(tr_1[2], tr_1[3], tr_2[2], tr_2[3], 'v(x) - trapez', 'wykresy/vx_trapez.png')'''


