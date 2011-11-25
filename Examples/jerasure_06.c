/* Examples/jerasure_06.c
Jerasure - A C/C++ Library for a Variety of Reed-Solomon and RAID-6 Erasure Coding Techniques

Revision 1.2A
May 24, 2011

James S. Plank
Department of Electrical Engineering and Computer Science
University of Tennessee
Knoxville, TN 37996
plank@cs.utk.edu

Copyright (c) 2011, James S. Plank
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

 - Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

 - Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in
   the documentation and/or other materials provided with the
   distribution.

 - Neither the name of the University of Tennessee nor the names of its
   contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.


 */
    
/*
	revised by S. Simmerman
	2/25/08  
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

void usage(char *s)
{
  fprintf(stderr, "usage: jerasure_06 k m w packetsize\n");
  fprintf(stderr, "Does a simple Cauchy Reed-Solomon coding example in GF(2^w).\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       k+m must be < 2^w.  Packetsize must be a multiple of sizeof(long)\n");
  fprintf(stderr, "       It sets up a Cauchy distribution matrix and encodes k devices of w*packetsize bytes.\n");
  fprintf(stderr, "       After that, it decodes device 0 by using jerasure_make_decoding_bitmatrix()\n");
  fprintf(stderr, "       and jerasure_bitmatrix_dotprod().\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates: jerasure_bitmatrix_encode()\n");
  fprintf(stderr, "                   jerasure_bitmatrix_decode()\n");
  fprintf(stderr, "                   jerasure_print_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_make_decoding_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_bitmatrix_dotprod()\n");
  if (s != NULL) fprintf(stderr, "\n%s\n\n", s);
  exit(1);
}

static void print_data_and_coding(int k, int m, int w, int psize, 
		char **data, char **coding) 
{
	int i, j, x, n, sp;
	long l;

	if(k > m) n = k;
	else n = m;
	sp = psize * 2 + (psize/4) + 12;

	printf("%-*sCoding\n", sp, "Data");
	for(i = 0; i < n; i++) {
		for (j = 0; j < w; j++) {
			if(i < k) {

				if(j==0) printf("D%-2d p%-2d:", i,j);
				else printf("    p%-2d:", j);
				for(x = 0; x < psize; x +=4) {
					memcpy(&l, data[i]+j*psize+x, sizeof(long));
					printf(" %08lx", l);
				}
				printf("    ");
			}
			else printf("%*s", sp, "");
			if(i < m) {
				if(j==0) printf("C%-2d p%-2d:", i,j);
				else printf("    p%-2d:", j);
				for(x = 0; x < psize; x +=4) {
					memcpy(&l, coding[i]+j*psize+x, sizeof(long));
					printf(" %08lx", l);
				}
			}
			printf("\n");
		}
	}

    printf("\n");
}

int main(int argc, char **argv)
{
  long l;
  int k, w, i, j, m, psize, x;
  int *matrix, *bitmatrix;
  char **data, **coding;
  int *erasures, *erased;
  int *decoding_matrix, *dm_ids;
  
  if (argc != 5) usage(NULL);
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &m) == 0 || m <= 0) usage("Bad m");
  if (sscanf(argv[3], "%d", &w) == 0 || w <= 0 || w > 32) usage("Bad w");
  if (w < 30 && (k+m) > (1 << w)) usage("k + m is too big");
  if (sscanf(argv[4], "%d", &psize) == 0 || psize <= 0) usage("Bad packetsize");
  if(psize%sizeof(long) != 0) usage("Packetsize must be multiple of sizeof(long)");

  matrix = talloc(int, m*k);
  for (i = 0; i < m; i++) {
    for (j = 0; j < k; j++) {
      matrix[i*k+j] = galois_single_divide(1, i ^ (m + j), w);
    }
  }
  bitmatrix = jerasure_matrix_to_bitmatrix(k, m, w, matrix);

  printf("Last (m * w) rows of the Binary Distribution Matrix:\n\n");
  jerasure_print_bitmatrix(bitmatrix, w*m, w*k, w);
  printf("\n");

  srand48(0);
  data = talloc(char *, k);
  for (i = 0; i < k; i++) {
    data[i] = talloc(char, psize*w);
    for (j = 0; j < w; j++) {
		for(x = 0; x < psize; x += 4) {
			l = lrand48();
			memcpy(data[i]+j*psize+x, &l, sizeof(long));
		}

    }
  }

  coding = talloc(char *, m);
  for (i = 0; i < m; i++) {
    coding[i] = talloc(char, psize*w);
  }

  jerasure_bitmatrix_encode(k, m, w, bitmatrix, data, coding, w*psize, psize);
  
  printf("Encoding Complete:\n\n");
  print_data_and_coding(k, m, w, psize, data, coding);

  erasures = talloc(int, (m+1));
  erased = talloc(int, (k+m));
  for (i = 0; i < m+k; i++) erased[i] = 0;
  for (i = 0; i < m; ) {
    erasures[i] = lrand48()%(k+m);
    if (erased[erasures[i]] == 0) {
      erased[erasures[i]] = 1;
      bzero((erasures[i] < k) ? data[erasures[i]] : coding[erasures[i]-k], psize*w);
      i++;
    }
  }
  erasures[i] = -1;

  printf("Erased %d random devices:\n\n", m);
  print_data_and_coding(k, m, w, psize, data, coding);
  
  i = jerasure_bitmatrix_decode(k, m, w, bitmatrix, 0, erasures, data, coding, 
		  w*psize, psize);

  printf("State of the system after decoding:\n\n");
  print_data_and_coding(k, m, w, psize, data, coding);
  
  decoding_matrix = talloc(int, k*k*w*w);
  dm_ids = talloc(int, k);

  for (i = 0; i < m; i++) erased[i] = 1;
  for (; i < k+m; i++) erased[i] = 0;

  jerasure_make_decoding_bitmatrix(k, m, w, bitmatrix, erased, decoding_matrix, dm_ids);

  printf("Suppose we erase the first %d devices.  Here is the decoding matrix:\n\n", m);
  jerasure_print_bitmatrix(decoding_matrix, k*w, k*w, w);
  printf("\n");
  printf("And dm_ids:\n\n");
  jerasure_print_matrix(dm_ids, 1, k, w);

  //memcpy(&l, data[0], sizeof(long));
  //printf("\nThe value of device #%d, word 0 is: %lx\n", 0, l);
  bzero(data[0], w*psize);
  jerasure_bitmatrix_dotprod(k, w, decoding_matrix, dm_ids, 0, data, coding, w*psize, psize);

  printf("\nAfter calling jerasure_matrix_dotprod, we calculate the value of device #0, packet 0 to be:\n");
	printf("\nD0  p0 :");
	for(i = 0; i < psize; i +=sizeof(long)) {
		memcpy(&l, data[0]+i, sizeof(long));
		printf(" %08lx", l);
	}
	printf("\n\n");
  //memcpy(&l, data[0], sizeof(long));

  return 0;
}
