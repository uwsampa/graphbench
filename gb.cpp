#include <iostream>
#include <cstdlib>
#include <string>
#include <set>
#include <ctime>
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

int main(int argc, const char **argv) {
	Graph graph, bfsResult;
	timespec before, after;
	
	importGraph(argv[1], graph);
	
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
	
	return EXIT_SUCCESS;
}

