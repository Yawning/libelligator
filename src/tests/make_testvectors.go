// make_testvectors.go - Make testvectors for libelligator.
//
// Written in 2014 by Yawning Angel <yawning at torproject dot org>
//
// To the extent possible under law, the author(s) have dedicated all copyright
// and related and neighboring rights to this software to the public domain
// worldwide. This software is distributed without any warranty.
//
// You should have received a copy of the CC0 Public Domain Dedication along
// with this software. If not, see
// <http://creativecommons.org/publicdomain/zero/1.0/>.

package main

import (
	"crypto/rand"
	"fmt"

	"github.com/agl/ed25519/extra25519"
)

func encodeToCharLiteral(buf []byte) string {
	s := ""
	for i := 0; i < len(buf); i++ {
		s += fmt.Sprintf("0x%x, ", buf[i])
	}
   return s
}

func main() {
	// Generate test vectors.
	fmt.Printf("struct TestVectors {\n")
	fmt.Printf("  bool valid;\n")
	fmt.Printf("  uint8_t pub[32];\n")
	fmt.Printf("  uint8_t repr[32];\n")
	fmt.Printf("  uint8_t priv[32];\n")
	fmt.Printf("};\n")
	fmt.Printf("\n")
    fmt.Printf("const TestVectors vectors[] = {\n")
	for i := 0; i < 10; i++ {
		var pub, repr, priv [32]byte
		_, err := rand.Read(priv[:])
		if err != nil {
			panic(fmt.Sprintf("Failed to create private key: %s", err))
		}
		priv[0] &= 248
		priv[31] &= 127
		priv[31] |= 64

		valid := extra25519.ScalarBaseMult(&pub, &repr, &priv)
		fmt.Printf("  {\n")
		fmt.Printf("    .valid = %t,\n", valid)
		fmt.Printf("    .pub = { %s },\n", encodeToCharLiteral(pub[:]))
		fmt.Printf("    .repr = { %s },\n", encodeToCharLiteral(repr[:]))
		fmt.Printf("    .priv = { %s }\n", encodeToCharLiteral(priv[:]))
		fmt.Printf("  },\n")
	}
    fmt.Printf("};\n")
}
