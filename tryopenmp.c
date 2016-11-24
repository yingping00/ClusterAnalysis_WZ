#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 4
#define NUM_ELEM 100
#define NUM_ELEM2 100
double A[NUM_ELEM][NUM_ELEM2];	// inputs; initialization not shown
//double C[NUM_THREADS];         	// result computed by each thread
double Result;                 	// final result
int main (void)
{
//	int i, nthreads;			// shared variables
		Result =0.0;
			for (int i=0;  i<NUM_ELEM; i++){

				for (int j=0;  j<NUM_ELEM2; j++){
					 A[i][j] = 2.89;
				}
			}


		omp_set_num_threads(NUM_THREADS);
			
			#pragma omp parallel for schedule(dynamic,1) collapse(2)
			for (int i=0;i<NUM_ELEM;i++){
				for (int j=0;j<NUM_ELEM2;j++){
					Result += A[i][j];
				}
			}

		//for (i=0, Result=0.0; i<nthreads; i++)  Result += C[i];
		printf ("result = %f\n", Result);

	}
//	int i, id, nthrds;	// private variables
	//	id = omp_get_thread_num();
	//	nthrds = omp_get_num_threads();
	//	if (id == 0) nthreads = nthrds;	// one thread writes nthreads
