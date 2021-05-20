#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cstring>

#include </usr/include/gsl/gsl_errno.h>
#include </usr/include/gsl/gsl_fft_complex.h>

const int k = 8; // 8, 10, 12
const int N = pow(2, k);
const double w = 4*M_PI/N;
const std::string filename1="k8_zab.txt";
const std::string filename2="k8_niezab.txt";

inline double delta()
{
	return 2 * (rand()/(RAND_MAX + 1.0)) - 1;
}

inline double y0(int i)
{
	return sin(w*i) + sin(2*w*i) + sin(3*w*i);
}

int main()
{
	srand(time(0));

	double* y1 = new double[2*N]; // zaburzone
	double* y2 = new double[2*N]; // niezaburzony
	

	for (int i=0; i < N; i++)
	{
		y1[2*i] = y0(i) + delta();
		y2[2*i] = y0(i);
		y1[2*i + 1] = y2[2*i + 1] = 0.0;
	}

	double* y1_copy = new double[2*N];
	double* y2_copy = new double[2*N];

	memcpy(y1_copy, y1, 2*N*sizeof(double));
	memcpy(y2_copy, y2, 2*N*sizeof(double));

	gsl_fft_complex_radix2_forward(y1, 1, N);
	gsl_fft_complex_radix2_forward(y2, 1, N);

	double* m1 = new double[N]; //moduły zaburzonego
	double* m2 = new double[N]; //moduły niezaburzonego
	double ck1, ck2;

	for (int i=0; i < N; i++)
	{
		m1[i] = sqrt(y1[2*i] * y1[2*i] + y1[2*i+1] * y1[2*i+1]);
		m2[i] = sqrt(y2[2*i] * y2[2*i] + y2[2*i+1] * y2[2*i+1]);
		
		if (i == 0)
		{
			ck1 = m1[0];
			ck2 = m2[0];
		}
		else
		{
			if (m1[i] > ck1)
				ck1 = m1[i];
			if (m2[i] > ck2)
				ck2 = m2[i];
		}
	}

	ck1 /= 2.0;
	ck2 /= 2.0;

	if (k == 8)
	{
		std::ofstream out;
		out.open("k8_real_img_FT.txt", std::ofstream::out);

		for (int i=0; i < N; i++)
		{
			out << i << " " << y1[2*i] << " " << y1[2*i + 1] << std::endl;
		}

		out.close();
	
		out.open("k8_mod.txt", std::ofstream::out);

		for (int i=0; i < N; i++)
		{
			out << i << " " << m1[i] << " " << ck1 <<  std::endl; 
		}

		out.close();
	}

	for (int i=0; i < N; i++)
	{
		if (m1[i] < ck1)
		{
			y1[2*i] = y1[2*i+1] = 0.0;
		}
		if (m2[i] < ck2)
		{
			y2[2*i] = y2[2*i+1] = 0.0;
		}
	}

	gsl_fft_complex_radix2_backward(y1, 1, N);
	gsl_fft_complex_radix2_backward(y2, 1, N);

	for (int i=0; i < 2*N; i++)
	{
		y1[i] /= N;
		y2[i] /= N;	
	}

	std::ofstream out1, out2;

	out1.open(filename1, std::ofstream::out);
	out2.open(filename2, std::ofstream::out);
	for (int i=0; i < N; i++)
	{
		out1 << i << " " << y1[2*i] << " " << y1_copy[2*i] << std::endl;
		out2 << i << " " << y2[2*i] << " " << y2_copy[2*i] << std::endl;
	}
	
	out1.close();
	out2.close();

		

	delete[] y1;
	delete[] y2;
	delete[] m1;
	delete[] m2;
	delete[] y1_copy;
	delete[] y2_copy;

	return 0;
}



