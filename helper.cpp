
#include "helper.h"
#include <math.h>

void SampleBounded(ZZ_pE &r, const long &bound){
  ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
  for(int i = 0; i < N; i++){
    SetCoeff(f,i,RandomBnd(2*bound+1)-bound);
  } r = to_ZZ_pE(f);}

bool isBounded(const ZZ_pE &r, const double &bound){
  ZZ b = ZZ(0);
  ZZ_pX f = conv<ZZ_pX>(r);
  for(int i = 0; i < N; i++){
    ZZ t = conv<ZZ>(coeff(f,i));
    if (t - (t > q/2)*q > b) { b = t; }
  } return b <= ZZ(bound);}

void SampleGaussian(Vec<ZZ_pE> &y, const double &sigma){
  random_device rd{}; mt19937 gen{rd()};
  normal_distribution<> d{0, sigma};
  for(int j = 0; j < y.length(); j++){
    ZZ_pX f = ZZ_pX(INIT_MONO, N-1);
    for(int i = 0; i < N; i++){
      SetCoeff(f,i,round(d(gen)));
    } y[j] = to_ZZ_pE(f);}}

void SquareNorm(double &norm, const ZZ_pE &poly){
  vector<double> v = PolyToVec(poly);
  for(int i = 0; i < N; i++){norm += pow(v[i],2);}}

bool CheckNorm(const Vec<ZZ_pE> &z, const double &bound){
  for(int j = 0; j < 3; j++){
    double norm = 0; SquareNorm(norm,z[j]);
    if (log2(norm) > bound) {return false;}}
  return true;}

void MatrixMult(Mat<ZZ_pE>& X, const Mat<ZZ_pE>& A, const Mat<ZZ_pE>& B){
  for (int i = 0; i < A.NumRows(); i++){
    for (int j = 0; j < B.NumCols(); j++){
      ZZ_pE tmp = ZZ_pE(0);
      for(int k = 0; k < A.NumCols(); k++){
        tmp += A[i][k] * B[k][j];}
      X[i][j] = tmp;}}}

void MatrixAdd(Mat<ZZ_pE> &X, const Mat<ZZ_pE> &A, const Mat<ZZ_pE> &B){
  for (int i = 0; i < A.NumRows(); i++){
    for (int j = 0; j < A.NumCols(); j++){
      X[i][j] = A[i][j] + B[i][j];}}}

vector<double> PolyToVec(const ZZ_pE &input){
    vector<double> output(N);
    ZZ_pX f = conv<ZZ_pX>(input);
    for (int i=0; i<N; i++){
      output[i] = conv<double>(rep(coeff(f,i)));
      if(output[i] > q/2){output[i] -= q;}}
  return output;}

void RejectionSamplingShortness(bool &success,
  const Mat<ZZ_pE> &Z, const Mat<ZZ_pE> &SC){
  double ip = 0, maxnorm = 0;
  for (int j = 0; j < lambda+2; j++){
    double norm = 0; for (int i = 0; i < 4; i++){
      SquareNorm(norm, SC[i][j]);}
    if (norm > maxnorm){maxnorm = norm;}}
  vector<double> zvec(N), scvec(N);
  for (int i = 0; i < 4; i++){for (int j = 0; j < lambda+2; j++){
        zvec = PolyToVec(Z[i][j]); scvec = PolyToVec(SC[i][j]);
        for (int j = 0; j < N; j++){ip += zvec[j]*scvec[j];}}}
  double u = ((double)rand()/(double)RAND_MAX);
  cout << MAInv << "\n";
  success = u < MAInv * exp((-2*ip+maxnorm)/TwoSigmaA2);}

void RejectionSamplingLinearity(bool &success,
  const Vec<ZZ_pE> &z, const Vec<ZZ_pE> & cr){
  double u = ((double)rand()/(double)RAND_MAX);
  double ip = 0, norm = 0; vector<double> zvec(N), rvec(N);
  for (int i = 0; i < 3; i++){SquareNorm(norm,cr[i]);
    zvec = PolyToVec(z[i]); rvec = PolyToVec(cr[i]);
    for (int j = 0; j < N; j++){ip += zvec[j]*rvec[j];}}
  success = u < MLinInv * exp((-2*ip+norm)/TwoSigmaC2);}
