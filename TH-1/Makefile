CC = g++
COUTPUT = -o
COBJECT = -c

all: array-summary clean


array-summary: array-summary.o
	$(CC) array-summary.o -pthread $(COUTPUT) array-summary

array-summary.o:
	$(CC) $(COBJECT) array-summary.cpp  $(COUTPUT) array-summary.o

clean:
	rm -f *.o
