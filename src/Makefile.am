# Jerasure AM file

INCLUDES=-I./
AM_CFLAGS = -O3 $(SIMD_FLAGS) -fPIC $(INCLUDES)

lib_LTLIBRARIES = libJerasure.la
libJerasure_la_SOURCES = galois.c jerasure.c reed_sol.c cauchy.c liberation.c
libJerasure_la_LDFLAGS = -version-info 2:0:0
libJerasure_la_LIBADD = -lgf_complete
include_HEADERS = ../include/jerasure.h
