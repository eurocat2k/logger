#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
# AC_INIT([logger], [1.0], [gabor.zelenak@me.com])
AC_INIT([logger], m4_esyscmd([git tag -l | sort -V | tail -n 1 | tr -d '\n' | tee ./.version]), [gabor.zelenak@me.com])
AC_CONFIG_SRCDIR([src/test/main.c])
AC_CONFIG_HEADERS([src/test/config.h])
AM_INIT_AUTOMAKE
LT_INIT([dlopen])
# Checks for programs.
AC_PROG_CC

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lc':
AC_CHECK_LIB([c], [main])
# FIXME: Replace `main' with a function in `-lm':
AC_CHECK_LIB([m], [main])
# FIXME: Replace `main' with a function in `-lpthread':
AC_CHECK_LIB([pthread], [main])

# Checks for header files.
AC_CHECK_HEADERS([stdio.h stdlib.h stdarg.h string.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_TYPE_SIZE_T

# Checks for library functions.

AC_CONFIG_FILES([
    Makefile
    src/Makefile
    src/include/Makefile
    src/libsrc/Makefile
    src/test/Makefile
])
AC_OUTPUT
