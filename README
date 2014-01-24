This is revision 2.0 of Jerasure.  This is pretty much Jerasure 1.2 without the
original Galois Field backend.  Version 2.0 links directly to GF-Complete, which 
is more flexible than the original, and *much* faster, because it leverages SIMD
instructions.

External Documentation:

See technical report CS-08-627 for a description of the main interfaces (Version 1.2)

See http://web.eecs.utk.edu/~plank/plank/papers/CS-13-703.html for information
on GF-Complete and the tarball needed to install it.

Custom usgae of GF-Complete is explained in this file (see below).

NOTE: You must have GF-Complete installed in order to use Jerasure 2.0.

There are two directories of source code:

The src directory contains the jerasure code.
The Examples directory contains the example programs.  

The makefile assumes that Examples is a subdirectory of the home directory.

Installing:

1.) Install GF-Complete

2.) ./configure

3.) make

4.) make install 

This will install the examples under PREFIX/bin, the library under PREFIX/lib
and the header files under PREFIX/include

See individual source files to determine what the examples do.  

Inclusion of GF-Complete:

As long as GF-Complete is installed, Jerasure 2.0 can be used just as previous
versions.  There is no need to define custom Galois Fields.  Jerasure will 
determine the default field to use, if one is not specified.

If you would like to explore a using a different Galois Field implementation,
you can dynamically set the backend GF for a given word-size (w).

The new galois.c and galois.h export the following functions to be used by applications
for dynamically setting the back-end GF:

1.) galois_change_technique

  Function signature:

    void galois_change_technique(gf_t *gf, int w);

  This is the recommended way for you to change techniques.  

  This function will take a pointer to a Galois field structure and set it as the 
  current backend for all operations in GF(2^w).  Note that you must specify 'w'
  here, since the internal GF structure is mostly opaque to Jerasure.  Be sure to
  change the technique with the correct structure and word-size.

  There are a few ways to get a pointer to a gf_t structure: GF-Complete gives three
  primitives for this -- create_gf_from_argv(), gf_init_easy() and gf_init_hard().
  Please read the documentation on GF-Complete for how these work.  By far, the
  most powerful and easy is create_gf_from_argv(), which parses an argv-style
  string.  Otherwise, the most flexible is gf_init_hard().

  In galois.c/galois.h, we have defined galois_init_field(), which is pretty much
  identical to gf_init_hard(), except it performs memory allocation with malloc(),
  and galois_init_composite_field(), which facilitates creating composite fields.

  These are described below, but once again, we recommend using create_gf_from_argv()
  or gf_init_hard() if you want to change your Galois field.

2.) galois_init_field

  Function signature:

  gf_t* galois_init_field(int w,
                          int mult_type,
                          int region_type,
                          int divide_type,
                          uint64_t prim_poly,
                          int arg1,
                          int arg2);

  This is a helper function that will initialize a Galois field.  See the GF-Complete
  documentation for more info on what the arguments mean.  Here is a brief description
  of the arguments:

  mult_type can be any *one* of the following:
    
    GF_MULT_DEFAULT
    GF_MULT_SHIFT
    GF_MULT_CARRY_FREE
    GF_MULT_GROUP
    GF_MULT_BYTWO_p
    GF_MULT_BYTWO_b
    GF_MULT_TABLE
    GF_MULT_LOG_TABLE
    GF_MULT_LOG_ZERO
    GF_MULT_LOG_ZERO_EXT
    GF_MULT_SPLIT_TABLE

  region_type can be a combination of the following (some combinations will not
  be valid):

    GF_REGION_DEFAULT
    GF_REGION_DOUBLE_TABLE
    GF_REGION_QUAD_TABLE
    GF_REGION_LAZY
    GF_REGION_SSE
    GF_REGION_NOSSE
    GF_REGION_ALTMAP
    GF_REGION_CAUCHY
  
  divide_type can be one of the following:

    GF_DIVIDE_DEFAULT
    GF_DIVIDE_MATRIX
    GF_DIVIDE_EUCLID

  prim_poly is the field-defining primitive polynomial

  arg1 and arg2 are special arguments usually used for defining SPLIT and GROUP
  operations

3.) galois_init_composite_field

  Function signature:

  gf_t* galois_init_composite_field(int w,
                                    int region_type,
                                    int divide_type,
                                    int degree,
                                    gf_t* base_gf);

  This is a helper function designed to make creating Composite fields easier.  All you
  need to do is hand it w, region mult type, divide type, degree and a pointer to a base 
  field.  Note that the base_gf must have degree w/degree in order for this to work.  
  For example, if we create a GF using:

  galois_init_composite_field(32, GF_REGION_DEFAULT, GF_DIVIDE_DEFAULT, 2, base_gf);

  Then base_gf must have w=16. 

For more information on how to change the backing fields for Jerasure, please refer to

  1.) Examples/reed_sol_test_gf.c: Runs basic tests for Reed-Solomon given args
  for a backing GF (uses create_gf_from_argv to get gf_t pointer)

  2.) Examples/reed_sol_time_gf.c: Runs more thorough timing and validation tests
  for a backing GF (uses create_gf_from_argv to get gf_t pointer)

Performance:

There are two performance-based test scripts: time_all_gfs_argv_init.sh and
time_all_gfs_hard_init.sh.  Both scripts run the same tests, but initialize the
underlying GF fields in different ways (*argv* uses reed_sol_time_gf and *hard*
uses reed_sol_hard_time_gf.c).

You can run 'time_all_gfs_argv_init.sh' to time *all* possible GF
implementations on your computer.  This script requires the 'gf_methods'
utility from GF-Complete to be in your PATH.

time_all_gfs_argv_init.sh was run on a MacBook Air and the distilled numbers
are given in ./PERF.txt.  The results are sorted by encoding throughput.  The
format of each entry reflects the arguments given to reed_sol_time_gf.  For example,
the test run of

'Examples/reed_sol_time_gf 12 3 8 128 65536 -m SPLIT 8 4 -r SSE'

is recorded as this in PERF.txt:

_12_3_8_128_65536_-m_SPLIT_8_4_-r_SSE_- 2813.34

