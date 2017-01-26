OBJS = main.o pr.o resGraph.o 

CC = clang++

CFLAGS = -O3 -std=c++11 -Wall -c

p: $(OBJS)
	$(CC) $(OBJS) -o p 

main.o: main.cpp resGraph.h pr.h
	$(CC)  $(CFLAGS) main.cpp

resGraph.o: resGraph.cpp resGraph.h 
	$(CC) $(CFLAGS) resGraph.cpp

pr.o: pr.cpp pr.h resGraph.h
	$(CC) $(CFLAGS) pr.cpp

clean:
	\rm *.o p


