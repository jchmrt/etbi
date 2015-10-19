dnl Copyright 2015 Jochem Raat
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



AC_INIT([etbi], [0.1], [jchmrt@riseup.net])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_PROG_CC
gl_EARLY

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
