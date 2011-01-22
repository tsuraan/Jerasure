/* Examples/reed_sol_04.c
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
  fprintf(stderr, "usage: reed_sol_04 w - Shows reed_sol_galois_wXX_region_multby_2\n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "       w must be 8, 16 or 32.  Sets up an array of 4 random words in\n");
  fprintf(stderr, "       GF(2^w) and multiplies them by two.  \n");
  fprintf(stderr, "       \n");
  fprintf(stderr, "This demonstrates: reed_sol_galois_w08_region_multby_2()\n");
  fprintf(stderr, "                   reed_sol_galois_w16_region_multby_2()\n");
  fprintf(stderr, "                   reed_sol_galois_w32_region_multby_2()\n");
  if (s != NULL) fprintf(stderr, "%s\n", s);
  exit(1);
}

int main(int argc, char **argv)
{
  unsigned char *x, *y;
  unsigned short *xs, *ys;
  unsigned int *xi, *yi;
  int *a32, *copy;
  int i;
  int w;
  
  if (argc != 2) usage(NULL);
  if (sscanf(argv[1], "%d", &w) == 0 || (w != 8 && w != 16 && w != 32)) usage("Bad w");

  srand48(time(0));
  a32 = talloc(int, 4);
  copy = talloc(int, 4);
  y = (unsigned char *) a32;
  for (i = 0; i < 4*sizeof(int); i++) y[i] = lrand48()%255;
  memcpy(copy, a32, sizeof(int)*4);

  if (w == 8) {
    x = (unsigned char *) copy;
    y = (unsigned char *) a32;
    reed_sol_galois_w08_region_multby_2((char *) a32, sizeof(int)*4);
    for (i = 0; i < 4*sizeof(int)/sizeof(char); i++) {
       printf("Char %2d: %3u *2 = %3u\n", i, x[i], y[i]);
    }
  } else if (w == 16) {
    xs = (unsigned short *) copy;
    ys = (unsigned short *) a32;
    reed_sol_galois_w16_region_multby_2((char *) a32, sizeof(int)*4);
    for (i = 0; i < 4*sizeof(int)/sizeof(short); i++) {
       printf("Short %2d: %5u *2 = %5u\n", i, xs[i], ys[i]);
    }
  } else if (w == 32) {
    xi = (unsigned int *) copy;
    yi = (unsigned int *) a32;
    reed_sol_galois_w16_region_multby_2((char *) a32, sizeof(int)*4);
    for (i = 0; i < 4*sizeof(int)/sizeof(int); i++) {
       printf("Int %2d: %10u *2 = %10u\n", i, xi[i], yi[i]);
    }
  } 
}
