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
#include <sys/time.h>
#include <time.h>

#include "make_graph.h"

inline double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1.e-6;
}

int main(int argc, char* argv[]) {
  FILE *fout;

  // Take the filenames from command line arguments
  if (argc != 3 && argc != 4) {
    fprintf(stderr, "usage: <program> <# of vertices (log 2 base)> <average # of edges per vertex> [<outfile>]\n");
    exit(0);
  }

  // define all the variables
  int log_numverts;
  long int numEdges;
  double start, time_taken;
  int64_t nedges;
  packed_edge* result;

  log_numverts = atoi(argv[1]); // In base 2
  numEdges = atoi(argv[2]);

  if (argc == 3) {
    fout = stdout;
  } else {
    // Open the output file
    fout = fopen(argv[3], "wb");
    if (fout == NULL) {
      fprintf(stderr, "%s -- ", argv[2]);
      perror("fopen for write failed");
      exit(0);
    }
  }

  //Start of graph generation timing
  start = get_time();
  make_graph(log_numverts, numEdges << log_numverts, 1, 2, &nedges, &result);
  time_taken = get_time() - start;

  // print to the file
  for (int i = 0; i < (numEdges << log_numverts); i++)
    fprintf(fout, "%lu\t%lu\n", get_v0_from_edge(result + i), get_v1_from_edge(result + i));
  fclose(fout);
  
  /* End of graph generation timing */
  fprintf(stderr, "%" PRIu64 " edge%s generated in %fs (%f Medges/s)\n", nedges, (nedges == 1 ? "" : "s"), time_taken, 1. * nedges / time_taken * 1.e-6);
  free(result);
  return 0;
}
