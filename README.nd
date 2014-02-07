This is revision 2.0 of Jerasure.  This is pretty much Jerasure 1.2 without the
original Galois Field backend.  Version 2.0 links directly to GF-Complete, which 
is more flexible than the original, and *much* faster, because it leverages SIMD
instructions.
Authors: James S. Plank (University of Tennessee)
         Kevin M. Greenan (Box)

------------------------------------------------------------

External Documentation:

See the file Manual.pdf for the programmer's manual and tutorial.  This manual
is also available at http://web.eecs.utk.edu/~plank/plank/papers/UT-EECS-14-721.html.

See https://bitbucket.org/jimplank/gf-complete for GF-Complete.

NOTE: You must have GF-Complete installed (or compiled) in order to use Jerasure 2.0.

There are two directories of source code:

The src directory contains the jerasure code.
The Examples directory contains the example programs.  

------------------------------------------------------------

The makefile assumes that Examples is a subdirectory of the home directory.

Installing if you are allowed to install GF-Complete on your machine:

1.) Install GF-Complete
2.) ./configure
3.) make
4.) sudo make install 

This will install the library into your machine's lib directory,
the headers into include, and the example programs into bin.

------------------------------------------------------------

Installing if you can compile GF-Complete, but you cannot install it:

1.) Install GF-Complete.  Let's suppose the full path to GF-Complete is
    in the environment variable  GFP
2A.) On Linux, set the environment variable LD_LIBRARY_PATH so that it 
     includes $GFP/src/.libs
2B.) On a mac, set the environment variable DYLD_LIBRARY_PATH so that it
     includes $GFP/src/.libs
2.) ./configure LDFLAGS=-L$GFP/src/.libs/ CPPFLAGS=-I$GFP/include
3.) make

The examples will be in the directory Examples.  The include files will
be in the directory include, and the library will be called libJerasure.a
in the directory src/.libs.

------------------------------------------------------------

As long as GF-Complete is installed, Jerasure 2.0 can be used just as previous
versions.  There is no need to define custom Galois Fields.  Jerasure will 
determine the default field to use, if one is not specified.

If you would like to explore a using a different Galois Field implementation,
please see the manual.
