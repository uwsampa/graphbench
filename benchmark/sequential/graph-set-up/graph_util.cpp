#include <iostream>
#include <cstdlib>
#include "graph_util.h"

/*
    Print the structure of the graph to the console, starting at the given node.
    Assumes a directed, acyclic graph.
*/
void printTree(Graph& graph, Node node, std::string tabbing) {
    std::map<Node, double> currentEdges;
    std::map<Node, double>::const_iterator it;

    graph.getEdges(node, &currentEdges);
    std::cout << tabbing << node.getLabel() <<std::endl;

    std::string nextTab = tabbing + std::string("	");
    for(it=currentEdges.begin(); it !=currentEdges.end(); ++it) {
        printTree(graph, it->first, nextTab);
    }
}

int parseNode(const char* str, Node &node) {
    int i;
    unsigned long ul;

    for(i = 0; str[i] != '\0'; ++i) {
        if(str[i] < '0' || str[i] > '9') {
            // error, non-numeric character
            return -1;
        }
    }

    // parse the unsigned long
    ul = strtoul (str, NULL, 0);

    Node newNode(ul);
    node = newNode;

    return 0;
}

