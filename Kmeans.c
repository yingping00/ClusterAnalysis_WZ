#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <omp.h>
#include "util.h"

int NUM_CLUSTERS = 6;
int MAX_ITERATIONS = 100;

//TODO: (1) modularize (2) Consider plotting the result



// comapre the old centriods aray and new centriods array, if they are the same, return 0
int compareArrays(float **cen_mtrx, float **cen_mtrxnew, int row, int column) {

    for(int ii = 0; ii < row; ii++) {
        for (int jj = 0; jj < column; jj++){
            if (cen_mtrx[ii][jj] != cen_mtrxnew[ii][jj]) return 1;
        }

    }
    return 0;
}

/*
 node number   o column
 cents index  x       y      distance to 1 distance to 2 distance to 3...  distance to NUM_CLUSTERS
 0            0 (original)   read   read        calulate     calulate    calulate     ...        calulate
 1
 2
 3
 4
 .
 .
 .
 num_points-1
 */




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
    char filename[30];
    strcpy(filename, argv[4]);
    strcat(filename,".csv");
    FILE *output_file = fopen(filename,"w");

    float **mtrx = (float**)malloc(sizeof(float*)*num_points);
    for (int i=0; i<num_points;i++){
        mtrx[i] = (float*)malloc(sizeof(float)*num_col);
    }

    read_data(data_file, num_points, num_col, num_dim, mtrx);

    // * b is the array that store the 6 initial pointers
    int *b = randsamp (NUM_CLUSTERS, 0, num_points-1);

    // checking the random number generation part
    for (int i=0; i<NUM_CLUSTERS; i++){
        printf(" %d \n", b[i]);
    }


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
    //check the cen_mtrx values right at the begining
    for (int i=0; i<NUM_CLUSTERS; i++){
        for (int j=0; j<num_dim; j++){
            printf("%.3f\t",cen_mtrx[i][j]);
        }
        printf("\n");
    }
    cal_dis (num_points, num_col, num_dim, mtrx,  cen_mtrx );
    assign_cen(num_points, num_dim,  mtrx);
    float **cen_mtrxnew = (float**)malloc(sizeof(float*)*NUM_CLUSTERS);
    for (int i=0; i<NUM_CLUSTERS;i++)
    {
        cen_mtrxnew[i] = (float*)malloc(sizeof(float)*num_dim);
    }
    cal_centriods(num_points,num_dim,  mtrx, cen_mtrxnew);
    int num_int =1 ;

    double start = omp_get_wtime();
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

    printf("Time without openmp is : \t %f \n", omp_get_wtime()-start);
    fprintf(output_file, "POINT_NUM,ASSIGNED_CLUSTER,XCOORD,YCOORD,");

    for(int i=1; i<NUM_CLUSTERS+1; i++){
      fprintf(output_file,"DIST_CLUSTER%d,",i);
    }

    for(int i=1; i<num_points+1; i++){
        fprintf(output_file,"\n%d,", i);
        for(int j=0; j<num_col; j++){
            fprintf(output_file, "%.3f,",mtrx[i-1][j]);
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
