#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include "util.h"
#include "mapper.h"

int NUM_THREADS = 8;

int main(int argc, char *argv[]){
  //a guard
  if(argc!= 3){
      fprintf(stderr, "Must provide 2 args -- "
              "a string specifying the filename of datasets, and another"
              " string for filename used to output resulut.\n");
  }

  FILE *data_file = fopen(argv[1],"r");
  char filename[12];
  strcpy(filename, argv[2]);
  strcat(filename,".csv");
  FILE *output_file = fopen(filename,"w");

  //read dataset; initialize cluster centroids to be the first <NUM_CLUSTER> points in the dataset
  point *plist_head = read_data(data_file);
  init(plist_head);

  run mapper function through the list of data sample points
  point *pCrawl = plist_head;
  omp_set_num_threads(NUM_THREADS);

  double start = omp_get_wtime();

  #pragma omp parallel private(pCrawl)
  #pragma omp single
    while(pCrawl){
  #pragma omp task
      mapper(pCrawl);
      pCrawl = pCrawl->next;
    }

  printf("Time w/ openmp md is : \t %f \n", omp_get_wtime()-start);

}
