/* jerasure.h - header of kernel procedures
 * James S. Plank

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

#ifndef _JERASURE_H
#define _JERASURE_H

/* This uses procedures from the Galois Field arithmetic library */

#include "galois.h"

/* ------------------------------------------------------------ */
/* In all of the routines below:

   operation = an array of 5 integers:

          0 = operation: 0 for copy, 1 for xor (-1 for end)
          1 = source device (0 - k+m-1)
          2 = source packet (0 - w-1)
          3 = destination device (0 - k+m-1)
          4 = destination packet (0 - w-1)
 */

/* ---------------------------------------------------------------  */
/* Bitmatrices / schedules ---------------------------------------- */

/** This function turns a \f$m \times k\f$ matrix in \f$GF(2^w)\f$ into a \f$wm \times wk\f$ bitmatrix (in \f$GF(2)\f$).
 *  For a detailed explanation see: J. Blomer, M. Kalfane, M. Karpinski, R. Karp, M. Luby and D. Zuckerman:
 *  An XOR-based erasure-resilinet coding scheme. Technical Report TR-95-048, International Computer Science
 *  Institute, August 1995
 *
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @return bit-matrix (int*)
 * @todo example code
 */
int *jerasure_matrix_to_bitmatrix(int k, int m, int w, int *matrix);

/** This function turns a bitmatrix into a schedule using the straightforward algorithm -- just schedule the dot products defined by each row of the matrix.
 * 
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j]
 * @todo return (int**)
 * @todo example code
 * @see jerasure_smart_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * @see jerasure_free_schedule_cache(int k, int m, int ***cache)
 */
int **jerasure_dumb_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix);

/** This function turns a bitmatrix into a schedule, but tries to use previous dot products to calculate new ones. This is the optimization explained in the original Liberation code paper.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j] 
 * @todo return data
 * @todo example code
 * @see jerasure_free_schedule_cache(int k, int m, int ***cache)
 * @see jerasure_dumb_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * 
 */
int **jerasure_smart_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix);

/** This function precalcalculate all the schedule for the given distribution bitmatrix.  M must equal 2.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j]
 * @see jerasure_free_schedule_cache(int k, int m, int ***cache)
 * @todo return data
 * @todo fix
 * @todo example code
 */
int ***jerasure_generate_schedule_cache(int k, int m, int w, int *bitmatrix, int smart);

/** This function frees a schedule that was allocated with jerasure_XXX_bitmatrix_to_schedule.
 * @param schedule Array of schedule operations. If there are m operations, then schedule[m][0] = -1. 
 * @todo example code
 * @see jerasure_dumb_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * @see jerasure_smart_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 */
void jerasure_free_schedule(int **schedule);

/** This function reads a schedule cache that was created with jerasure_generate_schedule_cache.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @see jerasure_generate_schedule_cache(int k, int m, int w, int *bitmatrix, int smart)
 * @see jerasure_smart_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * @todo fix
 * @todo example code
 */
void jerasure_free_schedule_cache(int k, int m, int ***cache);


/* ------------------------------------------------------------ */
/* Encoding - these are all straightforward.  jerasure_matrix_encode only 
   works with w = 8|16|32.  */

/** This function calculates the parity of size bytes of data from each of k regions of memory accessed by data_ptrs. It put the result into the size pointed to by parity_ptr.
 * @param k Number of data devices
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param size Size of memory allocated by data_ptrs in bytes.
 * @todo fix
 * @todo example code
 */
void jerasure_do_parity(int k, char **data_ptrs, char *parity_ptr, int size);

/** This function encodes a matrix in \f$GF(2^w)\f$. \f$w\f$ must be either 8, 16 or 32.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by coding_ptrs in bytes.
 * @see jerasure_matrix_decode(int k, int m, int w, int *matrix, int row_k_ones, int *erasures, char **data_ptrs, char **coding_ptrs, int size)
 * @see void jerasure_bitmatrix_encode(int k, int m, int w, int *bitmatrix, char **data_ptrs, char **coding_ptrs, int size, int packetsize)
 */
