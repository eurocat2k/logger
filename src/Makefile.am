AM_CFLAGS=-O2 -fPIC -Wall -Wextra
bin_PROGRAMS=loggerTest

mydir=$(prefix)/DIST_@PACKAGE_VERSION@
distlibdir=$(mydir)/lib

loggerTest_SOURCES=main.c
loggerTest_CFLAGS=-g3 -I. -I$(top_srcdir) -I/usr/local/include -I../include
loggerTest_LDFLAGS=-lc -lm
# loggerTest_LDADD=$(top_srcdir)/lib/libmylogger.la
loggerTest_LDADD=$(distlibdir)/libmylogger.la
loggerTest_LDFLAGS+=-L/usr/lib -R/usr/lib -lpthread


bindir=$(prefix)/DIST_@PACKAGE_VERSION@/bin
distdir=$(prefix)/DIST_@PACKAGE_VERSION@


#configdir=$(distdir)/etc
#config_DATA=./etc/lrbconv.conf

datadir=$(distdir)
data_DATA=README.md

