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
    cout << "usage: ./page_rank -g graph.txt -f <tsv|csv> -o <y|n> -d damping_factor" << endl;
    exit(1);
}

static void doPageRank (const Graph& graph, const float &dampingFactor, char print_output) {
    timespec before, after;
    std::map<Node, double> pr;
    cout << "doing PageRank" << endl;

    // run triangle count and time it
    clock_gettime(CLOCK_MONOTONIC, &before);
    pageRank(graph, dampingFactor, pr);
    clock_gettime(CLOCK_MONOTONIC, &after);

    // construct the runtime
    time_t sec = after.tv_sec - before.tv_sec;
    long milli = (after.tv_nsec - before.tv_nsec) / 1000000;
    if (milli < 0) { // if after's nsec < before's nsec
        milli += 1000;
        --sec;
    }

    if (print_output == 'y') {
        printPageRanks(pr);
    }

    //print the runtime results
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
    const char* damping_factor = NULL;
    const char* format = NULL;
    const char* print_output = NULL;
    
    float d;
    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, ":g:f:d:o")) != -1) {
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
            damping_factor = argv[position];
            position += 2;
            break;
            case 'o':
            print_output = argv[position];
            position += 2;
            break;
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use. "
        << "e.g. '-g graph.txt'" << endl;
        usage();
    }
    if (format == NULL) {
        cout << "Must specify the format of the graph input file. "
        << "e.g. '-f tsv' or '-f csv'" << endl;
        usage();
    }
    if (print_output == NULL) {
        cout << "Must specify whether to print output."
        << "e.g. '-o y' or '-o n'" << endl;
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
    // use the user supplised damping factor,
    // or default to 0.85
    if (damping_factor == NULL) {
        d = 0.85;
        } else {
        d = atof(damping_factor);
    }

    doPageRank(graph, d, *print_output);
    
    return EXIT_SUCCESS;
}