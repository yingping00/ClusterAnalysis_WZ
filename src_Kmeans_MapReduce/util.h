#include <stdio.h>

#ifndef UTIL_H
#define UTIL_H

typedef struct point_type point;
typedef struct cluster_type cluster;
typedef struct cluster_centroid_type cluster_centroid;
typedef struct seg_type seg;

extern int NUM_DIM;
extern int NUM_CLUSTERS;
extern int MAX_ITERATIONS;
extern int NUM_THREADS;

extern cluster_centroid *cltr_arr;

//A structure to represent every sample in the dataset.
typedef struct point_type{
  int cltr_assigned;
  int xcoord;
  int ycoord;
  point *next;
  point *next_in_cltr;
} ;

typedef struct seg_type{
  point *head;
  seg *next;
} ;

//A structure to represent every cluster.
typedef struct cluster_type{
  int num_points;
  int sum_x;
  int sum_y;
  //cluster *next;
} ;

typedef struct cluster_centroid_type{
  double xcoord;
  double ycoord;
  // cluster_centroid *next;
} ;

point* CreateList(FILE *data_file, int list_len);

double ComputeDist(point p, cluster_centroid center);

seg* read_data(FILE *data_file, int num_segs);

void init(seg *sHead);

#endif
