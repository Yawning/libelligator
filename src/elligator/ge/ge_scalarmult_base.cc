//
// ge_scalarmult_base.cc - SUPERCOP ed25519-ref10 ge_scalarmult_base.c
//

#include "elligator/ge/ge.h"

namespace elligator {

static unsigned char equal(signed char b,signed char c)
{
  unsigned char ub = b;
  unsigned char uc = c;
  unsigned char x = ub ^ uc; /* 0: yes; 1..255: no */
  crypto_uint32 y = x; /* 0: yes; 1..255: no */
  y -= 1; /* 4294967295: yes; 0..254: no */
  y >>= 31; /* 1: yes; 0: no */
  return y;
}

static unsigned char negative(signed char b)
{
  unsigned long long x = b; /* 18446744073709551361..18446744073709551615: yes; 0..255: no */
  x >>= 63; /* 1: yes; 0: no */
  return x;
}

static void cmov(ge_precomp *t,ge_precomp *u,unsigned char b)
{
  t->yplusx.cmov(u->yplusx,b);
  t->yminusx.cmov(u->yminusx,b);
  t->xy2d.cmov(u->xy2d,b);
}

/* base[i][j] = (j+1)*256^i*B */
static ge_precomp base[32][8] = {
#include "base.h"
} ;

static void select(ge_precomp *t,int pos,signed char b)
{
  ge_precomp minust;
  unsigned char bnegative = negative(b);
  unsigned char babs = b - (((-bnegative) & b) << 1);

  ge_precomp_0(t);
  cmov(t,&base[pos][0],equal(babs,1));
  cmov(t,&base[pos][1],equal(babs,2));
  cmov(t,&base[pos][2],equal(babs,3));
  cmov(t,&base[pos][3],equal(babs,4));
  cmov(t,&base[pos][4],equal(babs,5));
  cmov(t,&base[pos][5],equal(babs,6));
  cmov(t,&base[pos][6],equal(babs,7));
  cmov(t,&base[pos][7],equal(babs,8));
  minust.yplusx.copy(t->yminusx);
  minust.yminusx.copy(t->yplusx);
  minust.xy2d.neg(t->xy2d);
  cmov(t,&minust,bnegative);
}

/*
h = a * B
where a = a[0]+256*a[1]+...+256^31 a[31]
B is the Ed25519 base point (x,4/5) with x positive.

Preconditions:
  a[31] <= 127
*/

void ge_scalarmult_base(ge_p3 *h,const unsigned char *a)
{
  signed char e[64];
  signed char carry;
  ge_p1p1 r;
  ge_p2 s;
  ge_precomp t;
  int i;

  for (i = 0;i < 32;++i) {
    e[2 * i + 0] = (a[i] >> 0) & 15;
    e[2 * i + 1] = (a[i] >> 4) & 15;
  }
  /* each e[i] is between 0 and 15 */
  /* e[63] is between 0 and 7 */

  carry = 0;
  for (i = 0;i < 63;++i) {
    e[i] += carry;
    carry = e[i] + 8;
    carry >>= 4;
    e[i] -= carry << 4;
  }
  e[63] += carry;
  /* each e[i] is between -8 and 8 */

  ge_p3_0(h);
  for (i = 1;i < 64;i += 2) {
    select(&t,i / 2,e[i]);
    ge_madd(&r,h,&t); ge_p1p1_to_p3(h,&r);
  }

  ge_p3_dbl(&r,h);  ge_p1p1_to_p2(&s,&r);
  ge_p2_dbl(&r,&s); ge_p1p1_to_p2(&s,&r);
  ge_p2_dbl(&r,&s); ge_p1p1_to_p2(&s,&r);
  ge_p2_dbl(&r,&s); ge_p1p1_to_p3(h,&r);

  for (i = 0;i < 64;i += 2) {
    select(&t,i / 2,e[i]);
    ge_madd(&r,h,&t); ge_p1p1_to_p3(h,&r);
  }
}

} // namespace elligator
