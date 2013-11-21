#include <cstring>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>
#include <set>
#include "graph.h"
#include "graph_io.h"
#include "bfs.h"

/*
	Print the structure of the graph to the console, starting at the given node.
	Assumes a directed, acyclic graph.
*/
void printTree(Graph& graph, Node node, std::string tabbing) {
	std::set<Node> currentEdges;
	std::set<Node>::const_iterator it;
	
	graph.getEdges(node, &currentEdges);
	std::cout << tabbing << node.getLabel() <<std::endl;
	
	std::string nextTab = tabbing + std::string("	");
	for(it=currentEdges.begin(); it !=currentEdges.end(); ++it) {
		printTree(graph, *it, nextTab);
	}
}

void doBFS (const char* graphFile) {
    Graph graph, bfsResult;
    timespec before, after;
    importGraph(graphFile, graph);

    Node node(1);
    std::cout << "original graph:" <<std::endl;
    printTree(graph, node, std::string(""));

    clock_gettime(CLOCK_MONOTONIC, &before);
    bfs(node, graph, bfsResult);
    clock_gettime(CLOCK_MONOTONIC, &after);

    std::cout << "Runtime: "
              << after.tv_nsec - before.tv_nsec
              << "ns"
              << std::endl;

    std::cout << "bfs result:" <<std::endl;
    printTree(bfsResult, node, std::string(""));
}

void doShortestPath (const char* graphFile) {
    std::cout << "Unimplemented." << std::endl;
}

int main(int argc, const char **argv) {
    const char* graph_file = NULL;
    const char* graph_kern = NULL;

    if (argc < 5) {
        std::cout << "Must specify which benchmark to perform (e.g. '-b bfs') "
                  << "and which graph file to use (e.g. '-g graph.csv')." << std::endl;
        return EXIT_FAILURE;
    }
	
    for (int i = 1; i < argc -1; ++i) {
        if (strcmp(argv[i],"-g") == 0) {
            graph_file = argv[i + 1];
        } else if (strcmp(argv[i],"-b") == 0){
            graph_kern = argv[i + 1];
        }
    }

    if (graph_file == NULL) {
        std::cout << "Must specify which graph to use."
                  << "e.g. '-g graph.csv'" << std::endl;
        return EXIT_FAILURE;
    }

    if (graph_kern == NULL) {
        std::cout << "Must specify which kernel to execute."
                  << "e.g. '-b bfs'" << std::endl;
        return EXIT_FAILURE;
    } else if (strcmp(graph_kern, "bfs") == 0) {
        doBFS(graph_file);
    } else if (strcmp(graph_kern, "sp") == 0) {
        doShortestPath(graph_file);
    } else {
        std::cout << "Unknown benchmark: " << graph_kern << std::endl;
        return EXIT_FAILURE;
    }
	
	return EXIT_SUCCESS;
}

