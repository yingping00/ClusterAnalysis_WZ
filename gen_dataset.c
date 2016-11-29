#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int RANGE = 9999999;

int main(int argc, char *argv[]){

    int num_dim =atoi(argv[1]);
    int num_points = atoi(argv[2]);
    time_t t;

    char output_file_name[30];
    strcpy(output_file_name, argv[1]);
    strcat(output_file_name, "D_");
    strcat(output_file_name, argv[2]);
    strcat(output_file_name, ".txt");
    FILE *output_file = fopen(output_file_name,"w");

    fprintf(output_file,"THIS FILE IS A RANDOMLY GENERATED DATASET FOR TESTING CLUSTERING ALGORITHM.\n"
    "COMMENT: COORDINATE IS OF RANGE %d\nPOINT TYPE: %dD\nNUM_POINTS: %d\n", RANGE, num_dim, num_points);

    /*
    CHANGED
    fprintf(output_file,"POINT_NUM\t");
    for(int j=1; j<num_dim+1; j++){
      fprintf(output_file,"%dD-COORD\t",j);
    }
    fprintf(output_file,"\n");
    */

    fprintf(output_file,"NODE_COORD_SECTION\n");

    srand((unsigned) time(&t));

    for(int i=1; i<num_points+1; i++){
      fprintf(output_file,"%d",i);
      for(int j=0; j<num_dim;j++){
        int coord = rand()%RANGE;
        fprintf(output_file,"\t%d", coord);
      }
      fprintf(output_file,"\n");
    }
}
