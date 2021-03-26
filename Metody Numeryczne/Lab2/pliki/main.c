#include <stdio.h>
#include <stdlib.h>

#define N 500
#define Xa 0.5
#define Xb 2.0

int main()
{
	double ** matrix = (double **)malloc((N+1) * sizeof(double *));
	if (matrix == NULL)
		exit(EXIT_FAILURE);

	for (int i=0; i < N+1; i++)
	{
		matrix[i] = (double *)calloc(N+1, sizeof(double));
		if (matrix[i] == NULL)
			exit(EXIT_FAILURE);
	}

	const double h = 2*Xb/(N-1);

	for (int i=1; i < N+1; i++)
	{
		for (int j=1; j < N+1; j++)
		{
			if (i == j)
				matrix[i][j] = -2/(h*h);
			else if (i+1 == j || j+1 == i)
				matrix[i][j] = 1/(h*h);

		}
	}

	//warunki brzegowe
	matrix[1][1] = 1;
	matrix[1][2] = 0;

	matrix[N][N] = 1;
	matrix[N][N-1] = 0;

	double * x = (double *)calloc(N+1, sizeof(double));
	if (x == NULL)
		exit(EXIT_FAILURE);

	double * p = (double *)calloc(N+1, sizeof(double));
	if (p == NULL)
		exit(EXIT_FAILURE);

	for (int i=1; i < N+1; i++)
	{
		x[i] = -Xb + (h * (i-1));

		if (x[i] >= -Xa && x[i] < 0)
			p[i] = 1;
		else if (x[i] > 0 && x[i] <= Xa)
			p[i] = -1;
		else
			p[i] = 0;	
	}

	p[1] = p[N] = 0;

	double ** L = (double **)malloc((N+1) * sizeof(double *));
	double ** U = (double **)malloc((N+1) * sizeof(double *));

	if (!L || !U)
		exit(EXIT_FAILURE);

	for (int i=0; i < N+1; i++)
	{
		L[i] = (double *)calloc(N+1, sizeof(double));
		U[i] = (double *)calloc(N+1, sizeof(double));
		
		if (!L[i] || !U[i])
			exit(EXIT_FAILURE);
	}

	for (int i=1; i < N+1; i++)
	{
		for (int j=1; j < N+1; j++)
		{
			if (i == j)
			{
				L[i][j] = 1;
				if (i != 1)
					U[i][j] = matrix[i][j] - L[i][j-1]*U[i-1][j];
				else
					U[i][j] = 1;
			}
			else if (j+1 == i)
			{
				L[i][j] = matrix[i][j]/U[i-1][j];
			}
			else if(i+1 == j)
			{
				U[i][j] = matrix[i][j];
			}
			
		}
	}

	double * y = (double *)calloc(N+1, sizeof(double));
	if (!y)
		exit(EXIT_FAILURE);

	y[1] = -p[1];
	for (int i=2; i < N+1; i++)
	{
		y[i] = -p[i] - L[i][i-1]*y[i-1];
	}

	double * V = (double *)calloc(N+1, sizeof(double));
	if (!V)
		exit(EXIT_FAILURE);

	for (int i=1; i < N+1; i++)
	{
		V[i] = y[i]/U[i][i];
	}

	for (int i=N-1; i > 0; i--)
	{
		V[i] = (y[i] - U[i][i+1]*V[i+1])/U[i][i];
	}

	double * V2 = (double *)calloc(N+1, sizeof(double));
	for (int i=1; i < N+1; i++)
	{
		if (x[i] >= -Xb && x[i] <= -Xa)
		{
			V2[i] = x[i]/16 + 1.0/8;
		}
		else if (x[i] >= -Xa && x[i] <= 0)
		{
			V2[i] = -(x[i]*x[i]/2) - (7.0/16 * x[i]);
		}
		else if (x[i] >= 0 && x[i] <= Xa)
		{
			V2[i] = (x[i]*x[i]/2) - (7.0/16 * x[i]);
		}
		else
		{
			V2[i] = x[i]/16 - 1.0/8;
		}
	}

	FILE * file_ptr = fopen("results.txt", "w");
	for (int i=1; i < N+1; i++)
	{
		fprintf(file_ptr, "%10.4g\t%10.4g\t%10.4g\n", x[i], V[i], V2[i]);
	}
	fclose(file_ptr);

	free(x);
	free(V);
	free(V2);
	free(p);
	free(y);

	for (int i=0; i < N+1; i++)
	{
		free(L[i]);
		free(U[i]);
		free(matrix[i]);
	}

	free(L);
	free(U);
	free(matrix);

	return 0;
}









