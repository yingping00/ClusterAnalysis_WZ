// 0.344
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4
//#define MAX_ITERATIONS 100
static long NUM_STEP = 100000000;
double STEP;

void main()
{
int i, nthreads;
double pi;
double STEP = 1.00/(double)NUM_STEP;
double start = omp_get_wtime();
omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
 {
    int i, id, nthrds;
    double x;
    double sum;
    nthrds = omp_get_num_threads();
    id = omp_get_thread_num();
   if (id == 0) nthreads = nthrds;
  //#pragma omp parallel for reduction (+:sum)
    for (i=id, sum=0.0; i< NUM_STEP; i=i+nthrds)
    {
          x = (i+0.5)*STEP;
          sum+= 4.0/(1.0+x*x);
    }
    #pragma omp critical
    pi += sum *STEP;
  }
   printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);
   printf("the simulated psi is %f\n", pi);
}
