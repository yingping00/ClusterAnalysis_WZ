
#include "mapper.h"
#include "util.h"

void mapper(point *p){
  double minDist = ComputeDist(*p, cltr_arr[0]);
  int index = 1;     //IDEA: See if directly using the key will slow down the performance

  for (int i=1; i<NUM_CLUSTERS; i++){
    double dist = ComputeDist(*p, cltr_arr[i]);
    if (dist < minDist){
      minDist = dist;
      index = i+1;
    }
  }
  p->cltr_assigned = index;
}
