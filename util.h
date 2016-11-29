

//read the txt file, construct and return a 2-d array
void read_data(FILE *data_file, int num_points, int num_col, int  num_dim, float **mtrx);

// random number generation fcuntion
int* randsamp(int x, int min, int max);

// calculate new centrriods
void cal_centriods(int num_points,int num_dim,  float **mtrx, float **cen_mtrx);


  // this fucntion calcualte the distance of all nodes to all MAX_CLUSTER cluster centriods and store them in the mtrx
  // after the calculation, the mtrx is updated with each row's last MAX_CLUSTER columns are the distance to the centriods
  // for node number < number of points keep calculating
  // a is the centriods one dimentional matrix

  void cal_dis (int num_points, int num_col, int num_dim, float **mtrx,  float **cen_mtrx );


    // based on the mtrx after the distance calculation, assign the centriods to each node
    void assign_cen(int num_points,int num_dim,  float **mtrx) ;
