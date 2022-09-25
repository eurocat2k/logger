# LIBRARIES
libdir=$(prefix)/DIST_@PACKAGE_VERSION@/lib
lib_LTLIBRARIES=libmylogger.la
# MYLOGGER LIBRARY
libmylogger_la_SOURCES=mylogger.c mylogger.h misc.c misc.h
libmylogger_la_CFLAGS=-Wextra -g3 -O2 -I.
libmylogger_la_distdir=$(prefix)/lib
# DISTRIBUTION DIRECTORY
distdir=$(libdir)