# Examples/makefile
# Jerasure - A C/C++ Library for a Variety of Reed-Solomon and RAID-6 Erasure Coding Techniques
# 
# Revision 1.2A
# May 24, 2011
# 
# James S. Plank
# Department of Electrical Engineering and Computer Science
# University of Tennessee
# Knoxville, TN 37996
# plank@cs.utk.edu
# 
# Copyright (c) 2011, James S. Plank
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 
#  - Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 
#  - Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 
#  - Neither the name of the University of Tennessee nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
# A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
# HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
# WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

PREFIX=/usr/local
BINDIR=${PREFIX}/bin
LIBDIR=${PREFIX}/lib
INCDIR=${PREFIX}/include
CC = gcc  
CFLAGS = -O3 -I$(HOME)/include

ALL =	reed_sol_test_01 reed_sol_test_02

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

galois.o ${LIBDIR}/gf_complete.a: galois.h
jerasure.o: jerasure.h galois.h

reed_sol_test_01.o: galois.h reed_sol.h jerasure.h
reed_sol_test_01: reed_sol_test_01.o galois.o ${LIBDIR}/gf_complete.a jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_test_01 reed_sol_test_01.o reed_sol.o jerasure.o galois.o ${LIBDIR}/gf_complete.a

reed_sol_test_02.o: galois.h reed_sol.h jerasure.h
reed_sol_test_02: reed_sol_test_02.o galois.o ${LIBDIR}/gf_complete.a jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_test_02 reed_sol_test_02.o reed_sol.o jerasure.o galois.o ${LIBDIR}/gf_complete.a
