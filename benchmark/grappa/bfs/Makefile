
GRAPPA_IMPLICIT_RULES:=on
include $(GRAPPA_PREFIX)/share/Grappa/grappa.mk

VPATH = src:../common
CPPFLAGS+=-I../common

VARIANTS=bfs_vertex_centric bfs_beamer

all: $(VARIANTS)

bfs_vertex_centric: bfs_vertex_centric.o graphlab.o

bfs_beamer: bfs_beamer.o
bfs_beamer.o: nativegraph_common.hpp verifier.hpp

bfs_queues: bfs_queues.o
bfs_queues.o: nativegraph_common.hpp verifier.hpp

clean:
	rm -f *.o $(VARIANTS)
