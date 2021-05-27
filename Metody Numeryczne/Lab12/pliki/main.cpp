#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

double f(double x, int m, int k)
{
	return pow(x, m) * sin(k*x);
}

double factorial(unsigned n)
{
	double ret = 1.0;
	for (int i=1; i <= n; i++)
		ret *= i;

	return ret;
}

double integral1(int j, double a, double b, int m, int k, std::string filename)
{
	double sum_a = 0.0;
	double sum_b = 0.0;

	std::ofstream out;
	out.open(filename, std::ofstream::out);

	for (int i=0; i <= j; i++)
	{
		double l1 = pow(k*b, 2*i+m+2) * pow(-1.0, i);
		double l2 = pow(k*a, 2*i+m+2) * pow(-1.0, i);
		double m1 = pow(k, m+1) * factorial(2*i+1) * (2*i + m + 2);

		sum_b += l1 / m1;
		sum_a += l2 / m1;

		out << sum_b - sum_a << std::endl;
	}

	out.close();
	return sum_b - sum_a;
}

double integral2(double a, double b, int n, int m, int k)
{
	double h = (b - a) / (n-1);

	double sum = 0.0;
	for (int i=1; i <= (n-1)/2; i++)
	{
		sum += f(a + (2*i-2)*h, m, k) + 4*f(a + (2*i-1)*h, m, k) + f(a + (2*i)*h, m, k);
	}
	sum = sum * h / 3;
	return sum;
}

int main()
{
	double a = 0.0;
	double b = M_PI;
	int m[] = {0, 1, 5};
	int k[] = {1, 1, 5};

//1
	std::string filenames1[] = {"sumy_m0_k1.dat", "sumy_m1_k1.dat", "sumy_m5_k5.dat"};
	for (int i=0; i < 3; i++)
		integral1(30, a, b, m[i], k[i], filenames1[i]);

//2
	int n[] = {11, 21, 51, 101, 201};
	std::string filenames2[] = {"simpson_m0_k1.dat", "simpson_m1_k1.dat", "simpson_m5_k5.dat"};
	std::ofstream out;
	for (int j=0; j < 3; j++)
	{
		out.open(filenames2[j], std::ofstream::out);
		for (int i=0; i < 5; i++)
		{
			out << n[i] << "\t" << integral2(a, b, n[i], m[j], k[j]) << std::endl;
		}
		out.close();
	}
}