
#include "commitment.h"
#include "encryption.h"

using namespace std;

class LinProof {
public:
  ZZ_pE t1, t2, u, c; Vec<ZZ_pE> z1, z2;
  LinProof(){
    z1.SetLength(3); z2.SetLength(3);
}};

void SampleChallenge(ZZ_pE &);

void ProveLinearRelation(LinProof &, const ComKey &,const Commitment &,
  const Commitment &, const ZZ_pE &, const ZZ_pE &);

void ProveLinearRelations(Vec<LinProof> &,const Vec<Commitment> &, const ComKey, const Commitment, const Vec<Ciphertext>, const Vec<ZZ_pE>);

void VerifyLinearRelation(bool &, const LinProof &, const ComKey &,
  const Vec<ZZ_pE> &, const Vec<ZZ_pE> &, const ZZ_pE &, const ZZ_pE &);

void VerifyLinearRelations(bool &, const Vec<LinProof> &, const ComKey
    &, const Commitment &, const Vec<Commitment> &,
    const Vec<Ciphertext> &, const Vec<ZZ_pE> &);
