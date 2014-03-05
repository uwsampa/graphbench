CC=g++
CFLAGS=-c -Wall
OBJECTS = graph.o bfs.o sssp.o tc.o graph_io.o graph_util.o

VPATH = kernels

BINS = undirected_triangle_count \
		single_source_shortest_path \
		breadth_first_search \
		pagerank

all: $(BINS)

undirected_triangle_count: tc_main.o graph.o tc.o graph_io.o graph_util.o
	$(CC) $^ -o $@
	
breadth_first_search: bfs_main.o graph.o bfs.o graph_io.o graph_util.o
	$(CC) $^ -o $@
	
single_source_shortest_path: sssp_main.o graph.o sssp.o graph_io.o graph_util.o
	$(CC) $^ -o $@
	
pagerank: pr_main.o graph.o pr.o graph_io.o graph_util.o
	$(CC) $^ -o $@

bfs_main.o: bfs_main.cpp bfs.h graph_util.h graph_io.h graph.h
	$(CC) $(CFLAGS) $<
	
tc_main.o: tc_main.cpp tc.h graph_util.h graph_io.h graph.h
	$(CC) $(CFLAGS) $<
	
sssp_main.o: sssp_main.cpp sssp.h graph_util.h graph_io.h graph.h
	$(CC) $(CFLAGS) $<
	
pr_main.o: pr_main.cpp pr.h graph_util.h graph_io.h graph.h
	$(CC) $(CFLAGS) $<
	
gb.o: gb.cpp
	$(CC) $(CFLAGS) $<
	
graph.o: graph.cpp graph.h
	$(CC) $(CFLAGS) $<
	
bfs.o: bfs.cpp bfs.h graph.h
	$(CC) $(CFLAGS) $<
	
sssp.o: sssp.cpp sssp.h graph.h
	$(CC) $(CFLAGS) $<
	
pr.o: pr.cpp pr.h graph.h
	$(CC) $(CFLAGS) $<
	
tc.o: tc.cpp tc.h graph.h
	$(CC) $(CFLAGS) $<
	
graph_io.o: graph_io.cpp graph_io.h graph.h
	$(CC) $(CFLAGS) $<
	
graph_util.o: graph_util.cpp graph_util.h graph.h
	$(CC) $(CFLAGS) $<
	
clean:
	rm -rf $(BINS) *.o