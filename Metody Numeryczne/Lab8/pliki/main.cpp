#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"

double f1(double x)
{
	return 1.0 / (1.0 + x * x);
}

double f2(double x)
{
	return cos(2*x);
}

void wyznacz_M(gsl_vector * x, gsl_vector * y, gsl_vector * m, int n, double alfa, double beta, gsl_vector *d, double lambda, double u)
{

	gsl_matrix * A = gsl_matrix_calloc(n, n);
	for (int i=1; i < n-1; i++)
	{
		gsl_matrix_set(A, i, i, 2.0);
		gsl_matrix_set(A, i, i+1, lambda);
		gsl_matrix_set(A, i, i-1, u);
	}

	gsl_matrix_set(A, 0, 0, 1.0);
	gsl_matrix_set(A, n-1, n-1, 1.0);
	gsl_permutation * p = gsl_permutation_calloc(n);
	int signum;

	gsl_linalg_LU_decomp(A, p, &signum);
	gsl_linalg_LU_solve(A, p, d, m);
}

double wyznacz_Sx(gsl_vector * X, gsl_vector * Y, gsl_vector * m, int n, double x)
{

    double s;
    int i=1;
    while(x > gsl_vector_get(X, i))
        i++;
    
    double x0 = gsl_vector_get(X,i);
    double x1 = gsl_vector_get(X,i-1);
    double h = x0-x1;
    double y0 = gsl_vector_get(Y,i);
    double y1 = gsl_vector_get(Y,i-1);
    double A = (y0-y1)/h-(h/6)*(gsl_vector_get(m,i)-gsl_vector_get(m,i-1));
    double B = y1-gsl_vector_get(m,i-1)*h*h/6;
    double m0 = gsl_vector_get(m, i);
    double m1 = gsl_vector_get(m, i-1);

    s = m1 * pow(x0-x,3) / (6.0 * h) + m0 * pow(x-x1,3) / (6.0 * h) + A * (x-x1) + B;
    return s;
}

int main()
{
	const std::string file_name = "f1n4.txt";
	auto f = f1; // używana funkcja
	double x_min = -5.0;
	double x_max =  5.0;
	double alfa = 0.0;
	double beta = 0.0;
	int n = 4;
	double dx = (x_max - x_min) / (n - 1);
	double hi = dx;
	double lambda = 0.5;
	double u = 1 - lambda;

	gsl_vector *X = gsl_vector_calloc(n);//wektor węzłów
	gsl_vector *Y = gsl_vector_calloc(n);//wektor wartości funkcji w węzłach

	for (int i=0; i < n; i++)
	{
		double value = x_min + dx*i;
		gsl_vector_set(X, i, value);
		gsl_vector_set(Y, i, f(value));
	}

	gsl_vector * d = gsl_vector_calloc(n);
	gsl_vector_set(d, 0, alfa);
	gsl_vector_set(d, n-1, beta);

	for (int i=1; i <= n-2; i++)
	{
		double value =  6.0 / (hi + hi);
		value *= ((gsl_vector_get(Y, i+1)-gsl_vector_get(Y, i)) / hi) - ((gsl_vector_get(Y, i) - gsl_vector_get(Y, i-1)) /  hi);
		gsl_vector_set(d, i, value);
	}

	gsl_vector * m = gsl_vector_calloc(n);//wektor na wartości drugich pochodnych
	wyznacz_M(X, Y, m, n, alfa, beta, d, lambda, u);
	
	for (int i=0; i < n; i++)
		std::cout << gsl_vector_get(d, i) << std::endl;

	std::ofstream out;
	out.open(file_name, std::ofstream::out);

	double x = x_min;
	double delta = (x_max - x_min) / 200;
	for (int i=0; i <= 200; i++)
	{
		x = x_min + i * delta;
		double y = wyznacz_Sx(X, Y, m, n, x);

		out << x << " " << y << " " << f(x) << std::endl;
	}

	out.close();
	

	return 0;
}
