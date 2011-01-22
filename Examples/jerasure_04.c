/* Examples/jerasure_04.c
 * James S. Plank

Jerasure - A C/C++ Library for a Variety of Reed-Solomon and RAID-6 Erasure Coding Techniques
Copright (C) 2007 James S. Plank

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.
  
This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
  
James S. Plank
Department of Electrical Engineering and Computer Science
University of Tennessee 
Knoxville, TN 37996
plank@cs.utk.edu
*/

/*
 * $Revision: 1.2 $
 * $Date: 2008/08/19 17:41:40 $
 */
    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

usage(char *s)
{
  fprintf(stderr, "usage: jerasure_04 k w - Performs the analogous bit-matrix operations to jerasure_03.\n\n");
  fprintf(stderr, "       It converts the matrix to a kw*kw bit matrix and does the same operations.\n");
  fprintf(stderr, "       k must be < 2^w.\n");
  fprintf(stderr, "This demonstrates: jerasure_print_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_matrix_to_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_invertible_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_invert_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_matrix_multiply().\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  unsigned int k, w, i, j, n;
  int *matrix;
  int *bitmatrix;
  int *bitmatrix_copy;
  int *inverse;
  int *identity;

  if (argc != 3) usage(NULL);
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &w) == 0 || w <= 0 || w > 31) usage("Bad w");
  if (k >= (1 << w)) usage("K too big");

  matrix = talloc(int, k*k);
  bitmatrix_copy = talloc(int, k*w*k*w);
  inverse = talloc(int, k*w*k*w);

  for (i = 0; i < k; i++) {
    for (j = 0; j < k; j++) {
      n = i ^ ((1 << w)-1-j);
      matrix[i*k+j] = (n == 0) ? 0 : galois_single_divide(1, n, w);
    }
  }
  bitmatrix = jerasure_matrix_to_bitmatrix(k, k, w, matrix);

  printf("The Cauchy Bit-Matrix:\n");
  jerasure_print_bitmatrix(bitmatrix, k*w, k*w, w);
  memcpy(bitmatrix_copy, bitmatrix, sizeof(int)*k*w*k*w);
  i = jerasure_invertible_bitmatrix(bitmatrix_copy, k*w);
  printf("\nInvertible: %s\n", (i == 1) ? "Yes" : "No");
  if (i == 1) {
    printf("\nInverse:\n");
    memcpy(bitmatrix_copy, bitmatrix, sizeof(int)*k*w*k*w);
    i = jerasure_invert_bitmatrix(bitmatrix_copy, inverse, k*w);
    jerasure_print_bitmatrix(inverse, k*w, k*w, w);
    identity = jerasure_matrix_multiply(inverse, bitmatrix, k*w, k*w, k*w, k*w, 2);
    printf("\nInverse times matrix (should be identity):\n");
    jerasure_print_bitmatrix(identity, k*w, k*w, w);
  }
  return 0;
}

