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
  point *head;

  for (int i=0; i<3; i++){           //skip the first 3 lines
      fscanf(data_file, "%*[^\n]\n");
  }

  fscanf(data_file,"%*s %d", &num_points);

  fscanf(data_file, "%*s\n");

  for (int i=0; i<num_points; i++){          //start reading data points to array.
      point *newPoint = (point*)malloc(sizeof(point));
      point *pCrawl;

      // gurad
      if (newPoint == NULL){
        printf("memory not available for new node.");
        fflush(stdout);
        return NULL;
      }
      newPoint->next = NULL;
      fscanf(data_file,"%*d %d %d\n", &newPoint->xcoord, &newPoint->ycoord);  //The dataset has its first column being the index, which is of no use here.
      newPoint->cltr_assigned = 0;  //initialize the cluster center that each data point is assigned to as 0.

      //Linking
      if (i==0){
        head = newPoint;  //create a linked list to store the sample points
        pCrawl = newPoint;              //pCrawl is used to link the points.
      }
      else{
        pCrawl->next = newPoint;
        pCrawl = newPoint;
      }
  }
  return head;
}

void init(point *pCrawl){
  //initialize the cluster centroids
  cltr_arr = (cluster_centroid*)malloc(NUM_CLUSTERS*sizeof(cluster_centroid));
  for (int i=0; i<NUM_CLUSTERS; i++){
    cltr_arr[i].xcoord = pCrawl->xcoord;
    cltr_arr[i].ycoord = pCrawl->ycoord;
    pCrawl = pCrawl->next;
  }
}
