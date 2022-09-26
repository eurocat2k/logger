AUTOMAKE_OPTIONS=foreign
AM_CFLAGS=-O2 -fPIC -Wall -Wextra
bin_PROGRAMS=loggerTest

mydir=$(prefix)/DIST_@PACKAGE_VERSION@
distlibdir=$(mydir)/lib

loggerTest_SOURCES=main.c
loggerTest_CFLAGS=-g3 -I. -I$(top_srcdir) -I/usr/local/include -I../include
loggerTest_LDFLAGS=-lc -lm
# loggerTest_LDADD=$(distlibdir)/libmylogger.la
loggerTest_LDADD=$(distlibdir)/libmylogger.so
loggerTest_LDFLAGS+=-L/usr/lib -R/usr/lib -lpthread
loggerTest_LDFLAGS+=-L/usr/local/lib -R/usr/local/lib -lzlog
loggerTest_LDFLAGS+=-R$(distlibdir)/libmylogger.so

bindir=$(prefix)/DIST_@PACKAGE_VERSION@/bin
distdir=$(prefix)/DIST_@PACKAGE_VERSION@

#configdir=$(distdir)/etc
#config_DATA=./etc/lrbconv.conf

zlogdir=$(bindir)
zlog_DATA=zlog.conf

datadir=$(distdir)
data_DATA=README.md

