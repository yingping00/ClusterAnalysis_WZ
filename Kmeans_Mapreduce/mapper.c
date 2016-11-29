
#include "mapper.h"
#include "util.h"

extern int NUM_DIM;
extern int NUM_CLUSTERS;
extern cluster_centroid *cltr_arr;

void mapper(point p){
  double minDist = ComputeDist(p, cltr_arr[0]);
  int index = 1;     //IDEA: See if directly using the key will slow down the performance

  for (int i=1; i<NUM_CLUSTERS; i++){
    double dist = ComputeDist(p, cltr_arr[i]);
    if (dist < minDist){
      minDist = dist;
      index = i+1;
    }
  }
  p.cltr_assigned = index;

  printf("here address is %p",&p);

  printf("index is %d",p.cltr_assigned);
}
