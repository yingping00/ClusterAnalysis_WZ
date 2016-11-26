#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>

#define NUM_CLUSTERS 6
/#define NUM_THREADS 6
#define MAX_ITERATIONS 100

void read_data(FILE *data_file, int num_points, int num_col, int  num_dim, float **mtrx){
    for (int i=0; i<5; i++){           //skip the first 5 lines
        fscanf(data_file, "%*[^\n]\n", NULL);
    }

    for (int i=0; i<num_points; i++){          //start reading data points to array. Point i stores in mtrx[i-1][];
        fscanf(data_file,"%*f",	&mtrx[i][0]);   //mtrx[i-1][0] defines the cluster center it is assigned to; mtrx[i-1][1] is its first-dimension coordinate,and so forth.
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

// CHANGED add the parallel section
void cal_centriods(int num_points,int num_dim,  float **mtrx, float **cen_mtrx)
  {
    float x[NUM_CLUSTERS];
    float y[NUM_CLUSTERS];
    int num_points_in_cluster;

    for(int jj = 1, num_points_in_cluster = 0; jj < NUM_CLUSTERS +1; jj++){


        for(int ii = 0; ii < num_points; ii++){
            if (mtrx[ii][0]== jj){
                x[jj-1] = 0;
                y[jj-1] = 0;
                // this is to remove the inner and outter loop's carried dependence
                num_points_in_cluster = (jj-0)* num_points +ii+1;
                x [jj-1]+= mtrx[ii][1];
                y [jj-1]+= mtrx[ii][2];
            }
            cen_mtrx[jj-1][0] = x[jj-1]/num_points_in_cluster;
            cen_mtrx[jj-1][1] = y[jj-1]/num_points_in_cluster;
        }
    }
   }

// comapre the old centriods aray and new centriods array, if they are the same, return 0
int compareArrays(float **cen_mtrx, float **cen_mtrxnew, int row, int column) {

    for(int ii = 0; ii < row; ii++) {
        for (int jj = 0; jj < column; jj++){
            if (cen_mtrx[ii][jj] != cen_mtrxnew[ii][jj]) return 1;
        }

    }
    return 0;
}

void cal_dis (int num_points, int num_col, int num_dim, float **mtrx,  float **cen_mtrx ){

    for (int ii = 0; ii< num_points; ii++){
        for (int jj =0; jj<NUM_CLUSTERS; jj++){
            // (mtrx[ii][1]-mtrx[k][1])^2 +(mtrx[ii][2]-mtrx[k][2])^2
            float xdiff = mtrx[ii][1]-cen_mtrx[jj][0];
            float ydiff = mtrx[ii][2]-cen_mtrx[jj][1];
            mtrx[ii][jj+num_dim+1] = sqrt(xdiff*xdiff + ydiff*ydiff);
        }

    }
}

// based on the mtrx after the distance calculation, assign the centriods to each node
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
        //printf(" %.3f \n", min);
        for (int k = 0; k < NUM_CLUSTERS; k++){
            if (mtrx[ii][num_dim+1+k] == min)
            {
                mtrx[ii][0] = k+1;
                // printf(" %d \n", k+1);
            }

        }
    }
}

//To run: a.exe 2 20 Atlanta.exe output.exe
int main(int argc, char *argv[]){
    //a guard
    if(argc!= 5){
        fprintf(stderr, "Must provide 4 args--an integer as number"
                "of the dimensions, another integer as number of points,"
                "a string specifying the filename of datasets, and another"
                " string for filename used to output resulut.\n");
        exit(EXIT_FAILURE);
    }

    int num_dim = atoi(argv[1]), num_col = num_dim+1+NUM_CLUSTERS, num_points = atoi(argv[2]);
    FILE *data_file = fopen(argv[3],"r");
    FILE *output_file = fopen(argv[4],"w");

    float **mtrx = (float**)malloc(sizeof(float*)*num_points);
    for (int i=0; i<num_points;i++){
        mtrx[i] = (float*)malloc(sizeof(float)*num_col);
    }

    int *b = randsamp (NUM_CLUSTERS, 0, num_points-1);
    float **cen_mtrx = (float**)malloc(sizeof(float*)*NUM_CLUSTERS);
    for (int i=0; i<NUM_CLUSTERS;i++){
        cen_mtrx[i] = (float*)malloc(sizeof(float)*num_dim);
    }
    for (int ii = 0; ii< NUM_CLUSTERS; ii++){
        int k = b[ii];
        for (int jj =0; jj<num_dim; jj++){
            cen_mtrx[ii][jj] = mtrx[k][jj+1];
        }
    }
    read_data(data_file, num_points, num_col, num_dim, mtrx);
    cal_dis (num_points, num_col, num_dim, mtrx,  cen_mtrx );
    assign_cen(num_points, num_dim,  mtrx);
    printf("this is the first section");
    float **cen_mtrxnew = (float**)malloc(sizeof(float*)*NUM_CLUSTERS);
    for (int i=0; i<NUM_CLUSTERS;i++)
    {
        cen_mtrxnew[i] = (float*)malloc(sizeof(float)*num_dim);
    }
    cal_centriods(num_points,num_dim,  mtrx, cen_mtrxnew);
    int num_int = 1;
    printf("this is the 2 section");
    while( compareArrays(cen_mtrx, cen_mtrxnew, NUM_CLUSTERS, num_dim) == 1 && num_int < MAX_ITERATIONS)
    {

        cal_dis (num_points, num_col, num_dim, mtrx,  cen_mtrx );
        assign_cen(num_points, num_dim,  mtrx);
        float **cen_mtrxnew = (float**)malloc(sizeof(float*)*NUM_CLUSTERS);
        for (int i=0; i<NUM_CLUSTERS;i++)
        {
            cen_mtrxnew[i] = (float*)malloc(sizeof(float)*num_dim);
        }
        cal_centriods(num_points,num_dim,  mtrx, cen_mtrxnew);
        num_int ++;
    }
    printf("this is the 3section");
    fprintf(output_file, "POINT_NUM,ASSIGNED_CLUSTER,XCOORD,YCOORD,");
    for(int i=1; i<NUM_CLUSTERS+1; i++){
      fprintf(output_file,"DIST_CLUSTER%d,",i);
    }

    for(int i=1; i<num_points+1; i++){
        fprintf(output_file,"\n%d,", i);
        for(int j=0; j<num_col; j++){
            fprintf(output_file, "%.3f,",mtrx[i][j] );
        }
    }

    for (int i=0; i<NUM_CLUSTERS; i++)
    {
        for (int j=0; j<num_dim; j++)
        {printf("%.3f\t",cen_mtrxnew[i][j]);}
        printf("\n");
    }

    //TODO:  (1)close file handle (2)free pointer

    return 0;
}
