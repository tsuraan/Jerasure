CC			= gcc -g
CFLAGS	= -O3
OBJS  	= galois.o jerasure.o reed_sol.o cauchy.o liberation.o

../lib/libJinterface.so: ../lib/libJinterface.so.0
	ln -sf libJinterface.so.0 ../lib/libJinterface.so

../lib/libJinterface.so.0: ../lib $(OBJS)
	$(CC) -shared -Wl,-soname,libJinterface.so.0 \
		-o ../lib/libJinterface.so.0 $(OBJS)

../lib:
	mkdir -p ../lib

clean:
	rm -f ../lib/libJinterface.so* $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $<

galois.o: galois.h
jerasure.o: jerasure.h galois.h
reed_sol.o: jerasure.h galois.h reed_sol.h
cauchy.o: jerasure.h galois.h cauchy.h
liberation.o: jerasure.h galois.h liberation.h

