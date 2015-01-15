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

using std::cout;
using std::endl;

static void doPageRank (const Graph& graph, const float &dampingFactor) {
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

    // print the PR results
    printPageRanks(pr);
    //cout << "printing page ranks disabled" << endl;

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
    float d;

    if (argc < 5) {
        cout  << "Must specify which graph file to use "
              << "(e.g. '-g graph.txt' or '--graph graph.txt')."
              << endl
              << "as well as the file's format "
              << "(e.g. '-f tsv' or '--format csv')"
              << endl
              << "Damping factor may optionally be specified with -d or --damping "
              << "(e.g. '-d 0.75'). Default value: 0.85"
              << endl;
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-g") == 0 || strcmp(argv[i],"--graph") == 0) {
            graph_file = argv[i + 1];
        } else if (strcmp(argv[i],"-f") == 0 || strcmp(argv[i],"--format") == 0) {
            format = argv[i + 1];
        } else if (strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"--damping") == 0) {
            damping_factor = argv[i + 1];
        }
    }

    if (graph_file == NULL) {
        cout << "Must specify which graph to use. "
             << "e.g. '-g graph.txt' or '--graph graph.txt'" << endl;
        return EXIT_FAILURE;
    }

    if (format == NULL) {
        cout << "Must specify the format of the graph input file. "
             << "e.g. '-f tsv' or '--format csv'" << endl;
        return EXIT_FAILURE;
    }

    // import the graph in the specified format
    if (strcmp(format, "tsv") == 0) {
        importTSVGraph(graph_file, graph, true);
    } else if (strcmp(format, "csv") == 0) {
        importCSVGraph(graph_file, graph, true);
    } else {
        // the specified format does not match any supported format
        cout << "Unknown graph file format: " << format << endl;
        return EXIT_FAILURE;
    }

    // use the user supplised damping factor,
    // or default to 0.85
    if (damping_factor == NULL) {
        d = 0.85;
    } else {
        d = atof(damping_factor);
    }

    doPageRank(graph, d);

    return EXIT_SUCCESS;
}

