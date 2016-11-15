#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CLUSTERS 6
#define MAX_ITERATIONS 100

//read the txt file, construct and return a 2-d array
void read_data(FILE *data_file, int num_points, int num_col, float **mtrx){
	for (int i=0; i<5; i++){           //skip the first 5 lines
		fscanf(data_file, "%*[^\n]\n", NULL);
	}

	for (int i=0; i<num_points; i++){          //start reading data points to array. Point i stores in mtrx[i-1][];
		fscanf(data_file,"%*f",	&mtrx[i][0]);   //mtrx[i-1][0] defines the cluster center it is assigned to; mtrx[i-1][1] is its first-dimension coordinate,and so forth.
		mtrx[i][0]=0;					       //initialize the cluster center that each data point is assigned to as 0. 
		for (int j=1;j<num_col; j++){
			fscanf(data_file,"%f", &mtrx[i][j]);
		}
		fscanf(data_file,"\n",NULL);    
		
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

	int num_dim = atoi(argv[1]), num_col = num_dim+1, num_points = atoi(argv[2]);
	FILE *data_file = fopen(argv[3],"r");

	float **mtrx = (float**)malloc(sizeof(float*)*num_points);
	for (int i=0; i<num_points;i++){
		mtrx[i] = (float*)malloc(sizeof(float)*num_col);
	} 

	read_data(data_file, num_points, num_col, mtrx);
	
	//Just for checking
	for (int i=0; i<num_points; i++){
		for (int j=0; j<num_col; j++){
			printf("%f\t",mtrx[i][j]);
		}
		printf("\n");
	}
	return 0;
}