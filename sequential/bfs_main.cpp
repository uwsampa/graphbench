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
#include "graph_util.h"

using std::string;
using std::cout;
using std::endl;

static void doBFS (const char* graphFile, Node &start) {
    Graph graph, bfsResult;
    timespec before, after;

    importTSVGraph(graphFile, graph, true);

    cout << "original graph:" << endl;
    printTree(graph, start, string(""));

    clock_gettime(CLOCK_MONOTONIC, &before);
    bfs(start, graph, bfsResult);
    clock_gettime(CLOCK_MONOTONIC, &after);

    cout << "Runtime: "
              << after.tv_nsec - before.tv_nsec
              << "ns"
              << endl;

    cout << "bfs result:" << endl;
    printTree(bfsResult, start, string(""));
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

    doBFS(graph_file, startNode);

    return EXIT_SUCCESS;
}

