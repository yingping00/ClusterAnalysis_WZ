#include <stdio.h>
int main(int argc, char *argv[]){
  int num_points;
  FILE *data_file = fopen(argv[1],"r");
  for (int i=0; i<3; i++){           //skip the first 5 lines
      fscanf(data_file, "%*[^\n]\n", NULL);
  }
  fscanf(data_file,"%*s %d", &num_points);
  printf("num_points = %d\n",num_points);
}
