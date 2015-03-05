CFLAGS = -std=c99 -Wall -Drestrict=__restrict__ -O3 -DNDEBUG -ffast-math # -g -pg
LDFLAGS = -O3


GENERATOR_SOURCES = graph_generator.c make_graph.c splittable_mrg.c utils.c
GENERATOR_HEADERS = graph_generator.h make_graph.h mod_arith_32bit.h mod_arith_64bit.h mod_arith.h mod_arith_xmt.h splittable_mrg.h utils.h user_settings.h mrg_transitions.c

all: generator_seq generator_omp

generator_omp: generator_omp.c $(GENERATOR_SOURCES) $(GENERATOR_HEADERS)
	gcc -fopenmp $(CFLAGS) -DGRAPH_GENERATOR_OMP $(LDFLAGS) -o generator_omp generator_omp.c $(GENERATOR_SOURCES) -lm

generator_seq: generator_seq.c $(GENERATOR_SOURCES) $(GENERATOR_HEADERS)
	gcc -g $(CFLAGS) -DGRAPH_GENERATOR_SEQ -g -o generator_seq generator_seq.c $(GENERATOR_SOURCES) -lm

clean:
	-rm -f generator_seq
	-rm -f generator_omp
