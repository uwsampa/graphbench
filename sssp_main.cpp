#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include "graph.h"
#include "graph_io.h"
#include "sssp.h"
#include "graph_util.h"

using std::cout;
using std::endl;

static void doShortestPath (const char* graphFile, Node &start) {
    Graph graph;
    timespec before, after;
    std::map<Node, double> costs;
    std::map<Node, Node> prev;

    // TODO use real graph & start
    importTestGraph(graphFile, graph);

    Node node(1);

    std::cout << "Running single-source shortest path" << std::endl;

    clock_gettime(CLOCK_MONOTONIC, &before);
    singleSourceShortestPath(node, graph, costs, prev);
    clock_gettime(CLOCK_MONOTONIC, &after);

    std::cout << "Runtime: "
              << after.tv_nsec - before.tv_nsec
              << "ns"
              << std::endl;
}

int main(int argc, const char **argv) {
    Node startNode;
    const char* graph_file = NULL;
    const char* start = NULL;

    if (argc < 5) {
        cout << "Must specify which graph file to use (e.g. '-g graph.txt' or '--graph graph.txt') "
             << "and which node to start from (e.g. '-s 51' or '--start 51')." << endl;
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-g") == 0 || strcmp(argv[i],"--graph") == 0) {
            graph_file = argv[i + 1];
        } else if (strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--start") == 0){
            start = argv[i + 1];
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
             << "e.g. '-g graph.txt' or '--graph graph.txt'" << endl;
        return EXIT_FAILURE;
    }

    if (start == NULL) {
        cout << "Must specify which node to start from."
             << "e.g. '-s 51' or '--start 51'" << endl;
        return EXIT_FAILURE;
    }

    if(parseNode(start, startNode) < 0) {
        cout << "Error parsing start node: "
             << start
             << endl;
        return EXIT_FAILURE;
    }

    doShortestPath(graph_file, startNode);

    return EXIT_SUCCESS;
}

