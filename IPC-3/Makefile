CC = g++
COUTPUT = -o
COBJECT = -c

all: first second clean

first: first.o shared_array.o
	$(CC) first.o shared_array.o $(COUTPUT) first

second: second.o shared_array.o
	$(CC) second.o shared_array.o $(COUTPUT) second
first.o:
	$(CC) $(COBJECT) first.cpp $(COUTPUT) first.o


second.o:
	$(CC) $(COBJECT) second.cpp $(COUTPUT) second.o

shared_array.o:
	$(CC) $(COBJECT) shared_array.cpp $(COUTPUT) shared_array.o

clean:
	rm -f *.o
