#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <algorithm>

const double I = 0.2557840245;
const int N = 100000;
const double C = 1./(1. - exp(-1));

inline double g(double x, double y)
{
	return sin(x+y)/log(2+x+y);
}

inline double f(double x)
{
	return exp(-x);
}

double war(int n, const std::vector<double>& xi, const std::vector<double>& yi)
{
	double sum1 = 0.0;
	double sum2 = 0.0;
	for (int i=0; i < n; i++)
	{
		double z = g(xi[i], yi[i])*f(xi[i])*f(yi[i]);
		sum1 += pow(z, 2);
		sum2 += z;
	}

	return 1.0/(n-1) * (sum1 - 1.0/n * pow(sum2, 2));
}

double gen()
{
	static long long x=10;
	int a = 69069;
	int c = 1;
	static long long m = pow(2, 32);
	x = (a*x + c) % m;
	return static_cast<double>(x) / (m + 1.0);
}

inline double genQ()
{
	return -log(1. - gen()/C);
}

inline double F(double x)
{
	return C*(1-exp(-x));
}

int main()
{
	std::vector<double> xi;
	std::vector<double> yi;
	xi.reserve(N);
	yi.reserve(N);

	for (int i=0; i < N; i++)
	{
		xi[i] = gen();
		yi[i] = gen();
	}

	std::ofstream out1;

	int stop = 10;
	double I1 = 0.0;
	out1.open("../wyniki/kwadratura_mc.dat", std::ofstream::out);
	for (int i=1; i <= N; i++)
	{
		I1 += g(xi[i-1], yi[i-1]) * f(xi[i-1]) * f(yi[i-1]);

		if (i == stop)
		{
			double dev = sqrt(war(i, xi, yi)) / sqrt(i);
			double In = I1 / i;
			out1 << i << " " << In << " " << dev << std::endl;
			stop *= 10;
		}
	}
	I1 /= N;
	out1.close();

	stop = 10;
	double I2 = 0.0;
	out1.open("../wyniki/roz_exp.dat", std::ofstream::out);
	double sum1 = 0.0;
	double sum2 = 0.0;

	for (int i=0; i < N; i++)
	{
		xi[i] = genQ();
		yi[i] = genQ();
	}

	for (int i=1; i <= N; i++)
	{
		I2 += g(xi[i], yi[i]) / (C*C);

		double z = g(xi[i], yi[i])/(C*C);
		sum1 += pow(z, 2);
		sum2 += z;

		if (i == stop)
		{
			double dev = sqrt(1.0/(i-1) * (sum1 - 1.0 / i * pow(sum2, 2))) / sqrt(i);
			out1 << i << " " << I2/i << " " << dev << std::endl;
			stop *= 10;
		}
	}
	I2 /= N;
	out1.close();

	//xi - 10^5 liczb z genQ
	std::vector<int> bins;
	bins.reserve(10);
	for (int i=0; i < 10; i++)
	{
		bins[i] = 0;
	}

	for (int i=0; i < N; i++)
	{
		for (int j=1; j <= 10; j++)
		{
			if (xi[i] <= j*0.1)
			{
				bins[j-1]++;
				break;
			}
		}
	}
	std::ofstream out2;
	out1.open("../wyniki/hist_p_num.dat", std::ofstream::out);
	out2.open("../wyniki/hist_p_dok.dat", std::ofstream::out);
	double Pi[10];
	for (int i=0; i < 10; i++)
	{
		Pi[i] = F(0.1*(i+1)) - F(0.1 * i);
		out1 << bins[i] / (double)N << std::endl;
		out2 << Pi[i] << std::endl;
	}
	out1.close();
	out2.close();

	double chi_2 = 0.0;
	for (int i=0; i < 10; i++)
	{
		chi_2 += pow(bins[i] - N * Pi[i], 2) / (N * Pi[i]);
	}
	out1.open("../wyniki/chi_2.dat", std::ofstream::out);
	out1 << chi_2 << std::endl;
	out1.close();
}