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

There is no warranty.  agl's implementation doesn't use the correct square
root some of the time, leading to incorrect representative generation.  This
bug is fixed.

If [Google C++ Testing Framework](https://code.google.com/p/googletest/) is
installed on your system "make test" will compile a simple Known Answer Test.

It is the caller's responsibility to randomize the 2 high bits of the
representative, and to mask out said randomness before converting back from
the representative to the public key.

This will look something like:

        // Assuming `repr` holds the representative from ScalarBaseMult...
        uint8_t bits;
        random_bytes(&bits, 1);
        repr[31] |= bits & 0xc0;

        // ... on the other side, mask out the 2 bits, then reverse the map.
        repr[31] &= ~ 0xc0;
        RepresentativeToPublicKey(pub, repr);

If you already pull in Andrew Moon's ed25519-donna, then you should probably
use https://gist.github.com/Yawning/0181098c1119f49b3eb2 instead.

### TODO

 * Someone should use [ctgrind](https://github.com/agl/ctgrind) to make sure
   this is constant time.
 * More tests than "I generated a bunch of values with the go implementation,
   and check that the output matches" would be nice.

