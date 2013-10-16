/* Examples/reed_sol_01.c
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
#include <gf_complete.h>
#include "jerasure.h"
#include "reed_sol.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

void
timer_start (double *t)
{
    struct timeval  tv;

    gettimeofday (&tv, NULL);
    *t = (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
}

double
timer_split (const double *t)
{
    struct timeval  tv;
    double  cur_t;

    gettimeofday (&tv, NULL);
    cur_t = (double)tv.tv_sec + (double)tv.tv_usec * 1e-6;
    return (cur_t - *t);
}

usage(char *s)
{
  fprintf(stderr, "usage: reed_sol_test_01 k m w iterations bufsize [additional GF args]- Tests Reed-Solomon in GF(2^w).\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       w must be 8, 16 or 32.  k+m must be <= 2^w.  It sets up a classic\n");
  fprintf(stderr, "       Vandermonde-based distribution matrix and encodes k devices of\n");
  fprintf(stderr, "       <bufsize> bytes each with it.  Then it decodes.\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This tests:        jerasure_matrix_encode()\n");
  fprintf(stderr, "                   jerasure_matrix_decode()\n");
  fprintf(stderr, "                   jerasure_print_matrix()\n");
  fprintf(stderr, "                   reed_sol_vandermonde_coding_matrix()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

gf_t* get_gf(int w, int argc, char **argv, int starting)
{
  gf_t *gf = (gf_t*)malloc(sizeof(gf_t));
  if (create_gf_from_argv(gf, w, argc, argv, starting) == 0) {
    free(gf);
    gf = NULL;
  }
  return gf;
}

static void fill_buffer(unsigned char *buf, int size)
{
  int i;

  buf[0] = (char)(lrand48() % 256);

  for (i=1; i < size; i++) {
    buf[i] = ((buf[i-1] + i) % 256);
  }
}

int main(int argc, char **argv)
{
  long l;
  int k, w, i, j, m, iterations, bufsize;
  int *matrix;
  char **data, **coding, **old_values;
  int *erasures, *erased;
  int *decoding_matrix, *dm_ids;
  double t = 0, total_time = 0;
  gf_t *gf = NULL;
  
  if (argc < 6) usage(NULL);  
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &m) == 0 || m <= 0) usage("Bad m");
  if (sscanf(argv[3], "%d", &w) == 0 || (w != 8 && w != 16 && w != 32)) usage("Bad w");
  if (sscanf(argv[4], "%d", &iterations) == 0) usage("Bad iterations");
  if (sscanf(argv[5], "%d", &bufsize) == 0) usage("Bad bufsize");
  if (w <= 16 && k + m > (1 << w)) usage("k + m is too big");

  srand48(time(0));

  gf = get_gf(w, argc, argv, 6); 

  if (gf == NULL) {
    usage("Invalid arguments given for GF!\n");
  }

  galois_change_technique(gf, w); 

  matrix = reed_sol_vandermonde_coding_matrix(k, m, w);

  printf("Last m rows of the Distribution Matrix:\n\n");
  jerasure_print_matrix(matrix, m, k, w);
  printf("\n");

  data = talloc(char *, k);
  for (i = 0; i < k; i++) {
    data[i] = talloc(char, bufsize);
    fill_buffer(data[i], bufsize);
  }

  coding = talloc(char *, m);
  old_values = talloc(char *, m);
  for (i = 0; i < m; i++) {
    coding[i] = talloc(char, bufsize);
    old_values[i] = talloc(char, bufsize);
  }

  for (i = 0; i < iterations; i++) {
    timer_start(&t);
    jerasure_matrix_encode(k, m, w, matrix, data, coding, bufsize);
    total_time += timer_split(&t);
  }

  fprintf(stderr, "Encode thput for %d iterations: %.2f MB/s (%.2f sec)\n", iterations, (double)(k*iterations*bufsize/1024/1024) / total_time, total_time);
  
  erasures = talloc(int, (m+1));
  erased = talloc(int, (k+m));
  for (i = 0; i < m+k; i++) erased[i] = 0;
  l = 0;
  for (i = 0; i < m; ) {
    erasures[i] = ((unsigned int)lrand48())%(k+m);
    if (erased[erasures[i]] == 0) {
      erased[erasures[i]] = 1;
      memcpy(old_values[i], (erasures[i] < k) ? data[erasures[i]] : coding[erasures[i]-k], bufsize);
      bzero((erasures[i] < k) ? data[erasures[i]] : coding[erasures[i]-k], bufsize);
      i++;
    }
  }
  erasures[i] = -1;

  for (i = 0; i < iterations; i++) {
    timer_start(&t);
    jerasure_matrix_decode(k, m, w, matrix, 1, erasures, data, coding, bufsize);
    total_time += timer_split(&t);
  }
  
  fprintf(stderr, "Decode thput for %d iterations: %.2f MB/s (%.2f sec)\n", iterations, (double)(m*iterations*bufsize/1024/1024) / total_time, total_time);

  for (i = 0; i < m; i++) {
    if (erasures[i] < k) {
      if (memcmp(data[erasures[i]], old_values[i], bufsize)) {
        fprintf(stderr, "Decoding failed for %d!\n", erasures[i]);
        exit(1);
      }
    } else {
      if (memcmp(coding[erasures[i]-k], old_values[i], bufsize)) {
        fprintf(stderr, "Decoding failed for %d!\n", erasures[i]);
        exit(1);
      }
    }
  }
  
  return 0;
}
