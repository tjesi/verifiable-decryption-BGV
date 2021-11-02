
#include "parameters.h"
#include "sha2.h"
#include <iostream>
#include <random>
#include <NTL/ZZ_pE.h>

using namespace NTL;
using namespace std;

void SampleBounded(ZZ_pE &, const long &);

bool isBounded(const ZZ_pE &, const double &);

void SampleGaussian(Vec<ZZ_pE> &, const double &);

bool CheckNorm(const Vec<ZZ_pE> &, const double &);

void MatrixMult(Mat<ZZ_pE>&, const Mat<ZZ_pE>&, const Mat<ZZ_pE>&);

void MatrixAdd(Mat<ZZ_pE> &, const Mat<ZZ_pE> &, const Mat<ZZ_pE> &);

void InnerProduct(ZZ_pE &, const Vec<ZZ_pE> &, const Vec<ZZ_pE> &);

Vec<ZZ_p> PolyToVec(const ZZ_pE &);

bool RejectionSampling();
