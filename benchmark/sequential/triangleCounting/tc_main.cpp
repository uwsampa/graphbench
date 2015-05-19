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
#include "tc.h"
#include "graph_util.h"
#include <getopt.h>

using std::cout;
using std::endl;

void usage() {
    cout << "usage: ./undirected_triangle_count -g graph.txt -f <tsv|csv> -o <y|n>" << endl;
    exit(1);
}

static void doTriangleCount (const Graph &graph, char print_output) {
    double before, after;
    std::set<Triangle> triangles;
    std::set<Triangle>::iterator it;
    cout << "Running undirected triangle count" << endl;

    // run triangle count and time it
    before = getRealTime();
    undirectedTriangleCount(graph, triangles);
    after = getRealTime();

    // print triangles
    if (print_output == 'y') {
        for(it = triangles.begin(); it != triangles.end(); ++it) {
            cout << it->a.getLabel()
            << " "
            << it->b.getLabel()
            << " "
            << it->c.getLabel()
            << std::endl;
        }
    }

    // construct the runtime
    double sec = after - before;

    cout << "Runtime: "
    << sec
    << "s"
    << endl;
    cout << "Triangle count: "
    << triangles.size()
    << endl;
}

int main(int argc, const char **argv) {
    Graph graph;
    const char* graph_file = NULL;
    const char* format = NULL;
    const char* print_output = NULL;

    int opt;
    int position = 2;

    while ((opt = getopt(argc, (char* const*)argv, "g:f:o:")) != -1) {
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
        default:
            usage();
            break;
        }
    }

    if (format == NULL) {
        cout << "Must specify the format of the graph input file. "
        << "e.g. '-f tsv' or '--format csv'" << endl;
        usage();
    }
    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
        << "e.g. '-g graph.txt' or '--graph graph.txt'" << endl;
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

    doTriangleCount(graph, *print_output);

    return EXIT_SUCCESS;
}
