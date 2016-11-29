//PAD =8, 0.350, no matter which number that you set, the maximum wil be used
// for this computer, PAD =8 will be used in the future
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4
#define PAD 8
static long NUM_STEP = 100000000;
double STEP;

void main()
{
  int i, nthreads;
  double pi;
  double sum[NUM_THREADS][PAD];
  double STEP = 1.00/(double)NUM_STEP;
  double start = omp_get_wtime();
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel
   {
      int i, id, nthrds;
      double x;
      id = omp_get_thread_num();
      nthrds = omp_get_num_threads();
     if (id == 0) nthreads = nthrds;
    //#pragma omp parallel for reduction (+:sum)
      for (i=id, sum[id][0]=0.0;  i< NUM_STEP; i+=nthrds)
      {
            x = (i+0.5)*STEP;
            sum[id][0] += 4.0/(1.0+x*x);

      }
    }
     for (i=0, pi=0.0; i<nthreads; i++) pi +=sum[i][0]*STEP;
     printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);
     printf("the simulated psi is %f\n", pi);
}
