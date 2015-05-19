
# set to your preferred compiler
ifndef CXX
CXX=c++
endif

CXXFLAGS=-c -O3 -Wall -Igraph-set-up
SRC_DIR = bc \
		bfs \
		cc \
		graph-set-up \
		pagerank \
		sssp \
		triangleCounting

vpath %.cpp $(SRC_DIR)
vpath %.h $(SRC_DIR)

BINS = undirected_triangle_count \
		single_source_shortest_path \
		breadth_first_search \
		page_rank \
		connected_components \
		betweenness_centrality

all: $(BINS)

undirected_triangle_count: tc_main.o graph.o tc.o graph_io.o graph_util.o
	$(CXX) $^ -o $@

breadth_first_search: bfs_main.o graph.o bfs.o graph_io.o graph_util.o
	$(CXX) $^ -o $@

single_source_shortest_path: sssp_main.o graph.o sssp.o graph_io.o graph_util.o
	$(CXX) $^ -o $@

page_rank: pr_main.o graph.o pr.o graph_io.o graph_util.o
	$(CXX) $^ -o $@

connected_components: cc_main.o graph.o cc.o graph_io.o
	$(CXX) $^ -o $@

betweenness_centrality: bc_main.o graph.o bc.o graph_io.o
	$(CXX) $^ -o $@

bfs_main.o: bfs_main.cpp bfs.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

tc_main.o: tc_main.cpp tc.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

sssp_main.o: sssp_main.cpp sssp.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

pr_main.o: pr_main.cpp pr.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

cc_main.o: cc_main.cpp cc.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

bc_main.o: bc_main.cpp bc.o graph_util.o graph_io.o graph.o
	$(CXX) $(CXXFLAGS) $<

gb.o: gb.cpp
	$(CXX) $(CXXFLAGS) $<

graph.o: graph.cpp graph.h
	$(CXX) $(CXXFLAGS) $<

bfs.o: bfs.cpp bfs.h graph.h
	$(CXX) $(CXXFLAGS) $<

sssp.o: sssp.cpp sssp.h graph.h
	$(CXX) $(CXXFLAGS) $<

pr.o: pr.cpp pr.h graph.h
	$(CXX) $(CXXFLAGS) $<

tc.o: tc.cpp tc.h graph.h
	$(CXX) $(CXXFLAGS) $<

cc.o: cc.cpp cc.h graph.h
	$(CXX) $(CXXFLAGS) $<

bc.o: bc.cpp bc.h graph.h
	$(CXX) $(CXXFLAGS) $<

graph_io.o: graph_io.cpp graph_io.h graph.h
	$(CXX) $(CXXFLAGS) $<

graph_util.o: graph_util.cpp graph_util.h graph.h
	$(CXX) $(CXXFLAGS) $<

clean:
	rm -rf $(BINS) *.o

