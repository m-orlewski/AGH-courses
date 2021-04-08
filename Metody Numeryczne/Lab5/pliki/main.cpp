#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <fstream>


const int N = 7;
const int IT_MAX = 12;


std::vector<double> matrix_x_vector(const std::vector<std::vector<double>> &  m, const std::vector<double> &  v)
{
	std::vector<double> ret_vect(N);

	for (int i=0; i < N; i++)
	{
		ret_vect[i] = 0.0;
		for (int j=0; j < N; j++)
			ret_vect[i] += m[i][j] * v[j];
	}
	return ret_vect;
}

double vector_x_vector(const std::vector<double> & v1, const std::vector<double> & v2)
{
	double ret_val = 0.0;
	for (int i=0; i < N; i++)
		ret_val += v1[i] * v2[i];

	return ret_val;
}

std::vector<std::vector<double>> matrix_x_matrix(const std::vector<std::vector<double>> & m1, const std::vector<std::vector<double>> & m2)
{
	std::vector<std::vector<double>> ret_m(N);

	for (int i=0; i < N; i++)
	{
		ret_m[i].resize(N);
		for (int j=0; j < N; j++)
		{
			ret_m[i][j] = 0.0;
			for (int k=0; k < N; k++)
			{
				ret_m[i][j] += m1[i][k] * m2[k][j];
			}
		}
	}

	return ret_m;
}

double norm(const std::vector<double> & v)
{
	double sum = 0.0;
	for (double x: v)
	{
		sum += x * x;
	}

	return sqrt(sum);
}

void modify_matrix(std::vector<std::vector<double>> & m, double lambda, const std::vector<double> & v)
{
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < N; j++)
		{
			m[i][j] -= lambda*v[i]*v[j];
		}
	}
}

void transpose(std::vector<std::vector<double>> & X_T, const std::vector<std::vector<double>> & X)
{
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < N; j++)
		{
			X_T[j][i] = X[i][j];
		}
	}
}

int main()
{
	std::ofstream out;
	out.open("lambdas.txt", std::ofstream::out);

	std::vector<std::vector<double>>A(N);
	std::vector<std::vector<double>>W(N);
	std::vector<std::vector<double>>X(N);
	for (int i=0; i < N; i++)
	{
		A[i].resize(N);
		W[i].resize(N);
		X[i].resize(N);
		for (int j=0; j < N; j++)
		{
			A[i][j] = W[i][j] = 1.0/sqrt(2.0 + abs(i - j));
		}
	}

	for (int k = 0; k < N; k++)
	{
		std::vector<double> x0(N, 1.0);
		double lambda;

		for (int i=0; i < IT_MAX; i++)
		{
			std::vector<double> xk;
			xk = matrix_x_vector(W, x0);
			lambda = (vector_x_vector(xk, x0)) / (vector_x_vector(x0, x0));
			double norma = norm(xk);	
			for (int j=0; j < N; j++)
			{
				x0[j] = xk[j]/norma;
			}
			out << k << " " << i << " " << lambda << std::endl;
		}
		out << std::endl;

		modify_matrix(W, lambda, x0);

		for (int j=0; j < N; j++)
		{
			X[k][j] = x0[j];
		}

	}

	out.close();

	std::vector<std::vector<double>>X_T(N);
	for (int i=0; i < N; i++)
		X_T[i].resize(N);

	transpose(X_T, X);	

	out.open("D_matrix.txt", std::ofstream::out);
	auto D = matrix_x_matrix(matrix_x_matrix(X, A), X_T);
	for (int i=0; i < N; i++)
	{
		for (int j=0; j < N; j++)
			out << D[i][j] << " ";
		out << std::endl;
	}
	out.close();
}
















