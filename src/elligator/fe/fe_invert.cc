//
// fe_invert.cc - SUPERCOP ed25519-ref10 fe_invert.c
//

#include "elligator/fe/fe.h"

namespace elligator {

void FieldElement::invert(const FieldElement& z) {
  FieldElement t0;
  FieldElement t1;
  FieldElement t2;
  FieldElement t3;
  int i;

  /* qhasm: z2 = z1^2^1 */
  /* asm 1: fe_sq(>z2=fe#1,<z1=fe#11); for (i = 1;i < 1;++i) fe_sq(>z2=fe#1,>z2=fe#1); */
  /* asm 2: fe_sq(>z2=t0,<z1=z); for (i = 1;i < 1;++i) fe_sq(>z2=t0,>z2=t0); */
  t0.sq(z); for (i = 1;i < 1;++i) t0.sq();

  /* qhasm: z8 = z2^2^2 */
  /* asm 1: fe_sq(>z8=fe#2,<z2=fe#1); for (i = 1;i < 2;++i) fe_sq(>z8=fe#2,>z8=fe#2); */
  /* asm 2: fe_sq(>z8=t1,<z2=t0); for (i = 1;i < 2;++i) fe_sq(>z8=t1,>z8=t1); */
  t1.sq(t0); for (i = 1;i < 2;++i) t1.sq();

  /* qhasm: z9 = z1*z8 */
  /* asm 1: fe_mul(>z9=fe#2,<z1=fe#11,<z8=fe#2); */
  /* asm 2: fe_mul(>z9=t1,<z1=z,<z8=t1); */
  t1.mul(z);

  /* qhasm: z11 = z2*z9 */
  /* asm 1: fe_mul(>z11=fe#1,<z2=fe#1,<z9=fe#2); */
  /* asm 2: fe_mul(>z11=t0,<z2=t0,<z9=t1); */
  t0.mul(t1);

  /* qhasm: z22 = z11^2^1 */
  /* asm 1: fe_sq(>z22=fe#3,<z11=fe#1); for (i = 1;i < 1;++i) fe_sq(>z22=fe#3,>z22=fe#3); */
  /* asm 2: fe_sq(>z22=t2,<z11=t0); for (i = 1;i < 1;++i) fe_sq(>z22=t2,>z22=t2); */
  t2.sq(t0); for (i = 1;i < 1;++i) t2.sq();

  /* qhasm: z_5_0 = z9*z22 */
  /* asm 1: fe_mul(>z_5_0=fe#2,<z9=fe#2,<z22=fe#3); */
  /* asm 2: fe_mul(>z_5_0=t1,<z9=t1,<z22=t2); */
  t1.mul(t2);

  /* qhasm: z_10_5 = z_5_0^2^5 */
  /* asm 1: fe_sq(>z_10_5=fe#3,<z_5_0=fe#2); for (i = 1;i < 5;++i) fe_sq(>z_10_5=fe#3,>z_10_5=fe#3); */
  /* asm 2: fe_sq(>z_10_5=t2,<z_5_0=t1); for (i = 1;i < 5;++i) fe_sq(>z_10_5=t2,>z_10_5=t2); */
  t2.sq(t1); for (i = 1;i < 5;++i) t2.sq(t2);

  /* qhasm: z_10_0 = z_10_5*z_5_0 */
  /* asm 1: fe_mul(>z_10_0=fe#2,<z_10_5=fe#3,<z_5_0=fe#2); */
  /* asm 2: fe_mul(>z_10_0=t1,<z_10_5=t2,<z_5_0=t1); */
  t1.mul(t2);

  /* qhasm: z_20_10 = z_10_0^2^10 */
  /* asm 1: fe_sq(>z_20_10=fe#3,<z_10_0=fe#2); for (i = 1;i < 10;++i) fe_sq(>z_20_10=fe#3,>z_20_10=fe#3); */
  /* asm 2: fe_sq(>z_20_10=t2,<z_10_0=t1); for (i = 1;i < 10;++i) fe_sq(>z_20_10=t2,>z_20_10=t2); */
  t2.sq(t1); for (i = 1;i < 10;++i) t2.sq(t2);

  /* qhasm: z_20_0 = z_20_10*z_10_0 */
  /* asm 1: fe_mul(>z_20_0=fe#3,<z_20_10=fe#3,<z_10_0=fe#2); */
  /* asm 2: fe_mul(>z_20_0=t2,<z_20_10=t2,<z_10_0=t1); */
  t2.mul(t1);

  /* qhasm: z_40_20 = z_20_0^2^20 */
  /* asm 1: fe_sq(>z_40_20=fe#4,<z_20_0=fe#3); for (i = 1;i < 20;++i) fe_sq(>z_40_20=fe#4,>z_40_20=fe#4); */
  /* asm 2: fe_sq(>z_40_20=t3,<z_20_0=t2); for (i = 1;i < 20;++i) fe_sq(>z_40_20=t3,>z_40_20=t3); */
  t3.sq(t2); for (i = 1;i < 20;++i) t3.sq();

  /* qhasm: z_40_0 = z_40_20*z_20_0 */
  /* asm 1: fe_mul(>z_40_0=fe#3,<z_40_20=fe#4,<z_20_0=fe#3); */
  /* asm 2: fe_mul(>z_40_0=t2,<z_40_20=t3,<z_20_0=t2); */
  t2.mul(t3);

  /* qhasm: z_50_10 = z_40_0^2^10 */
  /* asm 1: fe_sq(>z_50_10=fe#3,<z_40_0=fe#3); for (i = 1;i < 10;++i) fe_sq(>z_50_10=fe#3,>z_50_10=fe#3); */
  /* asm 2: fe_sq(>z_50_10=t2,<z_40_0=t2); for (i = 1;i < 10;++i) fe_sq(>z_50_10=t2,>z_50_10=t2); */
  t2.sq(t2); for (i = 1;i < 10;++i) t2.sq(t2);

  /* qhasm: z_50_0 = z_50_10*z_10_0 */
  /* asm 1: fe_mul(>z_50_0=fe#2,<z_50_10=fe#3,<z_10_0=fe#2); */
  /* asm 2: fe_mul(>z_50_0=t1,<z_50_10=t2,<z_10_0=t1); */
  t1.mul(t2);

  /* qhasm: z_100_50 = z_50_0^2^50 */
  /* asm 1: fe_sq(>z_100_50=fe#3,<z_50_0=fe#2); for (i = 1;i < 50;++i) fe_sq(>z_100_50=fe#3,>z_100_50=fe#3); */
  /* asm 2: fe_sq(>z_100_50=t2,<z_50_0=t1); for (i = 1;i < 50;++i) fe_sq(>z_100_50=t2,>z_100_50=t2); */
  t2.sq(t1); for (i = 1;i < 50;++i) t2.sq();

  /* qhasm: z_100_0 = z_100_50*z_50_0 */
  /* asm 1: fe_mul(>z_100_0=fe#3,<z_100_50=fe#3,<z_50_0=fe#2); */
  /* asm 2: fe_mul(>z_100_0=t2,<z_100_50=t2,<z_50_0=t1); */
  t2.mul(t1);

  /* qhasm: z_200_100 = z_100_0^2^100 */
  /* asm 1: fe_sq(>z_200_100=fe#4,<z_100_0=fe#3); for (i = 1;i < 100;++i) fe_sq(>z_200_100=fe#4,>z_200_100=fe#4); */
  /* asm 2: fe_sq(>z_200_100=t3,<z_100_0=t2); for (i = 1;i < 100;++i) fe_sq(>z_200_100=t3,>z_200_100=t3); */
  t3.sq(t2); for (i = 1;i < 100;++i) t3.sq();

  /* qhasm: z_200_0 = z_200_100*z_100_0 */
  /* asm 1: fe_mul(>z_200_0=fe#3,<z_200_100=fe#4,<z_100_0=fe#3); */
  /* asm 2: fe_mul(>z_200_0=t2,<z_200_100=t3,<z_100_0=t2); */
  t2.mul(t3);

  /* qhasm: z_250_50 = z_200_0^2^50 */
  /* asm 1: fe_sq(>z_250_50=fe#3,<z_200_0=fe#3); for (i = 1;i < 50;++i) fe_sq(>z_250_50=fe#3,>z_250_50=fe#3); */
  /* asm 2: fe_sq(>z_250_50=t2,<z_200_0=t2); for (i = 1;i < 50;++i) fe_sq(>z_250_50=t2,>z_250_50=t2); */
  t2.sq(); for (i = 1;i < 50;++i) t2.sq(t2);

  /* qhasm: z_250_0 = z_250_50*z_50_0 */
  /* asm 1: fe_mul(>z_250_0=fe#2,<z_250_50=fe#3,<z_50_0=fe#2); */
  /* asm 2: fe_mul(>z_250_0=t1,<z_250_50=t2,<z_50_0=t1); */
  t1.mul(t2);

  /* qhasm: z_255_5 = z_250_0^2^5 */
  /* asm 1: fe_sq(>z_255_5=fe#2,<z_250_0=fe#2); for (i = 1;i < 5;++i) fe_sq(>z_255_5=fe#2,>z_255_5=fe#2); */
  /* asm 2: fe_sq(>z_255_5=t1,<z_250_0=t1); for (i = 1;i < 5;++i) fe_sq(>z_255_5=t1,>z_255_5=t1); */
  t1.sq(t1); for (i = 1;i < 5;++i) t1.sq();

  /* qhasm: z_255_21 = z_255_5*z11 */
  /* asm 1: fe_mul(>z_255_21=fe#12,<z_255_5=fe#2,<z11=fe#1); */
  /* asm 2: fe_mul(>z_255_21=out,<z_255_5=t1,<z11=t0); */
  mul(t1,t0);
}

} // namespace elligator
