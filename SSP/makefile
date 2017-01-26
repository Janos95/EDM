OBJS = main.o ssp.o pqueue.o resGraph.o 

CC = clang++

CFLAGS = -O3 -std=c++11 -Wall -c

prog: $(OBJS)
	$(CC) $(OBJS) -o prog 

main.o: main.cpp ssp.h resGraph.h 
	$(CC)  $(CFLAGS) main.cpp

resGraph.o: resGraph.cpp resGraph.h 
	$(CC) $(CFLAGS) resGraph.cpp

ssp.o: ssp.cpp ssp.h resGraph.h 
	$(CC) $(CFLAGS) ssp.cpp

pqueue.o: pqueue.cpp pqueue.h resGraph.h
	$(CC) $(CFLAGS) pqueue.cpp

clean:
	\rm *.o p


