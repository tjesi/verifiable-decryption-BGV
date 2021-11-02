
#include "commitment.h"

void KeyGenCom(ComKey &comKey){
  comKey.B1[0] = ZZ_pE(1);
  comKey.B1[1] = random_ZZ_pE();
  comKey.B1[2] = random_ZZ_pE();
  comKey.B2[0] = ZZ_pE(0);
  comKey.B2[1] = ZZ_pE(1);
  comKey.B2[2] = random_ZZ_pE();
}

void Commit(Commitment &com, const ComKey &comKey, const ZZ_pE &m){
  SampleBounded(com.r[0],B), SampleBounded(com.r[1],B);
  SampleBounded(com.r[2],B), com.msg = m;
  com.com[0] = com.r[0] + com.r[1]*comKey.B1[1] + com.r[2]*comKey.B1[2];
  com.com[1] = com.r[1] + com.r[2]*comKey.B2[2] + com.msg;}
