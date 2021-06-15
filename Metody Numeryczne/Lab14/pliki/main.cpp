#include <iostream>
#include <fstream>
#include <cmath>
#include <array>
#include <algorithm>

double gen_1()
{
	static long long x=10;
	int a = 123;
	int c = 1;
	static long long m = pow(2, 15);
	x = (a*x + c) % m;
	return static_cast<double>(x) / (m + 1.0);
}

double gen_2()
{
	static long long x=10;
	int a = 69069;
	int c = 1;
	static long long m = pow(2, 32);
	x = (a*x + c) % m;
	return static_cast<double>(x) / (m + 1.0);
}

double gen_3()
{
	return 4 + (gen_2() + gen_2() - 1) * 3;
}

double F(double x)
{
	if (x <= 4)
	{
		return (-1. / 9) * (-x*x/2 + 4 * x) + (x / 3);
	}
	else
	{
		return (-1. / 9) * (x*x/2 - 4 * x + 16) + (x / 3);
	}
}

int main()
{
	std::ofstream out1, out2;
	out1.open("../wyniki/gen_miesz_1.dat", std::ofstream::out);
	out2.open("../wyniki/gen_miesz_2.dat", std::ofstream::out);

	double prev1 = gen_1();
	double prev2 = gen_2();
	double temp;
	for (int i=0; i < 10000; i++)
	{
		temp = gen_1();
		out1 << prev1 << " " << temp << std::endl;
		prev1 = temp;
		temp = gen_2();
		out2 << prev2 << " " << temp << std::endl;
		prev2 = temp;
	}
	out1.close();
	out2.close();

	std::array<double, 1000> gen3;
	for (int i=0; i < 1000; i++)
	{
		gen3[i] = gen_3();
	}

	std::array<double, 1000> gen3_copy = gen3;
	std::sort(gen3_copy.begin(), gen3_copy.end());

	double a = 1;
	double b = 7;
	double h = (b - a)/10;
	std::array<int, 10> ranges;

	int count = 0;
	int i = 0;
	double limit = a + h;
	for (const double& x: gen3_copy)
	{
		if (x <= limit)
		{
			count++;
		}
		else
		{
			ranges[i] = count;
			std::cout << count << std::endl;
			count = 1;
			limit += h;
			i++;
		}
	}
	ranges[9] = count;
	std::cout << count << std::endl;

	out1.open("../wyniki/pi.dat", std::ofstream::out);
	std::array<double, 10> pi;
	for (int i=0; i < 10; i++)
	{
		pi[i] = F(a + (i+1)*h) - F(a + i*h);
		out1 << pi[i] << " " << pi[i] * ranges[i] << std::endl;
	}
	out1.close();

	double test_chi2 = 0.0;
	for (int i=0; i < 10; i++)
	{
		test_chi2 += pow(ranges[i] - 1000 * pi[i], 2) / (1000 * pi[i]);
	}
	
	double eps = 14.06714;

	if (test_chi2 < eps)
	{
		std::cout << "Nie ma podstaw do odrzucenia hipotezy." << std::endl;
	}
	else
	{
		std::cout << "Hipoteza odrzucona." << std::endl;
	}





	return 0;
}