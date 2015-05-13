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
#include "bc.h"
#include "graph_util.h"
#include <getopt.h>

using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./betweenness_centrality -g graph.txt -f <tsv|csv> -o <y|n>" << endl;
    exit(1);
}

static void doBetweennessCentrality (const Graph &graph, char print_output) {
    timespec before, after;
    std::map<Node, double> centrality;
    cout << "Running unweighted betweenness centrality" << endl;

    clock_gettime(CLOCK_MONOTONIC, &before);
    unweightedBetweennessCentrality(graph, centrality);
    clock_gettime(CLOCK_MONOTONIC, &after);

    // print the output
    if (print_output == 'y') {
        typedef std::map<Node, double>::iterator it_type;
        for (it_type iterator = centrality.begin(); iterator != centrality.end(); ++iterator) {
            cout << iterator->first.getLabel()
            << "->" << iterator->second << endl;
        }
    }

    // construct the runtime
    time_t sec = after.tv_sec - before.tv_sec;
    long milli = (after.tv_nsec - before.tv_nsec) / 1000000;
    if (milli < 0) { // if after's nsec < before's nsec
        milli += 1000;
        --sec;
    }

    cout << "Runtime: "
    << sec
    << "."
    << std::setw(3) << std::setfill('0') << milli
    << "s"
    << endl;
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = NULL;
    const char* print_output = NULL;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, ":g:f:o")) != -1) {
        switch (opt) {
            case 'g':
            graph_file = argv[position];
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

    if (format == NULL) {
        cout << "Must specify the format of the graph input file. "
        << "e.g. '-f tsv' or '-f csv'" << endl;
        usage();
    }
    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
        << "e.g. '-g graph.txt'" << endl;
        usage();
    }
    if (print_output == NULL) {
        cout << "Must specify whether to print output."
        << "e.g. '-o y' or '-o n'" << endl;
        usage();
    }
    // import the graph in the specified format
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, false);
        } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, false);
        } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        usage();
    }

    doBetweennessCentrality(graph, *print_output);
    
    return EXIT_SUCCESS;
}