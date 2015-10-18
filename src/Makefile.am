## Process this file with automake to produce Makefile.in

AM_CFLAGS = -pedantic-errors -Werror -Wall \
           -DEXAMPLE_PATH=\"$(exampledir)\" \
           -I$(top_builddir)/lib -I$(top_srcdir)/lib

bin_PROGRAMS = etbi
etbi_SOURCES = main.c \
               parse.h parse.c \
               optimize.h optimize.c \
               tape.h tape.c \
               eval.h eval.c \
               example.h example.c
