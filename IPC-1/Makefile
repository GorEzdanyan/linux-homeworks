CC = g++
COUTPUT = -o
COBJECT = -c

all: signal-echo clean

signal-echo: singal-echo.o 
	$(CC) signal-echo.o $(COUTPUT) signal-echo

singal-echo.o:
	$(CC) $(COBJECT) signal-echo.cpp $(COUTPUT) signal-echo.o

clean:
	rm -f *.o
