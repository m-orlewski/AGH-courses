#include <iostream>
#include <fstream>
#include <cmath>

const int IT_MAX = 1000;
const double h = 0.1;
const double eps = 0.01;

double f(double x, double y)
{
	return 5.0 * pow(x*x - y, 2) / 2.0 + pow(1 - x, 2); 
}

double dx(double x, double y, double delta)
{
	return (f(x + delta, y) - f(x - delta, y)) / (2 * delta);
}

double dy(double x, double y, double delta)
{
	return (f(x, y + delta) - f(x, y - delta)) / (2 * delta);
}

int main()
{
	double x0 = -0.75;
	double y0 =  1.75;
	double x1, y1;
	double delta = 0.0001;

	std::ofstream out;
	out.open("eps1.dat", std::ofstream::out);

	out << x0 << ", " << y0 << std::endl;
	for (int i = 1; i <= IT_MAX; i++)
	{
		x1 = x0 - h * dx(x0, y0, delta);
		y1 = y0 - h * dy(x0, y0, delta);
		out << x1 << ", " << y1 << std::endl;
		double val = sqrt(pow(x1-x0, 2) + pow(y1-y0, 2));
		if (val < eps)
			break;
		x0 = x1;
		y0 = y1;
	}

	return 0;
}
