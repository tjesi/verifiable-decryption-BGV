
#ifndef HEADER_P
#define HEADER_P

#include <math.h>

const long N           = 2048;
const double q         = pow(2,50) - pow(2,14) + 1;
const long p           = 2;
const long tau         = 2048;
const long lambda      = 128;
const long B           = 1;
const double MLinInv   = 1/sqrt(3);
const double Sigma_A   = 22668973295;
const double Bound_A   = 83;    // # bits * 2
const double Sigma_C   = 61147;
const double Bound_C   = 44.8;  // # bits * 2
const double twosigma2 = 2*Sigma_C*Sigma_C;

#endif
