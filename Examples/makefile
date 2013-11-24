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
CFLAGS = -O2 -I$(HOME)/include

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
        reed_sol_test_gf \
        reed_sol_time_gf \
        reed_sol_hard_time_gf \
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

jerasure.o: jerasure.h galois.h

jerasure_01.o: galois.h jerasure.h 
jerasure_01: jerasure_01.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_01 jerasure_01.o jerasure.o galois.o -lgf_complete

jerasure_02.o: galois.h jerasure.h 
jerasure_02: jerasure_02.o galois.o jerasure.o
	$(CC) $(CFLAGS) -o jerasure_02 jerasure_02.o jerasure.o galois.o -lgf_complete

jerasure_03.o: galois.h jerasure.h 
jerasure_03: jerasure_03.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_03 jerasure_03.o jerasure.o galois.o -lgf_complete

jerasure_04.o: galois.h jerasure.h 
jerasure_04: jerasure_04.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_04 jerasure_04.o jerasure.o galois.o -lgf_complete

jerasure_05.o: galois.h jerasure.h 
jerasure_05: jerasure_05.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_05 jerasure_05.o jerasure.o galois.o -lgf_complete

jerasure_06.o: galois.h jerasure.h 
jerasure_06: jerasure_06.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_06 jerasure_06.o jerasure.o galois.o -lgf_complete

jerasure_07.o: galois.h jerasure.h 
jerasure_07: jerasure_07.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_07 jerasure_07.o jerasure.o galois.o -lgf_complete

jerasure_08.o: galois.h jerasure.h 
jerasure_08: jerasure_08.o galois.o  jerasure.o
	$(CC) $(CFLAGS) -o jerasure_08 jerasure_08.o jerasure.o galois.o -lgf_complete

reed_sol_01.o: galois.h reed_sol.h jerasure.h
reed_sol_01: reed_sol_01.o galois.o  jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_01 reed_sol_01.o reed_sol.o jerasure.o galois.o -lgf_complete

reed_sol_02.o: galois.h reed_sol.h jerasure.h
reed_sol_02: reed_sol_02.o galois.o  jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_02 reed_sol_02.o reed_sol.o jerasure.o galois.o -lgf_complete

reed_sol_03.o: galois.h reed_sol.h jerasure.h
reed_sol_03: reed_sol_03.o galois.o  jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_03 reed_sol_03.o reed_sol.o jerasure.o galois.o -lgf_complete

reed_sol_04.o: galois.h reed_sol.h jerasure.h
reed_sol_04: reed_sol_04.o galois.o  jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_04 reed_sol_04.o reed_sol.o jerasure.o galois.o -lgf_complete

cauchy_01.o: galois.h cauchy.h jerasure.h
cauchy_01: cauchy_01.o galois.o  jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_01 cauchy_01.o cauchy.o jerasure.o galois.o -lgf_complete

cauchy_02.o: galois.h cauchy.h jerasure.h
cauchy_02: cauchy_02.o galois.o  jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_02 cauchy_02.o cauchy.o jerasure.o galois.o -lgf_complete

cauchy_03.o: galois.h cauchy.h jerasure.h
cauchy_03: cauchy_03.o galois.o  jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_03 cauchy_03.o cauchy.o jerasure.o galois.o -lgf_complete

cauchy_04.o: galois.h cauchy.h jerasure.h
cauchy_04: cauchy_04.o galois.o  jerasure.o cauchy.o
	$(CC) $(CFLAGS) -o cauchy_04 cauchy_04.o cauchy.o jerasure.o galois.o -lgf_complete

liberation_01.o: galois.h liberation.h jerasure.h
liberation_01: liberation_01.o galois.o  jerasure.o liberation.o
	$(CC) $(CFLAGS) -o liberation_01 liberation_01.o liberation.o jerasure.o galois.o -lgf_complete

encoder.o: galois.h liberation.h jerasure.h reed_sol.h cauchy.h
encoder: encoder.o galois.o  jerasure.o liberation.o reed_sol.o cauchy.o
	$(CC) $(CFLAGS) -o encoder encoder.o liberation.o jerasure.o galois.o  reed_sol.o cauchy.o -lgf_complete

decoder.o: galois.h liberation.h jerasure.h reed_sol.h cauchy.h
decoder: decoder.o galois.o  jerasure.o liberation.o reed_sol.o cauchy.o
	$(CC) $(CFLAGS) -o decoder decoder.o liberation.o jerasure.o galois.o  reed_sol.o cauchy.o -lgf_complete

reed_sol_test_gf.o: galois.h reed_sol.h jerasure.h
reed_sol_test_gf: reed_sol_test_gf.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_test_gf reed_sol_test_gf.o reed_sol.o jerasure.o galois.o -lgf_complete

reed_sol_time_gf.o: galois.h reed_sol.h jerasure.h
reed_sol_time_gf: reed_sol_time_gf.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_time_gf reed_sol_time_gf.o reed_sol.o jerasure.o galois.o -lgf_complete

reed_sol_hard_time_gf.o: galois.h reed_sol.h jerasure.h
reed_sol_hard_time_gf: reed_sol_hard_time_gf.o galois.o jerasure.o reed_sol.o
	$(CC) $(CFLAGS) -o reed_sol_hard_time_gf reed_sol_hard_time_gf.o reed_sol.o jerasure.o galois.o -lgf_complete
