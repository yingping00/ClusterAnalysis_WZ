// time for the callpse section is 0.001
// this callaspe funciton is wrong!!!! need private variable to be added
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define NUM_THREADS 4

void main ()
{
	int A[10][100];
	int Result=0;
	for(int i=0;i<10;i++)
		{		for(int j=0;j<100;j++)
			{
			  A[i][j] = 1;
			}
		}

		int i, j;
		double start = omp_get_wtime();
		omp_set_num_threads(NUM_THREADS);
		// if callpse is not used, 0.001, but when callaspe is used, then the time is 0.0000
		#pragma omp parallel for collapse(2) reduction(+: Result) private (j)
			for(i=0;i<10;i++)
				{
					for(j=0;j<100;j++)
					{
						Result += A[i][j];
					//	printf("%d", Result);
					}
				}

			printf("result = %d\n", Result);
			printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);

	}
