//
// ge_p2_dbl.cc - SUPERCOP ed25519-ref10 ge_p2_dbl.c
//

#include "elligator/ge/ge.h"

namespace elligator {

/*
r = 2 * p
*/

void ge_p2_dbl(ge_p1p1 *r,const ge_p2 *p)
{
  FieldElement t0;

  /* qhasm: XX=X1^2 */
  /* asm 1: fe_sq(>XX=fe#1,<X1=fe#11); */
  /* asm 2: fe_sq(>XX=r->X,<X1=p->X); */
  r->X.sq(p->X);

  /* qhasm: YY=Y1^2 */
  /* asm 1: fe_sq(>YY=fe#3,<Y1=fe#12); */
  /* asm 2: fe_sq(>YY=r->Z,<Y1=p->Y); */
  r->Z.sq(p->Y);

  /* qhasm: B=2*Z1^2 */
  /* asm 1: fe_sq2(>B=fe#4,<Z1=fe#13); */
  /* asm 2: fe_sq2(>B=r->T,<Z1=p->Z); */
  r->T.sq2(p->Z);

  /* qhasm: A=X1+Y1 */
  /* asm 1: fe_add(>A=fe#2,<X1=fe#11,<Y1=fe#12); */
  /* asm 2: fe_add(>A=r->Y,<X1=p->X,<Y1=p->Y); */
  r->Y.add(p->X,p->Y);

  /* qhasm: AA=A^2 */
  /* asm 1: fe_sq(>AA=fe#5,<A=fe#2); */
  /* asm 2: fe_sq(>AA=t0,<A=r->Y); */
  t0.sq(r->Y);

  /* qhasm: Y3=YY+XX */
  /* asm 1: fe_add(>Y3=fe#2,<YY=fe#3,<XX=fe#1); */
  /* asm 2: fe_add(>Y3=r->Y,<YY=r->Z,<XX=r->X); */
  r->Y.add(r->Z,r->X);

  /* qhasm: Z3=YY-XX */
  /* asm 1: fe_sub(>Z3=fe#3,<YY=fe#3,<XX=fe#1); */
  /* asm 2: fe_sub(>Z3=r->Z,<YY=r->Z,<XX=r->X); */
  r->Z.sub(r->Z,r->X);

  /* qhasm: X3=AA-Y3 */
  /* asm 1: fe_sub(>X3=fe#1,<AA=fe#5,<Y3=fe#2); */
  /* asm 2: fe_sub(>X3=r->X,<AA=t0,<Y3=r->Y); */
  r->X.sub(t0,r->Y);

  /* qhasm: T3=B-Z3 */
  /* asm 1: fe_sub(>T3=fe#4,<B=fe#4,<Z3=fe#3); */
  /* asm 2: fe_sub(>T3=r->T,<B=r->T,<Z3=r->Z); */
  r->T.sub(r->T,r->Z);
}

} // namespace elligator
