CC = g++
COUTPUT = -o
COBJECT = -c

all: prime-calculator clean

prime-calculator: prime-calculator.o 
	$(CC) prime-calculator.o $(COUTPUT) prime-calculator

prime-calculator.o:
	$(CC) $(COBJECT) prime-calculator.cpp $(COUTPUT) prime-calculator.o

clean:
	rm -f *.o
