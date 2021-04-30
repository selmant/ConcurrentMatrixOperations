CC = g++
CFLAGS  = -pthread -Wall -std=c++1y

default: matrix

matrix:  main.o Matrix.o MatrixMeanWorker.o 
	$(CC) $(CFLAGS) -o matrix main.o Matrix.o MatrixMeanWorker.o 

main.o:  main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Matrix.o:  Matrix.cpp Matrix.h 
	$(CC) $(CFLAGS) -c Matrix.cpp

MatrixMeanWorker.o:  MatrixMeanWorker.cpp MatrixMeanWorker.h 
	$(CC) $(CFLAGS) -c MatrixMeanWorker.cpp

clean: 
	$(RM) matrix matrix2.txt *.o *~
