#include </usr/include/gsl/gsl_eigen.h>
#include <stdio.h>
#include <math.h>

int Kronecker(int i, int j)
{
	if (i == j)
		return 1;
	else
		return 0;
}

double p(double x, double alfa)
{
	return 1 + 4* alfa * x * x;
}

int main()
{
	FILE * file_ptr1 = fopen("alfa.txt", "w");
	FILE * file_ptr2 = fopen("alfa0.txt", "w");
	FILE * file_ptr3 = fopen("alfa100.txt", "w");
	int L = 10;
	int n = 200;
	int N = 1;

	double delta_x = (double)L/(n + 1);

	gsl_matrix * A = gsl_matrix_calloc(n, n);
	gsl_matrix * B = gsl_matrix_calloc(n, n);
	gsl_vector * x = gsl_vector_calloc(n);
	gsl_eigen_gensymmv_workspace * w = gsl_eigen_gensymmv_alloc(n);
	gsl_vector * eval = gsl_vector_calloc(n);
	gsl_matrix * evec = gsl_matrix_calloc(n, n);

	for (int alfa=0; alfa <= 100; alfa += 2)
	{
		for (int i=0; i < n; i++)
		{
			for (int j=0; j < n; j++)
			{
				double valX = (double)-L/2 + delta_x * (i+1);
				double valA = (double)(-Kronecker(i, j+1) + 2*Kronecker(i, j) - Kronecker(i, j-1)) / (delta_x * delta_x); //!!!!!!!!!!!!!!!
				double valB = (p(valX, alfa) * Kronecker(i, j)) / N;
				gsl_matrix_set(A, i, j, valA);
				gsl_matrix_set(B, i, j, valB);
				gsl_vector_set(x, i, valX);
			}
		}

		gsl_eigen_gensymmv(A, B, eval, evec, w);
		gsl_eigen_gensymmv_sort(eval, evec, GSL_EIGEN_SORT_ABS_ASC);

		fprintf(file_ptr1, "%d", alfa);
		for (int i=0; i < 6; i++)
		{
			fprintf(file_ptr1, " %lf", sqrt(gsl_vector_get(eval, i)));
		}
		fprintf(file_ptr1, "\n");

		if (alfa == 0)
		{
			for (int i=0; i < n; i++)
			{
				fprintf(file_ptr2, "%lf", gsl_vector_get(x, i));
				for (int j=0; j < 6; j++)
				{
					fprintf(file_ptr2, "\t%lf", gsl_matrix_get(evec, i, j));
				}
				fprintf(file_ptr2, "\n");
			}
		}
		else if (alfa == 100)
		{
			for (int i=0; i < n; i++)
			{
				fprintf(file_ptr3, "%lf", gsl_vector_get(x, i));
				for (int j=0; j < 6; j++)
				{
					fprintf(file_ptr3, "\t%lf", gsl_matrix_get(evec, i, j));
				}
				fprintf(file_ptr3, "\n");
			}
		}

	}

	gsl_matrix_free(A);
	gsl_matrix_free(B);
	gsl_matrix_free(evec);
	gsl_vector_free(eval);
	gsl_vector_free(x);
	gsl_eigen_gensymmv_free(w);

	fclose(file_ptr1);
	fclose(file_ptr2);
	fclose(file_ptr3);


	return 0;
}
