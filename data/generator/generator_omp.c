/* Copyright (C) 2009-2010 The Trustees of Indiana University.             */
/*                                                                         */
/* Use, modification and distribution is subject to the Boost Software     */
/* License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at */
/* http://www.boost.org/LICENSE_1_0.txt)                                   */
/*                                                                         */
/*  Authors: Jeremiah Willcock                                             */
/*           Andrew Lumsdaine                                              */

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif
#include <inttypes.h>
#include <stdio.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "make_graph.h"



void printError() {
  fprintf(stderr, "usage: <program> <# of vertices (log 2 base)> <average # of edges per vertex [optional: -e intNumber]> <output file [optional: -o outputName]> <seed [optional: -s intNumber]> <tsv type: 0-tsv; 1-binary tsv [optional: -f 0 / -f 1]>\n");
  exit(0);
}


int main(int argc, char* argv[]) {
  struct timeval currentTime;
  gettimeofday(&currentTime, NULL);
  int seed = currentTime.tv_sec ^ currentTime.tv_usec;
  seed ^= seed >> 12;
  seed ^= seed << 25;
  seed ^= seed >> 27;

  FILE *fout;

  if (argc < 2 || argc > 10) {
      printError();
  }

  // define all the variables
  int log_numverts;
  long int numEdges;
  double start, time_taken;
  int64_t nedges;
  packed_edge* result;
  int binary = 0; // set default to be not binary, normal tsv

  log_numverts = atoi(argv[1]); // In base 2
  numEdges = 16;  // default 16
  fout = stdout;  // default the stdout

  int opt;
  int position = 3;
    while ((opt = getopt(argc, argv, "eosf:")) != -1) {
        switch (opt) {
        case 'e':
            numEdges = atoi(argv[position]);
            position += 2;
            break;
        case 'o':
            fout = fopen(argv[position], "wb");
            if (fout == NULL) {
              fprintf(stderr, "%s -- ", argv[position]);
              perror("fopen for write failed");
              exit(0);
            }
            position += 2;
            break;
        case 's':
            seed = atoi(argv[position]);
            position += 2;
            break;
        case 'f':
            binary = atoi(argv[position]);
            if (binary != 0 && binary != 1) {
                printError();
            }
            position += 2;
            break;
        default: 
            printError();
        }
    }

  /* Start of graph generation timing */
  start = omp_get_wtime();

  make_graph(log_numverts, numEdges << log_numverts, seed, seed, &nedges, &result);

  time_taken = omp_get_wtime() - start;
  /* End of graph generation timing */

  fprintf(stderr, "finish generating the edges and start to write to the file\n");

  if (binary == 0) {
  // print to the file
    for (int i = 0; i < (numEdges << log_numverts); i++) {
      fprintf(fout, "%lu\t%lu\n", get_v0_from_edge(result + i), get_v1_from_edge(result + i));
    }
  } else {
    // need to print binary
    for (int i = 0; i < (numEdges << log_numverts); i++) {
      uint32_t from = get_v0_from_edge(result + i);
      uint32_t to = get_v1_from_edge(result + i);
      // add the check for not exceed the uint32_t max
      fwrite((const void*) & from,sizeof(uint32_t),1,fout);
      fwrite((const void*) & to,sizeof(uint32_t),1,fout);
    }
  }
  fclose(fout);

  /* End of graph generation timing */
  // fprintf(stderr, "%" PRIu64 " edge%s generated in %fs (%f Medges/s)\n", nedges, (nedges == 1 ? "" : "s"), time_taken, 1. * nedges / time_taken * 1.e-6);
  printf("%d\t%f seconds\n", log_numverts, time_taken);
  return 0;
}




