/* Examples/jerasure_02.c
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
#include "jerasure.h"

#define talloc(type, num) (type *) malloc(sizeof(type)*(num))

usage(char *s)
{
  fprintf(stderr, "usage: jerasure_02 r c w - Converts the matrix of jerasure_01 to a bit matrix.\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates jerasure_print_bitmatrix() and jerasure_matrix_to_bitmatrix().\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  int r, c, w, i, n;
  int *matrix;
  int *bitmatrix;

  if (argc != 4) usage(NULL);
  if (sscanf(argv[1], "%d", &r) == 0 || r <= 0) usage("Bad r");
  if (sscanf(argv[2], "%d", &c) == 0 || c <= 0) usage("Bad c");
  if (sscanf(argv[3], "%d", &w) == 0 || w <= 0) usage("Bad w");

  matrix = talloc(int, r*c);

  n = 1;
  for (i = 0; i < r*c; i++) {
    matrix[i] = n;
    n = galois_single_multiply(n, 2, w);
  }

  bitmatrix = jerasure_matrix_to_bitmatrix(c, r, w, matrix);
  jerasure_print_bitmatrix(bitmatrix, r*w, c*w, w);
  return 0;
}

