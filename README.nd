This is revision 2.0 of Jerasure.  This is pretty much Jerasure 1.2 without the
original Galois Field backend.  Version 2.0 links directly to GF-Complete, which 
is more flexible than the original, and *much* faster, because it leverages SIMD
instructions.

Authors: James S. Plank (University of Tennessee)
         Kevin M. Greenan (Box)

External Documentation:

See the file Manual.pdf for the programmer's manual and tutorial.  This manual
is also available at http://web.eecs.utk.edu/~plank/plank/papers/UT-EECS-14-721.html.

See https://bitbucket.org/jimplank/gf-complete for GF-Complete.

NOTE: You must have GF-Complete installed in order to use Jerasure 2.0.

There are two directories of source code:

The src directory contains the jerasure code.
The Examples directory contains the example programs.  

The makefile assumes that Examples is a subdirectory of the home directory.

Installing:

1.) Install GF-Complete
2.) ./configure
3.) make
4.) sudo make install 

This will install the examples under PREFIX/bin, the library under PREFIX/lib
and the header files under PREFIX/include

Inclusion of GF-Complete:

As long as GF-Complete is installed, Jerasure 2.0 can be used just as previous
versions.  There is no need to define custom Galois Fields.  Jerasure will 
determine the default field to use, if one is not specified.

If you would like to explore a using a different Galois Field implementation,
please see the manual.
