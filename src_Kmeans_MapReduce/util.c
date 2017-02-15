#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <time.h>
int NUM_DIM = 2;
int NUM_CLUSTERS = 8;
int MAX_ITERATIONS = 100;
int NUM_THREADS = 8;
cluster_centroid *cltr_arr;

double ComputeDist(point p, cluster_centroid center){
  float xdiff = p.xcoord - center.xcoord;
  float ydiff = p.ycoord - center.ycoord;
  double dist = sqrt(xdiff*xdiff + ydiff*ydiff);
  return dist;
}

point* CreateList(FILE *data_file, int list_len){
  point *qHead;
  point *pCrawl;
  for (int i=0; i<list_len; i++){
      point *newPoint = (point*)malloc(sizeof(point));
      // gurad
      if (newPoint == NULL){
        printf("memory not available for new node.");
        fflush(stdout);
        return NULL;
      }

      //assign point attributes
      newPoint->next = NULL;
      fscanf(data_file,"%*d %d %d\n", &newPoint->xcoord, &newPoint->ycoord);  //The dataset has its first column being the index, which is of no use here.
      newPoint->cltr_assigned = 0;  //initialize the cluster center that each data point is assigned to as 0.

      //Linking
      if (i==0){
        qHead = newPoint;  //create a linked list to store the sample points
        pCrawl = newPoint;              //pCrawl is used to link the points.
      }
      else{
        pCrawl->next = newPoint;
        pCrawl = newPoint;
      }
  }
  return qHead;
}


seg* read_data(FILE *data_file, int num_segs){
  int num_points;

  for (int i=0; i<3; i++){           //skip the first 3 lines
      fscanf(data_file, "%*[^\n]\n");
  }

  fscanf(data_file,"%*s %d", &num_points);

  fscanf(data_file, "%*s\n");

  int seg_len = num_points/num_segs;
  seg *sCrawl;
  seg *sHead;
  for(int i=0;i<num_segs;i++){                        //start reading data points to the array
    seg *newSeg = (seg *)malloc(sizeof(seg));      //An array of num_segs sample lists

    // a guard
    if (newSeg == NULL){
      printf("memory not available for the newSeg.");
      fflush(stdout);
      return NULL;
    }

    //initialize seg elements
    if (i == (num_segs-1)){
      newSeg->head = CreateList(data_file, num_points-seg_len*(num_segs-1));
      newSeg->next = NULL;
    }
    else{
      newSeg->head = CreateList(data_file, seg_len);
      newSeg->next = NULL;
    }

    //Linking
    if (i == 0){
      sHead = newSeg;
      sCrawl = newSeg;
    }
    else{
      sCrawl->next = newSeg;
      sCrawl = newSeg;
    }
  }
  return sHead;
}

void init(seg *sHead){
  //initialize the cluster centroids
  point *pCrawl = sHead->head;
  cltr_arr = (cluster_centroid*)malloc(NUM_CLUSTERS*sizeof(cluster_centroid));
  time_t t;
  srand((unsigned) time(&t));
  for (int i=0; i<NUM_CLUSTERS; i++){
    cltr_arr[i].xcoord = rand()%9999999;       //9999999 is the range of the dataset coordinates
    cltr_arr[i].ycoord = rand()%9999999;
  }
}
