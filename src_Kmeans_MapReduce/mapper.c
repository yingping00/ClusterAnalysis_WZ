
#include "mapper.h"
#include "util.h"

//We used this function before, but with a different data structure. Now it only serves as a prototype.
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

void mapper_seg(seg *sHead){
  point *pCrawl = sHead->head;
  while (pCrawl){
    double minDist = ComputeDist(*pCrawl, cltr_arr[0]);
    int index = 1;
    for (int i=1; i<NUM_CLUSTERS; i++){
      double dist = ComputeDist(*pCrawl, cltr_arr[i]);
      if (dist < minDist){
        minDist = dist;
        index = i+1;
      }
    }
    pCrawl->cltr_assigned = index;
    pCrawl = pCrawl->next;
  }
}
