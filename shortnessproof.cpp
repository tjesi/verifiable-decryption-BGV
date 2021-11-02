
#include "shortnessproof.h"

void CreateProofStatement(ShortStatement &shortstmt, const ComKey &comKey, const Vec<Commitment> &noiseCom){
  shortstmt.A[0][0] = comKey.B1[0]; shortstmt.A[0][1] = comKey.B1[1];
  shortstmt.A[0][2] = comKey.B1[2]; shortstmt.A[0][3] = ZZ_pE(0);
  shortstmt.A[1][0] = comKey.B2[0]; shortstmt.A[1][1] = comKey.B2[1];
  shortstmt.A[1][2] = comKey.B2[2]; shortstmt.A[1][3] = ZZ_pE(1);

  for (int i = 0; i < tau; i++){
    shortstmt.S[0][i] = noiseCom[i].r[0];
    shortstmt.S[1][i] = noiseCom[i].r[1];
    shortstmt.S[2][i] = noiseCom[i].r[2];
    shortstmt.S[3][i] = noiseCom[i].msg;
    shortstmt.T[0][i] = noiseCom[i].com[0];
    shortstmt.T[1][i] = noiseCom[i].com[1];
}}

void SampleChallengeMatrix(Mat<ZZ_pE> &C){
  for (int i = 0; i < C.NumRows(); i++){
    for (int j = 0; j < C.NumCols(); j++){
      C[i][j] = RandomBnd(2);
}}}

void ProveShortness(ShortProof &proof, const ShortStatement &stmt){
  Mat<ZZ_pE> Y; Y.SetDims(4,lambda+2);
  Mat<ZZ_pE> SC; SC.SetDims(4,lambda+2);
  bool success = false;
  while (!success){
    SampleGaussian(Y[0],Sigma_A); SampleGaussian(Y[1],Sigma_A);
    SampleGaussian(Y[2],Sigma_A); SampleGaussian(Y[3],Sigma_A);
    MatrixMult(proof.W,stmt.A,Y);
    SampleChallengeMatrix(proof.C);
    success = RejectionSampling();}
  MatrixMult(SC,stmt.S,proof.C);
  MatrixAdd(proof.Z,SC,Y);
}

void VerifyShortness(bool &b, const ShortProof &proof,
  const ShortStatement &stmt){
  b = true; Mat<ZZ_pE> AZ,TC, TCW; AZ.SetDims(2,lambda+2);
  TC.SetDims(2,lambda+2); TCW.SetDims(2,lambda+2);
  MatrixMult(AZ,stmt.A,proof.Z);
  MatrixMult(TC,stmt.T,proof.C);
  MatrixAdd(TCW,TC,proof.W);
  if (AZ != TCW){b = false;}
  for (int i=0; i<lambda+2; i++){
    Vec<ZZ_pE> temp; temp.SetLength(4);
    temp[0] = proof.Z[0][i]; temp[1] = proof.Z[1][i];
    temp[2] = proof.Z[2][i]; temp[3] = proof.Z[3][i];
    if (!CheckNorm(temp,Bound_A)){b = false;}}
}
