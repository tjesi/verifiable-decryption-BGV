
#ifndef HEADER_E
#define HEADER_E

#include <NTL/ZZ_pE.h>
#include "parameters.h"
#include "commitment.h"
#include "helper.h"

using namespace NTL;

class Ciphertext {
public:
  ZZ_pE CTXu, CTXv;
};

class EncKey {
public:
  ZZ_pE PKa, PKb, SKs, SKe;
};

class Statement {
public:
  Vec<ZZ_pE> messages;
  Vec<Ciphertext> ciphertexts;
  Statement(){
    messages.SetLength(tau);
    ciphertexts.SetLength(tau);
}};

void SampleMessage(ZZ_pE &);

void KeyGenEnc(EncKey &);

void Encrypt(Ciphertext &, const EncKey &, const ZZ_pE &);

void RoundModP(ZZ_pE &);

void Decrypt(ZZ_pE &m, const EncKey &, const Ciphertext &);

void ExtractNoise(Vec<Commitment>&,const Statement &,
  const EncKey &, const ComKey &);

void CreateStatement(Statement &, const EncKey &);

#endif
