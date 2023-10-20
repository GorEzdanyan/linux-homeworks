CC = g++
COUTPUT = -o
COBJECT = -c

all: main clean

main: main.o
	g++ main.o

main.o:
	$(CC) $(COBJECT) FS-1.cpp $(COUTPUT) main.o

clean:
	rm main.o
