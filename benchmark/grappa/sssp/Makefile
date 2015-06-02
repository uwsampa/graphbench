
GRAPPA_IMPLICIT_RULES:=on
include $(GRAPPA_PREFIX)/share/Grappa/grappa.mk

VPATH = src:../common
CPPFLAGS+=-I../common

VARIANTS=sssp_vertex_centric

all: $(VARIANTS)

sssp_vertex_centric: sssp_vertex_centric.o graphlab.o

clean:
	rm -f *.o $(VARIANTS)
