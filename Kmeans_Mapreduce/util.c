#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int NUM_DIM = 2;
int NUM_CLUSTERS = 6;
int MAX_ITERATIONS = 100;

cluster_centroid *cltr_arr;

double ComputeDist(point p, cluster_centroid center){
  float xdiff = p.xcoord - center.xcoord;
  float ydiff = p.ycoord - center.ycoord;
  double dist = sqrt(xdiff*xdiff + ydiff*ydiff);
  return dist;
}

point* read_data(FILE *data_file){
  int num_points;
  point *array = (point*)malloc(sizeof(point));  //An array to hold all the sample points.

  for (int i=0; i<3; i++){           //skip the first 3 lines
      fscanf(data_file, "%*[^\n]\n");
  }

  fscanf(data_file,"%*s %d", &num_points);

  fscanf(data_file, "%*s\n");

  for (int i=0; i<num_points; i++){          //start reading data points to array.
      fscanf(data_file,"%*d %d %d\n", &array[i].xcoord, &array[i].ycoord);     //The dataset has its first column being the index, which is of no use here.
      array[i].cltr_assigned=0;					       //initialize the cluster center that each data point is assigned to as 0.
  }

  return array;
}

void init(point *p){
  //initialize the cluster centroids
  cltr_arr = (cluster_centroid*)malloc(NUM_CLUSTERS*sizeof(cluster_centroid));
  for (int i=0; i<NUM_CLUSTERS; i++){
    cltr_arr[i].xcoord = p[i].xcoord;
    cltr_arr[i].ycoord = p[i].ycoord;
  }
}