void jerasure_matrix_encode(int k, int m, int w, int *matrix,
                          char **data_ptrs, char **coding_ptrs, int size);

/** This function encodes a matrix with a bit-matrix in \f$GF(2^w)\f$. \f$w\f$ my be any number between 1 and 32.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j]
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo example code
 * @see jerasure_matrix_encode(int k, int m, int w, int *matrix, char **data_ptrs, char **coding_ptrs, int size)
 */
void jerasure_bitmatrix_encode(int k, int m, int w, int *bitmatrix,
                            char **data_ptrs, char **coding_ptrs, int size, int packetsize);

/** This function encodes with a previously created schedule.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param schedule Array of schedule operations. If there are m operations, then schedule[m][0] = -1.
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @see jerasure_dumb_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * @see jerasure_smart_bitmatrix_to_schedule(int k, int m, int w, int *bitmatrix)
 * @todo example code
 */
void jerasure_schedule_encode(int k, int m, int w, int **schedule,
                                  char **data_ptrs, char **coding_ptrs, int size, int packetsize);

/* ------------------------------------------------------------ */
/* Decoding. -------------------------------------------------- */

/* These return integers, because the matrix may not be invertible. 
   
   The parameter row_k_ones should be set to 1 if row k of the matrix
   (or rows kw to (k+1)w+1) of th distribution matrix are all ones
   (or all identity matrices).  Then you can improve the performance
   of decoding when there is more than one failure, and the parity
   device didn't fail.  You do it by decoding all but one of the data
   devices, and then decoding the last data device from the data devices
   and the parity device.

 */

/** This function decodes unsing a matrix in \f$GF(2^w)\f$, only when \f$w\f$ = 8|16|32.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @param erasures Array of id's of erased devices. Id's are integers between 0 and k+m-1. Id's 0 to k-1 are id's of data devices. Id's k to k+m-1 are id's of coding devices: Coding device id = id-k. If there are e erasures, erasures[e] = -1.
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by data_ptrs/coding_ptrs in bytes.
 * @return 0 if it worked, -1 if it failed
 * @todo crossreferences
 * @todo example code
 * @see jerasure_bitmatrix_decode(int k, int m, int w, int *bitmatrix, int row_k_ones, int *erasures, char **data_ptrs, char **coding_ptrs, int size, int packetsize)
 * @see jerasure_matrix_encode(int k, int m, int w, int *matrix, char **data_ptrs, char **coding_ptrs, int size)
 */
int jerasure_matrix_decode(int k, int m, int w, 
                          int *matrix, int row_k_ones, int *erasures,
                          char **data_ptrs, char **coding_ptrs, int size);

/** This function 
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j]
 * @param erasures Array of id's of erased devices. Id's are integers between 0 and k+m-1. Id's 0 to k-1 are id's of data devices. Id's k to k+m-1 are id's of coding devices: Coding device id = id-k. If there are e erasures, erasures[e] = -1.
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by coding_ptrs/data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo return data
 * @todo formula
 * @todo fix
 * @todo example code
 * @todo description
 * @todo references
 * @see jerasure_matrix_decode(int k, int m, int w, int *matrix, int row_k_ones, int *erasures, char **data_ptrs, char **coding_ptrs, int size)
 */
int jerasure_bitmatrix_decode(int k, int m, int w, 
                            int *bitmatrix, int row_k_ones, int *erasures,
                            char **data_ptrs, char **coding_ptrs, int size, int packetsize);

/** This function generates the schedule on the fly.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param bitmatrix Array of k*m*w*w integers. It represents an mw by kw matrix. Element i,j is in matrix[i*k*w+j]
 * @param erasures Array of id's of erased devices. Id's are integers between 0 and k+m-1. Id's 0 to k-1 are id's of data devices. Id's k to k+m-1 are id's of coding devices: Coding device id = id-k. If there are e erasures, erasures[e] = -1.
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by coding_ptrs/data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo return data
 * @todo formula
 * @todo fix
 * @todo example code
 */
