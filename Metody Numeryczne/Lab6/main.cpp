#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>

double df(double x)
{
	return cos(x) - x / 4;
}

double f(double x)
{
	return sin(x) - x*x/8;
}

std::vector<double> metSiecznych(double x0, double x1)
{
	std::vector<double> xi;
	xi.push_back(x0);
	xi.push_back(x1);
	for (int k=1; k <= 15; k++)
	{
		xi.push_back(x1 - ((f(x1)*(x1-x0)) / (f(x1)-f(x0))));
		x0 = x1;
		x1 = xi[xi.size()-1];
	}

	return xi;
}

std::vector<double>  metNewtona(double x0)
{
	std::vector<double> xi;
	xi.push_back(x0);
	for (int k=1; k <= 10; k++)
	{
		xi.push_back(xi[k-1] - f(xi[k-1]) / df(xi[k-1]));
	}

	return xi;
}

int main()
{
	std::ofstream out;
	out.open("MetodaNewtona.txt", std::ofstream::out);

	std::vector<double> Newton1 = metNewtona(-8.0);
	std::vector<double> Newton2 = metNewtona( 8.0);

	out << "Kolejne przybliżenia miejsc zerowych znalezionych metodą Newtona\n\n";
	out << "nr iteracji\twart. przybliżenia\twart. funkcji\twart. pochodnej\n";
	for (unsigned i=1; i < Newton1.size(); i++)
	{
		out << i  << "\t\t";
		out <<  Newton1[i] << "\t\t";
		out << f(Newton1[i]) << "\t\t";
		out << df(Newton1[i]) << std::endl;
	}

	out << std::endl;
	for (unsigned i=1; i < Newton2.size(); i++)
	{
		out << i  << "\t\t";
		out << Newton2[i] << "\t\t";
		out << f(Newton2[i]) << "\t\t";
		out << df(Newton2[i]) << std::endl;
	}
	
	out.close();
	
	out.open("MetodaSiecznych.txt", std::ofstream::out);

	std::vector<double> Sieczna1 = metSiecznych(-8.0, -8.1);
	std::vector<double> Sieczna2 = metSiecznych( 8.0,  8.1);
	
	out << "Kolejne przybliżenia miejsc zerowych znalezionych metodą siecznych\n\n";
	out << "nr iteracji\tx(k+1)\t\t\tf(x(k))\t\t\tf(x(k-1))\n";
	for (unsigned i=0; i < Sieczna1.size()-2; i++)
	{
		out << i+1 << "\t\t";
		out << Sieczna1[i+2] << "\t\t";
		out << f(Sieczna1[i+1]) << "\t\t";
		out << f(Sieczna1[i]) << std::endl;
	}
	out << std::endl;
	for (unsigned i=0; i < Sieczna2.size()-2; i++)
	{
		out << i+1 << "\t\t";
		out << Sieczna2[i+2] << "\t\t";
		out << f(Sieczna2[i+1]) << "\t\t";
		out << f(Sieczna2[i]) << std::endl;
	}
	out.close();
	
}









