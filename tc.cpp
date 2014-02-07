#include "tc.h"

int undirectedTriangleCount(const Graph &in, std::set<Triangle> &out) {
    std::map<Node,std::map<Node, double> >::const_iterator a_it;
    std::map<Node, double> a_edges;
    std::map<Node, double>::const_iterator a_edge_it;
    std::map<Node, double> b_edges;
    std::map<Node, double>::const_iterator b_edge_it;

    Node a, b, c, first, second, third;

    // clear the return set
    out.clear();

    // for every node a in the graph...
    for(a_it = in.begin(); a_it != in.end(); ++a_it) {
        a = a_it->first;
        a_edges = a_it->second;

        // for every edge a-b
        for(a_edge_it = a_edges.begin();
            a_edge_it != a_edges.end();
            ++a_edge_it) {

            b = a_edge_it->first;

            in.getEdges(a_edge_it->first, &b_edges);

            // for every edge b-c
            for(b_edge_it = b_edges.begin();
                b_edge_it != b_edges.end();
                ++b_edge_it) {
                c = b_edge_it->first;

                // check to see if there is an edge a-c
                if (a != b && a != c && b != c && in.edgeExists(a, c)) {
                    first = a;
                    second = b;
                    third = c;

                    // sort the verticies
                    if(second < first) {
                        Node temp = first;
                        first = second;
                        second = temp;
                    }

                    if(third < second) {
                        Node temp = second;
                        second = third;
                        third = temp;
                    }

                    if(second < first) {
                        Node temp = first;
                        first = second;
                        second = temp;
                    }

                    // insert the discovered trangle into the output set
                    Triangle newTri(first, second, third);
                    out.insert(newTri);
                }
            }
        }
    }

    return 1;
}
