# LIBRARIES
libdir=$(prefix)/DIST_@PACKAGE_VERSION@/lib
lib_LTLIBRARIES=libmylogger.la
# MYLOGGER LIBRARY
libmylogger_la_SOURCES=mylogger.c $(top_srcdir)/src/include/mylogger.h misc.c misc.h
libmylogger_la_CFLAGS=-Wextra -g3 -O2 -I. -I/urs/local/include -I../include
libmylogger_la_LDFLAGS=-L/usr/local/lib -lzlog
# libmylogger_la_libexecdir=$(top_srcdir)/libsrc
libmylogger_la_distdir=$(prefix)/lib
# DISTRIBUTION DIRECTORY
distdir=$(libdir)