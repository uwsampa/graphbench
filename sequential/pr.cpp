#include <map>
#include <iostream>
#include <cmath>
#include "pr.h"
#include "graph.h"

using std::cout;
using std::endl;

#define TOLERANCE 0.001

/*
 * Perform one iteration of PageRank, using PR as the initial PagrRank values
 * for each vertex and outputting the updated PageRanks to newPR
 */
void step(const Graph &graph, const float dampingFactor,
          std::map<Node, double> &PR, std::map<Node, double> &newPR) {
    std::map<Node, double> edges;
    std::map<Node, double>::iterator pr_it;
    std::map<Node, double>::iterator edge_it;
    uint32_t numOutbound;
    double randomSurferPR = 0.0; // the page rank contributed by random surfers
    uint32_t n = graph.size();

    // initialize the new PR values
    newPR.clear();
    for(pr_it = PR.begin(); pr_it != PR.end(); ++pr_it) {
        newPR[pr_it->first] = 0.0;
    }

    // for all nodes in the graph...
    for(pr_it = PR.begin(); pr_it != PR.end(); ++pr_it) {
        // retrieve the edges leading from the current node
        graph.getEdges(pr_it->first, &edges);

        if(edges.empty()) {
            // this is a dangling page, add its contribution to the
            // random surfer PR pool
            randomSurferPR += pr_it->second / n;
        } else {
            // this node has links leading from it

            numOutbound = edges.size();

            // for all of the edges leading from the current node...
            for(edge_it = edges.begin(); edge_it != edges.end(); ++edge_it) {
                // add the PR associated with a user browsing randomly to one of the links
                newPR[edge_it->first] += pr_it->second / numOutbound;
            }
        }
    }

    // for all nodes in the graph...
    for(pr_it = newPR.begin(); pr_it != newPR.end(); ++pr_it) {
        // set the new pageRank equal the weighted sum of incoming links, random surfers from dangling pages,
        // and teleporting surfers
//        pr_it->second = (dampingFactor * (pr_it->second + randomSurferPR)) + ((1.0 - dampingFactor) / n); // for 1.0-sum PR
        pr_it->second = (dampingFactor * (pr_it->second + randomSurferPR)) + (1.0 - dampingFactor); // n-sum
        //pr_it->second = (dampingFactor * (pr_it->second)) + (1.0 - dampingFactor); // n-sum
    }
}

/*
 * Calculates the L1-norm of the old and new PR vectors
 */
double getPRDiff (std::map<Node, double> oldPR, std::map<Node, double> newPR) {
    std::map<Node, double>::const_iterator it;
    double diff = 0.0;

    for(it = oldPR.begin(); it != oldPR.end(); ++it) {
        diff += fabs(it->second - newPR[it->first]);
    }

    return diff;
}

int pageRank(const Graph &in, const float dampingFactor, std::map<Node, double> &out) {
    double change;
//    double sum;
//    double normalization;
    std::map<Node, double> newPR;
    std::map<Node, std::map<Node, double> >::const_iterator web_it;
    std::map<Node, double>::iterator pr_it;
//    uint32_t webSize = in.size();

    // initialize the PR of each node to 1 / n where n is the number of nodes
    for(web_it = in.begin(); web_it != in.end(); ++web_it) {
        out[web_it->first] = 1.0; // for N-sum PR
        //out[web_it->first] = 1.0 / webSize; //for 1.0-sum PR
    }

    do {
        // 1 step of iterative PR
        step(in, dampingFactor, out, newPR);

        // find the L1-norm of the two iterations
        change = getPRDiff(out, newPR);

        cout << "Diff: " << change << endl;

        /*
        sum = 0.0;
        for(pr_it = newPR.begin(); pr_it != newPR.end(); ++pr_it) {
            sum += pr_it->second;
        }
        //normalization = sum; // 1.0-sum PR
        normalization = sum / webSize; // N-sum PR*/

        // set the PR values for the next iteration, normalizing the sum of PRs
        for(pr_it = out.begin(); pr_it != out.end(); ++pr_it) {
            //pr_it->second = newPR[pr_it->first] / normalization;
            pr_it->second = newPR[pr_it->first];
        }

        // iterate until reasonably close to convergence
    } while (change > TOLERANCE);

    return 0;
}

void printPageRanks(const std::map<Node, double> &in) {
    std::map<Node, double>::const_iterator it;
    double sum = 0.0;

    cout << "Page ranks:" << endl;

    for(it = in.begin(); it != in.end(); ++it) {
        sum += it->second;
        cout << it->first.getLabel() << " " << it->second << endl;
    }

    cout << "PR sum: " << sum << endl;
}
