/* Examples/jerasure_08.c
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
  fprintf(stderr, "usage: jerasure_08 k w - Example schedule cache usage with RAID-6\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       m=2.  k+m must be <= 2^w.  It sets up a RAID-6 distribution matrix and encodes\n");
  fprintf(stderr, "       k sets of w*%zu bytes. It creates a schedule cache for decoding.\n", sizeof(long));
  fprintf(stderr, "       It demonstrates using the schedule cache for both encoding and decoding.\n");
  fprintf(stderr, "       Then it demonstrates using jerasure_do_parity() to re-encode the first.\n");
  fprintf(stderr, "       coding device\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates: jerasure_generate_schedule_cache()\n");
  fprintf(stderr, "                   jerasure_smart_bitmatrix_to_schedule()\n");
  fprintf(stderr, "                   jerasure_schedule_encode()\n");
  fprintf(stderr, "                   jerasure_schedule_decode_cache()\n");
  fprintf(stderr, "                   jerasure_free_schedule()\n");
  fprintf(stderr, "                   jerasure_free_schedule_cache()\n");
  fprintf(stderr, "                   jerasure_get_stats()\n");
  fprintf(stderr, "                   jerasure_do_parity()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
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
  int k, w, i, j, m;
  int *matrix, *bitmatrix;
  char **data, **coding;
  int **smart, ***cache;
  int *erasures, *erased;
  double stats[3];
  
  if (argc != 3) usage(NULL);
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &w) == 0 || w <= 0 || w > 32) usage("Bad m");
  m = 2;
  if (w < 30 && (k+m) > (1 << w)) usage("k + m is too big");

  matrix = talloc(int, m*k);
  for (j = 0; j < k; j++) matrix[j] = 1;
  i = 1;
  for (j = 0; j < k; j++) {
    matrix[k+j] = i;
    i = galois_single_multiply(i, 2, w);
  }
  bitmatrix = jerasure_matrix_to_bitmatrix(k, m, w, matrix);

  smart = jerasure_smart_bitmatrix_to_schedule(k, m, w, bitmatrix);
  cache = jerasure_generate_schedule_cache(k, m, w, bitmatrix, 1);

  srand48(0);
  data = talloc(char *, k);
  for (i = 0; i < k; i++) {
    data[i] = talloc(char, sizeof(long)*w);
    for (j = 0; j < w; j++) {
      l = lrand48();
      memcpy(data[i]+j*sizeof(long), &l, sizeof(long));
    }
  }

  coding = talloc(char *, m);
  for (i = 0; i < m; i++) {
    coding[i] = talloc(char, sizeof(long)*w);
  }

  jerasure_schedule_encode(k, m, w, smart, data, coding, w*sizeof(long), sizeof(long));
  jerasure_get_stats(stats);
  printf("Encoding Complete: - %.0lf XOR'd bytes\n\n", stats[0]);
  print_data_and_coding(k, m, w, sizeof(long), data, coding);

  erasures = talloc(int, (m+1));
  erasures[0] = k;
  erasures[1] = k+1;
  erasures[2] = -1;
  for (j = 0; j < m; j++) bzero(coding[j], sizeof(long)*w);

  jerasure_schedule_decode_cache(k, m, w, cache, erasures, data, coding, w*sizeof(long), sizeof(long));
  jerasure_get_stats(stats);
  printf("Encoding Using the Schedule Cache: - %.0lf XOR'd bytes\n\n", stats[0]);
  print_data_and_coding(k, m, w, sizeof(long), data, coding);

  erased = talloc(int, (k+m));
  for (i = 0; i < m+k; i++) erased[i] = 0;
  for (i = 0; i < m; ) {
    erasures[i] = lrand48()%(k+m);
    if (erased[erasures[i]] == 0) {
      erased[erasures[i]] = 1;
      bzero((erasures[i] < k) ? data[erasures[i]] : coding[erasures[i]-k], sizeof(long)*w);
      i++;
    }
  }
  erasures[i] = -1;

  printf("Erased %d random devices:\n\n", m);
  print_data_and_coding(k, m, w, sizeof(long), data, coding);
  
  jerasure_schedule_decode_cache(k, m, w, cache, erasures, data, coding, w*sizeof(long), sizeof(long));
  jerasure_get_stats(stats);

  printf("State of the system after decoding: %.0lf XOR'd bytes\n\n", stats[0]);
  print_data_and_coding(k, m, w, sizeof(long), data, coding);
  
  bzero(coding[0], sizeof(long)*w);
  jerasure_do_parity(k, data, coding[0], sizeof(long)*w);
  printf("State of the system after deleting coding device 0 and using\n");
  printf("jerasure_do_parity to re-encode it:\n\n");
  print_data_and_coding(k, m, w, sizeof(long), data, coding);
  
  jerasure_free_schedule(smart);
  jerasure_free_schedule_cache(k, m, cache);
  
  printf("Smart schedule and cache freed\n\n");

  return 0;
}
