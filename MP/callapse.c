// time for the callpse section is 0.001
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS 4

void main ()
{
	double A[100][1000];
	printf("I'm here111");
	double Result =0.0;
	for(int i=0;i<100;i++)
		{		for(int j=0;j<1000;j++)
			{
			  A[i][j] = 2.89;
			}
		}

		double start = omp_get_wtime();
		omp_set_num_threads(NUM_THREADS);
		#pragma omp parallel for collapse(2)
		for(int i=0;i<100;i++)
			{
				for(int j=0;j<1000;j++)
				{
					Result += A[i][j];
				}
			}
			printf("result = %f\n", Result);
			printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);

	}
