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
#include "pr.h"
#include "graph_util.h"
#include <getopt.h>

using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./page_rank -g graph.txt -g graph.txt <-d damping_factor [optional, default to 0.85]> <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>" << endl;
    exit(1);
}

static void doPageRank (const Graph& graph, const float &dampingFactor, bool print_output) {
    double before, after;
    std::map<Node, double> pr;
    cout << "doing PageRank" << endl;

    // run triangle count and time it
    before = getRealTime();
    pageRank(graph, dampingFactor, pr);
    after = getRealTime();

    // construct the runtime
    double sec = after - before;

    if (print_output) {
        printPageRanks(pr);
    }

    //print the runtime results
    cout << "Runtime: "
    << sec
    << "s"
    << endl;
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = "tsv";
    bool print_output = false;
    
    float d = 0.85;
    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, "g:f:d:o")) != -1) {
        switch (opt) {
        case 'g':
            graph_file = argv[position];
            position += 2;
            break;
        case 'f':
            format = argv[position];
            position += 2;
            break;
        case 'd':
            d = atof(argv[position]);
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
        cout << "Must specify which graph to use. "
        << "e.g. '-g graph.txt'" << endl;
        usage();
    }
    // import the graph in the specified format
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, true);
        } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, true);
        } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        usage();
    }

    doPageRank(graph, d, print_output);
    
    return EXIT_SUCCESS;
}