CC = g++
COUTPUT = -o
COBJECT = -c

all: main clean


main: main.o
	$(CC) main.o $(COUTPUT) array-summary

main.o:
	$(CC) $(COBJECT) array-summary.cpp $(COUTPUT) main.o

clean:
	rm -f *.o
