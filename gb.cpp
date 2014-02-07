#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include "graph.h"
#include "graph_io.h"
#include "bfs.h"
#include "sp.h"
#include "tc.h"
#include "graph_util.h"

static void doBFS (const char* graphFile) {
    Graph graph, bfsResult;
    timespec before, after;
    importTestGraph(graphFile, graph);

    Node node(1);
    std::cout << "original graph:" <<std::endl;
    printTree(graph, node, std::string(""));

    clock_gettime(CLOCK_MONOTONIC, &before);
    bfs(node, graph, bfsResult);
    clock_gettime(CLOCK_MONOTONIC, &after);

    std::cout << "Runtime: "
              << after.tv_nsec - before.tv_nsec
              << "ns"
              << std::endl;

    std::cout << "bfs result:" <<std::endl;
    printTree(bfsResult, node, std::string(""));
}

static void doShortestPath (const char* graphFile) {
    Graph graph;
    timespec before, after;
    std::map<Node, double> costs;
    std::map<Node, Node> prev;

    importTestGraph(graphFile, graph);

    Node node(1);

    std::cout << "Running single-source shortest path" << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &before);
    shortestPath(node, graph, costs, prev);
    clock_gettime(CLOCK_MONOTONIC, &after);

    std::cout << "Runtime: "
              << after.tv_nsec - before.tv_nsec
              << "ns"
              << std::endl;
}

static void doTriangleCount (const char* graphFile) {
    Graph graph;
    timespec before, after;
    std::set<Triangle> triangles;
    std::set<Triangle>::iterator it;

    importTSVGraph(graphFile, graph, false);

    std::cout << "Running triangle count" << std::endl;

    // run triangle count and time it
    clock_gettime(CLOCK_MONOTONIC, &before);
    undirectedTriangleCount(graph, triangles);
    clock_gettime(CLOCK_MONOTONIC, &after);

    // print triangles
    /*
    for(it = triangles.begin(); it != triangles.end(); ++it) {
        std::cout << it->a.getLabel()
                  << " "
                  << it->b.getLabel()
                  << " "
                  << it->c.getLabel()
                  << std::endl;
    }*/

    // construct the runtime
    time_t sec = after.tv_sec - before.tv_sec;
    long milli = (after.tv_nsec - before.tv_nsec) / 1000000;
    if (milli < 0) milli += 1000; // if after's nsec < before's nsec

    std::cout << "Runtime: "
              << sec
              << "."
              << milli
              << "s"
              << std::endl;

    std::cout << "Triangle count: "
              << triangles.size()
              << std::endl;

}

int main(int argc, const char **argv) {
    const char* graph_file = NULL;
    const char* graph_kern = NULL;

    if (argc < 5) {
        std::cout << "Must specify which benchmark to perform (e.g. '-b bfs') "
                  << "and which graph file to use (e.g. '-g graph.csv')." << std::endl;
        return EXIT_FAILURE;
    }
	
    for (int i = 1; i < argc -1; ++i) {
        if (strcmp(argv[i],"-g") == 0) {
            graph_file = argv[i + 1];
        } else if (strcmp(argv[i],"-b") == 0){
            graph_kern = argv[i + 1];
        }
    }

    if (graph_file == NULL) {
        std::cout << "Must specify which graph to use."
                  << "e.g. '-g graph.csv'" << std::endl;
        return EXIT_FAILURE;
    }

    if (graph_kern == NULL) {
        std::cout << "Must specify which kernel to execute."
                  << "e.g. '-b bfs'" << std::endl;
        return EXIT_FAILURE;
    } else if (strcmp(graph_kern, "bfs") == 0) {
        doBFS(graph_file);
    } else if (strcmp(graph_kern, "sp") == 0) {
        doShortestPath(graph_file);
    } else if (strcmp(graph_kern, "tc") == 0) {
        doTriangleCount(graph_file);
    } else {
        std::cout << "Unknown benchmark: " << graph_kern << std::endl;
        std::cout << "Valid benchmarks: bfs, sp, tc" << std::endl;
        return EXIT_FAILURE;
    }
	
	return EXIT_SUCCESS;
}

