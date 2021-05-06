#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"

typedef std::vector<double> vect;
typedef std::vector<vect> matr;

double g(double x, double x0=2.0, double sigma=4.0)
{
	return exp((x-x0)*(x-x0)/(-2*sigma*sigma));
}

double f(double x, double x0=2.0, double sigma=4.0)
{
	return log(g(x, x0, sigma));
}

vect get_r_vector(const vect & f, const vect & x, int m, int N)
{
	vect ret;
	for (int k=0; k < m; k++)
	{
		double value = 0.;
		for (int j=0; j < N; j++)
		{
			value += f[j] * pow(x[j], k);
		}
		ret.push_back(value);
	}
	return ret;
}

matr get_G_matrix(const vect & x, int m, int N)
{
	matr ret;
	ret.resize(m);
	for (int i=0; i < m; i++)
	{
		for (int k=0; k < m; k++)
		{
			double value = 0.;
			for (int j=0; j < N; j++)
			{
				value += pow(x[j], i+k);
			}
			ret[i].push_back(value);
		}
	}
	return ret;
}

vect solve(const vect & r, const matr & G, int m)
{
	gsl_vector * r2 = gsl_vector_calloc(m);
	gsl_matrix * G2 = gsl_matrix_calloc(m, m);
	gsl_vector * b = gsl_vector_calloc(m);
	gsl_permutation * p = gsl_permutation_calloc(m);
	int signum;

	for (int i=0; i < m; i++)
	{
		for (int j=0; j < m; j++)
		{
			gsl_vector_set(r2, j, r[j]);
			gsl_matrix_set(G2, i, j, G[i][j]);
		}
	}

	gsl_linalg_LU_decomp(G2, p, &signum);
	gsl_linalg_LU_solve(G2, p, r2, b);

	vect ret;
	for (int i=0; i < m; i++)
		ret.push_back(gsl_vector_get(b, i));

	return ret;
	
}

double aprox_g(const vect & b, double x)
{
	return exp(b[0] + b[1]*x + b[2]*x*x + b[3]*x*x*x);
}

int main()
{
	int N = 11;

	double x0 = 2.;
	double sigma = 4.;
	double x_min = -3*sigma + x0;
	double x_max = 3*sigma + x0;

	double dx = (x_max - x_min) / (N-1);
	
	vect nodes, gs, fs;
	for (int i=0; i < N; i++)
	{
		double x = x_min + i * dx;
		nodes.push_back(x);
		gs.push_back(g(x));
		fs.push_back(f(x));
	}

	int m = 4;

	vect r = get_r_vector(fs, nodes, m, N); // wektor wyrazów wolnych
	matr G = get_G_matrix(nodes, m, N); // macierz układu
	vect b = solve(r, G, m); // rozwiązanie układu

	vect a;
	a.push_back(-x0*x0/(2*sigma*sigma)); //a0
	a.push_back(x0 / (sigma*sigma)); //a1
	a.push_back(-0.5/(sigma*sigma)); //a2
	a.push_back(0.0); //a3

	std::ofstream out;
	out.open("a_b_comp.txt", std::ofstream::out);
	out << "Porównanie współcznników dokładnych(1 kolumna) i oszacowanych(2 kolumna)\n";
	for (int i=0; i < m; i++)
	{
		out << std::setw(12) << a[i] << "\t" << std::setw(12) << b[i] << std::endl;
	}
	out.close();

	
	out.open("g_aprox.txt", std::ofstream::out);
	double delta = (x_max - x_min) / 240;
	for (int i=0; i <= 240; i++ )
	{
		double x = x_min + i * delta;
		out << x << "\t" << std::setw(12) << aprox_g(b, x) << std::endl;
	}
	out.close();

	double alfa = 0.5;
	srand(time(NULL));
	N = 11;
	dx = (x_max - x_min) / (N-1);
	b.clear();
	gs.clear();
	fs.clear();
	nodes.clear();
	r.clear();
	G.clear();

	for (int i=0; i < N; i++)
	{
		double x = x_min + i * dx;
		double U = rand() / (RAND_MAX + 1.0);
		double val = g(x) * (1.0 + alfa * (U - 0.5));
		nodes.push_back(x);
		gs.push_back(val);
		fs.push_back(log(val));
	}
	
	r = get_r_vector(fs, nodes, m, N);
	G = get_G_matrix(nodes, m, N);
	b = solve(r, G, m);

	out.open("a_b_comp2_N11.txt", std::ofstream::out);
	out << "Porównanie współczynników dokładnych (1 kolumna) i oszacowanych(2 kolumna)\n";
	for (int i=0; i < 4; i++)
	{
		out << std::setw(12) << a[i] << "\t" << std::setw(12) << b[i] << std::endl;
	}
	out.close();

	out.open("g_aprox2_N11.txt", std::ofstream::out);
	for (int i=0; i <= 240; i++)
	{
		double x = x_min + i * delta;
		out << x << "\t" << std::setw(16) << aprox_g(b, x) << std::endl;
	}
	out.close();

	out.open("node_values_N11.txt", std::ofstream::out);
	for (int i=0; i < N; i++)
	{
		out << nodes[i] << "\t" << gs[i] << std::endl;
	}
	out.close();
	
	return 0;
}









