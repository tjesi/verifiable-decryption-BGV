
#include "encryption.h"

void SampleMessage(ZZ_pE &m){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(p));
  } m = to_ZZ_pE(f);}

void KeyGenEnc(EncKey &encKey){
  encKey.PKa = random_ZZ_pE();
  SampleBounded(encKey.SKs,B), SampleBounded(encKey.SKe,B);
  encKey.PKb = encKey.PKa*encKey.SKs+ZZ_pE(p)*encKey.SKe;}

void Encrypt(Ciphertext &ctx, const EncKey &encKey, const ZZ_pE &m){
  ZZ_pE r,e1,e2;
  SampleBounded(r,B), SampleBounded(e1,B), SampleBounded(e1,B);
  ctx.CTXu = encKey.PKa*r+ZZ_pE(p)*e1, ctx.CTXv = encKey.PKb*r+ZZ_pE(p)*e2+m;}

void RoundModP(ZZ_pE &m){
  ZZ_pX f = conv<ZZ_pX>(m);
  for(int i = 0; i < N; i++){
    ZZ t = conv<ZZ>(coeff(f,i));
    SetCoeff(f,i,((t - (t > q/2)*q) % p + p) % p);
  } m = to_ZZ_pE(f);}

void Decrypt(ZZ_pE &m, const EncKey &encKey, const Ciphertext &ctx){
  m = ctx.CTXv - encKey.SKs*ctx.CTXu, RoundModP(m);}

void ExtractNoise(Vec<Commitment>&noiseCom,const Statement &stmt,
  const EncKey &encKey, const ComKey &comKey){
  for (int j = 0; j < tau; j++){
    ZZ_pE noise = (stmt.ciphertexts[j].CTXv -
    encKey.SKs*stmt.ciphertexts[j].CTXu - stmt.messages[j])/ZZ_p(p);
    Commit(noiseCom[j],comKey,noise);}}

void CreateStatement(Statement &stmt, const EncKey &encKey){
  ZZ_pE m; Ciphertext ctx;
  for (int j = 0; j < tau; j++){
    SampleMessage(m); Encrypt(ctx,encKey,m);
    stmt.messages[j] = m; stmt.ciphertexts[j] = ctx;}}
