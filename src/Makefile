CC	= gcc
CFLAGS	= -g -O3
OBJS  	= galois.o jerasure.o reed_sol.o cauchy.o liberation.o

all: ../lib/libJerasure.so headers

headers:
	mkdir -p "../include/"
	cp *.h ../include/

../lib/libJerasure.so: ../lib/libJerasure.so.0
	ln -sf libJerasure.so.0 ../lib/libJerasure.so

../lib/libJerasure.so.0: ../lib $(OBJS)
	$(CC) -shared -Wl,-soname,libJerasure.so.0 \
		-o ../lib/libJerasure.so.0 $(OBJS)

../lib:
	mkdir -p ../lib

clean:
	rm -f ../lib/libJerasure.so* $(OBJS) ../include/*

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $<

galois.o: galois.h
jerasure.o: jerasure.h galois.h
reed_sol.o: jerasure.h galois.h reed_sol.h
cauchy.o: jerasure.h galois.h cauchy.h
liberation.o: jerasure.h galois.h liberation.h

.PHONY: all headers
