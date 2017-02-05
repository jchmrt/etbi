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

TESTS = check_etbi
check_PROGRAMS = check_etbi
check_etbi_SOURCES = check_etbi.c \
	check_tape.c check_tape.h

check_etbi_CFLAGS = $(CHECK_CFLAGS) -pedantic-errors -Werror -Wall
check_etbi_LDADD = $(top_builddir)/src/libetbi.a $(CHECK_LIBS)
