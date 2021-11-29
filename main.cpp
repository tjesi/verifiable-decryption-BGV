
#include "parameters.h"
#include "encryption.h"
#include "commitment.h"
#include "linearityproof.h"
#include "shortnessproof.h"

class Proof {
public:
  Vec<Commitment> noiseCom;
  Vec<LinProof> linProof;
  ShortProof shortProof;
  ShortStatement shortstmt;
  Proof(){
    noiseCom.SetLength(tau);
    linProof.SetLength(tau);
}};

void PrintTimings(const clock_t begin, const clock_t end){
  double elapsed_secs = double(end - begin)/CLOCKS_PER_SEC;
  cout << "Total time: " <<elapsed_secs << " sec\n";
  cout << "Time / ctx: " <<elapsed_secs/tau << " sec\n";
  cout << "\n";
}

void Initialize(EncKey &encKey, ComKey &comKey, Commitment &keyCom){
  ZZ_p::init(ZZ(q));
  ZZ_pE::init(ZZ_pX(INIT_MONO, N)+1);
  KeyGenEnc(encKey);
  KeyGenCom(comKey);
  Commit(keyCom,comKey,encKey.SKs);}

int main()
{
  // Define variables
  EncKey encKey;
  ComKey comKey;
  Commitment keyCom;
  Statement stmt;
  Proof proof;
  bool bLin, bShort;
  clock_t begin, end;

  // Print number of ciphertexts
  cout << "\n" << "CIPHERTEXTS: " << tau << "\n\n";

  // Initialize keys
  cout << "INITIALIZED" << "\n"; begin = clock();
  Initialize(encKey,comKey,keyCom); end = clock();
  PrintTimings(begin,end);

  // Create tau messages and ciphertexts
  cout << "STATEMENT" << "\n"; begin = clock();
  CreateStatement(stmt,encKey); end = clock();
  PrintTimings(begin,end);

  // Extract the noise d from the decrypted ciphertexts
  cout << "NOISE" << "\n"; begin = clock();
  ExtractNoise(proof.noiseCom,stmt, encKey,comKey);
  end = clock(); PrintTimings(begin,end);

  // Create the proof statement for the proof of shortness
  cout << "PROOFSTATEMENT" << "\n"; begin = clock();
  CreateProofStatement(proof.shortstmt, comKey,proof.noiseCom);
  end = clock(); PrintTimings(begin,end);

  // Compute the amortized proof of shortness
  cout << "SHORTNESSPROOF" << "\n"; begin = clock();
  ProveShortness(proof.shortProof, proof.shortstmt);
  end = clock(); PrintTimings(begin,end);

  // Compute all the proofs of linear relations
  cout << "LINEARPROOFS" << "\n"; begin = clock();
  ProveLinearRelations(proof.linProof,proof.noiseCom,
    comKey,keyCom,stmt.ciphertexts,stmt.messages);
  end = clock(); PrintTimings(begin,end);

  // Verify the proof of shortness
  cout << "VERIFICATION SHORTNESS" << "\n"; begin = clock();
  VerifyShortness(bShort, proof.shortProof, proof.shortstmt);
  end = clock(); PrintTimings(begin,end);

  // Verify the proof of linearity
  cout << "VERIFICATION LINEARITY" << "\n"; begin = clock();
  VerifyLinearRelations(bLin,proof.linProof,comKey,keyCom,
    proof.noiseCom, stmt.ciphertexts, stmt.messages);
  end = clock(); PrintTimings(begin,end);

  // Print accept (1) or reject (0)
  cout << "ACCEPT? " << (bLin && bShort) << "\n";
}
