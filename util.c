#include <stdio.h>
#include <time.h>

extern int NUM_CLUSTERS;

void read_data(FILE *data_file, int num_points, int num_col, int  num_dim, float **mtrx){
    for (int i=0; i<5; i++){           //skip the first 5 lines
        fscanf(data_file, "%*[^\n]\n", NULL);
    }

    for (int i=0; i<num_points; i++){          //start reading data points to array. Point i stores in mtrx[i-1][];
        fscanf(data_file,"%*d");   //mtrx[i-1][0] defines the cluster center it is assigned to; mtrx[i-1][1] is its first-dimension coordinate,and so forth.
        mtrx[i][0]=0;					       //initialize the cluster center that each data point is assigned to as 0.
        for (int k=0; k<NUM_CLUSTERS; k++){
            mtrx[i][num_dim+k+1]=0;
        }

        for (int j=1;j<num_dim+1; j++){
            fscanf(data_file,"%f", &mtrx[i][j]);
        }
        fscanf(data_file,"\n",NULL);
    }
}

// random number generation fcuntion
int* randsamp(int x, int min, int max)
  {
    int r,i=x,*a_clus;

    a_clus=malloc(x*sizeof(int));

    while (i--) {
        r= (max-min+1-i);
        a_clus[i]=min+=(r ? rand()%r : 0);
        min++;
    }
    while (x>1) {
        r=a_clus[i=rand()%x--];
        a_clus[i]=a_clus[x];
        a_clus[x]=r;
    }

    return a_clus;
  }

  void cal_centriods(int num_points,int num_dim,  float **mtrx, float **cen_mtrx){
      float x;
      float y;
      int num_points_in_cluster;
      for(int jj = 1; jj < NUM_CLUSTERS +1; jj++){
        num_points_in_cluster = 0;
        x = 0;
        y = 0;
          for(int ii = 0; ii < num_points; ii++){
              if (mtrx[ii][0]== jj){
                  //mtrx[ii][num_dim+jj]
                  num_points_in_cluster++;
                  x += mtrx[ii][1];
                  y += mtrx[ii][2];
              }
              cen_mtrx[jj-1][0] = x/num_points_in_cluster;
              cen_mtrx[jj-1][1] = y/num_points_in_cluster;
          }
      }
  }

void cal_dis (int num_points, int num_col, int num_dim, float **mtrx,  float **cen_mtrx ){
      // assign the new centriods matrix
      for (int ii = 0; ii< num_points; ii++){
          for (int jj =0; jj<NUM_CLUSTERS; jj++){
              // (mtrx[ii][1]-mtrx[k][1])^2 +(mtrx[ii][2]-mtrx[k][2])^2
              float xdiff = mtrx[ii][1]-cen_mtrx[jj][0];
              float ydiff = mtrx[ii][2]-cen_mtrx[jj][1];
              mtrx[ii][jj+num_dim+1] = sqrt(xdiff*xdiff + ydiff*ydiff);
              /*IDEA:combine the assign_cen to here
                if (mtrx[ii][jj+num_dim+1] < temp){
                  mtrx[ii][0] = jj+1;
                }
              }
              */
          }
      }
  }

void assign_cen(int num_points,int num_dim,  float **mtrx) {
      float min ;
      for(int ii = 0; ii < num_points; ii++) {
          min = mtrx[ii][num_dim+1];
          for (int jj = 1; jj < NUM_CLUSTERS; jj++){
              if (mtrx[ii][num_dim+1+jj] < min)
              {
                  min = mtrx[ii][num_dim+1+jj];
              }
          }
        //  printf(" %.3f \n", min);
          for (int k = 0; k < NUM_CLUSTERS; k++){
              if (mtrx[ii][num_dim+1+k] == min)
              {
                  mtrx[ii][0] = k+1;
                  // printf(" %d \n", k+1);
              }

          }
      }
  }
