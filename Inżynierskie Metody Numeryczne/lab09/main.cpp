#include <iostream>
#include <fstream>
#include <cmath>

#include </usr/include/gsl/gsl_math.h>
#include </usr/include/gsl/gsl_linalg.h>
#include </usr/include/gsl/gsl_blas.h>

const int nx = 40;
const int ny = 40;
const int delTa = 1;
const int dt = 1;
const int Ta = 40;
const int Tb = 0;
const int Tc = 30;
const int Td = 0;
const double kB = 0.1;
const double kD = 0.6;
const int IT_MAX = 2000;

void fillMatrix(gsl_matrix* A, gsl_matrix* B, gsl_vector* c, gsl_vector* T, int N)
{
	for (int i = 0; i <= nx; i++)
    {
		for (int j = 0; j <= ny; j++)
        {
			int l = i + j * (nx + 1);
			if (i != 0 && i != nx && j != 0 && j != ny)
            {
				gsl_matrix_set(A, l, l - nx - 1, dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(A, l, l - 1, dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(A, l, l + 1, dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(A, l, l + nx + 1, dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(A, l, l, ((-2 * dt / pow(delTa, 2)) - 1));

				gsl_matrix_set(B, l, l - nx - 1, -dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(B, l, l - 1, -dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(B, l, l + 1, -dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(B, l, l + nx + 1, -dt / (2 * pow(delTa, 2)));
				gsl_matrix_set(B, l, l, ((2 * dt / pow(delTa, 2)) - 1));
			}
			else if (i == 0 || i == nx)
            {
				gsl_matrix_set(A, l, l, 1);
				gsl_matrix_set(B, l, l, 1);
				gsl_vector_set(c, l, 0);
			}
		}
	}

	for (int i = 1; i <= nx - 1; i++)
    {
		int l = i + ny * (nx + 1);
		gsl_matrix_set(A, l, l - nx - 1, -1 / (kB * delTa));
		gsl_matrix_set(A, l, l, 1 + (1 / (kB * delTa)));
		gsl_vector_set(c, l, Tb);
		for (int j = 0; j <= N - 1; j++)
        {
			gsl_matrix_set(B, l, j, 0.);
		}
	}

	for (int i = 1; i <= nx - 1; i++)
    {
		int l = i + 0 * (nx + 1);
		gsl_matrix_set(A, l, l + nx + 1, -1 / (kD * delTa));
		gsl_matrix_set(A, l, l, 1 + (1 / (kD * delTa)));
		gsl_vector_set(c, l, Td);
		for (int j = 0; j <= N - 1; j++)
        {
			gsl_matrix_set(B, l, j, 0.);
		}
	}
	
	for (int j = 0; j <= ny; j++)
    {
		int l = 0 + j * (nx + 1);
		gsl_vector_set(T, l, Ta);
	}

	for (int j = 0; j <= ny; j++)
    {
		int l = nx + j * (nx + 1);
		gsl_vector_set(T, l, Tc);
	}

	for (int i = 0; i <= nx; i++)
    {
		for (int j = 0; j <= ny; j++)
        {
			int l = i + j * (nx + 1);
			if (i != 0 && i != nx)
				gsl_vector_set(T, l, 0.);
		}
	}
}

void map(std::fstream& file1, std::fstream& file2, gsl_vector* T, int N)
{
		int i = 0;
		int j = 0;
		for (int k = 0; k < N; k++)
		{
			j = k / (nx + 1);
			i = k - (j * (nx + 1));
			file1 << i << "\t" << j << "\t" << gsl_vector_get(T, k) << "\n";
			if ((k + 1) % (nx + 1) == 0)
				file1 << "\n";
		}
}

void CN(gsl_matrix* A, gsl_matrix* B, gsl_vector* c, gsl_vector* b, gsl_vector* T, gsl_permutation* p, int N)
{
	std::fstream out1, out2, out3, out4, out5;
	std::fstream out6, out7, out8, out9, out10;

	out1.open("wyniki/T_it_100.dat", std::ostream::out);
	out2.open("wyniki/T_it_200.dat", std::ostream::out);
	out3.open("wyniki/T_it_500.dat", std::ostream::out);
	out4.open("wyniki/T_it_1000.dat", std::ostream::out);
	out5.open("wyniki/T_it_2000.dat", std::ostream::out);

	out6.open("wyniki/T2_it_100.dat", std::ostream::out);
	out7.open("wyniki/T2_it_200.dat", std::ostream::out);
	out8.open("wyniki/T2_it_500.dat", std::ostream::out);
	out9.open("wyniki/T_2it_1000.dat", std::ostream::out);
	out10.open("wyniki/T_2it_2000.dat", std::ostream::out);

	for (int it=1; it <= IT_MAX; it++)
	{
		gsl_blas_dgemv(CblasNoTrans, 1, B, T, 0, b);
		gsl_blas_daxpy(1, c, b);
		gsl_linalg_LU_solve(A, p, b, T);

		if (it == 100)
			map(out1, out6, T, N);
		else if (it == 200)
			map(out2, out7, T, N);
		else if (it == 500)
			map(out3, out8, T, N);
		else if (it == 1000)
			map(out4, out9, T, N);
		else if (it == 2000)
			map(out5, out10, T, N);
	}

	out1.close();
	out2.close();
	out3.close();
	out4.close();
	out5.close();
	out6.close();
	out7.close();
	out8.close();
	out9.close();
	out10.close();
}

int main()
{
	//1
    int N = (nx + 1) * (ny + 1);

	//2
	gsl_matrix* A = gsl_matrix_alloc(N, N);
	gsl_matrix* B = gsl_matrix_alloc(N, N);
	gsl_vector* c = gsl_vector_alloc(N);
	gsl_vector* b = gsl_vector_alloc(N);
	gsl_vector* T = gsl_vector_alloc(N);

	//3
    fillMatrix(A, B, c, T, N);

	//4
    gsl_permutation* p = gsl_permutation_alloc(N);
	int signum=0;
	gsl_linalg_LU_decomp(A, p, &signum);

	//5, 6
	CN(A, B, c, b, T, p, N);

	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_vector_free(c);
	gsl_vector_free(b);
	gsl_vector_free(T);

    return 0;
}
