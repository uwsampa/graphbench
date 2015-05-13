#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <vector>
#include "graph.h"
#include "graph_io.h"
#include "cc.h"
#include <getopt.h>

using std::string;
using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./connected_components -g graph.txt -f <tsv|csv> -o <y|n>" << endl;
    exit(1);
}

void printComponents(const vector<set<Node> > &components) {
    vector<set<Node> >::const_iterator comp_it;
    set<Node>::const_iterator node_it;
    int componentCount = 0;
    for (comp_it = components.begin(); comp_it != components.end(); ++comp_it) {
        cout << "Component " << ++componentCount << ":" << endl;
        for (node_it = comp_it->begin(); node_it != comp_it->end(); ++node_it) {
            cout << node_it->getLabel() << endl;
        }
    }
}

static void doConnectedComponents (const Graph &graph, char print_output) {
    vector<set<Node> > components;
    timespec before, after;
    cout << "Running connected components" << endl;

    clock_gettime(CLOCK_MONOTONIC, &before);
    connectedComponents(graph, components);
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
        cout << "Number of components: " << components.size() << endl;
        printComponents(components);
    }
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

    doConnectedComponents(graph, *print_output);

    return EXIT_SUCCESS;
}