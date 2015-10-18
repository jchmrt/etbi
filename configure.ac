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
