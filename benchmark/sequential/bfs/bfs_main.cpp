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
#include <getopt.h>

using std::string;
using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./breadth_first_search -g graph.txt -f <tsv|csv> -o <y|n> -s startnode" << endl;
    exit(1);
}

static void doBFS (const Graph& graph, Node &start, char print_output) {
    Graph bfsResult;
    timespec before, after;

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

    if (print_output == 'y') {
        cout << "bfs result:" << endl;
        printTree(bfsResult, start, string(""));
    }
}

int main(int argc, const char **argv) {
    Graph graph;
    Node startNode;

    const char* graph_file = NULL;
    const char* start = NULL;
    const char* format = NULL;
    const char* print_output = NULL;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, ":g:s:f:o")) != -1) {
        switch (opt) {
            case 'g':
            graph_file = argv[position];
            position += 2;
            break;
            case 's':
            start = argv[position];
            position += 2;
            break;
            case 'f':
            format = argv[position];
            position += 2;
            break;
            case 'o':
            print_output = argv[position];
            position += 2;
            break;
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
        << "e.g. '-g graph.txt'" << endl;
        usage();
    }
    if (format == NULL) {
        cout << "Must specify the format of the graph input file."
        << "e.g. '-f tsv' or '-f csv'" << endl;
        usage();
    }
    if (print_output == NULL) {
        cout << "Must specify whether to print output."
        << "e.g. '-o y' or '-o n'" << endl;
        usage();
    }
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, true);
        } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, true);
        } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        usage();
    }
    if (start == NULL) {
        cout << "Must specify which node to start from."
        << "e.g. '-s 51'" << endl;
        usage();
    }
    if(parseNode(start, startNode) < 0) {
        cout << "Error parsing start node: "
        << start
        << endl;
        return EXIT_FAILURE;
    }

    doBFS(graph, startNode, *print_output);

    return EXIT_SUCCESS;
}