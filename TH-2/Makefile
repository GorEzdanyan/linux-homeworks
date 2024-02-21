CC = g++
COUTPUT = -o
COBJECT = -c

all: link clean

link: parallel-scheduler.o demo-application.o
	$(CC) parallel_scheduler.o demo-application.o  $(COUTPUT) demo-application


parallel-scheduler.o:
	$(CC) $(COBJECT) parallel_scheduler.cpp -pthread $(COUTPUT) parallel_scheduler.o


demo-application.o:
	$(CC) $(COBJECT) demo-application.cpp -pthread $(COUTPUT) demo-application.o

clean:
	rm -f *.o
