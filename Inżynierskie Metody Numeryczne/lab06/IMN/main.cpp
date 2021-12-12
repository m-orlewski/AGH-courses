#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "mgmres.h"

const double delta = 0.1;
const int V1 = 10, V3 = 10;
const int V2 = -10, V4 = -10;

void wb_dirichlet(std::vector<double> & a, std::vector<int> & ja, std::vector<int> & ia, std::vector<double> & b, int N,
                  double pl1, double pl2, int V1, int V2, int V3, int V4, int nx, int ny, int eps1, int eps2, bool save=false);

inline int epsl(int l, int eps1, int eps2, int nx, int ny)
{
    int j = l / (nx + 1);
    int i = l - j * (nx + 1);
    return i <= nx/2 ? eps1 : eps2;
}

inline double sig1(double x, double y, double delta, int nx, int ny)
{
    double xmax = delta * nx;
    double ymax = delta * ny;
    double sigma2 = pow(xmax/10, 2);
    return exp(-1 * pow(x-0.25*xmax, 2)/sigma2 - pow(y-0.5*ymax, 2)/sigma2);
}

inline double sig2(double x, double y, double delta, int nx, int ny)
{
    double xmax = delta * nx;
    double ymax = delta * ny;
    double sigma2 = pow(xmax/10, 2);
    return -1. * exp(-1 * pow(x-0.75*xmax, 2)/sigma2 - pow(y-0.5*ymax, 2)/sigma2);
}

void map_data(std::string filename, const std::vector<double> & V, int N, int nx, int ny)
{
    std::ofstream out;
    out.open(filename);
    int prev = -1;
    for (int l=0; l < N; l++)
    {
        int j = l / (nx + 1);
        int i = l - j * (nx + 1);

        if (prev != j)
        {
            prev = j;
            out << std::endl;
        }

        out << j*delta << " " << i*delta << " " << V[l] << std::endl;
    }
}

int main()
{

      

    std::vector<double> a;
    std::vector<int> ja;
    std::vector<int> ia;
    std::vector<double> b, V;

    int nx, ny, N, eps1, eps2;

    eps1 = eps2 = 1;
    nx = ny = 4;
    N = (nx + 1)*(ny + 1); 
    a.resize(5*N);
    ja.resize(5*N);
    ia.resize(N+1);
    b.resize(N);
    V.resize(N);
    std::fill(ia.begin(), ia.end(), -1);

    wb_dirichlet(a, ja, ia, b, N, 0, 0, 10, -10, 10, -10, nx, ny, eps1, eps2, true);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);


    nx = ny = 50;
    N = (nx + 1)*(ny + 1);
    a.resize(5*N);
    ja.resize(5*N);
    ia.resize(N+1);
    b.resize(N);
    V.resize(N);
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 0, 0, 10, -10, 10, -10, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV5a.dat", V, N, nx, ny);

    nx = ny = 100;
    N = (nx + 1)*(ny + 1);
    a.resize(5*N);
    ja.resize(5*N);
    ia.resize(N+1);
    b.resize(N);
    V.resize(N);
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 0, 0, 10, -10, 10, -10, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV5b.dat", V, N, nx, ny);

    nx = ny = 200;
    N = (nx + 1)*(ny + 1);
    a.resize(5*N);
    ja.resize(5*N);
    ia.resize(N+1);
    b.resize(N);
    V.resize(N);
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 0, 0, 10, -10, 10, -10, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV5c.dat", V, N, nx, ny);

    nx = ny = 100;
    N = (nx + 1)*(ny + 1);
    a.resize(5*N);
    ja.resize(5*N);
    ia.resize(N+1);
    b.resize(N);
    V.resize(N);
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 1, 1, 0, 0, 0, 0, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV6a.dat", V, N, nx, ny);

    eps1 = 1;
    eps2 = 2;
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 1, 1, 0, 0, 0, 0, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV6b.dat", V, N, nx, ny);

    eps1 = 1;
    eps2 = 10;
    std::fill(ia.begin(), ia.end(), -1);
    wb_dirichlet(a, ja, ia, b, N, 1, 1, 0, 0, 0, 0, nx, ny, eps1, eps2, false);
    pmgmres_ilu_cr(N, ia[N], ia.data(), ja.data(), a.data(), V.data(), b.data(), 500, 500, 1e-8, 1e-8);

    map_data("wyniki/mapV6c.dat", V, N, nx, ny);

    return 0;
}

void wb_dirichlet(std::vector<double> & a, std::vector<int> & ja, std::vector<int> & ia, std::vector<double> & b, int N,
                  double pl1, double pl2, int V1, int V2, int V3, int V4, int nx, int ny, int eps1, int eps2, bool save)
{
    int k = -1;


    for (int l=0; l < N; l++)
    {
        int j = l / (nx + 1);
        int i = l - j * (nx + 1);

        int brzeg = 0;
        double vb = 0.;

        if (i == 0)
        {
            brzeg = 1;
            vb = V1;
        }
                
        if (j == ny)
        {
            brzeg = 1;
            vb = V2;
        }
        
        if (i == nx)
        {
            brzeg = 1;
            vb = V3;
        }
        
        if (j == 0)
        {
            brzeg = 1;
            vb = V4;
        }

        b[l] = -(pl1*sig1(i*delta, j*delta, delta, nx, ny) + pl2*sig2(i*delta, j*delta, delta, nx, ny));

        if (brzeg == 1)
        {
            b[l] = vb;
        }

        ia[l] = -1;

        if (l-nx-1 >= 0 && brzeg == 0)
        {
            k++;
            if (ia[l] < 0) ia[l] = k;
            a[k] = epsl(l, eps1, eps2, nx, ny)/(delta * delta);
            ja[k] = l - nx - 1;
        }

        if (l-1 >= 0 && brzeg == 0)
        {
            k++;
            if (ia[l] < 0) ia[l] = k;
            a[k] = epsl(l, eps1, eps2, nx, ny) / (delta * delta);
            ja[k] = l - 1;
        }

        //diagonala
        k++;
        if (ia[l] < 0) ia[l] = k;
        if (brzeg == 0)
            a[k] = -(2*epsl(l, eps1, eps2, nx, ny) + epsl(l+1, eps1, eps2, nx, ny)+epsl(l+nx+1, eps1, eps2, nx, ny))/(delta * delta);
        else
            a[k] = 1;
        ja[k] = l;

        //naddiagonala
        if (l < N && brzeg == 0)
        {
            k++;
            a[k] = epsl(l+1, eps1, eps2, nx, ny)/(delta*delta);
            ja[k] = l+1;
        }

        //prawa skrajna przekątna
        if (l < N - nx - 1 && brzeg == 0)
        {
            k++;
            a[k] = epsl(l+nx+1, eps1, eps2, nx, ny) / (delta * delta);
            ja[k] = l + nx + 1;
        }
    }

    if (save)
    {
        std::ofstream out1, out2;
        out1.open("wyniki/A.dat");
        out2.open("wyniki/b.dat");

        for (int l=0; l < N; l++)
        {
            int j = l / (nx + 1);
            int i = l - j * (nx + 1);

            out1 << l << " " << i << " " << j << " " << a[l] << std::endl;
            out2 << l << " " << i << " " << j << " " << b[l] << std::endl;
        }

        out1.close();
        out2.close();
    }

    ia[N] = k + 1;
}