# Examples/makefile
# James S. Plank
# 
# JERASURE - Library for Erasure Coding
# Copright (C) 2007 James S. Plank
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# 
# James S. Plank
# Department of Computer Science
# University of Tennessee
# Knoxville, TN 37996
# plank@cs.utk.edu

# $Revision: 1.2 $
# $Date: 2008/08/19 17:41:40 $

CC = gcc  
CFLAGS = -g -I$(HOME)/include

ALL =	jerasure_01 \
        jerasure_02 \
        jerasure_03 \
        jerasure_04 \
        jerasure_05 \
        jerasure_06 \
        jerasure_07 \
        jerasure_08 \
        reed_sol_01 \
        reed_sol_02 \
        reed_sol_03 \
        reed_sol_04 \
        cauchy_01 \
        cauchy_02 \
        cauchy_03 \
        cauchy_04 \
        liberation_01 \
		encoder \
		decoder \

all: $(ALL)

clean:
	rm -f core *.o $(ALL) a.out cauchy.h cauchy.c liberation.h liberation.c reed_sol.c reed_sol.h\
              jerasure.c jerasure.h galois.c galois.h

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c $*.c

liberation.h: ../liberation.h
	rm -f liberation.h ; cp ../liberation.h . ; chmod 0444 liberation.h

liberation.c: ../liberation.c
	rm -f liberation.c ; cp ../liberation.c . ; chmod 0444 liberation.c

cauchy.h: ../cauchy.h
	rm -f cauchy.h ; cp ../cauchy.h . ; chmod 0444 cauchy.h

cauchy.c: ../cauchy.c
	rm -f cauchy.c ; cp ../cauchy.c . ; chmod 0444 cauchy.c

reed_sol.h: ../reed_sol.h
	rm -f reed_sol.h ; cp ../reed_sol.h . ; chmod 0444 reed_sol.h

reed_sol.c: ../reed_sol.c
	rm -f reed_sol.c ; cp ../reed_sol.c . ; chmod 0444 reed_sol.c

jerasure.h: ../jerasure.h
	rm -f jerasure.h ; cp ../jerasure.h . ; chmod 0444 jerasure.h

jerasure.c: ../jerasure.c
	rm -f jerasure.c ; cp ../jerasure.c . ; chmod 0444 jerasure.c

galois.h: ../galois.h
	rm -f galois.h ; cp ../galois.h . ; chmod 0444 galois.h

galois.c: ../galois.c
	rm -f galois.c ; cp ../galois.c . ; chmod 0444 galois.c

galois.o: galois.h
jerasure.o: jerasure.h galois.h

jerasure_01.o: galois.h jerasure.h 
jerasure_01: jerasure_01.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_01 jerasure_01.o jerasure.o galois.o

jerasure_02.o: galois.h jerasure.h 
jerasure_02: jerasure_02.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_02 jerasure_02.o jerasure.o galois.o

jerasure_03.o: galois.h jerasure.h 
jerasure_03: jerasure_03.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_03 jerasure_03.o jerasure.o galois.o

jerasure_04.o: galois.h jerasure.h 
jerasure_04: jerasure_04.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_04 jerasure_04.o jerasure.o galois.o

jerasure_05.o: galois.h jerasure.h 
jerasure_05: jerasure_05.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_05 jerasure_05.o jerasure.o galois.o

jerasure_06.o: galois.h jerasure.h 
jerasure_06: jerasure_06.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_06 jerasure_06.o jerasure.o galois.o

jerasure_07.o: galois.h jerasure.h 
jerasure_07: jerasure_07.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_07 jerasure_07.o jerasure.o galois.o

jerasure_08.o: galois.h jerasure.h 
jerasure_08: jerasure_08.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_08 jerasure_08.o jerasure.o galois.o

reed_sol_01.o: galois.h reed_sol.h jerasure.h
reed_sol_01: reed_sol_01.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_01 reed_sol_01.o reed_sol.o jerasure.o galois.o

reed_sol_02.o: galois.h reed_sol.h jerasure.h
reed_sol_02: reed_sol_02.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_02 reed_sol_02.o reed_sol.o jerasure.o galois.o

reed_sol_03.o: galois.h reed_sol.h jerasure.h
reed_sol_03: reed_sol_03.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_03 reed_sol_03.o reed_sol.o jerasure.o galois.o

reed_sol_04.o: galois.h reed_sol.h jerasure.h
reed_sol_04: reed_sol_04.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_04 reed_sol_04.o reed_sol.o jerasure.o galois.o

cauchy_01.o: galois.h cauchy.h jerasure.h
cauchy_01: cauchy_01.o galois.o jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_01 cauchy_01.o cauchy.o jerasure.o galois.o

cauchy_02.o: galois.h cauchy.h jerasure.h
cauchy_02: cauchy_02.o galois.o jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_02 cauchy_02.o cauchy.o jerasure.o galois.o

cauchy_03.o: galois.h cauchy.h jerasure.h
cauchy_03: cauchy_03.o galois.o jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_03 cauchy_03.o cauchy.o jerasure.o galois.o

cauchy_04.o: galois.h cauchy.h jerasure.h
cauchy_04: cauchy_04.o galois.o jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_04 cauchy_04.o cauchy.o jerasure.o galois.o

liberation_01.o: galois.h liberation.h jerasure.h
liberation_01: liberation_01.o galois.o jerasure.o liberation.o
	$(CC) $(CFLAGS) -o liberation_01 liberation_01.o liberation.o jerasure.o galois.o

encoder.o: galois.h liberation.h jerasure.h reed_sol.h cauchy.h
encoder: encoder.o galois.o jerasure.o liberation.o reed_sol.o cauchy.o
	$(CC) $(CFLAGS) -o encoder encoder.o liberation.o jerasure.o galois.o reed_sol.o cauchy.o

decoder.o: galois.h liberation.h jerasure.h reed_sol.h cauchy.h
decoder: decoder.o galois.o jerasure.o liberation.o reed_sol.o cauchy.o
	$(CC) $(CFLAGS) -o decoder decoder.o liberation.o jerasure.o galois.o reed_sol.o cauchy.o
