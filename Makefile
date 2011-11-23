PREFIX=${HOME}/local
BINDIR=${PREFIX}/bin
LIBDIR=${PREFIX}/lib
INCDIR=${PREFIX}/include

all: lib/libJerasure.so
	make -C Examples

clean:
	make -C src clean
	make -C Examples clean
	rm -rf include

install: lib/libJerasure.so
	cp -P lib/libJerasure.so* ${LIBDIR}
	mkdir -p ${INCDIR}/jerasure
	cp include/* ${INCDIR}/jerasure

lib/libJerasure.so:
	make -C src
