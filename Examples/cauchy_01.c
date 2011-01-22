/* Examples/cauchy_01.c
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
#include "reed_sol.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

usage(char *s)
{
  fprintf(stderr, "usage: cauchy_01 n w - Prints the number of ones in the bitmatrix representation of n in GF(2^w).\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       It also prints out the bit-matrix and confirms that the number of ones is correct.\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates: cauchy_n_ones()\n");
  fprintf(stderr, "                   jerasure_matrix_to_bitmatrix()\n");
  fprintf(stderr, "                   jerasure_print_bitmatrix()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  int n, i, no, w;
  int *bitmatrix;
  
  if (argc != 3) usage(NULL);
  if (sscanf(argv[1], "%d", &n) == 0 || n <= 0) usage("Bad n");
  if (sscanf(argv[2], "%d", &w) == 0 || w <= 0 || w > 32) usage("Bad w");
  if (w < 30 && n >= (1 << w)) usage("n is too big");

  bitmatrix = jerasure_matrix_to_bitmatrix(1, 1, w, &n);
  no = 0;
  for (i = 0; i < w*w; i++) no += bitmatrix[i];

  printf("# Ones: %d\n", cauchy_n_ones(n, w));
  printf("\n");
  printf("Bitmatrix has %d ones\n", no);
  printf("\n");
  jerasure_print_bitmatrix(bitmatrix, w, w, w);

  return 0;
}
