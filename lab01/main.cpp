#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>

using vect = std::vector<double>;

inline double f(double t, double l=-1.0)
{
    return exp(l*t);
}

void euler(double dt, std::string filename, double y0=1.0, int t0=0, int tk=5, double l=-1.0)
{
    double y;
    std::ofstream fout;
    fout.open(filename, std::ofstream::out);

    y = y0;
    fout << t0 << "\t" << y0 << "\t" << y0 << "\t" << 0.0 << std::endl;
    int n = std::round((tk - t0) / dt);

    for (int i=1; i <= n; i++)
    {
        double t = t0 + dt * i;
        double y_new = y + dt * l * y;
        y = y_new;
        fout << t << "\t" << y_new <<  "\t" << f(t) << "\t" << y_new - f(t) << std::endl;
    }
    fout.close();
}

void RK2(double dt, std::string filename, double y0=1.0, int t0=0, int tk=5, double l=-1.0)
{
    double y;
    std::ofstream fout;
    fout.open(filename, std::ofstream::out);

    y = y0;
    fout << t0 << "\t" << y0 << "\t" << y0 << "\t" << 0.0 << std::endl;

    int n = std::round((tk - t0) / dt);
    for (int i=1; i <= n; i++)
    {
        double t = t0 + i * dt;
        double k1 = l * y;
        double k2 = l * (y + dt * k1);
        double y_new = y + dt/2 * (k1 + k2);

        y = y_new;
        fout << t << "\t" << y_new <<  "\t" << f(t) << "\t" << y_new - f(t) << std::endl;
    }
    fout.close();
}

void RK4(double dt, std::string filename, double y0=1.0, int t0=0, int tk=5, double l=-1.0)
{
    double y;
    std::ofstream fout;
    fout.open(filename, std::ofstream::out);

    y = y0;
    fout << t0 << "\t" << y0 << "\t" << y0 << "\t" << 0.0 << std::endl;

    int n = std::round((tk - t0) / dt);
    for (int i=1; i <= n; i++)
    {
        double t = t0 + i * dt;
        double k1 = l * y;
        double k2 = l * (y + dt/2 * k1);
        double k3 = l * (y + dt/2 * k2);
        double k4 = l * (y + dt * k3);
        double y_new = y + dt/6 * (k1 + 2*k2 + 2*k3 + k4);

        y = y_new;
        fout << t << "\t" << y_new <<  "\t" << f(t) << "\t" << y_new - f(t) << std::endl;
    }
    fout.close();
}

double V(double t, double wv)
{
    return 10 * sin(wv * t);
}

void RK4_IQ(double wv, std::string filename, double dt=0.0001, double R=100.0, double L=0.1,
            double C=0.001, double t0=0, double Q0=0, double I0=0)
{
    std::ofstream fout;
    fout.open(filename, std::ofstream::out);

    double w0 = 1 / sqrt(L * C);
    wv *= w0;
    double T0 = 2 * M_PI / w0;
    double tk = 4 * T0;

    double Q, I;
    Q = Q0;
    I = I0;
    fout << t0 << "\t" << Q0 << "\t" << I0 << std::endl;

    int n = std::round((tk - t0) / dt);
    for (int i=1; i <= n; i++)
    {
        double t = t0 + i * dt;

        double k1q = I;
        double k1i = (V(t, wv) / L) - (Q / (L * C)) - R*I / L;
        double k2q = I + dt / 2 * k1i;
        double k2i = (V(t + dt/2, wv) / L) - 1/(L*C) * (Q + dt/2 * k1q) - R / L * (I + dt/2 * k1i);
        double k3q = I + dt / 2 * k2i;
        double k3i = V(t + dt/2, wv) / L - 1 / (L * C) * (Q + dt/2 * k2q) - R / L * (I + dt/2*k2i);
        double k4q = I + dt * k3i;
        double k4i = V(t + dt, wv) / L - 1 / (L*C) * (Q + dt * k3q) - R / L * (I + dt*k3i);

        double Q_new = Q + dt / 6 * (k1q + 2*k2q + 2*k3q + k4q);
        double I_new = I + dt / 6 * (k1i + 2*k2i + 2*k3i + k4i);

        Q = Q_new;
        I = I_new;

        fout << t << "\t" << Q_new << "\t" << I_new << std::endl;
    }
    fout.close();

}



int main()
{
    // 1) Metoda Jawna Eulera
    euler(0.01, "wyniki/euler1.dat");
    euler(0.1, "wyniki/euler2.dat");
    euler(1.0, "wyniki/euler3.dat");

    // 2) Metoda Jawna RK2
    RK2(0.01, "wyniki/rk2_1.dat");
    RK2(0.10, "wyniki/rk2_2.dat");
    RK2(1.00, "wyniki/rk2_3.dat");

    // 3) Metoda Jawna RK4
    RK4(0.01, "wyniki/rk4_1.dat");
    RK4(0.10, "wyniki/rk4_2.dat");
    RK4(1.00, "wyniki/rk4_3.dat");

    // 4) RRZ 2 rzędu
    RK4_IQ(0.5, "wyniki/RLC1.dat");
    RK4_IQ(0.8, "wyniki/RLC2.dat");
    RK4_IQ(1.0, "wyniki/RLC3.dat");
    RK4_IQ(1.2, "wyniki/RLC4.dat");

    return 0;
}