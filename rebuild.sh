#!/bin/sh
autoreconf -imf && ./configure --prefix=`pwd` && make install clean