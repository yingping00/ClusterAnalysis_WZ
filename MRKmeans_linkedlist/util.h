#include <stdio.h>

#ifndef UTIL_H
#define UTIL_H

typedef struct point_type point;
typedef struct cluter_type cluster;
typedef struct cluster_centroid_type cluster_centroid;

extern int NUM_DIM;
extern int NUM_CLUSTERS;
extern int MAX_ITERATIONS;

extern cluster_centroid *cltr_arr;

//A structure to represent every sample in the dataset.
typedef struct point_type{
  int cltr_assigned;
  int xcoord;
  int ycoord;
  point *next;
} point;

//A structure to represent every cluster.
typedef struct cluter_type{
  int num_points;
  int sum_x;
  int sum_y;
  //cluster *next;
} cluster;

typedef struct cluster_centroid_type{
  int xcoord;
  int ycoord;
  // cluster_centroid *next;
} cluster_centroid;

double ComputeDist(point p, cluster_centroid center);

point* read_data(FILE *data_file);

void init(point *pCrawl);

#endif
