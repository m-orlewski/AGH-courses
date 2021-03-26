#include <stdio.h>
#include <stdlib.h>

#include "/usr/include/gsl/gsl_math.h"
#include "/usr/include/gsl/gsl_linalg.h"

int main(void)
{
	//wymiary macierzy
	int n=4;
	int signum;


	FILE * file_ptr = fopen("results.txt", "w");
	if (!file_ptr)
	{
		printf("Unable to open file\n");
		exit(EXIT_FAILURE);
	}

	//alokacja macierzy i jej kopii
	gsl_matrix * A = gsl_matrix_calloc(n, n);
	gsl_matrix * A_copy = gsl_matrix_calloc(n, n);

	//Inicjalizacja macierzy A i kopii
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			double a = 1.0/(i + j + 2);
			gsl_matrix_set(A, i, j, a);
			gsl_matrix_set(A_copy, i, j, a);
		}
	}

	//Wypisanie macierzy A
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			printf("%10.5g ", gsl_matrix_get(A, i, j));
		}
		printf("\n");
	}

	//wektor permutacji wierszy
	gsl_permutation * p = gsl_permutation_calloc(n);

	//rozkład LU macierzy A
	gsl_linalg_LU_decomp(A, p, &signum);

	//wyznacznik macierzy A
	double det=1.0;

	fprintf(file_ptr, "Elementy diagonali macierzy U:\n");
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			if (i == j)
			{
				double a = gsl_matrix_get(A, i, j);
				det *= a;
				fprintf(file_ptr, "%lf ", a);
			}
		}
	}
	
	fprintf(file_ptr, "\nWyznacznik macierzy A: %.5g\n\n", det);

	//Macierz odwrotna do A
	gsl_matrix * A_inv = gsl_matrix_calloc(n, n);
	//Wektor wyrazów wolnych b
	gsl_vector * b = gsl_vector_calloc(n);
	//Wektro rozwiązań x
	gsl_vector * x = gsl_vector_calloc(n);

	//Wyznaczanie macierzy odwrotnej do A 
	for (int j=0; j < n; j++)
	{
		for (int i=0; i < n; i++) gsl_vector_set(b, i, 0.0);

		gsl_vector_set(b, j, 1.0);
		gsl_linalg_LU_solve(A, p, b, x);

		for (int i=0; i < n; i++) gsl_matrix_set(A_inv, i, j, gsl_vector_get(x, i));
	}

	//Wpisanie macierzy odwrotnej do A do pliku
	fprintf(file_ptr, "-------Macierz odwrotna A--------\n");
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			fprintf(file_ptr, "%10.5g ", gsl_matrix_get(A_inv, i, j));
		}
		fprintf(file_ptr, "\n");
	}

	gsl_matrix * C = gsl_matrix_calloc(n, n);

	//Iloczyn macierzy
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			double sum = 0.0;
			for (int k=0; k < n; k++)
			{
				sum += gsl_matrix_get(A_copy, i, k) * gsl_matrix_get(A_inv, k, j);
			}
			gsl_matrix_set(C, i, j, sum);		
		}
	}

	//Wpisanie macierzy C(A*A_inv) do pliku
	fprintf(file_ptr, "\n-----Iloczyn macierzy A i macierzy odwrotnej-----\n");
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			fprintf(file_ptr, "%10.5g ", gsl_matrix_get(C, i, j));
		}
		fprintf(file_ptr, "\n");
	}

	double cond, max1, max2;
	for (int i=0; i < n; i++)
	{
		for (int j=0; j < n; j++)
		{
			if (i == 0 && j == 0)
			{
				max1 = gsl_matrix_get(A_copy, i, j);
				max2 = gsl_matrix_get(A_inv, i, j);
				continue;
			}

			double z = gsl_matrix_get(A_copy, i, j);
			if (z > max1)
				max1 = z;

			z = gsl_matrix_get(A_inv, i, j);
			if (z > max2)
				max2 = z;
		}
	}

	cond = max1 * max2;
	fprintf(file_ptr, "\nWskaźnik uwarunkowania macierzy: %.5g\n", cond);

	fclose(file_ptr);
	return 0;
}











