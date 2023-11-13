CC = g++
COUTPUT = -o
COBJECT = -c

all: main clean


main: main.o
	$(CC) main.o -o interactive-shell

main.o:
	$(CC) $(COBJECT) interactive-shell.cpp $(COUTPUT) main.o

clean:
	rm -f *.o
