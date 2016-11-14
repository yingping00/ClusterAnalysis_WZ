#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_CLUSTERS 6
#define MAX_ITERATIONS 100

//read the txt file, construct and return a 2-d array
int *[] read_data(FILE *data_file){
	int num_lines,num_points;

	while(!feof(data_file)){                  //count the number of data points in the file
		char ch = fgetc(data_file);
		if(ch == '\n'){
			num_lines++;
		}
	}
	num_points = num_lines-5;     
	//Todo: count the number of data in a line to obtain the number of dimensions.
	float mtrx[num_points][3];        //the 2-d array to store the data points
	float (*mtrx_ptr)[3] = mtrx; 
	for (int i=0; i<5; i++){           //skip the first 5 lines
		fscanf(data_file, "%*[^\n]\n", NULL);
	}

	for (int i=0; i<num_points; i++){          //start reading data points to array. Point i stores in mtrx[i-1][];
											   // mtrx[i-1][0] defines the cluster center it is assigned to; mtrx[i-1][1] is its first-dimension coordinate,and so forth.
		fscanf(data_file,"%*f %f %f\n", &mtrx[i][0], &mtrx[i][1], &mtrx[i][2]);
	}

	for (int i=1;i<num_points;i++){
		mtrx[i][0]=0;
	}

	return mtrx_ptr;
} 

int main(){
	FILE *data_file = fopen("atlanta.txt","r");
	read_data(data_file);
}