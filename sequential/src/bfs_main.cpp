#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include "graph.h"
#include "graph_io.h"
#include "bfs.h"
#include "graph_util.h"

using std::string;
using std::cout;
using std::endl;

static void doBFS (const Graph& graph, Node &start) {
    Graph bfsResult;
    timespec before, after;

//    cout << "original graph:" << endl;
//    printTree(graph, start, string(""));

    clock_gettime(CLOCK_MONOTONIC, &before);
    bfs(start, graph, bfsResult);
    clock_gettime(CLOCK_MONOTONIC, &after);

    // construct the runtime
    time_t sec = after.tv_sec - before.tv_sec;
    long milli = (after.tv_nsec - before.tv_nsec) / 1000000;
    if (milli < 0) { // if after's nsec < before's nsec
        milli += 1000;
        --sec;
    }

    //print the runtime results
    cout << "Runtime: "
         << sec
         << "."
         << std::setw(3) << std::setfill('0') << milli
         << "s"
         << endl;

//    cout << "bfs result:" << endl;
//    printTree(bfsResult, start, string(""));
}

int main(int argc, const char **argv) {
    Graph graph;
    Node startNode;
    const char* graph_file = NULL;
    const char* start = NULL;
    const char* format = NULL;

    if (argc < 7) {
        cout << "Must specify which graph file to use (e.g. '-g graph.txt' or '--graph graph.txt'), " << endl
             << "which format the graph is stored in (e.g. '-f tsv' or '--format tsv'), " << endl
             << "and which node to start from (e.g. '-s 51' or '--start 51'), " << endl;

        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-g") == 0 || strcmp(argv[i],"--graph") == 0) {
            graph_file = argv[i + 1];
        } else if (strcmp(argv[i],"-s") == 0 || strcmp(argv[i],"--start") == 0){
            start = argv[i + 1];
        } else if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--format") == 0) {
            format = argv[i + 1];
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
             << "e.g. '-g graph.txt' or '--graph graph.txt'" << endl;
        return EXIT_FAILURE;
    }

    if (format == NULL) {
        cout << "Must specify the format of the graph input file."
             << "e.g. '-f tsv' or '--format csv'" << endl;
        return EXIT_FAILURE;
    }

    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, true);
    } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, true);
    } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
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

    doBFS(graph, startNode);

    return EXIT_SUCCESS;
}

