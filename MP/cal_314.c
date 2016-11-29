#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define NUM_THREADS 4
//#define MAX_ITERATIONS 100
static long NUM_STEP = 100000000;
double STEP;
// int
//omp_get_num_threads;
// this is the function to get the time in seconds since a fixed
// point fo time in the past
//double omp_get_wtime();
void main()
{
  int i, nthreads;
  double pi;
  double sum;
  double STEP = 1.00/(double)NUM_STEP;
  omp_set_num_threads(NUM_THREADS);


    int id, nthrds;
    double x;
    id = omp_get_num_threads();
    nthrds = omp_get_num_threads();
    if (id == 0) nthreads = nthrds;
  #pragma omp parallel for reduction (+:sum)
    for (i=0; i< NUM_STEP; i++)
    {
          x = (i+0.5)*STEP;
          sum += 4.0/(1.0+x*x);

    }


     pi = sum *STEP;

printf("the simulated psi is %f\n", pi);


}
