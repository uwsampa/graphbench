/* Copyright (C) 2009-2010 The Trustees of Indiana University.             */
/*                                                                         */
/* Use, modification and distribution is subject to the Boost Software     */
/* License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at */
/* http://www.boost.org/LICENSE_1_0.txt)                                   */
/*                                                                         */
/*  Authors: Jeremiah Willcock                                             */
/*           Andrew Lumsdaine                                              */
/*  Revised                                                                */

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
#include <unistd.h>

#include "make_graph.h"

inline double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1.e-6;
}

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
  double start, time_taken, start_write, time_taken_write;
  int64_t nedges;
  packed_edge* result;
  int binary = 0; // set default to be not binary, normal tsv

  log_numverts = atoi(argv[1]); // In base 2
  numEdges = 16;  // default 16
  fout = stdout;  // default the stdout

  int opt;
  int position = 3;
    while ((opt = getopt(argc, argv, "e:o:s:f")) != -1) {
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
            binary = 1;
            position += 1;
            break;
        default: 
            printError();
        }
    }

  //Start of graph generation timing
  start = get_time();
  make_graph(log_numverts, numEdges << log_numverts, seed, seed, &nedges, &result);
  time_taken = get_time() - start;

  printf("For 2^%d\n", log_numverts);
  printf("\t%f seconds for making graph\n", time_taken);

  if (binary == 0) {
  // print to the file
    start_write = get_time();
    for (int i = 0; i < (numEdges << log_numverts); i++) {
      fprintf(fout, "%lu\t%lu\n", get_v0_from_edge(result + i), get_v1_from_edge(result + i));
    }
    time_taken_write = get_time() - start_write;
    printf("\t%f seconds for writing ascii version\n", time_taken_write);
  } else {
    // need to print binary
    start_write = get_time();
    for (int i = 0; i < (numEdges << log_numverts); i++) {
      uint32_t from = get_v0_from_edge(result + i);
      uint32_t to = get_v1_from_edge(result + i);
      // add the check for not exceed the uint32_t max
      fwrite((const void*) & from,sizeof(uint32_t),1,fout);
      fwrite((const void*) & to,sizeof(uint32_t),1,fout);
    }
    time_taken_write = get_time() - start_write;
    printf("\t%f seconds for writing binary version\n", time_taken_write);
  }
  fclose(fout);

  free(result);
  return 0;
}
