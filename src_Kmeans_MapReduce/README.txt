1. Compile by:
	make
(There might be some warning concerning redundant declarations, just ignore it.)
2. Check if the EXE file has been generated using ‘ls’ and Run by:
	./EXEMRKmeans_omp.out <data file>.txt <output file>. 
(For example: ./EXEMRKmeans_omp.out 2D_20000.txt output)
3. The <output file>.csv will show up in the current folder with results.

Note: 
1. If the makefile doesn’t fit your stored compilers or system, you can change the macros in the makefile.
2. If you want to change any parameters concerning the implementation:
NUM_DIM, NUM_CLUSTERS, MAX_ITERATIONS, NUM_THREADS are defined in util.c.
num_segs is defined in main.