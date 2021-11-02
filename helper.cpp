
#include "helper.h"

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

bool CheckNorm(const Vec<ZZ_pE> &z, const double &bound){
  for(int j = 0; j < 3; j++){
    long sum = 0; Vec<ZZ_p> v = PolyToVec(z[j]);
    for(int i = 0; i < N; i++){
      long temp = conv<long>(v[i])-(conv<long>(v[i])>q/2)*q;
      sum += pow(temp,2);}
    double norm = sqrt(sum);
    if (norm > bound) {return false;}}
  return true;}

void MatrixMult(Mat<ZZ_pE>& X, const Mat<ZZ_pE>& A, const Mat<ZZ_pE>& B){
  ZZ_pE tmp;
  for (int i = 0; i < A.NumRows(); i++){
    for (int j = 0; j < B.NumCols(); j++){
      tmp = 0;
      for(int k = 0; k < A.NumCols(); k++){
        tmp += A[i][k] * B[k][j];}
      X[i][j] = tmp;
}}}

void MatrixAdd(Mat<ZZ_pE> &X, const Mat<ZZ_pE> &A, const Mat<ZZ_pE> &B){
  for (int i = 0; i < A.NumRows(); i++){
    for (int j = 0; j < A.NumCols(); j++){
      X[i][j] = A[i][j] + B[i][j];
}}}

Vec<ZZ_p> PolyToVec(const ZZ_pE &input){
    Vec<ZZ_p> output; output.SetLength(input.degree());
    ZZ_pX f = conv<ZZ_pX>(input);
    for (int i=0; i<output.length(); i++){output[i] = coeff(f,i);}
  return output;}

bool RejectionSampling(){
  // We are cheating here, returning accept with prob 1/M:
  double u = ((double)rand()/(double)RAND_MAX);
  return u <= double(0.33);
}
