#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <set>
#include <map>
#include "graph.h"
#include "graph_io.h"
#include "pr.h"
#include "graph_util.h"

using std::cout;
using std::endl;

static void doPageRank (const char* graphFile) {
    Graph graph;
    timespec before, after;
    std::set<Triangle> triangles;
    //std::set<Triangle>::iterator it;

    importTSVGraph(graphFile, graph, false);

    cout << "Running undirected triangle count" << endl;

    // run triangle count and time it
    clock_gettime(CLOCK_MONOTONIC, &before);
    undirectedTriangleCount(graph, triangles);
    clock_gettime(CLOCK_MONOTONIC, &after);

    // print triangles
    /*
    for(it = triangles.begin(); it != triangles.end(); ++it) {
        cout << it->a.getLabel()
              << " "
              << it->b.getLabel()
              << " "
              << it->c.getLabel()
              << std::endl;
    }*/

    // construct the runtime
    time_t sec = after.tv_sec - before.tv_sec;
    long milli = (after.tv_nsec - before.tv_nsec) / 1000000;
    if (milli < 0) milli += 1000; // if after's nsec < before's nsec

    cout << "Runtime: "
          << sec
          << "."
          << milli
          << "s"
          << std::endl;

    cout << "Triangle count: "
          << triangles.size()
          << endl;

}

int main(int argc, const char **argv) {
    const char* graph_file = NULL;
    const char* damping_factor = NULL;
    float d;

    if (argc < 3) {
        std::cout << "Must specify which graph file to use "
                  << "(e.g. '-g graph.txt' or '--graph graph.txt')."
                  << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-g") == 0 || strcmp(argv[i],"--graph") == 0) {
            graph_file = argv[i + 1];
        }
    }
    for (int i = 1; i < argc-1; ++i) {
        if (strcmp(argv[i],"-d") == 0 || strcmp(argv[i],"--damping") == 0) {
            damping_factor = argv[i + 1];
        }
    }


    if (graph_file == NULL) {
        cout << "Must specify which graph to use."
             << "e.g. '-g graph.txt' or '--graph graph.txt'" << endl;
        return EXIT_FAILURE;
    }



    doTriangleCount(graph_file);

    return EXIT_SUCCESS;
}

