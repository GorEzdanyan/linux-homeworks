all: main.o complex.o complex_sort.o finish clean


main.o: main.cpp
	g++ -c main.cpp


complex.o: complex.cpp
	g++ -c complex.cpp


complex_sort.o: complex_sort.cpp
	g++ -c complex_sort.cpp


finish:
	 g++ complex.o main.o complex_sort.o -o main

clean:
	rm -f *.o 
