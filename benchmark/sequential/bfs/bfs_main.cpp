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
    cout << "usage: ./breadth_first_search -g graph.txt -s startnode <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>" << endl;
    exit(1);
}

static void doBFS (const Graph& graph, Node &start, char print_output) {
    Graph bfsResult;
    double before, after;

    before = getRealTime();
    bfs(start, graph, bfsResult);
    after = getRealTime();

    // construct the runtime
    double sec = after - before;

    //print the runtime results
    cout << "Runtime: "
    << sec
    << "s"
    << endl;

    if (print_output) {
        cout << "bfs result:" << endl;
        printTree(bfsResult, start, string(""));
    }
}

int main(int argc, const char **argv) {
    Graph graph;
    Node startNode;

    const char* graph_file = NULL;
    const char* start = NULL;
    const char* format = "tsv";
    double print_output = false;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, "g:s:f:o")) != -1) {
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
            print_output = true;
            position += 1;
            break;
        default:
            usage();
            break;
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
        << "e.g. '-g graph.txt'" << endl;
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

    doBFS(graph, startNode, print_output);

    return EXIT_SUCCESS;
}