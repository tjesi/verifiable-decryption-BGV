
#include "linearityproof.h"
#include <algorithm>

void SampleChallenge(ZZ_pE &c){
  vector<int> list(N); iota(list.begin(), list.end(), 0);
  random_shuffle(list.begin(), list.end());
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < 36; i++){
    long r = RandomBnd(2);
    SetCoeff(f,list[i],r + (r-1)*1);
  } c = to_ZZ_pE(f);}

void ProveLinearRelation(LinProof &proof, const ComKey &comKey, const
  Commitment &X1, const Commitment &X2, const ZZ_pE &alpha, const ZZ_pE &beta){
    Vec<ZZ_pE> y1, y2, cr1, cr2; y1.SetLength(3),
    y2.SetLength(3), cr1.SetLength(3), cr2.SetLength(3);
    bool success = false, success1 = false, success2 = false;
    while (!success){
      SampleGaussian(y1,Sigma_C), SampleGaussian(y2,Sigma_C);
      proof.t1 = y1[0] + (y1[1]*comKey.B1[1]) + (y1[2]*comKey.B1[2]);
      proof.t2 = y2[0] + (y2[1]*comKey.B1[1]) + (y2[2]*comKey.B1[2]);
      proof.u = alpha * (y1[1] + y1[2]*comKey.B2[2]) -
        (y2[1] + y2[2]*comKey.B2[2]); SampleChallenge(proof.c);
    for(int j = 0; j < 3; j++){
      cr1[j] = proof.c * X1.r[j]; cr2[j] = proof.c * X2.r[j];
      proof.z1[j] = y1[j] + cr1[j]; proof.z2[j] = y2[j] + cr2[j];}
    RejectionSamplingLinearity(success1, proof.z1, cr1);
    RejectionSamplingLinearity(success2, proof.z2, cr2);
    success = success1 and success2;}
}

void ProveLinearRelations(Vec<LinProof> &linProof, const Vec<Commitment>
  &noiseCom, const ComKey comKey, const Commitment keyCom, const
  Vec<Ciphertext> ciphertexts, const Vec<ZZ_pE> messages){
  for(int j = 0; j < tau; j++){
    ProveLinearRelation(linProof[j], comKey, keyCom, noiseCom[j],
    -ciphertexts[j].CTXu/ZZ_p(p),(ciphertexts[j].CTXv-messages[j])/ZZ_p(p));
}}

void VerifyLinearRelation(bool &b, const LinProof &proof, const ComKey &comKey,
  const Vec<ZZ_pE> &X1, const Vec<ZZ_pE> &X2, const ZZ_pE &alpha, const ZZ_pE
  &beta){b = true;
  if (!CheckNorm(proof.z1,Bound_C) || !CheckNorm(proof.z2,Bound_C)){b = false;}
  if ((proof.z1[0] + proof.z1[1]*comKey.B1[1] + proof.z1[2]*comKey.B1[2])
  != (proof.t1 + proof.c*X1[0])){b = false;}
  if ((proof.z2[0] + proof.z2[1]*comKey.B1[1] + proof.z2[2]*comKey.B1[2])
  != (proof.t2 + proof.c*X2[0])){b = false;}
  if ((alpha*(proof.z1[1] + proof.z1[2]*comKey.B2[2]) - (proof.z2[1] +
    proof.z2[2]*comKey.B2[2])) != ((alpha*X1[1]+beta-X2[1]))*proof.c + proof.u)
    {b = false;}
}

void VerifyLinearRelations(bool &b, const Vec<LinProof> &linProof, const ComKey
  &comKey, const Commitment &keyCom, const Vec<Commitment> &noiseCom,
  const Vec<Ciphertext> &ciphertexts, const Vec<ZZ_pE> &messages){
  bool bTemp; b = true;
  for(int j = 0; j < tau; j++){
    VerifyLinearRelation(bTemp,linProof[j],comKey,keyCom.com, noiseCom[j].com,
    - ciphertexts[j].CTXu/ZZ_p(p), (ciphertexts[j].CTXv -messages[j])/ZZ_p(p));
    b = b && bTemp;
}}
