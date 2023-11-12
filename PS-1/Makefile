CC = g++
COUTPUT = -o
COBJECT = -c

all: main clean


main: main.o
	$(CC) main.o -o do-command

main.o:
	$(CC) $(COBJECT) do-command.cpp $(COUTPUT) main.o

clean:
	rm -f *.o
