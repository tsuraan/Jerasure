/* Examples/reed_sol_02.c
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
  fprintf(stderr, "usage: reed_sol_02 k m w - Vandermonde matrices in GF(2^w).\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       k+m must be <= 2^w.  This simply prints out the \n");
  fprintf(stderr, "       Vandermonde matrix in GF(2^w), and then the distribution\n");
  fprintf(stderr, "       matrix that is constructed from it.  See [Plank-Ding-05] for\n");
  fprintf(stderr, "       information on how this construction proceeds\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates: reed_sol_extended_vandermonde_matrix()\n");
  fprintf(stderr, "                   reed_sol_big_vandermonde_coding_matrix()\n");
  fprintf(stderr, "                   reed_sol_vandermonde_coding_matrix()\n");
  fprintf(stderr, "                   jerasure_print_matrix()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  long l;
  int k, w, i, j, m;
  int *matrix;
  
  if (argc != 4) usage(NULL);
  if (sscanf(argv[1], "%d", &k) == 0 || k <= 0) usage("Bad k");
  if (sscanf(argv[2], "%d", &m) == 0 || m <= 0) usage("Bad m");
  if (sscanf(argv[3], "%d", &w) == 0 || w <= 0 || w > 32) usage("Bad w");
  if (w <= 30 && k + m > (1 << w)) usage("k + m is too big");

  matrix = reed_sol_extended_vandermonde_matrix(k+m, k, w);
  printf("Extended Vandermonde Matrix:\n\n");
  jerasure_print_matrix(matrix, k+m, k, w);
  printf("\n");

  matrix = reed_sol_big_vandermonde_distribution_matrix(k+m, k, w);
  printf("Vandermonde Distribution Matrix:\n\n");
  jerasure_print_matrix(matrix, k+m, k, w);
  printf("\n");

  matrix = reed_sol_vandermonde_coding_matrix(k, m, w);
  printf("Vandermonde Coding Matrix:\n\n");
  jerasure_print_matrix(matrix, m, k, w);
  printf("\n");

  
  return 0;
}
