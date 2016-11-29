# _*_ MakeFile _*_

CC = gcc-6
CFLAGS = -I -Wall
OPTFLAGS = -fopenmp
DEPS = util.h mapper.h reducer.h

OBJ = MRKmeans.o mapper.o reducer.o util.o

EXE = .out
DEL = rm

all: EXEMRKmeans$(EXE)

%.o: %.c $(DEPS)
	$(CC) $(OPTFLAGS) -c -o $@ $< $(CFLAGS)

EXEMRKmeans$(EXE): $(OBJ)
	$(CC) $(OPTFLAGS) -o $@ $^ $(CFLAGS)

cleanobj:
	$(DEL) *.o

cleanexe:
	$(DEL) *$(EXE)
