#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "graph_io.h"

void importTestGraph(char const* filename, Graph& out) {
	//TODO actually do file IO
	out.addNode(1);
    out.addEdge(1, 2, 1);
    out.addEdge(1, 3, 2);
    out.addEdge(1, 4, 3);
	
	out.addNode(2);
    out.addEdge(2, 3, 1);
    out.addEdge(2, 4, 2);

    out.addNode(3);
	
	out.addNode(4);
    out.addEdge(4, 5, 1);
	
	out.addNode(5);
}

void importTriangleTestGraph(char const* filename, Graph& out) {
    //TODO actually do file IO
    out.addNode(1);
    out.addNode(2);
    out.addNode(3);
    out.addNode(4);
    out.addNode(5);
    out.addNode(6);
    out.addNode(7);

    // 1-2-3
    out.addEdgeUndirected(1, 2, 1);
    out.addEdgeUndirected(1, 3, 1);
    out.addEdgeUndirected(3, 2, 1);

    // 3-4-5
    out.addEdgeUndirected(3, 4, 1);
    out.addEdgeUndirected(5, 4, 1);
    out.addEdgeUndirected(3, 5, 1);

    // red herrings
    out.addEdgeUndirected(1, 6, 1);
    out.addEdgeUndirected(4, 7, 1);
}

int getTwoInts(std::string str, int *firstInt, int *secondInt) {
    size_t i = 0;
    char *buf = new char[str.length() + 1];
    strcpy(buf, str.c_str());

    // skip leading whitespace
    while (i < str.length() && (str[i] == ' ' || str[i] == '\t')) {
        ++i;
    }

    if(i == str.length()) {
        // no first number
        delete[] buf;
        return -1;
    }

    char* num = buf + i;

    *firstInt = atoi(num);

    // skip over the first number
    while (i < str.length() && str[i] != ' ' && str[i] != '\t') {
        ++i;
    }
    // skip over the middle whitespace
    while (i < str.length() && (str[i] == ' ' || str[i] == '\t')) {
        ++i;
    }

    if (i == str.length()) {
        // no second number
        delete[] buf;
        return -1;
    }

    num = buf + i;

    *secondInt = atoi(num);

    delete[] buf;
    return 0;
}

int importTSVGraph(char const* filename, Graph& out, bool directed) {
    std::string line;
    std::ifstream infile(filename);
    int first, second, result;

    if (infile) {
        while (getline(infile, line)) {
            if (line[0] == '#') {
                // line is a comment
                std::cout << line << std::endl;
            } else {
                result = getTwoInts(line, &first, &second);
                if (result != 0) {
                    // read error
                    return -1;
                }

                if (directed) {
                    out.addEdge(first, second);
                } else {
                    out.addEdgeUndirected(first, second);
                }

            }

            line.clear();
        }
    } else {
        // file error
        return -1;
    }

    infile.close();
    return 0;
}
