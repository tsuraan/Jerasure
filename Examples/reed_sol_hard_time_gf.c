/* *
 * Copyright (c) 2013, James S. Plank and Kevin Greenan
 * All rights reserved.
 *
 * Jerasure - A C/C++ Library for a Variety of Reed-Solomon and RAID-6 Erasure
 * Coding Techniques
 *
 * Revision 2.0: Galois Field backend now links to GF-Complete
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 *  - Neither the name of the University of Tennessee nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY
 * WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gf_complete.h>
#include "jerasure.h"
#include "reed_sol.h"

#define BUFSIZE 4096

int get_gfp_from_argv(gf_t **gfp, int w, int argc, char **argv, int starting)
{
  int mult_type, divide_type, region_type;
  int arg1, arg2, subrg_size, degree;
  uint64_t prim_poly;
  gf_t *base;
  char *crt, *x, *y;

  mult_type = GF_MULT_DEFAULT;
  region_type = GF_REGION_DEFAULT;
  divide_type = GF_DIVIDE_DEFAULT;
  prim_poly = 0;
  base = NULL;
  arg1 = 0;
  arg2 = 0;
  degree = 0;
  while (1) {
    if (argc > starting) {
      if (strcmp(argv[starting], "-m") == 0) {
        starting++;
        if (mult_type != GF_MULT_DEFAULT) {
          if (base != NULL) gf_free(base, 1);
          return 0;
        }
        if (strcmp(argv[starting], "SHIFT") == 0) {
          mult_type = GF_MULT_SHIFT;
          starting++;
        } else if (strcmp(argv[starting], "CARRY_FREE") == 0) {
          mult_type = GF_MULT_CARRY_FREE;
          starting++;
        } else if (strcmp(argv[starting], "GROUP") == 0) {
          mult_type = GF_MULT_GROUP;
          if (argc < starting + 3) {
            return 0;
          }
          if (sscanf(argv[starting+1], "%d", &arg1) == 0 ||
              sscanf(argv[starting+2], "%d", &arg2) == 0) {
            return 0;
          }
          starting += 3;
        } else if (strcmp(argv[starting], "BYTWO_p") == 0) {
          mult_type = GF_MULT_BYTWO_p;
          starting++;
        } else if (strcmp(argv[starting], "BYTWO_b") == 0) {
          mult_type = GF_MULT_BYTWO_b;
          starting++;
        } else if (strcmp(argv[starting], "TABLE") == 0) {
          mult_type = GF_MULT_TABLE;
          starting++;
        } else if (strcmp(argv[starting], "LOG") == 0) {
          mult_type = GF_MULT_LOG_TABLE;
          starting++;
        } else if (strcmp(argv[starting], "LOG_ZERO") == 0) {
          mult_type = GF_MULT_LOG_ZERO;
          starting++;
        } else if (strcmp(argv[starting], "LOG_ZERO_EXT") == 0) {
          mult_type = GF_MULT_LOG_ZERO_EXT;
          starting++;
        } else if (strcmp(argv[starting], "SPLIT") == 0) {
          mult_type = GF_MULT_SPLIT_TABLE;
          if (argc < starting + 3) {
            return 0;
          }
          if (sscanf(argv[starting+1], "%d", &arg1) == 0 ||
              sscanf(argv[starting+2], "%d", &arg2) == 0) {
            return 0;
          }
          starting += 3;
        } else if (strcmp(argv[starting], "COMPOSITE") == 0) {
          mult_type = GF_MULT_COMPOSITE;
          if (argc < starting + 2) { return 0; }
          if (sscanf(argv[starting+1], "%d", &arg1) == 0) {
            return 0;
          }
          starting += 2;
          degree = arg1;
          starting = get_gfp_from_argv(&base, w/degree, argc, argv, starting);
          if (starting == 0) {
            free(base);
            return 0;
          }
        } else {
          if (base != NULL) gf_free(base, 1);
          return 0;
        }
      } else if (strcmp(argv[starting], "-r") == 0) {
        starting++;
        if (strcmp(argv[starting], "DOUBLE") == 0) {
          region_type |= GF_REGION_DOUBLE_TABLE;
          starting++;
        } else if (strcmp(argv[starting], "QUAD") == 0) {
          region_type |= GF_REGION_QUAD_TABLE;
          starting++;
        } else if (strcmp(argv[starting], "LAZY") == 0) {
          region_type |= GF_REGION_LAZY;
          starting++;
        } else if (strcmp(argv[starting], "SSE") == 0) {
          region_type |= GF_REGION_SSE;
          starting++;
        } else if (strcmp(argv[starting], "NOSSE") == 0) {
          region_type |= GF_REGION_NOSSE;
          starting++;
        } else if (strcmp(argv[starting], "CAUCHY") == 0) {
          region_type |= GF_REGION_CAUCHY;
          starting++;
        } else if (strcmp(argv[starting], "ALTMAP") == 0) {
          region_type |= GF_REGION_ALTMAP;
          starting++;
        } else {
          if (base != NULL) gf_free(base, 1);
          return 0;
        }
      } else if (strcmp(argv[starting], "-p") == 0) {
        starting++;
        if (sscanf(argv[starting], "%llx", (long long unsigned int *)(&prim_poly)) == 0) {
          if (base != NULL) gf_free(base, 1);
          return 0;
        }
        starting++;
      } else if (strcmp(argv[starting], "-d") == 0) {
        starting++;
        if (divide_type != GF_DIVIDE_DEFAULT) {
          if (base != NULL) gf_free(base, 1);
          return 0;
        } else if (strcmp(argv[starting], "EUCLID") == 0) {
          divide_type = GF_DIVIDE_EUCLID;
          starting++;
        } else if (strcmp(argv[starting], "MATRIX") == 0) {
          divide_type = GF_DIVIDE_MATRIX;
          starting++;
        } else {
          return 0;
        }
      } else if (strcmp(argv[starting], "-") == 0) {
        if (mult_type == GF_MULT_COMPOSITE) {
          *gfp = galois_init_composite_field(w, region_type, divide_type, degree, base); 
        } else {
          *gfp = galois_init_field(w, mult_type, region_type, divide_type, prim_poly, arg1, arg2);
        }
        starting++;
        break; 
      } else {
        if (base != NULL) gf_free(base, 1);
        return 0;
      }
    }
  }

  return starting;
}

static void *malloc16(int size) {
    void *mem = malloc(size+16+sizeof(void*));
    void **ptr = (void**)((long)(mem+16+sizeof(void*)) & ~(15));
    ptr[-1] = mem;
    return ptr;
}

static void free16(void *ptr) {
    free(((void**)ptr)[-1]);
}

#define talloc(type, num) (type *) malloc16(sizeof(type)*(num))

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
  fprintf(stderr, "usage: reed_sol_hard_test_gf k m w iterations bufsize [additional GF args]- Test and time Reed-Solomon in a particular GF(2^w).\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       w must be 8, 16 or 32.  k+m must be <= 2^w.\n");
  fprintf(stderr, "       See the README for information on the additional GF args.\n");
  fprintf(stderr, "       Set up a Vandermonde-based distribution matrix and encodes k devices of\n");
  fprintf(stderr, "       %d bytes each with it.  Then it decodes.\n", BUFSIZE);
  fprintf(stderr, "       \n");
  fprintf(stderr, "This tests:        jerasure_matrix_encode()\n");
  fprintf(stderr, "                   jerasure_matrix_decode()\n");
  fprintf(stderr, "                   jerasure_print_matrix()\n");
  fprintf(stderr, "                   galois_init_composite_field()\n");
  fprintf(stderr, "                   galois_init_field()\n");
  fprintf(stderr, "                   galois_change_technique()\n");
  fprintf(stderr, "                   reed_sol_vandermonde_coding_matrix()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
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
  int ret = 0;
  
  if (argc < 6) usage(NULL);  
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &m) == 0 || m <= 0) usage("Bad m");
  if (sscanf(argv[3], "%d", &w) == 0 || (w != 8 && w != 16 && w != 32)) usage("Bad w");
  if (sscanf(argv[4], "%d", &iterations) == 0) usage("Bad iterations");
  if (sscanf(argv[5], "%d", &bufsize) == 0) usage("Bad bufsize");
  if (w <= 16 && k + m > (1 << w)) usage("k + m is too big");

  srand48(time(0));

  ret = get_gfp_from_argv(&gf, w, argc, argv, 6);

  if (ret == 0 || gf == NULL) {
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
