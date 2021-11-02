
#include "parameters.h"
#include "commitment.h"
#include "encryption.h"
#include "helper.h"
#include <NTL/matrix.h>
#include <NTL/ZZ_pE.h>

using namespace NTL;

class ShortStatement {
public:
  Mat<ZZ_pE> A, S, T;
  ShortStatement(){
    A.SetDims(2,4);
    S.SetDims(4,tau);
    T.SetDims(2,tau);
}};

class ShortProof {
public:
  Mat<ZZ_pE> W, C, Z;
  ShortProof(){
    W.SetDims(2,lambda+2);
    C.SetDims(tau,lambda+2);
    Z.SetDims(4,lambda+2);
}};

void CreateProofStatement(ShortStatement &, const ComKey &,
  const Vec<Commitment> &);

void SampleChallengeMatrix(Mat<ZZ_pE> &);

void ProveShortness(ShortProof &, const ShortStatement &);

void VerifyShortness(bool &, const ShortProof &, const ShortStatement &);
