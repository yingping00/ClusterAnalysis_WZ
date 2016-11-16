#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_CLUSTERS 6
#define MAX_ITERATIONS 100

//read the txt file, construct and return a 2-d array
void read_data(FILE *data_file, int num_points, int num_col, int  num_dim, float **mtrx){
    for (int i=0; i<5; i++){           //skip the first 5 lines
        fscanf(data_file, "%*[^\n]\n", NULL);
    }
    
    for (int i=0; i<num_points; i++){          //start reading data points to array. Point i stores in mtrx[i-1][];
        fscanf(data_file,"%*f",	&mtrx[i][0]);   //mtrx[i-1][0] defines the cluster center it is assigned to; mtrx[i-1][1] is its first-dimension coordinate,and so forth.
        mtrx[i][0]=0;					       //initialize the cluster center that each data point is assigned to as 0.
        for (int k=0; k<MAX_CLUSTERS; k++){
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

// calculate new centrriods

void cal_centriods(int num_points,int num_dim,  float **mtrx, float **cen_mtrx){
    
    float x = 0;
    int x1 =0;
    float y = 0;
    int y1=0;
    for(int jj = 1; jj < MAX_CLUSTERS +1; jj++){
        for(int ii = 0; ii < num_points; ii++){
            if (mtrx[ii][0]== jj){
                //mtrx[ii][num_dim+jj]
                x1++;
                y1++;
                x += mtrx[ii][1];
                y += mtrx[ii][2];
                x = x/x1;
                y = y/y1;
                cen_mtrx[jj-1][0]=x;
                cen_mtrx[jj-1][1]=y;
            }
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

/*
 node number   o column
 cents index  x       y      distance to 1 distance to 2 distance to 3...  distance to MAX_CLUSTERS
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
// this fucntion calcualte the distance of all nodes to all MAX_CLUSTER cluster centriods and store them in the mtrx
// after the calculation, the mtrx is updated with each row's last MAX_CLUSTER columns are the distance to the centriods
// for node number < number of points keep calculating
// a is the centriods one dimentional matrix
void cal_dis (int num_points, int num_col, int num_dim, float **mtrx,  float **cen_mtrx ){
    // assign the new centriods matrix
    for (int ii = 0; ii< num_points; ii++){
        for (int jj =0; jj<MAX_CLUSTERS; jj++){
            
            // (mtrx[ii][1]-mtrx[k][1])^2 +(mtrx[ii][2]-mtrx[k][2])^2
            
            mtrx[ii][jj+num_dim+1] = sqrt((mtrx[ii][1]-cen_mtrx[jj][0])*(mtrx[ii][1]-cen_mtrx[jj][0]) + (mtrx[ii][2]-cen_mtrx[jj][1])*(mtrx[ii][2]-cen_mtrx[jj][1]) );
        }
    }
}
// based on the mtrx after the distance calculation, assign the centriods to each node
void assign_cen(int num_points,int num_dim,  float **mtrx) {
    float min ;
    for(int ii = 0; ii < num_points; ii++) {
        
        min = mtrx[ii][num_dim+1];
        for (int jj = 1; jj < MAX_CLUSTERS; jj++){
            
            if (mtrx[ii][num_dim+1+jj] < min)
            {
                min = mtrx[ii][num_dim+1+jj];
            }
            
        }
        //printf(" %.3f \n", min);
        for (int k = 0; k < MAX_CLUSTERS; k++){
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
    
    int num_dim = atoi(argv[1]), num_col = num_dim+1+MAX_CLUSTERS, num_points = atoi(argv[2]);
    FILE *data_file = fopen(argv[3],"r");
    
    float **mtrx = (float**)malloc(sizeof(float*)*num_points);
    for (int i=0; i<num_points;i++){
        mtrx[i] = (float*)malloc(sizeof(float)*num_col);
    }
    
    read_data(data_file, num_points, num_col, num_dim, mtrx);
    
    // * b is the array that store the 6 initial pointers
    int *b = randsamp (MAX_CLUSTERS, 0, num_points-1);
    // checking the random number generation part
    for (int i=0; i<MAX_CLUSTERS; i++){
        printf(" %d \n", b[i]);
    }
    
    
    float **cen_mtrx = (float**)malloc(sizeof(float*)*MAX_CLUSTERS);
    for (int i=0; i<MAX_CLUSTERS;i++){
        cen_mtrx[i] = (float*)malloc(sizeof(float)*num_dim);
    }
    for (int ii = 0; ii< MAX_CLUSTERS; ii++){
        int k = b[ii];
        
        for (int jj =0; jj<num_dim; jj++){
            
            cen_mtrx[ii][jj] = mtrx[k][jj+1];
            
        }
    }
    //check the cen_mtrx values right at the begining
    for (int i=0; i<MAX_CLUSTERS; i++){
        for (int j=0; j<num_dim; j++){
            printf("%.3f\t",cen_mtrx[i][j]);
        }
        printf("\n");
    }
    cal_dis (num_points, num_col, num_dim, mtrx,  cen_mtrx );
    assign_cen(num_points, num_dim,  mtrx);
    float **cen_mtrxnew = (float**)malloc(sizeof(float*)*MAX_CLUSTERS);
    for (int i=0; i<MAX_CLUSTERS;i++)
    {
        cen_mtrxnew[i] = (float*)malloc(sizeof(float)*num_dim);
    }
    cal_centriods(num_points,num_dim,  mtrx, cen_mtrxnew);
    int num_int =1 ;
    
    
    while( compareArrays(cen_mtrx, cen_mtrxnew, MAX_CLUSTERS, num_dim) == 1 && num_int < MAX_ITERATIONS)
    {
        cal_dis (num_points, num_col, num_dim, mtrx,  cen_mtrx );
        assign_cen(num_points, num_dim,  mtrx);
        float **cen_mtrxnew = (float**)malloc(sizeof(float*)*MAX_CLUSTERS);
        for (int i=0; i<MAX_CLUSTERS;i++)
        {
            cen_mtrxnew[i] = (float*)malloc(sizeof(float)*num_dim);
        }
        cal_centriods(num_points,num_dim,  mtrx, cen_mtrxnew);
        num_int ++;
    }
    
    
    
    for (int i=0; i<num_points; i++)
    {
        for (int j=0; j<num_col; j++)
        {printf("%.3f\t",mtrx[i][j]);}
        printf("\n");
    }
    
    for (int i=0; i<MAX_CLUSTERS; i++)
    {
        for (int j=0; j<num_dim; j++)
        {printf("%.3f\t",cen_mtrxnew[i][j]);}
        printf("\n");
    }
    return 0;
}

