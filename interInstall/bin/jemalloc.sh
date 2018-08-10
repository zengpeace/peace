#!/bin/sh

prefix=/work/jemalloc_install
exec_prefix=/work/jemalloc_install
libdir=${exec_prefix}/lib

LD_PRELOAD=${libdir}/libjemalloc.so.2
export LD_PRELOAD
exec "$@"
