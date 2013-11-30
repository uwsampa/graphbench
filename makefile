CC=g++
CFLAGS=-c -Wall

all: gb

gb: gb.o graph.o bfs.o sp.o tc.o graph_io.o graph_util.o
	$(CC) gb.o graph.o bfs.o sp.o tc.o graph_io.o graph_util.o -o gb

gb.o: gb.cpp
	$(CC) $(CFLAGS) gb.cpp
	
graph.o: graph.cpp
	$(CC) $(CFLAGS) graph.cpp
	
bfs.o: bfs.cpp
	$(CC) $(CFLAGS) bfs.cpp
	
sp.o: sp.cpp
	$(CC) $(CFLAGS) sp.cpp
	
tc.o: tc.cpp
	$(CC) $(CFLAGS) tc.cpp
	
graph_io.o: graph_io.cpp
	$(CC) $(CFLAGS) graph_io.cpp
	
graph_util.o: graph_util.cpp
	$(CC) $(CFLAGS) graph_util.cpp
	
clean:
	rm -rf *o gb