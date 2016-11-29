#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4
static long NUM_STEP = 100000000;
double STEP;

void main()
{
  //int i, nthreads;
  double pi;
  double sum;
  double STEP = 1.00/(double)NUM_STEP;
  double start = omp_get_wtime();
  omp_set_num_threads(NUM_THREADS);
  #pragma omp parallel for reduction (+:sum) schedule (auto)
    for (int i=0; i< NUM_STEP; i++)
    {
          double x=0.0;
          x = (i+0.5)*STEP;
          sum += 4.0/(1.0+x*x);
    }
     pi = sum *STEP;
     printf("Time for this omp process is : \t %f \n", omp_get_wtime()-start);
     printf("the simulated psi is %f\n", pi);


}
