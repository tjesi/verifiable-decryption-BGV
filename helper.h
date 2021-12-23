
#include "parameters.h"
#include <iostream>
#include <random>
#include <math.h>
#include <NTL/ZZ_pE.h>

using namespace NTL;
using namespace std;

void SampleBounded(ZZ_pE &, const long &);

bool isBounded(const ZZ_pE &, const double &);

void SampleGaussian(Vec<ZZ_pE> &, const double &);

bool CheckNorm(const Vec<ZZ_pE> &, const double &);

void SquareNorm(double &, const ZZ_pE &);

void MatrixMult(Mat<ZZ_pE>&, const Mat<ZZ_pE>&, const Mat<ZZ_pE>&);

void MatrixAdd(Mat<ZZ_pE> &, const Mat<ZZ_pE> &, const Mat<ZZ_pE> &);

void InnerProduct(ZZ_pE &, const Vec<ZZ_pE> &, const Vec<ZZ_pE> &);

vector<double> PolyToVec(const ZZ_pE &);

void RejectionSamplingLinearity (bool &,const Vec<ZZ_pE> &,const Vec<ZZ_pE> &);

void RejectionSamplingShortness(bool &, const Mat<ZZ_pE> &,const Mat<ZZ_pE> &);
