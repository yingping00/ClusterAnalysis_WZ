#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <omp.h>
#include "util.h"
#include "mapper.h"

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
  point *point_arr = read_data(data_file);
  init(point_arr);

  //run mapper function through the list of data sample points
  mapper(point_arr[2]);
  printf("actual address is %p",&point_arr[2]);
  printf("cltr_assigned for point 2 is %d\n", point_arr[2].cltr_assigned);


}
