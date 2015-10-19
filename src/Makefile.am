## Copyright 2015 Jochem Raat
##
## This file is part of etbi.
##
## etbi is free software: you can redistribute it and/or modify it under
## the terms of the GNU General Public License as published by the Free
## Software Foundation, either version 3 of the License, or (at your
## option) any later version.
##
## etbi is distributed in the hope that it will be useful, but WITHOUT
## ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
## FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
## for more details.
##
## You should have received a copy of the GNU General Public License
## along with etbi.  If not, see <http://www.gnu.org/licenses/>.

## Process this file with automake to produce Makefile.in

AM_CFLAGS = -pedantic-errors -Werror -Wall \
           -DEXAMPLE_PATH=\"$(exampledir)\" \
           -I$(top_builddir)/lib -I$(top_srcdir)/lib # for gnulib

etbi_LDADD = $(READLINE_LIBS)

bin_PROGRAMS = etbi
etbi_SOURCES = main.c \
               parse.h parse.c \
               optimize.h optimize.c \
               tape.h tape.c \
               eval.h eval.c \
               example.h example.c \
               interactive.h interactive.c
