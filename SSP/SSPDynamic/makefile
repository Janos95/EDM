OBJS = main.o ssp.o plist.o resGraph.o 

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

plist.o: plist.cpp plist.h resGraph.h
	$(CC) $(CFLAGS) plist.cpp

clean:
	\rm *.o p


