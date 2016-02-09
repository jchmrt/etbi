dnl Copyright 2015, 2016 Jochem Raat
dnl
dnl This file is part of etbi.
dnl
dnl etbi is free software: you can redistribute it and/or modify it under
dnl the terms of the GNU General Public License as published by the Free
dnl Software Foundation, either version 3 of the License, or (at your
dnl option) any later version.
dnl
dnl etbi is distributed in the hope that it will be useful, but WITHOUT
dnl ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
dnl FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
dnl for more details.
dnl
dnl You should have received a copy of the GNU General Public License
dnl along with etbi.  If not, see <http://www.gnu.org/licenses/>.



AC_INIT([etbi], [0.1.2], [jchmrt@riseup.net])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
gl_EARLY

AC_ARG_WITH([readline],
  [AS_HELP_STRING([--with-readline],
    [support fancy command line editing @<:@default=check@:>@])],
  [],
  [with_readline=check])

LIBREADLINE=
AS_IF([test "x$with_readline" != xno],
  [AC_CHECK_LIB([readline], [main],
    [AC_SUBST([LIBREADLINE], ["-lreadline $READLINE_EXTRA"])
     AC_DEFINE([HAVE_LIBREADLINE], [1],
               [Define if you have libreadline])
    for termlib in ncurses curses termcap terminfo termlib ; do
     	AC_CHECK_LIB(${termlib}, tgoto,
		[READLINE_EXTRA="-l${termlib}"; break])
    done
    ],
    [if test "x$with_readline" != xcheck; then
       AC_MSG_FAILURE(
         [--with-readline was given, but test for readline failed])
     fi
    ], )])


READLINE_LIBS="$LIBREADLINE $READLINE_EXTRA"

AC_SUBST(READLINE_LIBS)

AC_SUBST(exampledir, "\$(docdir)/examples")

AC_DEFINE(BF_SUFFIX, ".b")
AH_TEMPLATE([BF_SUFFIX],
            [Define to the suffix of brainfuck source files])

AC_DEFINE(COPYRIGHT_STRING,
          "Copyright 2015 Jochem Raat <jchmrt@riseup.net>")
AH_TEMPLATE([COPYRIGHT_STRING],
            [Define to the copyright notice for this package])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  lib/Makefile
  src/Makefile
  examples/Makefile
  ])

gl_INIT

AC_OUTPUT
