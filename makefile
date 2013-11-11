CC=g++
CFLAGS=-c -Wall

all: gb

gb: gb.o graph.o bfs.o graph_io.o
	$(CC) gb.o graph.o bfs.o graph_io.o -o gb

gb.o: gb.cpp
	$(CC) $(CFLAGS) gb.cpp
	
graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp
	
bfs.o: bfs.cpp
	$(CC) $(CFLAGS) bfs.cpp
	
graph_io.o: graph_io.cpp
	$(CC) $(CFLAGS) graph_io.cpp
	
clean:
	rm -rf *o gb