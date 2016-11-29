// 0.524
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4
static long NUM_STEP = 100000000;
double STEP;

void main()
{
int i, nthreads;
double pi;
double sum[NUM_THREADS];
double STEP = 1.00/(double)NUM_STEP;
double start = omp_get_wtime();
omp_set_num_threads(NUM_THREADS);

#pragma omp parallel
 {
    int i, id, nthrds;
    double x;
    nthrds = omp_get_num_threads();
    id = omp_get_thread_num();
    if (id == 0) nthreads = nthrds;
   //#pragma omp parallel for reduction (+:sum)
    for (i=id, sum[id]=0.0; i< NUM_STEP; i=i+nthrds)
    {
          x = (i+0.5)*STEP;
          sum[id] += 4.0/(1.0+x*x);

    }
  }
   for (i=0, pi=0.0; i<nthreads; i++) pi +=sum[i]*STEP;
   printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);
   printf("the simulated psi is %f\n", pi);
}
