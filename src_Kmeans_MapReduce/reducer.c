#include "util.h"
#include <omp.h>

point* combine(int index, seg* sCrawl, point* head_cltr_list){
  point *pCrawl = sCrawl->head;
  point *clCrawl;
  int num_in_cltr = 0;
  while(sCrawl){
    while(pCrawl){
      if(pCrawl->cltr_assigned == index){
        num_in_cltr+=1;
        //linking with a different attribubte
        if(num_in_cltr == 1){
          head_cltr_list = pCrawl;        //IDEA:comman bug. The change in the argument itself will not be stored outside the function
          head_cltr_list->next_in_cltr = NULL;
          clCrawl = head_cltr_list;
        }
        else{
          pCrawl->next_in_cltr=NULL;
          clCrawl->next_in_cltr = pCrawl;
          clCrawl = pCrawl;
        }
      }
      pCrawl = pCrawl->next;
    }
    sCrawl = sCrawl->next;
    if(sCrawl){
      pCrawl = sCrawl->head;
    }
  }
  return head_cltr_list;
}

int reduce(int index, point* heads_cltr_list){
  point* clCrawl = heads_cltr_list;
  double x_sum = 0.0;
  double y_sum = 0.0;
  int num_points_cltr = 0;
  int unchanged = 0;

  while(clCrawl){
    num_points_cltr++;
    x_sum += clCrawl->xcoord;
    y_sum += clCrawl->ycoord;
    clCrawl = clCrawl->next_in_cltr;
  }

  double x_new = x_sum/num_points_cltr;
  double y_new = y_sum/num_points_cltr;
#pragma omp single
  if(( x_new != cltr_arr[index].xcoord) ||(y_new != cltr_arr[index].xcoord)){
    cltr_arr[index].xcoord = x_new;
    cltr_arr[index].ycoord = y_new;
  }
  else{
    unchanged = 1;
  }
  return unchanged;
}
