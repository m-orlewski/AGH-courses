#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 1000

float iloczyn_skalarny(const float * a, const float * b)
{
	float s=0;
	for (int i=0; i < N; i++)
	{
		s += a[i]*a[i];
	}
	return s;
}

void print_vector(float * a)
{
	for (int i=0; i < N; i++)
		printf("%lf ", a[i]);
	printf("\n");
}

void print_matrix(float ** a)
{
	for (int i=0; i < N; i++)
	{
		print_vector(a[i]);
		printf("\n");
	}
}

int main()
{
	int m=10;
	
	float ** A = (float **)malloc(N * sizeof(float *));
	if (!A)
		exit(EXIT_FAILURE);

	for (int i=0; i < N; i++)
	{
		A[i] = (float *)calloc(N, sizeof(float));
		if (!A[i])
		{
			exit(EXIT_FAILURE);
		}

		for (int j=0; j < N; j++)
		{
			if (abs(i-j) <= m)
				A[i][j] = 1.0/(1.0+abs(i-j));
		}
	}

	float * b = (float *)malloc(N * sizeof(float));
	if (!b)
		exit(EXIT_FAILURE);
	for (int i=0; i < N; i++)
	{
		b[i] = i;
	}

	float * x = (float *)malloc(N * sizeof(float));
	if (!x)
		exit(EXIT_FAILURE);

	for (int i=0; i < N; i++)
		x[i] = 1;

	float * r = (float *)calloc(N, sizeof(float));
	if (!r)
		exit(EXIT_FAILURE);
	float * temp = (float *)calloc(N, sizeof(float));
	if (!temp)
		exit(EXIT_FAILURE);

	FILE * file_ptr = fopen("float_1.txt", "w");
	if (!file_ptr)
	{
		exit(EXIT_FAILURE);
	}

	int k=0;
	float alfa;
	float norm_r, norm_x;
	do
	{
		k++;
		for (int i=0; i < N; i++)
		{
			float val=0;
			for (int j=0; j < N; j++)
			{
				val += A[i][j]*x[j];
			}
			r[i] = b[i] - val;
		}
		
		float licznik = iloczyn_skalarny(r, r);

		for (int i=0; i < N; i++)
		{
			temp[i] = 0;
			for (int j=0; j < N; j++)
			{
				temp[i] += r[j] * A[j][i];
			}
		}

		float mianownik = 0;
		for (int i=0; i < N; i++)
		{
			mianownik += temp[i]*r[i];	
		}

		alfa = licznik/mianownik;
		for (int i=0; i < N; i++)
		{
			x[i] += alfa*r[i];
		}
		norm_r = sqrt(iloczyn_skalarny(r, r));
		norm_x = sqrt(iloczyn_skalarny(x, x));
		fprintf(file_ptr, "%d\t%.12f\t%.12f\t%.12f\n", k, norm_r, alfa, norm_x);
	} while(k < 500 && norm_r > 1e-6);


	free(x);
	free(r);
	free(b);
	free(temp);

	for (int i=0; i < N; i++)
		free(A[i]);
	free(A);

	fclose(file_ptr);

	return 0;
}
















