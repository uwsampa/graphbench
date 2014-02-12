CC=g++
CFLAGS=-c -Wall

OBJECTS = gb.o graph.o bfs.o sssp.o tc.o graph_io.o graph_util.o

all: gb

gb: $(OBJECTS)
	$(CC) $(OBJECTS) -o gb

gb.o: gb.cpp
	$(CC) $(CFLAGS) gb.cpp
	
graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) graph.cpp
	
bfs.o: bfs.cpp bfs.h
	$(CC) $(CFLAGS) bfs.cpp
	
sssp.o: sssp.cpp sssp.h
	$(CC) $(CFLAGS) sssp.cpp
	
tc.o: tc.cpp tc.h
	$(CC) $(CFLAGS) tc.cpp
	
graph_io.o: graph_io.cpp graph_io.h
	$(CC) $(CFLAGS) graph_io.cpp
	
graph_util.o: graph_util.cpp graph_util.h
	$(CC) $(CFLAGS) graph_util.cpp
	
clean:
	rm -rf gb $(OBJECTS)