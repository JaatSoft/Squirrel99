# $Id: Makefile.gcc,v 1.17 1999/11/22 03:19:24 kaz Exp $
# $Name: kazlib_1_19 $

CC	= gcc
#CFLAGS	= -Wid-clash-15 -Wall -Wmissing-prototypes -ansi -pedantic -g
CFLAGS	= -Wall -Wmissing-prototypes -ansi -pedantic -O2 -DNDEBUG

project: dep tdict tlist thash teh tsfx

tlist: list.c list.h
	$(CC) $(CFLAGS) -DKAZLIB_TEST_MAIN -o tlist list.c

tdict: dict.c dict.h
	$(CC) $(CFLAGS) -DKAZLIB_TEST_MAIN -o tdict dict.c

thash: hash.c hash.h
	$(CC) $(CFLAGS) -DKAZLIB_TEST_MAIN -o thash hash.c

teh: except.c except.h
	$(CC) $(CFLAGS) -DKAZLIB_TEST_MAIN -o teh except.c

tsfx: sfx.c sfx.h except.o hash.o
	$(CC) $(CFLAGS) -DKAZLIB_TEST_MAIN -o tsfx sfx.c except.o hash.o

docs: docs.dvi

docs.dvi: docs.ltx docs.toc docs.ind
	latex docs.ltx

docs.ind: docs.idx docs.ist
	makeindex -s docs.ist docs.idx

docs.toc: docs.ltx
	latex docs.ltx

docs.idx: docs.ltx
	latex docs.ltx

clean:
	-rm tags tlist tdict thash teh tsfx except.o docs.aux docs.log docs.dvi docs.toc docs.idx docs.ind docs.ilg

dep: .depend

.depend: *.h
	gcc -MM *.c > .depend

-include .depend
