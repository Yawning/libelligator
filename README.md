## libelligator - A C++ Elligator2 implementation
#### Yawning Angel (yawning at torproject dot org)

### What?

A C++ version of ["Elligator: Elliptic-curve points indistinguishable from
uniform random strings"] (http://elligator.cr.yp.to/elligator-20130828.pdf.)
for Curve25519.  It is a straight forward mechanical conversion of the code
authored by agl in the [ed25519/extra25519](https://github.com/agl/ed25519)
package, using the math routines from the SUPERCOP ref10 ed25519 code.

For those of you that are familiar with the packages that inspired this, yes,
this indeed means that we have come full circle, from C to Go to C(++).

C++ was chosen over C primarily because it can be a nicer language, and
polluting the global namespace with all the code taken from SUPERCOP is
extremely rude.

There is no warranty.  As far as I can tell the output matches agl's
implementation, but I may have done something wrong.

If [Google C++ Testing Framework](https://code.google.com/p/googletest/) is
installed on your system "make test" will compile a simple Known Answer Test.

### TODO

 * Someone should use [ctgrind](https://github.com/agl/ctgrind) to make sure
   this is constant time.
 * More tests than "I generated a bunch of values with the go implementation,
   and check that the output matches" would be nice.

