from math import fabs, sin, pi, pow
import numpy as np

def rel(V, k, nx, ny, delta, TOL, it_total):
    
    filename1 = "wyniki/S_k_" + str(k) + ".dat"
    filename2 = "wyniki/V_k_" + str(k) + ".dat"

    f1 = open(filename1, "w")
    f2 = open(filename2, "w")

    s = 0.0
    for i in range(0, nx-k+1, k):
        for j in range(0, ny-k+1, k):
            s += ( (V[i+k][j] - V[i][j] + V[i+k][j+k] - V[i][j+k])/(2*k*delta) )**2
            s += ( (V[i][j+k] - V[i][j] + V[i+k][j+k] - V[i+k][j])/(2*k*delta) )**2

    s *= 0.5 * (k * delta)**2

    f1.write(f'{it_total}\t{s}\n')
    it = 1
    while True:
        for i in range(k, nx-k+1, k):
            for j in range(k, ny-k+1, k):
                V[i][j] = 0.25 * (V[i-k][j] + V[i+k][j] + V[i][j-k] + V[i][j+k])

        s_prev = s
        s = 0.0
        for i in range(0, nx-k+1, k):
            for j in range(0, ny-k+1, k):
                s += ( (V[i+k][j] - V[i][j] + V[i+k][j+k] - V[i][j+k])/(2*k*delta) )**2
                s += ( (V[i][j+k] - V[i][j] + V[i+k][j+k] - V[i+k][j])/(2*k*delta) )**2

        s *= 0.5 * (k * delta)**2

        it += 1
        it_total += 1
        f1.write(f'{it_total}\t{s}\n')

        if (it > 2 and fabs((s - s_prev) / s_prev) < TOL):
            break

    f1.close()

    for i in range(0, nx+1, k):
        for j in range(0, ny+1, k):
            f2.write(f'{delta*i}\t{delta*j}\t{V[i][j]}\n')
        f2.write('\n')

    for i in range(0, nx-k+1, k):
        for j in range(0, ny-k+1, k):
            V[i+k//2][j+k//2] = 0.25 * (V[i][j] + V[i+k][j] + V[i][j+k] + V[i+k][j+k])
            if i != nx - k:
                V[i+k][j+k//2] = 0.5 * (V[i+k][j] + V[i+k][j+k])
            if j != ny - k:
                V[i+k//2][j+k] = 0.5 * (V[i][j+k] + V[i+k][j+k])
            if j != 0:
                V[i+k//2][j] = 0.5 * (V[i][j] + V[i+k][j])
            if i != 0:
                V[i][j+k//2] = 0.5 * (V[i][j] + V[i][j+k])

    return V, it


if __name__ == '__main__':
    delta = 0.2
    nx, ny = 128, 128
    xmax, ymax = delta*nx, delta*ny
    TOL = 1e-8

    ks = [16, 8, 4, 2, 1]
    V = np.zeros([nx+1, ny+1])

    for i in range(nx+1):
        V[i][0] = sin(2 * pi * delta * i / xmax)
        V[i][ny] = -sin(2 * pi * delta * i / xmax)

    for j in range(ny+1):
        V[0][j] = sin(pi * delta * j / ymax)
        V[nx][j] = sin(pi * delta * j / ymax)

    it_total = 1
    for k in ks:
        V, i = rel(V, k, nx, ny, delta, TOL, it_total)
        it_total += i





    


