#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

const double beta = 0.001;
const int N = 500;
const double gamma = 0.1;
const double t_max = 100;
const double dt = 0.1;
const int mi0 = 1;
const double TOL = 1e-6;
const int MI_MAX = 20;

inline double f(double t, double u)
{
    return (beta*N - gamma)*u - beta*u*u;
}

void picard()
{
    double alfa = beta * N - gamma;
    int n = round(t_max / dt);

    std::ofstream fout;
    fout.open("wyniki/picard.dat", std::ofstream::out);


    std::vector<double> picard;
    picard.push_back(mi0);
    fout << 0.0 << "\t" << mi0 << std::endl;
    for (int i=1; i <= n; i++)
    {
        double t = i * dt;
        int mi = 1;
        double u_prev_final = picard.back();
        double u_prev = picard.back();
        double u_curr = u_prev_final + dt/2 * (f(t, u_prev_final) + f(t, u_prev));

        while (fabs(u_curr - u_prev) >= TOL && mi <= MI_MAX)
        {   
            u_prev = u_curr;
            u_curr = u_prev_final + dt/2 * (f(t, u_prev_final) + f(t, u_prev));
            mi++;
        }
        picard.push_back(u_curr);
        fout << t << "\t" << u_curr << std::endl;
    }

    fout.close();
}

void newton()
{
    std::vector<double> newton;

    double alfa = beta * N - gamma;
    int n = round(t_max / dt);

    std::ofstream fout;
    fout.open("wyniki/newton.dat", std::ofstream::out);
    
    newton.push_back(mi0);
    fout << 0.0 << "\t" << mi0 << std::endl;

    for (int i=1; i <= n; i++)
    {
        double t = i * dt;
        int mi = 1;
        double u_prev_final = newton.back();
        double u_prev = newton.back();
        double l = (u_prev - u_prev_final - dt/2 * (f(t, u_prev_final) + f(t, u_prev)));
        double m = (1 - dt/2 * (2 * beta * u_prev));
        double u_curr = u_prev - l / m;

        while (fabs(u_curr - u_prev) >= TOL && mi <= MI_MAX)
        {   
            u_prev = u_curr;
            l = (u_prev - u_prev_final - dt/2 * (f(t, u_prev_final) + f(t, u_prev)));
            m = (1 - dt/2 * (2 * beta * u_prev));
            u_curr = u_prev - l / m;
            mi++;
        }
        newton.push_back(u_curr);
        fout << t << "\t" << u_curr << std::endl;
    }

    fout.close();
}

void rk2()
{
    double a11 = 0.25;
    double a12 = 0.25 - sqrt(3)/6;
    double a21 = 0.25 + sqrt(3)/6;
    double a22 = 0.25;

    double b1 = 0.5;
    double b2 = 0.5;

    double c1 = 0.5 - sqrt(3)/6;
    double c2 = 0.5 + sqrt(3)/6;

    std::vector<double> rk2;

    double alfa = beta * N - gamma;
    int n = round(t_max / dt);

    std::ofstream fout;
    fout.open("wyniki/rk2.dat", std::ofstream::out);
    
    rk2.push_back(mi0);
    fout << 0.0 << "\t" << mi0 << std::endl;

    double U1_prev, U1_curr;
    double U2_prev, U2_curr;
    double dU1, dU2;
    double F1, F2;
    double m11, m12, m21, m22;
    double u_curr, u_prev;

    for (int i=1; i <= n; i++)
    {
        double t = i * dt;
        int mi = 0;
        do
        {
            if (mi == 0)
                U1_prev = U2_prev = rk2.back();
            else
            {
                U1_prev = U1_curr;
                U2_prev = U2_curr;
            }
            
            F1 = U1_prev - rk2.back() - dt * (a11*f(t, U1_prev) + a12*f(t, U1_prev));
            F2 = U2_prev - rk2.back() - dt * (a21*f(t, U2_prev) + a22*f(t, U2_prev));

            m11 = 1 - dt*a11*(alfa-2*beta*U1_prev);
            m12 = -dt*a12*(alfa-2*beta*U2_prev);
            m21 = -dt*a21*(alfa-2*beta*U1_prev);
            m22 = 1 - dt*a22*(alfa-2*beta*U2_prev);

            dU1 = (F2*m12 - F1*m22) / (m11*m22 - m12*m21);
            dU2 = (F1*m21 - F2*m11) / (m11*m22 - m12*m21);

            U1_curr = U1_prev + dU1;
            U2_curr = U2_prev + dU2;
            mi++;
            
        } while (fabs(U1_curr - U1_prev) >= TOL && fabs(U2_curr - U2_prev) >= TOL && mi <= MI_MAX);

        u_curr = rk2.back() + dt * (b1*f(t, U1_curr) + b2*f(t, U2_curr));
        rk2.push_back(u_curr);
        fout << t << "\t" << u_curr << std::endl;
        
    /*
        double t = i * dt;
        int mi=1;
        U1_prev = U2_prev = rk2.back();
        
        F1 = U1_prev - rk2.back() - dt * (a11*f(t, U1_prev) + a12*f(t, U1_prev));
        F2 = U2_prev - rk2.back() - dt * (a21*f(t, U2_prev) + a22*f(t, U2_prev));

        m11 = 1 - dt*a11*(alfa-2*beta*U1_prev);
        m12 = -dt*a12*(alfa-2*beta*U2_prev);
        m21 = -dt*a21*(alfa-2*beta*U1_prev);
        m22 = 1 - dt*a22*(alfa-2*beta*U2_prev);

        dU1 = (F2*m12 - F1*m22) / (m11*m22 - m12*m21);
        dU2 = (F1*m21 - F2*m11) / (m11*m22 - m12*m21);

        U1_curr = U1_prev + dU1;
        U2_curr = U2_prev + dU2;

        u_prev = rk2.back();



        while (fabs(U1_curr - U2_curr) >= TOL && fabs(U1_curr - U2_curr) >= TOL && mi <= MI_MAX)
        {
            U1_prev = U1_curr;
            U2_prev = U2_curr;

            F1 = U1_prev - rk2.back() - dt * (a11*f(t, U1_prev) + a12*f(t, U1_prev));
            F2 = U2_prev - rk2.back() - dt * (a21*f(t, U2_prev) + a22*f(t, U2_prev));

            m11 = 1 - dt*a11*(alfa-2*beta*U1_prev);
            m12 = -dt*a12*(alfa-2*beta*U2_prev);
            m21 = -dt*a21*(alfa-2*beta*U1_prev);
            m22 = 1 - dt*a22*(alfa-2*beta*U2_prev);

            dU1 = (F2*m12 - F1*m22) / (m11*m22 - m12*m21);
            dU2 = (F1*m21 - F2*m11) / (m11*m22 - m12*m21);

            U1_curr = U1_prev + dU1;
            U2_curr = U2_prev + dU2;

            u_curr = u_prev + dt * (b1*f(t, U1_curr) + b2*f(t, U2_curr));
            mi++;
        }
        u_curr = u_prev + dt * (b1*f(t, U1_curr) + b2*f(t, U2_curr));
        rk2.push_back(u_curr);
        fout << t << "\t" << u_curr << std::endl;
    */
    }
}


int main()
{
    picard();
    newton();
    rk2();
    return 0;
}