To run sequential Kmeans:
1. Compile by:
	gcc -fopenmp -std=c99 Kmeans.c -o EXEKmeans.out -lm
2. Run by:
	./EXEKmeans.out <Dimension> <Number of points> <data file>.txt <output file>
(For example:./EXEKmeans.out 2 20000 2D_20000.txt  out)

To run simple OpenMP Kmeans:
1. Compile by:
	gcc -fopenmp -std=c99 Kmeans_mp.c -o EXEKmeans_mp.out -lm
2. Run by:
	./EXEKmeans_mp.out <Dimension> <Number of points> <data file>.txt <output file>
(For example:./EXEKmeans_mp.out 2 20000 2D_20000.txt  out)