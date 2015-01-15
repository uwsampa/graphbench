#include <stdlib.h>
#include <set>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <cstdlib>
#include <unistd.h>
#include <cmath>
#include <string>
#include <cstdio>
#include <fcntl.h>
#include <sstream>
#include <fstream>
#include <set>

#include "graph_gen.h"

gm_graph* create_Graph(char* filename, bool directed) {

    gm_graph* g = new gm_graph();

    std::set<int> nodes;
    std::string line;
    int max = 0;
    {
        std::ifstream file(filename);
        while(std::getline(file, line)) {
            std::istringstream iss(line);
            int from, to;
            if (!(iss >> from >> to)) {
                break;
            }
            nodes.insert(from);
            nodes.insert(to);
            if (max < from)
                max = from;
            if (max < to)
                max = to;
        }

        for (int i = 0; i < max + 1; i++) {
            g->add_node();
        }
        printf("number of nodes added %d\n", max + 1);
    }

    {
        std::ifstream file2(filename);
        while(std::getline(file2, line)) {
            std::istringstream iss(line);
            node_t from, to;
            if (!(iss >> from >> to))
                break;
            if (!g->has_edge(from, to))
              g->add_edge(from, to);
            if (!directed && !g->has_edge(to, from)){
              g->add_edge(to, from);
        }
    }
    g->freeze();
    return g;
}
}
