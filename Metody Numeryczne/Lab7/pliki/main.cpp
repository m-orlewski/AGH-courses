#include <vector>
#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

double y(double x)
{
	return x / (1.0 + x * x);
}

double dx(double xa, double xb, int n)
{
		return (xb - xa) / n;
}

void fill_1(std::vector<double> & v, int n, double x_a, double x_b)
{
	for (int i=0; i <= n; i++)
	{
		v.push_back(x_a + i * dx(x_a, x_b, n));
	}
}
void fill_2(std::vector<double> & v, int n, double x_a, double x_b)
{	
	for (int i=0; i <= n; i++)
	{
		v.push_back(0.5 * ((x_b - x_a) * cos(M_PI * (2*i + 1) / (2*n + 2)) + (x_a + x_b)));
	}
}

double interpolacja(const std::vector<double> xi, double x)
{
	double w = 0.0;
	for (unsigned i=0; i < xi.size(); i++)
	{
		double L = 1.;
		double M = 1.;
		
		for (unsigned j=0; j < xi.size(); j++)
		{
			if (i != j)
			{
				L *= x - xi[j];
				M *= xi[i] - xi[j];
			}
		}
		w += y(xi[i]) * L / M;
	}
	return w;
}


int main()
{
	double x_a = -3;
    double x_b = 8;
	
	std::vector<double> xi1_5;
	std::vector<double> xi2_5;
	fill_1(xi1_5, 5, x_a, x_b);
	fill_2(xi2_5, 5, x_a, x_b);
	
	std::vector<double> xi1_10;
	std::vector<double> xi2_10;
	fill_1(xi1_10, 10, x_a, x_b);
	fill_2(xi2_10, 10, x_a, x_b);
	
	std::vector<double> xi1_15;
	std::vector<double> xi2_15;
	fill_1(xi1_15, 15, x_a, x_b);
	fill_2(xi2_15, 15, x_a, x_b);
	
	std::vector<std::vector<double>> xs = {xi1_5, xi1_10, xi1_15, xi2_5, xi2_10, xi2_15};
	std::vector<std::string> file_names = {"xi1_5.txt", "xi1_10.txt", "xi1_15.txt"};
	
	for (int index = 0; index < 3; index++)
	{
		std::ofstream out;
		out.open(file_names[index], std::ofstream::out);
		for (int i=0; i <= 220; i++)
		{
			double x = x_a + i * 0.05;
			double w1 = interpolacja(xs[index], x);
			double w2 = interpolacja(xs[index+3], x);
			out << x << "\t" << w1 << "\t" << w2 << std::endl; 
		}
		
		out.close();
	}
}



