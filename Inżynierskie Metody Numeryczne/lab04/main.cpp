#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using vect = std::vector<std::vector<double>>;

double density1(double x, double y, double x_max, double y_max, double sigma_x, double sigma_y)
{
    return exp(-pow(x-0.35*x_max, 2) / (sigma_x*sigma_x) - pow(y - 0.5*y_max, 2) / (sigma_y*sigma_y));
}
double density2(double x, double y, double x_max, double y_max, double sigma_x, double sigma_y)
{
    return -exp(-pow(x-0.65*x_max, 2) / (sigma_x*sigma_x) - pow(y - 0.5*y_max, 2) / (sigma_y*sigma_y));
}

double globalV(double V1, double V2, double V3, double V4, double eps, double delta, double density)
{
    return 0.25 * (V1 + V2 + V3 + V4 + delta*delta*density/eps);
}

double localV(double V, double V1, double V2, double V3, double V4, double eps, double delta, double density, double omega)
{
    return (1 - omega) * V + omega/4 * (V1 + V2 + V3 + V4 + delta*delta*density/eps);
}

double e(double V1, double V2, double V3, double V4, double V5, double delta, double density, double eps)
{
    return ((V1 - 2 * V2 + V3) / (delta*delta)) + ((V4 - 2 * V2 + V5) / (delta*delta)) + (density / eps);
}

double stop(const vect& V, const vect& density, double delta, int nx, int ny)
{
    double s = 0;
    
    for (int i=0; i < nx; i++)
        for (int j=0; j < ny; j++)
            s += 0.5 * pow((V[i+1][j] - V[i][j])/delta, 2) + 0.5 * pow((V[i][j+1] - V[i][j])/delta, 2) - density[i][j]*V[i][j];
    s *= delta*delta;
    return s;
}

void globalRelaxation(double omega, std::string filename1, std::string filename2)
{
    double eps = 1.0;
    double delta = 0.1;
    int nx = 150;
    int ny = 100;
    double V1 = 10.0;
    double V2 = 0.0;
    double x_max = delta*nx;
    double y_max = delta*ny;
    double TOL = 1e-8;
    double sigma_x = 0.1*x_max;
    double sigma_y = 0.1*y_max;

    vect density(nx+1);
    vect Vs(nx+1);
    vect Vn(nx+1);
    vect err(nx+1);

    for (int i=0; i < nx + 1; i++)
    {
        density[i].resize(ny+1, 0.0);
        Vs[i].resize(ny+1, 0.0);
        Vn[i].resize(ny+1, 0.0);
        err[i].resize(ny+1, 0.0);

        Vs[i][0] = V1;
        Vn[i][0] = V1;

        Vs[i][nx] = V2;
        Vn[i][nx] = V2;

        for (int j=0; j < ny+1; j++)
        {
            density[i][j] = density1(i*delta, j*delta, x_max, y_max, sigma_x, sigma_y)
                          + density2(i*delta, j*delta, x_max, y_max, sigma_x, sigma_y);
        }  
    }

    std::ofstream f;
    f.open(filename1, std::ios::out);
    double s1, s=0.0;
    int it = 1;

    s = stop(Vn, density, delta, nx, ny);
    f << it << " " << s << std::endl;
    it++;
    do
    {
        for (int i=1; i < nx; i++)
        {
            for (int j=1; j < ny; j++)
            {
                Vn[i][j] = globalV(Vs[i+1][j], Vs[i-1][j], Vs[i][j+1], Vs[i][j-1], eps, delta, density[i][j]);
            }
        }

        for (int j=1; j < ny; j++)
        {
            Vn[0][j] = Vn[1][j];
            Vn[nx][j] = Vn[nx-1][j];
        }

        for (int i=0; i < nx+1; i++)
        {
            for (int j=0; j < ny+1; j++)
            {
                Vs[i][j] = (1.0 - omega) * Vs[i][j] + omega * Vn[i][j];
            }
        }

        s1 = s;
        s = stop(Vs, density, delta, nx, ny);
        f << it << " " << s << std::endl;
        it++;
    } while (fabs((s - s1) / s1) >= TOL);
    
    f.close();
    f.open(filename2, std::ios::out);

    for (int i=1; i < nx; i++)
    {
        for (int j=1; j < ny; j++)
        {
            err[i][j] = e(Vs[i+1][j], Vs[i][j], Vs[i-1][j], Vs[i][j+1], Vs[i][j-1], delta, density[i][j], eps);
            f << i*delta << " " << j*delta << " " << Vn[i][j] << " " << err[i][j] << std::endl;
        }
    }
    f.close();
}

void localRelaxation(double omega, std::string filename1)
{
    double eps = 1.0;
    double delta = 0.1;
    int nx = 150;
    int ny = 100;
    double V1 = 10.0;
    double V2 = 0.0;
    double x_max = delta*nx;
    double y_max = delta*ny;
    double TOL = 1e-8;
    double sigma_x = 0.1*x_max;
    double sigma_y = 0.1*y_max;

    vect density(nx+1);
    vect Vn(nx+1);

    for (int i=0; i < nx + 1; i++)
    {
        density[i].resize(ny+1, 0.0);
        Vn[i].resize(ny+1, 0.0);

        Vn[i][0] = V1;

        for (int j=0; j < ny+1; j++)
        {
            density[i][j] = density1(i*delta, j*delta, x_max, y_max, sigma_x, sigma_y)
                          + density2(i*delta, j*delta, x_max, y_max, sigma_x, sigma_y);
        }  
    }

    std::ofstream f;
    f.open(filename1, std::ios::out);
    double s = 0.0;
    double s1;
    int it = 1;

    s = stop(Vn, density, delta, nx, ny);
    f << it << " " << s << std::endl;
    it++;
    do
    {
        for (int i=1; i < nx; i++)
        {
            for (int j=1; j < ny; j++)
            {
                Vn[i][j] = localV(Vn[i][j], Vn[i+1][j], Vn[i-1][j], Vn[i][j+1], Vn[i][j-1], eps, delta, density[i][j], omega);
            }
        }

        for (int j=1; j < ny; j++)
        {
            Vn[0][j] = Vn[1][j];
            Vn[nx][j] = Vn[nx-1][j];
        }

        s1 = s;
        s = stop(Vn, density, delta, nx, ny);
        f << it << " " << s << std::endl;
        it++;
    } while (fabs((s - s1) / s1) >= TOL);
    
    f.close();
}

int main()
{
    globalRelaxation(0.6, "wyniki/global_0_6.dat", "wyniki/global_0_6_err.dat");  
    globalRelaxation(1.0, "wyniki/global_1_0.dat", "wyniki/global_1_0_err.dat");
    localRelaxation(1.0, "wyniki/local_1_0.dat");
    localRelaxation(1.4, "wyniki/local_1_4.dat");
    localRelaxation(1.8, "wyniki/local_1_8.dat");
    localRelaxation(1.9, "wyniki/local_1_9.dat");

   return 0;
}