CC = g++
COUTPUT = -o
COBJECT = -c

all: array-summary clean


array-summary: array-summary.o
	$(CC) array-summary.o $(COUTPUT) array-summary

array-summary.o:
	$(CC) $(COBJECT) array-summary.cpp -pthread $(COUTPUT) array-summary.o

clean:
	rm -f *.o