int jerasure_schedule_decode_lazy(int k, int m, int w, int *bitmatrix, int *erasures,
                            char **data_ptrs, char **coding_ptrs, int size, int packetsize,
                            int smart);
/** This function 
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param erasures Array of id's of erased devices. Id's are integers between 0 and k+m-1. Id's 0 to k-1 are id's of data devices. Id's k to k+m-1 are id's of coding devices: Coding device id = id-k. If there are e erasures, erasures[e] = -1.
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by coding_ptrs/data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo return data
 * @todo fix
 * @todo example code
 */
int jerasure_schedule_decode_cache(int k, int m, int w, int ***scache, int *erasures,
                            char **data_ptrs, char **coding_ptrs, int size, int packetsize);

/** This function makes the k*k decoding matrix (or wk*wk bitmatrix) by taking the rows corresponding to k non-erased devices of the distribution matrix, and then inverting that matrix. You should already have allocated the decoding matrix and dm_ids, which is a vector of k integers.  These will be filled in appropriately.  dm_ids[i] is the id of element i of the survivors vector.  I.e. row i of the decoding matrix times dm_ids equals data drive i. Both of these routines take "erased" instead of "erasures". Erased is a vector with k+m elements, which has 0 or 1 for each device's id, according to whether the device is erased.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @todo fix
 * @todo return data
 * @todo example code
 */
int jerasure_make_decoding_matrix(int k, int m, int w, int *matrix, int *erased, 
                                  int *decoding_matrix, int *dm_ids);

/** This function makes the k*k decoding matrix (or wk*wk bitmatrix) by taking the rows corresponding to k non-erased devices of the distribution matrix, and then inverting that matrix. You should already have allocated the decoding matrix and dm_ids, which is a vector of k integers.  These will be filled in appropriately.  dm_ids[i] is the id of element i of the survivors vector.  I.e. row i of the decoding matrix times dm_ids equals data drive i. Both of these routines take "erased" instead of "erasures". Erased is a vector with k+m elements, which has 0 or 1 for each device's id, according to whether the device is erased.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param w Word size
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @todo fix
 * @todo example code
 */
int jerasure_make_decoding_bitmatrix(int k, int m, int w, int *matrix, int *erased, 
                                  int *decoding_matrix, int *dm_ids);

/** This function allocates and returns erased from erasures.
 * @param k Number of data devices
 * @param m Number of coding devices
 * @param erasures Array of id's of erased devices. Id's are integers between 0 and k+m-1. Id's 0 to k-1 are id's of data devices. Id's k to k+m-1 are id's of coding devices: Coding device id = id-k. If there are e erasures, erasures[e] = -1.
 * @todo return data
 * @todo usage example
 */
int *jerasure_erasures_to_erased(int k, int m, int *erasures);

/* ------------------------------------------------------------ */
/* These perform dot products and schedules. -------------------*/
/*
   src_ids is a matrix of k id's (0 - k-1 for data devices, k - k+m-1
   for coding devices) that identify the source devices.  Dest_id is
   the id of the destination device.

   jerasure_do_scheduled_operations executes the schedule on w*packetsize worth of
   bytes from each device.  ptrs is an array of pointers which should have as many
   elements as the highest referenced device in the schedule.

 */
 
/** This function only works when w = 8|16|32.
 * @param k Number of data devices
 * @param w Word size
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @todo fix
 * @todo sample code
 * @todo description
 */
void jerasure_matrix_dotprod(int k, int w, int *matrix_row,
                          int *src_ids, int dest_id,
                          char **data_ptrs, char **coding_ptrs, int size);

/** This function 
 * @param k Number of data devices
 * @param w Word size
 * @param data_ptrs Array of k pointers to data which is size bytes. Size must be a multiple of sizeof(long). Pointers must also be longword aligned.
 * @param coding_ptrs Array of m pointers to coding data which is size bytes
 * @param size Size of memory allocated by coding_ptrs/data_ptrs in bytes.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo fix
 * @todo example code
 * @todo description
 */
