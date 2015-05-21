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
#include "graph_util.h"
#include <getopt.h>

using std::string;
using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./connected_components -g graph.txt <-f csv [optional, default to tsv]>  <-o [optional, default to not print the result>" << endl;
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

static void doConnectedComponents (const Graph &graph, bool print_output) {
    vector<set<Node> > components;

    double before, after;
    cout << "Running connected components" << endl;

    before = getRealTime();
    connectedComponents(graph, components);
    after = getRealTime();

    // construct the runtime
    double sec = after - before;

    //print the runtime results
    cout << "Runtime: "
    << sec
    << "s"
    << endl;

    if (print_output) {
        cout << "Number of components: " << components.size() << endl;
        printComponents(components);
    }
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = "tsv";
    bool print_output = false;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, "g:f:o")) != -1) {
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

    doConnectedComponents(graph, print_output);

    return EXIT_SUCCESS;
}