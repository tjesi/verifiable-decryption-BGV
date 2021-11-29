
#ifndef HEADER_C
#define HEADER_C

#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include "helper.h"

using namespace NTL;

class ComKey {
public:
  Vec<ZZ_pE> B1;
  Vec<ZZ_pE> B2;
  ComKey(){
    B1.SetLength(3);
    B2.SetLength(3);
}};

class Commitment {
public:
  Vec<ZZ_pE> com, r;
  ZZ_pE msg;
  Commitment(){
    com.SetLength(2);
    r.SetLength(3);
}};

void KeyGenCom(ComKey &);

void Commit(Commitment &, const ComKey &, const ZZ_pE &);

#endif
