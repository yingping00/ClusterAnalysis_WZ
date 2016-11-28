# _*_ MakeFile _*_

CC = gcc-6
CFLAGS = -I -Wall
OPTFLAGS = -fopenmp
DEPS = util.h

OBJ1 = Kmeans.o util.o
OBJ2 = Kmeans_mp.o

EXE = .out
DEL = rm

all: EXEKmeans$(EXE) EXEKmeans_mp$(EXE)

%.o: %.c $(DEPS)
	$(CC) $(OPTFLAGS) -c -o $@ $< $(CFLAGS)

EXEKmeans$(EXE): $(OBJ1)
	$(CC) $(OPTFLAGS) -o $@ $^ $(CFLAGS)

EXEKmeans_mp$(EXE): $(OBJ2)
	$(CC) $(OPTFLAGS) -o $@ $^ $(CFLAGS)

cleanobj:
	$(DEL) *.o

cleanexe:
	$(DEL) *$(EXE)
