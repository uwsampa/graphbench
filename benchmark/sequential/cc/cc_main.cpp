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

using std::string;
using std::cout;
using std::endl;

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

static void doConnectedComponents (const Graph &graph) {
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

    cout << "Printing components disabled" << endl;
    //cout << "Number of components: " << components.size() << endl;
    //printComponents(components);
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = NULL;

    if (argc < 5) {
        cout << "Must specify which graph file to use (e.g. '-g graph.txt' or '--graph graph.txt'), " << endl
             << "and which format the graph is stored in (e.g. '-f tsv' or '--format tsv'), " << endl;

        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-g") == 0 || strcmp(argv[i],"--graph") == 0) {
            graph_file = argv[i + 1];
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

    // import the graph in the specified format
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, false);
    } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, false);
    } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        return EXIT_FAILURE;
    }

    doConnectedComponents(graph);

    return EXIT_SUCCESS;
}

