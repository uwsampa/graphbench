#include "gm_graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <assert.h>
#include <sys/time.h>
#include <inttypes.h>  // for PRId64

#include "graph_gen.h"

//  CREATE RMAT  or random file and dump
int main(int argc, char** argv) {

    //-----------------------------
    // create RMAT graph
    //-----------------------------
    if (argc < 4) {
        printf("%s <out filename> <inputfile> <0~1>\n", argv[0]);
        exit(0);
    }

    int gtype = atoi(argv[3]);
    if (gtype != 0 && gtype != 1) {
        printf("%s <out filename> <inputfile> <0~1>\n", argv[0]);
        exit(0);
    }
    
    gm_graph* g;
    struct timeval T1, T2;
    gettimeofday(&T1, NULL);

    // 0 is undirected graph
    // 1 is directed graph
    if (gtype == 1) {
        g = create_Graph(argv[2], true);
        printf("create directed graph\n");
    } else {
        g = create_Graph(argv[2], false);
        printf("create undirected graph\n");
    }   

    gettimeofday(&T2, NULL);
    printf("creation time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);

    printf("saving to file = %s\n", argv[1]);
    fflush (stdout);
    gettimeofday(&T1, NULL);
    g->store_binary(argv[1]);
    gettimeofday(&T2, NULL);
    printf("storing time (ms) = %lf\n", ((T2.tv_sec) - (T1.tv_sec)) * 1000 + (T2.tv_usec - T1.tv_usec) * 0.001);

    delete g;
    return EXIT_SUCCESS;
}

