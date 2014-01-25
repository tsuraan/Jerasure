# Jerasure autoconf template

# FIXME - add project url as the last argument
AC_INIT(Jerasure, 2.0)

AC_PREREQ([2.61])

AM_INIT_AUTOMAKE([no-dependencies], [foreign])
LT_INIT # libtool

AC_CONFIG_HEADER(include/config.h)

dnl Needed when reconfiguring with 'autoreconf -i -s'
AC_CONFIG_MACRO_DIR([m4])

dnl Compiling with per-target flags requires AM_PROG_CC_C_O.
AC_PROG_CC

# Check for gf_complete headers
AC_CHECK_HEADERS(gf_complete.h gf_general.h gf_int.h gf_method.h gf_rand.h)

AC_CHECK_LIB([gf_complete], [gf_init_easy], [],
             [
              echo "Error! You need to have gf_complete installed."
              echo "gf_complete is available from http://web.eecs.utk.edu/~plank/plank/papers/CS-13-703.html"
              exit -1
             ])

AX_EXT()

AC_CONFIG_FILES([Makefile Examples/Makefile src/Makefile])
AC_OUTPUT
