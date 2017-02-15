# _*_ MakeFile _*_

CC = gcc
CFLAGS = -lm
OPTFLAGS = -fopenmp -std=c99 
DEPS = util.h mapper.h reducer.h

OBJ1 = MRKmeans_omp.o mapper.o reducer.o util.o

EXE = .out
DEL = rm

#all: EXEMRKmeans_omp$(EXE)

%.o: %.c $(DEPS)
	$(CC) $(OPTFLAGS) -c -o $@ $< $(CFLAGS)

EXEMRKmeans_omp$(EXE): $(OBJ1)
	$(CC) $(OPTFLAGS) -o $@ $^ $(CFLAGS)

cleanobj:
	$(DEL) *.o

cleanexe:
	$(DEL) *$(EXE)
