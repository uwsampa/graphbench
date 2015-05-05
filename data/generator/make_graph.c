/* Copyright (C) 2009-2010 The Trustees of Indiana University.             */
/*                                                                         */
/* Use, modification and distribution is subject to the Boost Software     */
/* License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at */
/* http://www.boost.org/LICENSE_1_0.txt)                                   */
/*                                                                         */
/*  Authors: Jeremiah Willcock                                             */
/*           Andrew Lumsdaine                                              */

/* Modified by Xin Yi                                                      */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include <math.h>
#ifdef __MTA__
#include <sys/mta_task.h>
#endif
#ifdef GRAPH_GENERATOR_MPI
#include <mpi.h>
#endif
#ifdef GRAPH_GENERATOR_OMP
#include <omp.h>
#endif

/* Simplified interface to build graphs with scrambled vertices. */
#include "graph_generator.h"
#include "utils.h"

#ifdef GRAPH_GENERATOR_MPI
static void compute_edge_range(int rank, int size, int64_t M, int64_t* start_idx, int64_t* end_idx) {
  int64_t rankc = (int64_t)(rank);
  int64_t sizec = (int64_t)(size);
  *start_idx = rankc * (M / sizec) + (rankc < (M % sizec) ? rankc : (M % sizec));
  *end_idx = (rankc + 1) * (M / sizec) + (rankc + 1 < (M % sizec) ? rankc + 1 : (M % sizec));
}
#endif

#ifndef GRAPH_GENERATOR_MPI
#include <omp.h>
void make_graph(int log_numverts, int64_t M, uint64_t userseed1, uint64_t userseed2, int64_t* nedges_ptr_in, packed_edge** result_ptr_in) {
  /* Add restrict to input pointers. */
  int64_t* restrict nedges_ptr = nedges_ptr_in;
  packed_edge* restrict* restrict result_ptr = result_ptr_in;

  /* Spread the two 64-bit numbers into five nonzero values in the correct
   * range. */
  uint_fast32_t seed[5];
  make_mrg_seed(userseed1, userseed2, seed);

  *nedges_ptr = M;
  packed_edge* edges = (packed_edge*)xmalloc(M * sizeof(packed_edge));
  *result_ptr = edges;

  /* In OpenMP and XMT versions, the inner loop in generate_kronecker_range is
   * parallel.  */
  generate_kronecker_range(seed, log_numverts, 0, M, edges);
}

// Modified part
void produce_graph(int64_t M, packed_edge** result_ptr_in, FILE *fout, int64_t binary) {
  uint32_t element_count = M * 2;
  uint32_t buffer_size = M * 2 * sizeof(uint32_t);
  uint32_t buffer_constant = 1 << 20;

  if (binary == 0) {

  	#ifdef GRAPH_GENERATOR_OMP
  	#pragma omp parallel
  	#endif

  	{
  		char* buff = (char*)xmalloc(buffer_constant);
  		int total_length = 0;

  		#ifdef GRAPH_GENERATOR_OMP
  		#pragma omp for 
  		#endif

			for (int64_t i = 0; i < M; i++) {
				char temp[50];
				int temp_length;
				int check_correctness;

				uint32_t from = get_v0_from_edge(*result_ptr_in + i);
    		uint32_t to = get_v1_from_edge(*result_ptr_in + i);
    		temp_length = snprintf(temp, 50, "%u\t%u\n", from, to);

    		if (temp_length < 0) {
    			fprintf(stderr, "snprintf error\n");
    			exit(1);
    		}

    		if (total_length + temp_length < buffer_constant) {
    			// still enough room available
    			check_correctness = snprintf(&(buff[total_length]), buffer_constant - total_length, "%s", temp);
    			if (check_correctness < 0) {
    				fprintf(stderr, "snprintf error\n");
    				exit(1);
    			}
    			total_length += temp_length;
    		} else {
    			// the buffer is run out of memory
    			#ifdef GRAPH_GENERATOR_OMP
    			#pragma omp critical 
    			#endif
    			{
						check_correctness = fprintf(fout, "%s", buff);
						if (check_correctness < 0) {
							fprintf(stderr, "fprintf error;\n");
							exit(1);
						}
    			}
    			buff[0] = '\0';
    			check_correctness = snprintf(&(buff[0]), buffer_constant, "%s", temp);
    			if (check_correctness < 0) {
						fprintf(stderr, "snprintf error;\n");
						exit(1);
					}
    			total_length = temp_length;
    		}
			}
			#ifdef GRAPH_GENERATOR_OMP
  		#pragma omp critical 
  		#endif
  		{
  			int check_correctness;
				check_correctness = fprintf(fout, "%s", buff);
				if (check_correctness < 0) {
					fprintf(stderr, "fprintf error;\n");
					exit(1);
				}
			}	
  	}
  } else {
	  uint32_t* buff = (uint32_t*)xmalloc(buffer_size);

	  #ifdef GRAPH_GENERATOR_OMP
	  #pragma omp parallel for 
	  #endif
	  for (int64_t i = 0; i < M; i++) {
	    uint32_t from = get_v0_from_edge(*result_ptr_in + i);
	    buff[2 * i] = from;
	    uint32_t to = get_v1_from_edge(*result_ptr_in + i);
	    buff[2 * i + 1] = to;
	  }
	  
	  size_t check_correctness;
	  check_correctness = fwrite(buff, sizeof(uint32_t), element_count, fout);
		if (check_correctness != element_count) {
			fprintf(stderr, "fwrite error;\n");
			exit(1);
		}
	}
}

#endif /* !GRAPH_GENERATOR_MPI */

#ifdef GRAPH_GENERATOR_MPI
void make_graph(int log_numverts, int64_t M, uint64_t userseed1, uint64_t userseed2, int64_t* nedges_ptr, packed_edge** result_ptr) {
  int rank, size;

  /* Spread the two 64-bit numbers into five nonzero values in the correct
   * range. */
  uint_fast32_t seed[5];
  make_mrg_seed(userseed1, userseed2, seed);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  int64_t start_idx, end_idx;
  compute_edge_range(rank, size, M, &start_idx, &end_idx);
  int64_t nedges = end_idx - start_idx;

  packed_edge* local_edges = (packed_edge*)xmalloc((size_t)nedges * sizeof(packed_edge));

  double start = MPI_Wtime();
  generate_kronecker_range(seed, log_numverts, start_idx, end_idx, local_edges);
  double gen_time = MPI_Wtime() - start;

  *result_ptr = local_edges;
  *nedges_ptr = nedges;

  if (rank == 0) {
    fprintf(stdout, "graph_generation:               %f s\n", gen_time);
  }
}
#endif

/* PRNG interface for implementations; takes seed in same format as given by
 * users, and creates a vector of doubles in a reproducible (and
 * random-access) way. */
void make_random_numbers(
       /* in */ int64_t nvalues    /* Number of values to generate */,
       /* in */ uint64_t userseed1 /* Arbitrary 64-bit seed value */,
       /* in */ uint64_t userseed2 /* Arbitrary 64-bit seed value */,
       /* in */ int64_t position   /* Start index in random number stream */,
       /* out */ double* result    /* Returned array of values */
) {
  int64_t i;
  uint_fast32_t seed[5];
  make_mrg_seed(userseed1, userseed2, seed);

  mrg_state st;
  mrg_seed(&st, seed);

  mrg_skip(&st, 2, 0, 2 * (uint64_t)position); /* Each double takes two PRNG outputs */

  for (i = 0; i < nvalues; ++i) {
    result[i] = mrg_get_double_orig(&st);
  }
}