void jerasure_bitmatrix_dotprod(int k, int w, int *bitmatrix_row,
                             int *src_ids, int dest_id,
                             char **data_ptrs, char **coding_ptrs, int size, int packetsize);

/** This function executes the schedule on w*packetsize worth of bytes from each device.  ptrs is an array of pointers which should have as many elements as the highest referenced device in the schedule.
 * @param schedule Array of schedule operations. If there are m operations, then schedule[m][0] = -1.
 * @param packetsize The size of a coding block with bitmatrix coding. When you code with a bitmatrix, you will use w packets of size packetsize.
 * @todo fix
 * @todo example code
*/
void jerasure_do_scheduled_operations(char **ptrs, int **schedule, int packetsize);

/* ------------------------------------------------------------ */
/* Matrix Inversion ------------------------------------------- */
/*
   The two matrix inversion functions work on rows*rows matrices of
   ints.  If a bitmatrix, then each int will just be zero or one.
   Otherwise, they will be elements of gf(2^w).  Obviously, you can
   do bit matrices with crs_invert_matrix() and set w = 1, but
   crs_invert_bitmatrix will be more efficient.

   The two invertible functions return whether a matrix is invertible.
   They are more efficient than the inverstion functions.

   Mat will be destroyed when the matrix inversion or invertible
   testing is done.  Sorry.

   Inv must be allocated by the caller.

   The two invert_matrix functions return 0 on success, and -1 if the
   matrix is uninvertible.

   The two invertible function simply return whether the matrix is
   invertible.  (0 or 1). Mat will be destroyed.
 */

/** This function 
 * @param w Word size
 * @todo fix
 * @todo return data
 * @todo example code
 * @todo description
 */
int jerasure_invert_matrix(int *mat, int *inv, int rows, int w);

/** This function 
 * @todo fix
 * @todo return data
 * @todo description
 */
int jerasure_invert_bitmatrix(int *mat, int *inv, int rows);

/** This function 
 * @param w Word size
 * @todo fix
 * @todo return data
 * @todo description
 */
int jerasure_invertible_matrix(int *mat, int rows, int w);

/** This function 
 * @todo return data
 * @todo fix
 * @todo description
 */
int jerasure_invertible_bitmatrix(int *mat, int rows);

/* ------------------------------------------------------------ */
/* Basic matrix operations -------------------------------------*/
/*
   Each of the print_matrix routines require a w.  In jerasure_print_matrix,
   this is to calculate the field width.  In jerasure_print_bitmatrix, it is
   to put spaces between the bits.

   jerasure_matrix_multiply is a simple matrix multiplier in GF(2^w).  It returns a r1*c2
   matrix, which is the product of the two input matrices.  It allocates
   the product.  Obviously, c1 should equal r2.  However, this is not
   validated by the procedure.  
*/

/** This function 
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @param w Word size
 * @todo fix
 * @todo description
 */
void jerasure_print_matrix(int *matrix, int rows, int cols, int w);

/** This function 
 * @param matrix Array of k*m integers. It represents an m by k matrix. Element i,j is in matrix[i*k+j]
 * @param w Word size
 * @todo fix
 * @todo description
 */
void jerasure_print_bitmatrix(int *matrix, int rows, int cols, int w);

/** This function 
 * @param w Word size
 * @todo fix
 * @todo return data
 * @todo description
 */
int *jerasure_matrix_multiply(int *m1, int *m2, int r1, int c1, int r2, int c2, int w);

/* ------------------------------------------------------------ */
/* Stats ------------------------------------------------------ */

/** This function fills in a vector of three doubles: fill_in[0] is the number of bytes that have been XOR'd, fill_in[1] is the number of bytes that have been copied, fill_in[2] is the number of bytes that have been multiplied by a constant in \f$GF(2^w)\f$. When jerasure_get_stats() is called, it resets its values.
 * @param fill_in vector of three doubles to be filled
 * @code
 * jerasure_get_stats(); // reset all values
 * @endcode
 */
void jerasure_get_stats(double *fill_in);

#endif
