/* Copyright (C) 2009-2010 The Trustees of Indiana University.             */
/*                                                                         */
/* Use, modification and distribution is subject to the Boost Software     */
/* License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at */
/* http://www.boost.org/LICENSE_1_0.txt)                                   */
/*                                                                         */
/*  Authors: Jeremiah Willcock                                             */
/*           Andrew Lumsdaine                                              */

/* Modified by Xin Yi                                                      */

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
#include <getopt.h>
#include "make_graph.h"

void printError() {
  fprintf(stderr, "usage: ./generator_omp <# of vertices (log 2 base)> <-e intNumber [optional: average # of edges per vertex, defualt to be 16> <-o outputFileName [optional: default to stdout]> <-s randomSeedInt [optional: default to use the current time]> <-b [optional: default is ascii version, -b for binary version]>\n");
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
  int log_numverts = -1;
  char * filename = "";
  long int numEdges;
  double start, time_taken;
  double start_write, time_taken_write;
  int64_t nedges;
  packed_edge* result;
  int binary = 0; // set default to be not binary, normal tsv

  numEdges = 16;  // default 16
  fout = stdout;  // default the stdout

  int opt;
  while(optind < argc) {
    if ((opt = getopt(argc, argv, "+e:o:s:b")) != -1) {
      switch (opt) {
        case 'e':
            numEdges = atoi(optarg);
            break;
        case 'o':
            filename = optarg;
            fout = fopen(optarg, "wb");
            if (fout == NULL) {
              fprintf(stderr, "%s -- ", optarg);
              perror("fopen for write failed");
              exit(1);
            }
            break;
        case 's':
            seed = atoi(optarg);
            break;
        case 'b':
            binary = 1;
            break;
        default: 
            printError();
            break;
        }
    } else {
      if(argv[optind] == NULL) {
        printError();
      } else {
        log_numverts = atoi(argv[optind]); // In base 2
        optind++;
      }
    }
  }

  if( log_numverts < 0 ) {
    printError();
  }

  /* Start of graph generation timing */
  start = omp_get_wtime();
  make_graph(log_numverts, numEdges << log_numverts, seed, seed, &nedges, &result);
  time_taken = omp_get_wtime() - start;

  /* End of graph generation timing */
  printf("For 2^%d\n", log_numverts);
  printf("\t%f seconds for making graph\n", time_taken);

  start_write = omp_get_wtime();
  produce_graph(numEdges << log_numverts, &result, fout, binary);
  time_taken_write = omp_get_wtime() - start_write;

  if (binary == 0) {
    printf("\t%f seconds for writing ascii version\n", time_taken_write);
  } else {
  	printf("\t%f seconds for writing binary version\n", time_taken_write);
  }

  // used to check if fclose works well
  int check_correctness;
  check_correctness = fclose(fout);
  if (check_correctness == EOF) {
    fprintf(stderr, "%s -- ", filename);
    perror("fclose for failed");
    exit(1);
  }

  return 0;
}
