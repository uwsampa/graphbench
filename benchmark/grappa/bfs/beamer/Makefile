
GRAPPA_IMPLICIT_RULES:=on
include $(GRAPPA_PREFIX)/share/Grappa/grappa.mk

VPATH = src:../../common
CPPFLAGS+=-I../../common

bfs_beamer: main.o bfs_beamer.o
bfs_beamer.o: common.hpp verifier.hpp

