#include <iostream>
#include <fstream>
#include <functional>
#include <cmath>

#include "nrutil.h"
#include "nr.h"

#include "nrutil.c"
#include "gauher.c"
#include "gauleg.c"
#include "gaulag.c"
#include "gammln.c"

double integral(float* x, float* w, int n, std::function<double(double)> f)
{
	double C = 0.0;
	for (int i=1; i < n; i++)
	{
		C += f(x[i])*w[i];
	}
	return C;
}

double f1_(double x)
{
	return log(x);
}

double f2_(double x)
{
	return pow(x-10, 2) * sin(4*x);
}

double f2p(double x)
{
	return pow(x-10, 2) * sin(4*x) * exp(-x);
}

double f3_(double x)
{
	return pow(x, 7) * pow(2, -x*x+x+4);
}

double f3p(double x)
{
	return pow(x, 7) * pow(2, -x*x+x+4) * exp(-x*x);
} 

int main()
{
	std::ofstream out;
	
	float x[71];
	float w[71];
	
	double C = 10 * log(10) - 10;
	out.open("../wyniki/gauleg_1.dat", std::ofstream::out);
	for (int n=6; n <= 71; n++)
	{
		gauleg(0, 10, x, w, n-1);
		out << n-1 << " " << std::fabs(integral(x, w, n, f1_) - C) << std::endl;
	}
	out.close();
	
	#2
	
	C = 22.95461022;
	out.open("../wyniki/gaulag_2.dat", std::ofstream::out);
	for (int n=6; n <= 71; n++)
	{
		gaulag(x, w, n-1, 0);
		out << n-1 << " " << std::fabs(integral(x, w, n, f2_) - C) << std::endl;
	}
	out.close();
	
	out.open("../wyniki/gauleg_2.dat", std::ofstream::out);
	for (int n=6; n <= 71; n++)
	{
		gauleg(0, 10, x, w, n-1);
		out << n-1 << " " << std::fabs(integral(x, w, n, f2p) - C) << std::endl;
	}
	out.close();
	
	#3
	C = 14.83995751;
	
	out.open("../wyniki/gauher_3.dat", std::ofstream::out);
	for (int n=6; n <= 71; n++)
	{
		gauher(x, w, n-1);
		out << n-1 << " " << std::fabs(integral(x, w, n, f3_) - C) << std::endl;
	}
	out.close();
	
	out.open("../wyniki/gauleg_3.dat", std::ofstream::out);
	for (int n=6; n <= 71; n++)
	{
		gauleg(-10, 15, x, w, n-1);
		out << n-1 << " " << std::fabs(integral(x, w, n, f3p) - C) << std::endl;
	}
	out.close();
	
	#4
	std::ofstream out1, out2;
	out1.open("../wyniki/f2(x)p(x).dat", std::ofstream::out);
	out2.open("../wyniki/f3(x)p(x).dat", std::ofstream::out);
	double x1 = 0.;
	double x2 = 100.;
	for (int i=0; i <= 1000; i++)
	{
		double x = x1 + i*0.1;
		out1 << x << " " << f2p(x) << std::endl;
	}
	out1.close();
	
	x1 = -10.;
	x2 = 100.;
	for (int i=0; i <= 1100; i++)
	{
		double x = x1 + i*0.1;
		out2 << x << " " << f3p(x) << std::endl;
	}
	
	out2.close();
}


